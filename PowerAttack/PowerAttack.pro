#-------------------------------------------------
#
# Project created by QtCreator 2019-04-02T11:31:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PowerAttack
TEMPLATE = app

QT += widgets network
QT += testlib
QT += charts
QT += printsupport


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    main.cpp \
    powerattack.cpp \
    about_us.cpp \
    boot_start_time.cpp \
    common.cpp \
    drop_shadow_widget.cpp \
    push_button.cpp \
    main_menu.cpp \
    title_widget.cpp \
    buttom_widget.cpp \
    tool_button.cpp \
    show_percent_page.cpp \
    Utils/chartcallout.cpp \
    Utils/csysutils.cpp \
    Utils/cwebutils.cpp \
    Utils/transformutil.cpp \
    systemdata/systemdata.cpp \
    controlcmd/controlcmd.cpp \
    net_speed.cpp \
    c37292.cpp

HEADERS += \
    powerattack.h \
    about_us.h \
    boot_start_time.h \
    common.h \
    drop_shadow_widget.h \
    push_button.h \
    main_menu.h \
    title_widget.h \
    buttom_widget.h \
    tool_button.h \
    show_percent_page.h \
    Utils/chartcallout.h \
    Utils/csysutils.h \
    Utils/cwebutils.h \
    Utils/transformutil.h \
    systemdata/systemdata.h \
    controlcmd/controlcmd.h \
    net_speed.h \
    c37292.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sources/resources.qrc

QT += widgets
QT += charts
#QT += webkit
QT += network

