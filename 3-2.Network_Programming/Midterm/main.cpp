#include "main.h"

int main(int argc, char *argv[])
{
    char dev[] = "wlan0";
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t *handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr)
    {
        fprintf(stderr, "pcap_open_live(%s) return nullptr - %s\n", dev, errbuf);
        return -1;
    }

    while (true)
    {
        struct pcap_pkthdr *header;
        const u_char *packet;

        int res = pcap_next_ex(handle, &header, &packet);
        if (res == 0)
            continue;
        if (res == -1 || res == -2)
            break;

        struct ieee80211_radiotap_header *radiotap_hdr = (struct ieee80211_radiotap_header *)packet;
        struct ieee80211_beacon_header *beacon_hdr = (struct ieee80211_beacon_header *)(radiotap_hdr->len + packet);
        struct ieee80211_wireless_header *wireless_hdr = (struct ieee80211_wireless_header *)(radiotap_hdr->len + sizeof(ieee80211_beacon_header) + packet);

        print_radiotap_header(radiotap_hdr);
        print_beacon_header(beacon_hdr);
        print_wireless_header(wireless_hdr);
        print_line();
    }

    pcap_close(handle);

    return 0;
}
