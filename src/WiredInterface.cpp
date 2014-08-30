/*
 * WiredInterface.cpp
 *
 *  Created on: Jul 10, 2014
 *      Author: kurt
 */

#include "WiredInterface.h"
#include <string.h>

namespace ur {

WiredInterface::WiredInterface() {
	// TODO Auto-generated constructor stub
	m_iIndex = 0;
	m_iMTU = 0;
	m_uiHardwareAddressLength = 0;
	m_iFlags = 0;
	m_iMyFlags = 0;
}

WiredInterface::~WiredInterface() {
	// TODO Auto-generated destructor stub
}

std::string WiredInterface::GetName()
{
	return m_sName;
}

void WiredInterface::SetName(CString *s)
{
	m_sName = s;
}

short WiredInterface::GetIndex()
{
	return m_iIndex;
}

void WiredInterface::SetIndex(short i)
{
	m_iIndex = i;
}

short WiredInterface::GetMTU()
{
	return m_iMTU;
}

void WiredInterface::SetMTU(short i)
{
	m_iMTU = i;
}

unsigned char *WiredInterface::GetHardwareAddress()
{
	return m_ucHardwareAddress;
}

void WiredInterface::SetHardwareAddress(unsigned char *ha)
{
	memcpy(ha, &m_ucHardwareAddress, sizeof(m_ucHardwareAddress));
}

unsigned short WiredInterface::GetHardwareAddressLength()
{
	return m_uiHardwareAddressLength;
}

void WiredInterface::SetHardwareAddressLength(unsigned short i)
{
	m_uiHardwareAddressLength = i;
}

short WiredInterface::GetFlags()
{
	return m_iFlags;
}

void WiredInterface::SetFlags(short i)
{
	m_iFlags = i;
}

short WiredInterface::GetMyFlags()
{
	return m_iMyFlags;
}

void WiredInterface::SetMyFlags(short i)
{
	m_iMyFlags = i;
}

struct sockaddr WiredInterface::GetPrimaryAddress()
{
	return m_saPrimaryAddress;
}

void WiredInterface::SetPrimaryAddress(sockaddr addr)
{
	memcpy(&addr, &m_saPrimaryAddress, sizeof(sockaddr));
}

struct sockaddr WiredInterface::GetBroadcastAddress()
{
	return m_saBroadcastAddress;
}

void WiredInterface::SetBroadcastAddress(sockaddr addr)
{
	memcpy(&addr, &m_saBroadcastAddress, sizeof(sockaddr));
}

struct sockaddr WiredInterface::GetDestinationAddress()
{
	return m_saDestinationAddress;
}

void WiredInterface::SetDestinationAddress(struct sockaddr addr)
{
	memcpy(&addr, &m_saDestinationAddress, sizeof(sockaddr));
}

WiredInterface *WiredInterface::GetNext()
{
	return m_next;
}

void WiredInterface::SetNext(WiredInterface *iface)
{
	m_next = iface;
}

} /* namespace ur */
