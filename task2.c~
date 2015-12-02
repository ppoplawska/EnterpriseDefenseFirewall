//task2.c
#define __KERNEL__
#define MODULE
#include <linux/ip.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/udp.h>
#include <linux/tcp.h>
#include <linux/ip.h>

static struct nf_hook_ops netfilter_ops;
//static unsigned char *ip_address = "\xC0\xA8\x00\x01";
static unsigned char *ip_address1 = "\x80\xE3\x09\x30"; //0x80E30930 ufl.edu
static unsigned char *ip_address2 = "\x62\x8A\xFD\x6D"; //0x628AFD6D belongs to yahoo.com
static char *interface = "lo";
unsigned char *port = "\x00\x17";

//FOR TCP STUFF
unsigned int src_port;
unsigned int dest_port;

struct sk_buff *sock_buff;
struct udphdr *udp_header;
struct tcphdr *tcp_header;
unsigned int main_hook(unsigned int hooknum,
                  struct sk_buff *skb,
                  const struct net_device *in,
                  const struct net_device *out,
                  int (*okfn)(struct sk_buff*))
{
  printk(KERN_INFO "main hook\n");
  if(strcmp(in->name,interface) == 0){ return NF_DROP; }

  //get ip header info
  struct iphdr *ip_header = (struct iphdr *)skb_network_header(skb);
 
  //GET TCP HEADER
  if (ip_header->protocol == 6) {
	printk(KERN_INFO "Found TCP Packet: Protocol %d\n", ip_header->protocol);
	tcp_header = (struct tcphdr *)((__u32 *)ip_header->ihl);
	src_port = htons((unsigned short int)tcp_header->source);
	dest_port = htons((unsigned short int)tcp_header->source);
  }

  //GET UDP HEADER
  if (ip_header->protocol == 17) {
	printk(KERN_INFO "Found UDP Packet: Protocl %d\n", ip_header->protocol);
	udp_header = (struct udphdr *)((__u32 *)ip_header->ihl);
	src_port = htons((unsigned short int)udp_header->source);
	dest_port = htons((unsigned short int)udp_header->dest);
  }
  //get source address
  unsigned int src_ip = (unsigned int)ip_header->saddr;
  if(!skb){
     printk(KERN_INFO "socket buffer is empty\n");
     return NF_ACCEPT;
  }
  if(!ip_header){
	printk(KERN_INFO "no ip header in the socket buffer!\n");
	return NF_ACCEPT;
  }
  if(src_ip == *(unsigned int*)ip_address1){
	printk(KERN_INFO "ufl ip is blocked!\n");
	return NF_DROP;
  }

  printk(KERN_INFO "SRC: %d DEST: %d", src_port, dest_port);
  if(dest_port == 23 || src_port == 23) {
	printk(KERN_INFO "Telnet attempted: blocked.\n");
  	return NF_DROP;
  }
  if(src_ip == *(unsigned int*)ip_address2){
	printk(KERN_INFO "yahoo.com ip is blocked!\n");
	return NF_DROP;
  }

/*
if(sock_buff->nh.iph->protocol != 17){ return NF_ACCEPT; }
udp_header = (struct udphdr *)(sock_buff->data + (sock_buff->nh.iph->ihl *4));
if((udp_header->dest) == *(unsigned short*)port){ return NF_DROP; }
*/

return NF_ACCEPT;
}
int init_module()
{
        netfilter_ops.hook              =       main_hook;
        netfilter_ops.pf                =       PF_INET;
        netfilter_ops.hooknum           =       NF_INET_PRE_ROUTING;
        netfilter_ops.priority          =       NF_IP_PRI_FIRST;
        nf_register_hook(&netfilter_ops);

return 0;
}
void cleanup_module() { nf_unregister_hook(&netfilter_ops); }
