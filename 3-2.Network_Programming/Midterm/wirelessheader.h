#include <stdint.h>

struct ieee80211_wireless_header {
	uint64_t timestamp;
    	uint16_t beacon_interval;
	uint16_t capabilities_information;
    	uint8_t tag_number;
    	uint8_t tag_length;
    	uint8_t ssid[0];
};

void print_wireless_header(struct ieee80211_wireless_header* wireless_hdr) {
    printf("[*] WIRELESS HEADER\n");
    printf("[*] timestamp       | beacon interval | capabilities info | tag number | tag length | ssid\n");
    printf("[*] %-15llu | %-15hu | %-17hu | %-10hhu | %-10hhu | ", wireless_hdr->timestamp, wireless_hdr->beacon_interval, wireless_hdr->capabilities_information, wireless_hdr->tag_number, wireless_hdr->tag_length);
    for(int i = 0; i < wireless_hdr->tag_length; i++)
        printf("%c", wireless_hdr->ssid[i]);
    printf("\n\n");
}
