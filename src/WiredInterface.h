/*
 * WiredInterface.h
 *
 *  Created on: Jul 10, 2014
 *      Author: kurt
 */

#ifndef WIREDINTERFACE_H_
#define WIREDINTERFACE_H_

#include <string>
#include <net/if.h>

namespace ur {

#define IFI_HADDR 8 /* taken from Stevens - Network Programming
                       "allow for 64-bit EUI-64 in the future */

class WiredInterface {
private:
	std::string m_sName;
	short m_iIndex;
	short m_iMTU;
	unsigned char m_ucHardwareAddress[IFI_HADDR];
	unsigned short m_uiHardwareAddressLength;
	short m_iFlags;
	short m_iMyFlags;
	struct sockaddr m_saPrimaryAddress;
	struct sockaddr m_saBroadcastAddress;
	struct sockaddr m_saDestinationAddress;
	WiredInterface *m_next;

public:
	WiredInterface();
	virtual ~WiredInterface();

	std::string GetName();
	void SetName(std::string *s);

	short GetIndex();
	void GetIndex(short i);

	short GetMTU();
	void SetMTU(short i);

	unsigned char *GetHardwareAddress();
	void SetHardwareAddress(unsigned char *ha);

	unsigned short GetHardwareAddressLength();
	void SetHardwareAddressLength(unsigned short i);

	short GetFlags();
	void SetFlags(short i);

	short GetMyFlags();
	void SetMyFlags(short i);

	struct sockaddr GetPrimaryAddress();
	void SetPrimaryAddress(struct sockaddr addr);

	struct sockaddr GetBroadcastAddress();
	void SetBroadcastAddress(struct sockaddr addr);

	struct sockaddr GetDestinationAddress();
	void SetDestinationAddress(struct sockaddr addr);

	WiredInterface *GetNext();
	void SetNext(WiredInterface *);
};

} /* namespace ur */

#endif /* WIREDINTERFACE_H_ */
