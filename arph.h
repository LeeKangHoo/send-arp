#include "mac.h"
#include "ip.h"

struct arpH{
    uint16_t h_type;
    uint16_t p_type;
    uint8_t h_length;
    uint8_t p_length;
    uint16_t op_code;
    Mac smac;
    Ip sip;
    Mac tmac;
    Ip tip;

};
