/*
系统全局变量
*/
#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QDialog>
#include <QLabel>
#include <QListWidget>
#include <QProcess>
#include <QPushButton>
#include <QSplitter>
#include <QStackedWidget>
#include <QTextBrowser>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPrinter>
#include <qdebug.h>
#include <QPainter>
#include <QFile>
#include <QPdfWriter>
#include <QDateTime>
#include <qplaintextedit.h>
#include <Utils/csysutils.h>
#include <Utils/cwebutils.h>

#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <arpa/inet.h>
#include  <pthread.h>

#include <string.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>



#define DEFAULT_SKIN ":/skin/7_big"
/*保存密码*/
extern QString PWD;
 /*密码操作标志*/
extern int Flag_Read_Pwd;//密码可读
extern int Flag_Read_Pwd_times;

extern int Flag_skin; //皮肤改变
extern int Flag_Cancel; //取消操作

extern int Flag_Sys_Test_Page;//是否一键检测页面

//extern int pp;
extern int Flag_Current_Main_Page;

//==============================================================
// New version written by Wei Yitao

extern QString g_sWorkingPath;  // Current running path of this desktop application

//==============================================================
#define SYNFLOOD    0
#define ICMPFLOOD   1
#define LANDATTACK  2


#endif // COMMON_H
