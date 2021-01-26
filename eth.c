#include <stdio.h>	//For standard things
#include <net/ethernet.h>	//For ether_header
#include "prototypes.h"

#define TABS "\t"

struct ethhdr * eth_alloc(struct ethhdr *eth, unsigned char *buffer ) {
	eth = (struct ethhdr * ) buffer;
	return eth;
}

void display_eth(struct ethhdr *eth){
	printf("Ethernet Header\n");
	printf(TABS"|-Source Address       :%.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", eth->h_source[0], eth->h_source[1], eth->h_source[2], eth->h_source[3], eth->h_source[4], eth->h_source[5]);
	printf(TABS"|-Source Address       :%.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", eth->h_dest[0], eth->h_dest[1], eth->h_dest[2], eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);
	printf(TABS"|-Ether Type           :%u\n", (unsigned short) eth->h_proto);
}
