#include <stdint.h>

struct ieee80211_beacon_header{
	uint16_t	frame_control;
	uint16_t	duration;
	uint8_t		receiver_adress[6];
	uint8_t		transmitter_address[6];
	uint8_t		bssid[6];
	uint16_t	sequence_control;
};


void print_beacon_header(struct ieee80211_beacon_header *beacon_hdr) {
    printf("[*] BEACON HEADER\n");
    printf("[*] frame control | duration | receiver address  | transmitter address  |       bssid       | sequence control\n");
    printf("[*] %-13x | %-8x | ", beacon_hdr->frame_control, beacon_hdr->duration);
    for(int i = 0; i < 6; i++)
        printf("%02x%s", beacon_hdr->receiver_adress[i], (i == 5) ? " | " : ":");
    for(int i = 0; i < 6; i++)
        printf("%02x%s", beacon_hdr->transmitter_address[i], (i == 5) ? "    | " : ":");
    for(int i = 0; i < 6; i++)
        printf("%02x%s", beacon_hdr->bssid[i], (i == 5) ? " | " : ":");
    printf("%-16x\n", beacon_hdr->sequence_control);
    printf("\n");
}

