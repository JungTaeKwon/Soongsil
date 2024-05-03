#include <iostream>
#include <pcap.h>
#include <cstring>
#include "radioheader.h"
#include "beaconheader.h"
#include "wirelessheader.h"

// CONST
#define PKT_CAPTURING true
#define WIRELESS_INTERFACE "wlan0"

void print_line()
{
    printf("----------------------------------------------------------------------------------------------------------------------------------\n");
}