import feedparser
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

set_proc_name('Mwave_newsreader')

if(sys.argv[1]=="build"):
	#Default
	url = 'http://news.google.com/news?pz=1&cf=all&ned=in&hl=en&output=rss'
else:
#for world news
#url = 'http://news.google.com/news/feeds?pz=1&cf=all&ned=in&hl=en&topic=w&output=rss'

#add &topic=<something> for local(india)=n,world=w,business=b,tech=tc,entertainment=e,sports=s,science=snc,health=m,spotlight=ir
	url = 'http://news.google.com/news?pz=1&cf=all&ned=in&hl=en&topic='+sys.argv[1]+'&output=rss'
i=0;
feed = feedparser.parse(url)
for post in feed.entries:
	i=i+1
	print " "+str(i)+". "+post.title.encode('utf8')
