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
#define TABS "\t"

void display_payload(unsigned char * buffer, size_t size) {
	printf("DATA Payload\n");
	
	for (uint32_t i = 0; i < size; i++) {
		if (i != 0 && i % 16 == 0)
		{
			printf(TABS);
			for (uint32_t j = i - 16; j < i; j++) {
				if (buffer[j] >= 32 && buffer[j] <= 128){
					printf("%c", (unsigned char) buffer[j]);
				}
				else {
					printf(".");
				}
			}
			printf("\n");
		}
		
		if (i % 16 == 0) 
		{
			printf(TABS);
		}
		printf(" %02X", (uint32_t) buffer[i]);
		
		if (i == size - 1)
		{
			for (uint32_t j = 0; j < 15 - i % 16; j++) {
				printf("   "); //extra spaces
			}
			
			printf(TABS);
			
			for (uint32_t j = i - i % 16; j <= i; j++) {
				if (buffer[j] >= 32 && buffer[j] <= 128) {
					printf( "%c", (unsigned char) buffer[j]);
				} 
				else {
					printf(".");
				}
			}
		printf("\n");
		}
	}
}
