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
//sd
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
  
  sock_buff = skb;

  //get ip header info
  struct iphdr *ip_header = (struct iphdr *)skb_network_header(sock_buff);
 
  char* UFL_EDU = "128.227.9.48";
  char*	YAHOO_COM = "206.190.36.45";
 
  //get source address
  unsigned int src_ip = (unsigned int)ip_header->saddr;
  if(!sock_buff){
     printk(KERN_INFO "socket buffer is empty\n");
     return NF_ACCEPT;
  }
  
  if(!ip_header){
	printk(KERN_INFO "no ip header in the socket buffer!\n");
	return NF_ACCEPT;
  }
  
  // get ip and anaylise
  
  int ipSize = 15;
  char * str[ipSize];
  snprintf(str, ipSize, "%pI4", &ip_header->saddr);
  
  if(!strcmp(str, UFL_EDU) || !strcmp(str, YAHOO_COM)) // if we wnated to make this dynamic, register each of the banned IPS to an array
														// figure out how to get user input for dynamic execution (piping mostlikey)
  {
		printk(KERN_INFO "Found blacklisted IP [ %s ] Dropping packet...\n", str);
	  return NF_DROP; //drop it
  }
  


printk(KERN_INFO "Did not hit any firewall rules, packet recieved...\n");
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
