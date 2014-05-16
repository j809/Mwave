import json
import urllib
import sys

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

set_proc_name('Mwave_cricscorereader')

matches_url = "http://cricscore-api.appspot.com/csa"
try:
	matches_data = json.loads(urllib.urlopen(matches_url).read())
	if(sys.argv[1][0:5]=="build") : 
		print "Current Matches"
		print "-------------------"
		i=0
		for j in matches_data:
			print str(i+1)+" . "+matches_data[i]['t2'].encode('utf-8')+" V/S "+matches_data[i]['t1'].encode('utf-8')
			i=i+1
		print "\nEnter number to get Match status..."
	else : 
		match_id=int(sys.argv[1])
		score_url = "http://cricscore-api.appspot.com/csa?id=" +str(matches_data[match_id-1]['id'])
		try:
			score_data = json.loads(urllib.urlopen(score_url).read())
			print "Match Status"
			print "--------------------"
			print score_data[0]['de'].encode('utf-8')
			print score_data[0]['si'].encode('utf-8')
		except:
			print "Error in fetching score!"
except:
	print "Error in fetching data!"
