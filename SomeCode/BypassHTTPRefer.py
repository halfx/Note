#!/usr/bin/env python
# -*- coding: utf-8 -*-

def download1(provice, city, district, foutName):
    cj = CookieJar()
    url = "http://www.XXX.com/api/xxxxx?&t=2"
    provice_uri = "&provice=" + urllib2.quote(unicode(provice,"gbk").encode("utf-8"))
    city_uri = "&city=" + urllib2.quote(unicode(city,"gbk").encode("utf-8"))
    district_uri = "&district=" + urllib2.quote(unicode(district,"gbk").encode("utf-8"))
    
    url = url + provice_uri + city_uri + district_uri;
    print url
    httplib.HTTPConnection.debuglevel = 1
    request = urllib2.Request(url)

    request.add_header("Accept", "*/*")
    request.add_header('Referer', "http://www.XXX.com")

    request.add_header("Accept-Language", "zh-cn")
    request.add_header("User-Agent", "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; Trident/4.0; MyIE9; BTRS123646; .NET CLR 2.0.50727; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729)")
    request.add_header("Accept-Encoding", "gzip, deflate, sdch")
    request.add_header("Host", "www.XXX.com")
    request.add_header("Connection", "Keep-Alive")
    opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
    f = opener.open(request).read()
    fout_name = "download//"+str(foutName)+".txt"
    count = 1
    for f_byte in f:
        print repr(f_byte)
        #print f_byte
        count += 1
        if count == 7:
            break
    if f[:6] == '\x1f\x8b\x08\x00\x00\x00':
        content = gzip.GzipFile(fileobj = cStringIO.StringIO(f)).read()
        print fout_name
        fout = open(fout_name,"w")
        fout.write(content)
        fout.close()
    