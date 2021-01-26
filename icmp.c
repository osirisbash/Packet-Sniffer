#include <stdio.h>	//For standard things
#include <stdint.h>
#include <netinet/ip_icmp.h>	//Provides declarations for icmp header
#include <netinet/ip.h>	//Provides declarations for ip header
#include <net/ethernet.h>	//For ether_header
#include "prototypes.h"

#define TABS "\t"


struct icmphdr * icmp_alloc(struct icmphdr *icmp, unsigned char *buffer ){
	
	icmp = (struct icmphdr *)(buffer + sizeof(struct ethhdr) + sizeof(struct iphdr));       
	return icmp;
			
}

void display_icmp(struct icmphdr *icmp){
	
	printf("ICMP Header\n");
	
	printf(TABS"|-Type                 :%d\n", icmp->type);
	printf(TABS"|-Code                 :%d\n", icmp->code);
	printf(TABS"|-Checksum             :%d\n", ntohs(icmp-> checksum));
			
	if ((uint8_t)(icmp->type) == 11) {
		printf(TABS"|-TTL Expired\n");
				
	} 
	else if ((uint8_t)(icmp->type) == ICMP_ECHOREPLY) {
		printf(TABS"|-ICMP Echo Reply\n");
	}

			

}
