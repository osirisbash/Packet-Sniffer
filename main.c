#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/if.h>
#include "prototypes.h"
#include <sys/ioctl.h>

#define MAX_SIZE 65536
#define NULL_MESS	0
#define NULL_SOCK	0
#define MAX_ARGC	2
#define TCP_FLAG	"-T"
#define UDP_FLAG 	"-U"
#define ICMP_FLAG	"-I"
#define TABS "\t"
#define DEVICE "enp2s0"
int main(int argc, char **argv){

	uint8_t iphdr_size;
	uint32_t addr_len;
	
	uint16_t pkt = 0;
	int16_t sock = 0;
	int32_t mess = 0;
	uint32_t header_size = 0;
	
	unsigned char 	*buf 	= 	NULL;
	struct ethhdr 	*eth	=	NULL;
	struct iphdr  	*ip 	=	NULL;
	struct tcphdr 	*tcp 	= 	NULL; 
	struct udphdr 	*udp 	= 	NULL;
	struct icmphdr 	*icmp 	= 	NULL;
	struct ifreq ifr;

	struct sockaddr src_addr;
	
	
	buf = (unsigned char * ) malloc(MAX_SIZE);
	sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP));
	
	strcpy(ifr.ifr_name, DEVICE);
	if (ioctl(sock, SIOCGIFFLAGS, &ifr) < 0){
		perror("ioctl() failed");
			fprintf(stderr, "Error\n");
			exit(EXIT_FAILURE);
	}
	
	ifr.ifr_flags |= IFF_PROMISC;
	
	if (ioctl(sock, SIOCGIFFLAGS, &ifr) < 0){
		perror("ioctl() failed");
			fprintf(stderr, "Error\n");
			exit(EXIT_FAILURE);
	}
		

	while (pkt < 100) {
		
		addr_len = sizeof src_addr;
		mess = recvfrom(sock, buf, MAX_SIZE, 0, &src_addr, (socklen_t * ) &addr_len);
		
		if (argc != MAX_ARGC || sock < NULL_SOCK || mess < NULL_MESS){
			fprintf(stderr, "Error\n");
			exit(EXIT_FAILURE);
		}
			 
		else if (strcmp(argv[1], TCP_FLAG ) == 0){
			eth = eth_alloc(eth, buf);
			
			if (ntohs(eth->h_proto) == ETH_P_IP){
				ip = ip_alloc(ip, buf);
				if ((ip->protocol) == IPPROTO_TCP) {
					printf("\n\nPacket ID : %d (%d bytes read)\n", ++pkt, mess);
					tcp = tcp_alloc(tcp, buf);
					display_eth(eth);
					display_ip(ip);
					display_tcp(tcp);
					
					iphdr_size = ip->ihl * 4;
					header_size = sizeof(struct ethhdr) + iphdr_size + tcp->doff * 4;
					
					display_payload(buf + header_size, mess - header_size);
				}
			}
		}
		
		else if (strcmp(argv[1], UDP_FLAG ) == 0) {
			eth = eth_alloc(eth, buf);
			
			if (ntohs(eth->h_proto) == ETH_P_IP){
				ip = ip_alloc(ip, buf);
				
				if ((ip->protocol) == IPPROTO_UDP){
					printf("\n\nPacket ID : %d (%d bytes read)\n", ++pkt, mess);
					udp = udp_alloc(udp, buf);
					display_eth(eth);
					display_ip(ip);
					display_udp(udp);
					
					iphdr_size = ip->ihl * 4;
					header_size = sizeof(struct ethhdr) + iphdr_size + sizeof(udp);
					display_payload(buf + header_size, mess - header_size);
				}
			}
		}
		
		else if (strcmp(argv[1], ICMP_FLAG ) == 0) {
			eth = eth_alloc(eth, buf);
			if (ntohs(eth->h_proto) == ETH_P_IP){
				ip = ip_alloc(ip, buf);
				
				if ((ip->protocol) == IPPROTO_ICMP){
					printf("\n\nPacket ID : %d (%d bytes read)\n", ++pkt, mess);
					icmp = icmp_alloc(icmp, buf);
					display_eth(eth);
					display_ip(ip);
					display_icmp(icmp);
					iphdr_size = ip->ihl * 4;
					header_size = sizeof(struct ethhdr) + iphdr_size + sizeof (icmp);
					display_payload(buf + header_size, mess - header_size);
				}		
			}
		}
	}
	
  return 0;
}




