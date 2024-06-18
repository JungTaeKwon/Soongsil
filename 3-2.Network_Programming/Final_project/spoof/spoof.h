#include <cstdio>
#include <pcap.h>
#include "util.h"
#include "ethhdr.h"
#include "arphdr.h"
#include "iphdr.h"
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <thread>

#pragma pack(push, 1)
struct EthArpPacket final
{
	EthArpPacket(uint8_t mode, Mac ether_dmac, Mac ether_smac, uint16_t _type, uint16_t _hrd, uint16_t _pro, uint8_t _hln, uint8_t _pln, Mac arp_smac, Ip arp_sip, Mac arp_tmac, Ip arp_tip)
	{
		eth_.dmac_ = ether_dmac;
		eth_.smac_ = ether_smac;
		eth_.type_ = htons(EthHdr::Arp);

		arp_.hrd_ = htons(ArpHdr::ETHER);
		arp_.pro_ = htons(EthHdr::Ip4);

		arp_.op_ = htons(mode);

		arp_.hln_ = Mac::SIZE;
		arp_.pln_ = Ip::SIZE;

		arp_.smac_ = arp_smac;
		arp_.sip_ = htonl(arp_sip);
		arp_.tmac_ = arp_tmac;
		arp_.tip_ = htonl(arp_tip);
	}

	EthHdr eth_;
	ArpHdr arp_;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct EthIpPacket final
{
	EthHdr eth_;
	IpHdr ip_;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Flow final
{
	Ip attackerIp = Ip();
	Ip senderIp = Ip();
	Ip targetIp = Ip();

	Mac attackerMac = Mac::nullMac();
	Mac senderMac = Mac::nullMac();
	Mac targetMac = Mac::nullMac();
};
#pragma pack(pop)

void sendArp(pcap_t *, EthArpPacket);
void continueSendArp(pcap_t *, EthArpPacket, int);
Mac getMac(pcap_t *, Ip, Mac, Ip);
bool isRefreshed(pcap_t *, const u_char *, Flow);
void spoofProcess(int, pcap_t *, EthArpPacket, Flow);
void relayPacket(pcap_t *, const u_char *, Flow);
bool isInfectedPkt(pcap_t *, const u_char *, Flow);