/*
 * WirelessInterface.h
 *
 *  Created on: Jul 11, 2014
 *      Author: kurt
 */

#ifndef WIRELESSINTERFACE_H_
#define WIRELESSINTERFACE_H_

#include <iwlib.h>

namespace ur {

class WirelessInterface {
private:
	wireless_config m_config;

//	typedef struct wireless_config
	{
//	  char		name[IFNAMSIZ + 1];	/* Wireless/protocol name */
//	  int		has_nwid;
//	  iwparam	nwid;			/* Network ID */
//	  int		has_freq;
//	  double	freq;			/* Frequency/channel */
//	  int		freq_flags;
//	  int		has_key;
//	  unsigned char	key[IW_ENCODING_TOKEN_MAX];	/* Encoding key used */
//	  int		key_size;		/* Number of bytes */
//	  int		key_flags;		/* Various flags */
//	  int		has_essid;
//	  int		essid_on;
//	  char		essid[IW_ESSID_MAX_SIZE + 2];	/* ESSID (extended network) */
//	  int		essid_len;
//	  int		has_mode;
//	  int		mode;			/* Operation mode */
//	} wireless_config;

	/* Structure for storing all wireless information for each device
	 * This is pretty exhaustive... */
//	typedef struct wireless_info
//	{
//	  struct wireless_config	b;	/* Basic information */

//	  int		has_sens;
//	  iwparam	sens;			/* sensitivity */
//	  int		has_nickname;
//	  char		nickname[IW_ESSID_MAX_SIZE + 2]; /* NickName */
//	  int		has_ap_addr;
//	  sockaddr	ap_addr;		/* Access point address */
//	  int		has_bitrate;
//	  iwparam	bitrate;		/* Bit rate in bps */
//	  int		has_rts;
//	  iwparam	rts;			/* RTS threshold in bytes */
//	  int		has_frag;
//	  iwparam	frag;			/* Fragmentation threshold in bytes */
//	  int		has_power;
//	  iwparam	power;			/* Power management parameters */
//	  int		has_txpower;
//	  iwparam	txpower;		/* Transmit Power in dBm */
//	  int		has_retry;
//	  iwparam	retry;			/* Retry limit or lifetime */



public:
	WirelessInterface();
	virtual ~WirelessInterface();
};

} /* namespace ur */

#endif /* WIRELESSINTERFACE_H_ */
