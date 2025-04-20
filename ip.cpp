#include "ip.h"
#include "mac.h"

Ip::Ip(std::string ipadd){
    uint32_t a,b,c,d;
    sscanf(ipadd.c_str(),"%u.%u.%u.%u",&a,&b,&c,&d);
    ip = a<<24 | b<<16 | c<<8 | d;
}
