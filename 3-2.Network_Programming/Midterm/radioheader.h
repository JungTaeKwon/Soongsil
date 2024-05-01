#include <unistd.h>

struct ieee80211_radiotap_header
{
	u_int8_t version;
	u_int8_t pad;
	u_int16_t len;
	u_int32_t present;
} __attribute__((packed));

void print_radiotap_header(struct ieee80211_radiotap_header *radiotap_hdr)
{
	printf("[*] RADIOTAP HEADER\n");
	printf("[*] version | pad | len | present\n");
	printf("[*] %-7d | %-3d | %-3d | %-7d\n\n", radiotap_hdr->version, radiotap_hdr->pad, radiotap_hdr->len, radiotap_hdr->version);
}
