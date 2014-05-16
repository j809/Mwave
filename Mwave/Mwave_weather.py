import pywapi
import string
import re
import socket
import urllib2
import os
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

set_proc_name('Mwave_weather')

__version__ = "0.3.6"

try:
    # Python 3 imports
    from urllib.request import urlopen
    from urllib.parse import quote
    from urllib.parse import urlencode
    from urllib.error import URLError
    xrange = range
    unicode = str
except ImportError:
    from urllib2 import urlopen
    from urllib import quote
    from urllib import urlencode
    from urllib2 import URLError
import sys
import re
from math import pow
from xml.dom import minidom
import json

try:
    from unidecode import unidecode
except ImportError:
    pass

GOOGLE_COUNTRIES_URL = 'http://www.google.com/ig/countries?output=xml&hl=%s'
GOOGLE_CITIES_URL    = 'http://www.google.com/ig/cities?output=xml&' + \
                       'country=%s&hl=%s'

YAHOO_WEATHER_URL    = 'http://xml.weather.yahoo.com/forecastrss/%s_%s.xml'
YAHOO_WEATHER_NS     = 'http://xml.weather.yahoo.com/ns/rss/1.0'

NOAA_WEATHER_URL     = 'http://www.weather.gov/xml/current_obs/%s.xml'

WEATHER_COM_URL      = 'http://xml.weather.com/weather/local/%s?' + \
                       'par=1138276742&key=15ee9c789ccd70f5&' + \
                       'unit=%s&dayf=5&cc=*'

LOCID_SEARCH_URL     = 'http://xml.weather.com/search/search?where=%s'

WOEID_SEARCH_URL     = 'http://query.yahooapis.com/v1/public/yql'
WOEID_QUERY_STRING   = 'select line1, line2, line3, line4, ' + \
                       'woeid from geo.placefinder where text="%s"'

def get_loc_id_from_weather_com(search_string):
    try:
        search_string = unidecode(search_string)
    except NameError:
        pass

    url = LOCID_SEARCH_URL % quote(search_string)
    try:
        handler = urlopen(url)
    except URLError:
        return {'error': 'Could not connect to server'}
    if sys.version > '3':
        # Python 3
        content_type = dict(handler.getheaders())['Content-Type']
    else:
        # Python 2
        content_type = handler.info().dict['content-type']
    try:
        charset = re.search('charset\=(.*)', content_type).group(1)
    except AttributeError:
        charset = 'utf-8'
    if charset.lower() != 'utf-8':
        xml_response = handler.read().decode(charset).encode('utf-8')
    else:
        xml_response = handler.read()
    dom = minidom.parseString(xml_response)
    handler.close()

    loc_id_data = {}
    try:
        num_locs = 0
        for loc in dom.getElementsByTagName('search')[0].getElementsByTagName('loc'):
            loc_id = loc.getAttribute('id')  # loc id
            place_name = loc.firstChild.data  # place name
            loc_id_data[num_locs] = (loc_id, place_name)
            num_locs += 1
        loc_id_data['count'] = num_locs
    except IndexError:
        error_data = {'error': 'No matching Location IDs found'}
        return error_data
    finally:
        dom.unlink()

    return loc_id_data

## Ip address
my_ip=urllib2.urlopen("http://myip.dnsdynamic.org/").read()
st="http://api.hostip.info/get_html.php?ip="+my_ip
f = urllib2.urlopen(st)
data = f.read()
#print data
f.close()
city_name=" "
#data = "Country: INDIA (IN)\nCity: Surat\nIP: 123.201.110.122"
#print sys.argv[1]
if sys.argv[1][0:5]=="build":
    i=0
    while data[i]!=':':
        i=i+1
    i=i+2
    if data[i]=='I':
        while data[i]!=':':
            i=i+1
        i=i+2
        while data[i]!='\n':
            city_name+=data[i]
            i=i+1
        city_name=str(city_name)
else:
    city_name=" "+sys.argv[1]

try:
    loc_id_data = get_loc_id_from_weather_com(city_name[1:])
    strn="(.*), India"
    compiled = re.compile(strn)

    my_loc_id=loc_id_data[0][0]
    for i in xrange(loc_id_data['count']):
            if compiled.match(loc_id_data[i][1]):
                    my_loc_id=loc_id_data[i][0]
                    break

    yahoo_result = pywapi.get_weather_from_yahoo(my_loc_id,'metric')
    try:
         print "It is ".encode('utf-8') + string.lower(yahoo_result['condition']['text']).encode('utf-8') + " and ".encode('utf-8') + yahoo_result['condition']['temp'].encode('utf-8') + "*C in ".encode('utf-8') + yahoo_result['location']['city'].encode('utf-8') + ", India.".encode('utf-8')+yahoo_result['condition']['code'].encode('utf-8')
    except:
            i=0
except:
    i=0
