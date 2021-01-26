#include <stdio.h>	//For standard things
#include <netinet/udp.h>	//Provides declarations for udp header
#include <netinet/ip.h>	//Provides declarations for ip header
#include <net/ethernet.h>	//For ether_header

#include "prototypes.h"
#define TABS "\t"

struct udphdr * udp_alloc(struct udphdr *udp, unsigned char *buffer ){
	
	udp = (struct udphdr *)(buffer + sizeof(struct ethhdr) + sizeof(struct iphdr));       
	return udp;
			
}

void display_udp(struct udphdr *udp){
	
	printf("UDP Header\n");
	printf(TABS"|-source Port          :%d\n", ntohs(udp->source));
	printf(TABS"|-Destination Port     :%d\n", ntohs(udp->dest));
	printf(TABS"|-Length               :%d\n", ntohs(udp->len));
	printf(TABS"|-Checksun             :%d\n", ntohs(udp->check));

}
