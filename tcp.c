#include <stdio.h>	//For standard things
#include <netinet/tcp.h>	//Provides declarations for tcp header
#include <netinet/ip.h>	//Provides declarations for ip header
#include <net/ethernet.h>	//For ether_header
#include "prototypes.h"

#define TABS "\t"

struct tcphdr * tcp_alloc(struct tcphdr *tcp, unsigned char *buffer ){
	
	tcp = (struct tcphdr *)(buffer + sizeof(struct ethhdr) + sizeof(struct iphdr));
	return tcp;
			
}

void display_tcp(struct tcphdr *tcp){
	printf("TCP Header\n");
	printf(TABS"|-Source Port          :%d\n", ntohs(tcp->source));
	printf(TABS"|-Destination Port     :%d\n", ntohs(tcp->dest));
	printf(TABS"|-Sequence Number      :%d\n", ntohs(tcp->seq));
	printf(TABS"|-Ack Number           :%d\n", ntohs(tcp->ack_seq));
	printf(TABS"|-Offset               :%d\n", tcp->doff);
	printf(TABS"|-URG                  :%d\n", tcp->urg);
	printf(TABS"|-ACK                  :%d\n", tcp->ack);
	printf(TABS"|-PSH                  :%d\n", tcp->psh);
	printf(TABS"|-RST                  :%d\n", tcp->rst);
	printf(TABS"|-SYN                  :%d\n", tcp->syn);
	printf(TABS"|-FIN                  :%d\n", tcp->fin);
	printf(TABS"|-Window               :%d\n", ntohs(tcp->window));
	printf(TABS"|-Urgent Pointer       :%d\n", tcp->urg_ptr);
}
