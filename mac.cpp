#include "mac.h"


Mac::Mac(std::string a){
    memset(mac, 0, sizeof(mac));

    sscanf(a.c_str(),"%02x:%02x:%02x:%02x:%02x:%02x", &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);
    // MAC 주소 값 확인
    for(int i = 0; i < 6; i++) {
        printf("%02x ", mac[i]);
    }
    printf("\n");

}
