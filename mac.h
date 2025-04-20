#pragma once

#include <iostream>
#include <string>
#include <pcap.h>
#include <iostream>
#include <arpa/inet.h>
#include <sstream>
#include <cstdio>
#include <cstring>


struct Mac {
    uint8_t mac[6];


    Mac(){memset(mac, 0, sizeof(mac));}
    Mac(std::string a);


};

