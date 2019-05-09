#include "landattack.h"
#include <netinet/ip.h>
/*
 * LAND攻击（局域网拒绝服务攻击，英语：Local Area Network Denial attack，缩写：LAND attack），是拒绝服务攻击（DoS攻击）的一种，
 * 通过发送精心构造的、具有相同源地址和目标地址的欺骗数据包，致使缺乏相应防护机制的目标设备瘫痪。
 * 原理/land攻击
这种攻击方式采用了特别构造的TCP SYN数据包（通常用于开启一个新的连接），使目标机器开启一个源地址与目标地址均为自身IP地址的空连接，持续地自我应答，消耗系统资源直至崩溃。这种攻击方法与SYN洪泛攻击并不相同。
其他类型的LAND攻击在类似SNMP和Windows 88/tcp（Kerberos 协议）的服务中也有发现。类似的系统存在设计上的缺陷，允许设备接受并响应来自网络、却宣称来自于设备自身的数据包，导致循环应答。
*/

landattack::landattack()
{

}
