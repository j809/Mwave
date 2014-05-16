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

set_proc_name('Mwave_dict_reader')

try:
	state = sys.argv[2]
except:
	print "Please enter a word!"
	sys.exit()
dict_url = "http://api.wordnik.com:80/v4/word.json/"+sys.argv[1]+"/definitions?-limit=200&includeRelated=false&sourceDictionaries=webster&useCanonical=true&includeTags=true&api_key=702e37abc0f151ae6780f0936c305580a0fc1808884630460"
dict_data = json.loads(urllib.urlopen(dict_url).read())
i=0
#headingflag=0
for j in dict_data:
	if(j==0):
		prevPOS=dict_data[i]['partOfSpeech']
		print dict_data[i]['partOfSpeech'].title().encode('utf-8')
        	print "-------------------\n"
	else:
		try:
			if(dict_data[i]['seqString']=="1."):
				print "\n"+dict_data[i]	['partOfSpeech'].title().encode('utf-8')
                		print "-------------------\n"
		except:
			junk=0
	'''
        	headingflag=1
        elif(headingflag==0):
		prevPOS=dict_data[i]['partOfSpeech']
                print "\n"+dict_data[i]['partOfSpeech'].title().encode('utf-8')
                print "-------------------\n"
                headingflag=1
	elif(headingflag==1 and dict_data[i]['seqString']):
		headingflag=0
	'''
	try:
		print "  "+dict_data[i]['seqString']+" "+dict_data[i]['text'].replace("\n"," ").replace("<ex>","").replace("</ex>","").replace("<xref>","").replace("</xref>","").replace("<altname>","").replace("</altname>","").replace("<ant>","").replace("</ant>","").encode('utf-8')
	except:
		print "\t"+dict_data[i]['text'].replace("\n"," ").replace("<ex>","").replace("</ex>","").replace("<xref>","").replace("</xref>","").replace("<altname>","").replace("</altname>","").replace("<ant>","").replace("</ant>","").encode('utf-8')
	i=i+1
	try:
		print "\teg. "+dict_data[i]['citations'][0]['cite'].replace("\n"," ").replace("<ex>","").replace("</ex>","").replace("<xref>","").replace("</xref>","").replace("<altname>","").replace("</altname>","").replace("<ant>","").replace("</ant>","").lower().encode('utf-8')
	except : continue
		
#except:
	#print "Error getting data!"
