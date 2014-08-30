/*
 ============================================================================
 Name        : getraddr.cpp
 Author      : Kurt Christofferson
 Version     :
 Copyright   : (c) Ubiquity Robotics 2014
 Description : Hello World in C++,
 ============================================================================
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>



#include <iostream>
#include <string>
#include <string.h>

#include <net/if.h>
#include <iwlib.h>
#include <ifaddrs.h>

#include "getraddr.hpp"
#include "WiredInterface.h"

// defines
#define IFT_WIRED 100
#define IFT_WIRELESS 101


//static functions
static int get_interfaces(int, char *, int *, std::string *);
static int get_wired_interface(int, char *, ur::WiredInterface *);
static int get_wireless_interface(int, char *, std::string *);

int main(int argc, char **argv) {
	int sockfd = 0;
	int iftype = 0;
	struct if_nameindex *pInterfaces;
	struct if_nameindex *pFreeInterfacesMem;
	ur::WiredInterface *ifWiredHead = NULL;
	std::string ssidname;
	std::string wirelessaddress("notset");

	pInterfaces = pFreeInterfacesMem = if_nameindex();

	while ((pInterfaces != NULL) && (pInterfaces->if_name != NULL)) {
// (DEBUG)		std::cout << "Interface[" << pInterfaces->if_index << "]: " << pInterfaces->if_name << std::endl;
		if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
			continue;

		/* For now we only need to find wireless interfaces.  Eventually
		 * we will enumerate both wired and wireless, so I will just loop through all
		 * interfaces for now and call a 'no_op()' function for the wired interface */
		get_interfaces(sockfd, pInterfaces->if_name, &iftype, &ssidname);
		if(iftype == IFT_WIRED) {
			get_wired_interface(sockfd, pInterfaces->if_name, ifWiredHead);
		}
		if(iftype == IFT_WIRELESS) {
			get_wireless_interface(sockfd, pInterfaces->if_name, &wirelessaddress);
		}
		close(sockfd);
		++pInterfaces;
	}

	// (DEBUG) See if it worked
	std::cout << "SSID: " << ssidname << std::endl;
	std::cout <<  "ADDR: " << wirelessaddress << std::endl;


	/* Open the serial comm port for the LCD display */

	/* Print the SSID and the IPv4 Address */

	/* cleanup and go away */
		if (pFreeInterfacesMem != NULL)
		if_freenameindex(pFreeInterfacesMem);
	while (ifWiredHead != NULL) {
		ur::WiredInterface *pWiredInterface;
		pWiredInterface = ifWiredHead->GetNext();
		delete ifWiredHead;
		ifWiredHead = pWiredInterface;
	}
	return EXEC_SUCCESS;
}

static int get_interfaces(int sock, char *ifname, int *type, std::string *ssid)
{
	int rval;
	struct wireless_info wless_info;
	struct ifreq ifr;
	struct sockaddr_in *sa;
	unsigned char ip[4];
	char a[16];

	/* initialize info */
	bzero((wireless_info *) &wless_info, sizeof(struct wireless_info));

	/* Attempt to get basic wireless information */
	if(iw_get_basic_config(sock, ifname, &(wless_info.b)) < 0)
	{
		/* no wireless extentions.  We need to check for the existence of a wired one */
		strncpy(ifr.ifr_name, ifname, IFNAMSIZ);
		if(ioctl(sock, SIOCGIFFLAGS, &ifr) < 0)
			return(-ENODEV);
		else  	   /* we found a wired network interface */ {
			ssid->assign("Not Applicable");
			*type = IFT_WIRED;
			return (EXEC_SUCCESS);
		}
	}
	/* we found a wireless network interface:
	 * Grab the SSID while I have it in wless_info
	 */
	ssid->assign(wless_info.b.essid, wless_info.b.essid_len);
	*type = IFT_WIRELESS;
	return (EXEC_SUCCESS);
}

/*
 * Current version of this tool, I just want to grab robotic address information for the
 * wireless connection.  This function just returns without any work.
 */
static int get_wired_interface(int sock, char * ifname, ur::WiredInterface *head)
{
	int rval = 0;

	// std::cout << ifname << " is a wired interface" << std::endl;


    return rval;
}


static int get_wireless_interface(int sock, char * ifname, std::string *addr)
{
	int rval = 0;
	struct ifaddrs *ifaddr, *ifa;

	int family, s, n;
	char host[NI_MAXHOST];

	if (getifaddrs(&ifaddr) == -1) {
		std::cout << "unable to get addresses" << std::endl;
		return (ERROR_UNHANDLED_EXCEPTION);
	}

	/* Walk through linked list, maintaining head pointer so we
	              can free list later */

	for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) {
		if (ifa->ifa_addr == NULL)
			continue;

		/* We are only interested in the wireless interface */
		if (strcmp(ifa->ifa_name, ifname) != 0)
			continue;

		family = ifa->ifa_addr->sa_family;

		/* we are only interested in the ipv4 address for now */
		if (family != AF_INET)
			continue;

		/* Display interface name and family (including symbolic
	                  form of the latter for the common families) */

		/* For an AF_INET* interface address, display the address.  Currently
		 * we will only have AF_NET when we get this far.  Keeping this code
		 * as we will eventually handle both 4 and 6 */

		if (family == AF_INET || family == AF_INET6) {
			s = getnameinfo(ifa->ifa_addr,
					(family == AF_INET) ? sizeof(struct sockaddr_in) :
							sizeof(struct sockaddr_in6),
							host, NI_MAXHOST,
							NULL, 0, NI_NUMERICHOST);
			if (s != 0) {
				return (ERROR_UNHANDLED_EXCEPTION);
			}
			addr->assign(host);
		}
	}
	freeifaddrs(ifaddr);

	return rval;
}

