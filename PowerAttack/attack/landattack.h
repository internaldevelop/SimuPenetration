#ifndef LANDATTACK_H
#define LANDATTACK_H

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <QThread>
#include <QTimer>

//#include <netdb.h>
//#include <stdio.h>
//#include <arpa/inet.h>

class landattack
{
public:
    landattack();
    int do_land(char *strip,int port);
    void set_sig_int();

};

#endif // LANDATTACK_H