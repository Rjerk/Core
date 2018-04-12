# -*- coding: utf-8 -*-

import requests
from awsauth import S3Auth
from bs4 import BeautifulSoup


authv2 = S3Auth('admin',
                'admin',
                '10.9.34.206:8000')


def get_bucket_versioning(bucket):
    url = 'http://10.9.34.206:8000/' + bucket + '/' + '?versioning'
    res = requests.get(url=url,
                       auth=authv2)
    soup = BeautifulSoup(res.content, "lxml")
    if res.status_code == 200:
        tag = soup.find('status')
        if tag is not None:
            status = tag.get_text(strip=True)
            return status
        else:
            print "Versioning state has never been set on the bucket."
            return None
    else:
        print "get_bucket_versioning error :", soup.find('code').get_text(strip=True)
        assert(res.status_code == 200)


def bucket_versioning(bucket, enable=None):
    url = 'http://10.9.34.206:8000/' + bucket + '/' + '?versioning'
    if enable is False:
        data = '<VersioningConfiguration xmlns="http://s3.amazonaws.com/doc/2006-03-01/">' \
            + '<Status>Suspended</Status>' \
            + '</VersioningConfiguration>'
    else:
        data = '<VersioningConfiguration xmlns="http://s3.amazonaws.com/doc/2006-03-01/">' \
            + '<Status>Enabled</Status>' \
            + '</VersioningConfiguration>'

    res = requests.put(url=url,
                       data=data,
                       auth=authv2)
    if res.status_code != 200:
        print res.status_code
        print res.content
        print res.headers
    else:
        if enable:
            print "Enable bucket versioning"
        else:
            print "Suspend bucket versioning"


status = get_bucket_versioning('tag-test')
if status is None or status == "Suspended":
    bucket_versioning('tag-test', True)

print "Current versioning: ", get_bucket_versioning('tag-test')

