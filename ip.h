#pragma once
#include <arpa/inet.h>
#include <string>


struct Ip {
    uint32_t ip;

    Ip(){}
    Ip(std::string ip);

    operator uint32_t() {
        return ip;
    }

    Ip& operator=(uint32_t v) {
        ip = v;
        return *this;
    }
};
