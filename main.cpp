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

    packet.eth.smac = Mac("FF:FF:FF:FF:FF:FF");
    packet.eth.dmac = Mac("FF:FF:FF:FF:FF:FF");
    packet.eth.etype = htons(0x0806);//arp

    packet.arp.h_type = htons(0x0001);//ethernet
    packet.arp.p_type = htons(0x0800);//ipv4
    packet.arp.h_length = 0x06; //mac
    packet.arp.p_length = 0x04; //ipv4
    packet.arp.op_code = 0x0002; //reply
    packet.arp.smac = Mac("FF:FF:FF:FF:FF:FF");
    packet.arp.sip = Ip("0.0.0.0");
    packet.arp.tmac = Mac("FF:FF:FF:FF:FF:FF");
    packet.arp.tip = Ip("0.0.0.0");






    pcap_sendpacket(pcap,reinterpret_cast<u_char*>(&packet),sizeof(etharpPacket)); // gudqusghks
    pcap_close(pcap);

}
