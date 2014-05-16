import serial
import sys
import os

def set_proc_name(newname):
    from ctypes import cdll, byref, create_string_buffer
    libc = cdll.LoadLibrary('libc.so.6')
    buff = create_string_buffer(len(newname)+1)
    buff.value = newname
    libc.prctl(15, byref(buff), 0, 0, 0)

def get_proc_name():
    from ctypes import cdll, byref, create_string_buffer
    libc = cdll.LoadLibrary('libc.so.6')
    buff = create_string_buffer(128)
    # 16 == PR_GET_NAME from <linux/prctl.h>
    libc.prctl(16, byref(buff), 0, 0, 0)
    return buff.value

set_proc_name('Mwave_portreader')

ser = serial.Serial('/dev/ttyUSB0',4800,timeout=1)
x='A'
x1='A'
y='n'
while True:
	f_read=open('room_automation.txt','r')
	y=f_read.read()
	f_read.close()
	f_read=open('room_automation.txt','w')
	f_read.write('n')
	f_read.close()
	if y!='n':
		ser.write(y)
		print y
	x=ser.read()
	if x!=x1:
		f=open('demo.txt','w')
		f.write(x)
		f.close()
		x1=x
		print x1
