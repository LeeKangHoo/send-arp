#include "mac.h"


Mac::Mac(std::string a){
    memset(mac, 0, sizeof(mac));

    sscanf(a.c_str(),"%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);


}
