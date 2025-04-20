#include "ip.h"

Ip::Ip(std::string ipadd){
    uint8_t buf[4];
    sscanf(ipadd.c_str(),"%d.%d.%d.%d",&buf[0],&buf[1],&buf[2],&buf[3]);
    ip = buf[0]<<24 | buf[1]<<16 | buf[2]<<8 | buf[3];
}