DISTFILES += \
    sources/score.gif \
    sources/html/picture/1.jpg \
    sources/html/picture/new_11.jpg \
    sources/html/picture/new_13.jpg \
    sources/html/picture/new_15.jpg \
    sources/html/picture/new_6.jpg \
    sources/html/picture/new_8.jpg \
    sources/html/picture/new_9.jpg \
    sources/img/skin/15.jpg \
    sources/img/skin/15_big.jpg \
    sources/img/skin/16.jpg \
    sources/img/skin/16_big.jpg \
    sources/img/skin/17.jpg \
    sources/img/skin/17_big.jpg \
    sources/img/skin/18.jpg \
    sources/img/skin/18_big.jpg \
    sources/img/skin/19.jpg \
    sources/img/skin/19_big.jpg \
    sources/img/skin/20.jpg \
    sources/img/skin/20_big.jpg \
    sources/img/skin/21.jpg \
    sources/img/skin/21_big.jpg \
    sources/img/skin/22.jpg \
    sources/img/skin/22_big.jpg \
    sources/img/skin/23.jpg \
    sources/img/skin/23_big.jpg \
    sources/1_big.jpg \
    sources/3_big.jpg \
    sources/4_big.jpg \
    sources/5_big.jpg \
    sources/6_big.jpg \
    sources/7_big.jpg \
    sources/cpu1.jpg \
    sources/cpu2.jpg \
    sources/disk1.jpg \
    sources/disk2.jpg \
    sources/disk3.jpg \
    sources/disk4.jpg \
    sources/net1.jpg \
    sources/net2.jpg \
    sources/net3.jpg \
    sources/net4.jpg \
    sources/os1.jpg \
    sources/os2.jpg \
    sources/os3.jpg \
    sources/html/picture/new_1.png \
    sources/html/picture/new_10.png \
    sources/html/picture/new_12.png \
    sources/html/picture/new_14.png \
    sources/html/picture/new_16.png \
    sources/html/picture/new_2.png \
    sources/html/picture/new_3.png \
    sources/html/picture/new_4.png \
    sources/html/picture/new_5.png \
    sources/html/picture/new_7.png \
    sources/img/skin/12_big.png \
    sources/img/skin/13.png \
    sources/img/skin/13_big.png \
    sources/img/skin/14.png \
    sources/img/skin/14_big.png \
    sources/img/skin/9.png \
    sources/img/11 \
    sources/img/loading.png \
    sources/2_big.png \
    sources/8_big.png \
    sources/arrow_down.png \
    sources/check.png \
    sources/close.png \
    sources/close_hover.png \
    sources/close_pressed.png \
    sources/feedback.png \
    sources/feedback_hover.png \
    sources/feedback_pressed.png \
    sources/func1.png \
    sources/func2.png \
    sources/func3.png \
    sources/func4.png \
    sources/func5.png \
    sources/func6.png \
    sources/func7.png \
    sources/func8.png \
    sources/logo.png \
    sources/logo1.png \
    sources/logo2.png \
    sources/menu.png \
    sources/menu_hover.png \
    sources/menu_pressed.png \
    sources/min.png \
    sources/min_hover.png \
    sources/min_pressed.png \
    sources/power.png \
    sources/score.png \
    sources/security_1.png \
    sources/security_2.png \
    sources/security_3.png \
    sources/security_4.png \
    sources/skin.png \
    sources/skin_hover.png \
    sources/skin_pressed.png \
    sources/xx.png \
    sources/xxxx.png \
    sources/logo.ico \
    sources/html/index.html \
    sources/index.html \
    sources/logo1.rc \
    sources/sys_test.ts \
    sources/score.gif \
    sources/html/picture/1.jpg \
    sources/html/picture/new_11.jpg \
    sources/html/picture/new_13.jpg \
    sources/html/picture/new_15.jpg \
    sources/html/picture/new_6.jpg \
    sources/html/picture/new_8.jpg \
    sources/html/picture/new_9.jpg \
    sources/img/skin/15.jpg \
    sources/img/skin/15_big.jpg \
    sources/img/skin/16.jpg \
    sources/img/skin/16_big.jpg \
    sources/img/skin/17.jpg \
    sources/img/skin/17_big.jpg \
    sources/img/skin/18.jpg \
    sources/img/skin/18_big.jpg \
    sources/img/skin/19.jpg \
    sources/img/skin/19_big.jpg \
    sources/img/skin/20.jpg \
    sources/img/skin/20_big.jpg \
    sources/img/skin/21.jpg \
    sources/img/skin/21_big.jpg \
    sources/img/skin/22.jpg \
    sources/img/skin/22_big.jpg \
    sources/img/skin/23.jpg \
    sources/img/skin/23_big.jpg \
    sources/1_big.jpg \
    sources/3_big.jpg \
    sources/4_big.jpg \
    sources/5_big.jpg \
    sources/6_big.jpg \
    sources/7_big.jpg \
    sources/cpu1.jpg \
    sources/cpu2.jpg \
    sources/disk1.jpg \
    sources/disk2.jpg \
    sources/disk3.jpg \
    sources/disk4.jpg \
    sources/net1.jpg \
    sources/net2.jpg \
    sources/net3.jpg \
    sources/net4.jpg \
    sources/os1.jpg \
    sources/os2.jpg \
    sources/os3.jpg \
    sources/html/picture/new_1.png \
    sources/html/picture/new_10.png \
    sources/html/picture/new_12.png \
    sources/html/picture/new_14.png \
    sources/html/picture/new_16.png \
    sources/html/picture/new_2.png \
    sources/html/picture/new_3.png \
    sources/html/picture/new_4.png \
    sources/html/picture/new_5.png \
    sources/html/picture/new_7.png \
    sources/img/skin/12_big.png \
    sources/img/skin/13.png \
    sources/img/skin/13_big.png \
    sources/img/skin/14.png \
    sources/img/skin/14_big.png \
    sources/img/skin/9.png \
    sources/img/11 \
    sources/img/loading.png \
    sources/2_big.png \
    sources/8_big.png \
    sources/arrow_down.png \
    sources/check.png \
    sources/close.png \
    sources/close_hover.png \
    sources/close_pressed.png \
    sources/feedback.png \
    sources/feedback_hover.png \
    sources/feedback_pressed.png \
    sources/func1.png \
    sources/func2.png \
    sources/func3.png \
    sources/func4.png \
    sources/func5.png \
    sources/func6.png \
    sources/func7.png \
    sources/func8.png \
    sources/logo.png \
    sources/logo1.png \
    sources/logo2.png \
    sources/menu.png \
    sources/menu_hover.png \
    sources/menu_pressed.png \
    sources/min.png \
    sources/min_hover.png \
    sources/min_pressed.png \
    sources/power.png \
    sources/score.png \
    sources/security_1.png \
    sources/security_2.png \
    sources/security_3.png \
    sources/security_4.png \
    sources/skin.png \
    sources/skin_hover.png \
    sources/skin_pressed.png \
    sources/xx.png \
    sources/xxxx.png \
    sources/logo.ico \
    sources/html/index.html \
    sources/index.html \
    sources/logo1.rc \
    sources/sys_test.ts \
    sources/score.gif \
    sources/html/picture/1.jpg \
    sources/html/picture/new_11.jpg \
    sources/html/picture/new_13.jpg \
    sources/html/picture/new_15.jpg \
    sources/html/picture/new_6.jpg \
    sources/html/picture/new_8.jpg \
    sources/html/picture/new_9.jpg \
    sources/img/skin/15.jpg \
    sources/img/skin/15_big.jpg \
    sources/img/skin/16.jpg \
    sources/img/skin/16_big.jpg \
    sources/img/skin/17.jpg \
    sources/img/skin/17_big.jpg \
    sources/img/skin/18.jpg \
    sources/img/skin/18_big.jpg \
    sources/img/skin/19.jpg \
    sources/img/skin/19_big.jpg \
    sources/img/skin/20.jpg \
    sources/img/skin/20_big.jpg \
    sources/img/skin/21.jpg \
    sources/img/skin/21_big.jpg \
    sources/img/skin/22.jpg \
    sources/img/skin/22_big.jpg \
    sources/img/skin/23.jpg \
    sources/img/skin/23_big.jpg \
    sources/1_big.jpg \
    sources/3_big.jpg \
    sources/4_big.jpg \
    sources/5_big.jpg \
    sources/6_big.jpg \
    sources/7_big.jpg \
    sources/cpu1.jpg \
    sources/cpu2.jpg \
    sources/disk1.jpg \
    sources/disk2.jpg \
    sources/disk3.jpg \
    sources/disk4.jpg \
    sources/net1.jpg \
    sources/net2.jpg \
    sources/net3.jpg \
    sources/net4.jpg \
    sources/os1.jpg \
    sources/os2.jpg \
    sources/os3.jpg \
    sources/html/picture/new_1.png \
    sources/html/picture/new_10.png \
    sources/html/picture/new_12.png \
    sources/html/picture/new_14.png \
    sources/html/picture/new_16.png \
    sources/html/picture/new_2.png \
    sources/html/picture/new_3.png \
    sources/html/picture/new_4.png \
    sources/html/picture/new_5.png \
    sources/html/picture/new_7.png \
    sources/img/skin/12_big.png \
    sources/img/skin/13.png \
    sources/img/skin/13_big.png \
    sources/img/skin/14.png \
    sources/img/skin/14_big.png \
    sources/img/skin/9.png \
    sources/img/11 \
    sources/img/loading.png \
    sources/2_big.png \
    sources/8_big.png \
    sources/arrow_down.png \
    sources/check.png \
    sources/close.png \
    sources/close_hover.png \
    sources/close_pressed.png \
    sources/feedback.png \
    sources/feedback_hover.png \
    sources/feedback_pressed.png \
    sources/func1.png \
    sources/func2.png \
    sources/func3.png \
    sources/func4.png \
    sources/func5.png \
    sources/func6.png \
    sources/func7.png \
    sources/func8.png \
    sources/logo.png \
    sources/logo1.png \
    sources/logo2.png \
    sources/menu.png \
    sources/menu_hover.png \
    sources/menu_pressed.png \
    sources/min.png \
    sources/min_hover.png \
    sources/min_pressed.png \
    sources/power.png \
    sources/score.png \
    sources/security_1.png \
    sources/security_2.png \
    sources/security_3.png \
    sources/security_4.png \
    sources/skin.png \
    sources/skin_hover.png \
    sources/skin_pressed.png \
    sources/xx.png \
    sources/xxxx.png \
    sources/logo.ico \
    sources/html/index.html \
    sources/index.html \
    sources/logo1.rc \
    sources/sys_test.ts \
    sources/score.gif \
    sources/html/picture/1.jpg \
    sources/html/picture/new_11.jpg \
    sources/html/picture/new_13.jpg \
    sources/html/picture/new_15.jpg \
    sources/html/picture/new_6.jpg \
    sources/html/picture/new_8.jpg \
    sources/html/picture/new_9.jpg \
    sources/img/skin/15.jpg \
    sources/img/skin/15_big.jpg \
    sources/img/skin/16.jpg \
    sources/img/skin/16_big.jpg \
    sources/img/skin/17.jpg \
    sources/img/skin/17_big.jpg \
    sources/img/skin/18.jpg \
    sources/img/skin/18_big.jpg \
    sources/img/skin/19.jpg \
    sources/img/skin/19_big.jpg \
    sources/img/skin/20.jpg \
    sources/img/skin/20_big.jpg \
    sources/img/skin/21.jpg \
    sources/img/skin/21_big.jpg \
    sources/img/skin/22.jpg \
    sources/img/skin/22_big.jpg \
    sources/img/skin/23.jpg \
    sources/img/skin/23_big.jpg \
    sources/1_big.jpg \
    sources/3_big.jpg \
    sources/4_big.jpg \
    sources/5_big.jpg \
    sources/6_big.jpg \
    sources/7_big.jpg \
    sources/cpu1.jpg \
    sources/cpu2.jpg \
    sources/disk1.jpg \
    sources/disk2.jpg \
    sources/disk3.jpg \
    sources/disk4.jpg \
    sources/net1.jpg \
    sources/net2.jpg \
    sources/net3.jpg \
    sources/net4.jpg \
    sources/os1.jpg \
    sources/os2.jpg \
    sources/os3.jpg \
    sources/html/picture/new_1.png \
    sources/html/picture/new_10.png \
    sources/html/picture/new_12.png \
    sources/html/picture/new_14.png \
    sources/html/picture/new_16.png \
    sources/html/picture/new_2.png \
    sources/html/picture/new_3.png \
    sources/html/picture/new_4.png \
    sources/html/picture/new_5.png \
    sources/html/picture/new_7.png \
    sources/img/skin/12_big.png \
    sources/img/skin/13.png \
    sources/img/skin/13_big.png \
    sources/img/skin/14.png \
    sources/img/skin/14_big.png \
    sources/img/skin/9.png \
    sources/img/11 \
    sources/img/loading.png \
    sources/2_big.png \
    sources/8_big.png \
    sources/arrow_down.png \
    sources/check.png \
    sources/close.png \
    sources/close_hover.png \
    sources/close_pressed.png \
    sources/feedback.png \
    sources/feedback_hover.png \
    sources/feedback_pressed.png \
    sources/func1.png \
    sources/func2.png \
    sources/func3.png \
    sources/func4.png \
    sources/func5.png \
    sources/func6.png \
    sources/func7.png \
    sources/func8.png \
    sources/logo.png \
    sources/logo1.png \
    sources/logo2.png \
    sources/menu.png \
    sources/menu_hover.png \
    sources/menu_pressed.png \
    sources/min.png \
    sources/min_hover.png \
    sources/min_pressed.png \
    sources/power.png \
    sources/score.png \
    sources/security_1.png \
    sources/security_2.png \
    sources/security_3.png \
    sources/security_4.png \
    sources/skin.png \
    sources/skin_hover.png \
    sources/skin_pressed.png \
    sources/xx.png \
    sources/xxxx.png \
    sources/logo.ico \
    sources/html/index.html \
    sources/index.html \
    sources/logo1.rc \
    sources/sys_test.ts
