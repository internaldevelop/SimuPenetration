#ifndef SYN_FLOOD_H
#define SYN_FLOOD_H

#include "common.h"

class syn_flood
{
public:
    syn_flood();

    void set_sig_int();
    int do_main(char *strip,int port);
    int do_land(char *strip,int port);

};

#endif // SYN_FLOOD_H
