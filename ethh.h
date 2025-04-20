#include "mac.h"

#pragma pack(push,1)
struct ethH {
    Mac dmac;
    Mac smac;
    uint16_t etype;




};
#pragma pack(pop)
