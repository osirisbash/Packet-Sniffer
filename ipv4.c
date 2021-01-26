#include <stdio.h>
#include <string.h>
#include <netinet/ip.h>
#include <net/ethernet.h>
#include <arpa/inet.h>

#include "prototypes.h"

#define TABS "\t"

struct iphdr * ip_alloc(struct iphdr *ip, unsigned char *buffer ){
	
	ip  = (struct iphdr *)(buffer + sizeof(struct ethhdr));
	return ip;
}

void display_ip(struct iphdr *ip){
	
	struct sockaddr_in source, dest;
	memset(&source, 0, sizeof(source));
	memset(&dest, 0, sizeof(dest));
	
	source.sin_addr.s_addr = ip->saddr;
	dest.sin_addr.s_addr = ip->daddr;
	
	printf("IPV4 Header\n");
	printf(TABS"|-Version              :%d\n", ip->version);
	printf(TABS"|-IHL                  :%d\n", ip->ihl);
	printf(TABS"|-Type of Service      :%d\n", ip->tos);
	printf(TABS"|-Total Length         :%d\n", ntohs(ip->tot_len));
	printf(TABS"|-Identification       :%d\n", ntohs(ip->id));
	printf(TABS"|-Fragment Offset      :%#x\n", ntohs(ip->frag_off));
	printf(TABS"|-Time To Live         :%d\n", ip->ttl);
	printf(TABS"|-Protocol             :%d\n", ip->protocol);
	printf(TABS"|-Source Address       :%s\n", inet_ntoa(source.sin_addr));
	printf(TABS"|-Destination Address  :%s\n", inet_ntoa(dest.sin_addr));
	}
