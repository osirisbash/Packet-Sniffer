 #ifndef PROTOTYPES_H
 #define PROTOTYPES_H


struct ethhdr * eth_alloc(struct ethhdr *eth, unsigned char *buffer);
struct iphdr * ip_alloc(struct iphdr *ip, unsigned char *buffer);
struct tcphdr * tcp_alloc(struct tcphdr *tcp, unsigned char *buffer);
struct udphdr * udp_alloc(struct udphdr *udp, unsigned char *buffer);
struct icmphdr * icmp_alloc(struct icmphdr *icmp, unsigned char *buffer);

void display_eth(struct ethhdr *eth);
void display_ip(struct iphdr *ip);
void display_tcp(struct tcphdr *tcp);
void display_udp(struct udphdr *udp);
void display_icmp(struct icmphdr *icmp);
void display_payload(unsigned char * buffer, size_t size);

#endif
