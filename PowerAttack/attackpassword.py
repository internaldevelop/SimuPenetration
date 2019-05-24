#!/usr/bin/env python
#coding=gbk 
import crypt

# ��ȡshadow�ļ�����������user_pwfile
user_pwfile = "/etc/shadow"
# �����ȡ���뺯��get_pw()
def get_pw(u_p):
    # �����û����������Ӧ���ֵ�
    user_pw = {}
    # ��ȡshadow�ļ�
    f = open(u_p,'r')
    userline = f.readlines()
    f.close()
    for l in userline:
        # ɸѡ��ϵͳ�û�
        if len(l.split(":")[1]) > 3:
            # ���û�����������ֵ�user_pw
            user_pw[l.split(":")[0]] = l.split(":")[1]
    return user_pw

# ��ȡ�����ֵ伯�ļ�������dicti
dicti = "/home/ljz/passwd.txt"
# �����ȡ�����ֵ伯����
def get_dic(g_d):
    f = open(g_d,'r')
    mw_dic = f.readlines()
    f.close()
    return mw_dic

# ����������
def main():
    # ���������û��������루�ֵ䣩
    user_passwd = get_pw(user_pwfile)
    # �������б����ֵ伯
    mw_dic = get_dic(dicti)
    # ѭ�����û�����
    for u in user_passwd:
        # ���ÿ���û�����
        passwd = user_passwd[u]
        # ���ÿ���û���ֵ
        salt = "$6$" + passwd.split("$")[2]
        for pw_mv in mw_dic:
            #rstrip()ȥ�����У�\n��
            if passwd == crypt.crypt(pw_mv.rstrip(),salt):
                print("�û�����%s  ���룺%s" %(u,pw_mv.rstrip()))

if __name__ == "__main__":
    main()
