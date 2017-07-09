#!/usr/bin/env python
import paramiko
import sys

def error_handle(stderr,message):
    error_msg = stderr.readlines()
    if not error_msg:
        return
    else:
        print(error_msg)
        print(message)

if __name__ == '__main__':
    ssh = paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh.connect('192.168.7.2', username='cwilliamson')

    #Put the executable in the remote
    ftp = ssh.open_sftp()
    ftp.put('ROBO','executables/DEBUG_FILE')

    stdin, stdout, stderr = ssh.exec_command("cd executables && chmod 777 DEBUG_FILE")
    error_handle(stderr,"TEST")

    stdin, stdout, stderr = ssh.exec_command("gdbserver 192.168.7.2:1234 executables/DEBUG_FILE")
    print(stdout.readlines())
    error_handle(stderr,"")

