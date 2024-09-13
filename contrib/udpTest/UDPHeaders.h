#ifndef UDPHEADERS_H
#define UDPHEADERS_H

#include"ns3/mt-header.h"

class UDPHeader : public ns3::MTHeader
{
	public:
	int src_port;
	int dst_port;
	int length;
	UDPHeader(){}
};

#endif