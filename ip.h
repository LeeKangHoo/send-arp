#pragma once
#include <arpa/inet.h>
#include <string>


struct Ip {
    uint32_t ip;

    Ip(){}
    Ip(std::string ip);
};
