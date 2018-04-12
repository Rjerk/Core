# -*- coding: utf-8 -*-

import requests
import hashlib
from awsauth import S3Auth
from base64 import encodestring

authv2 = S3Auth('tagger',
                'tagger',
                '10.9.34.206:8000')


def get_obj_tag(bucket, obj, versionid=None):
    url = 'http://10.9.34.206:8000/' + bucket + '/' + obj + '?tagging'
    res = requests.get(url,
                       params={'versionId': versionid},
                       auth=authv2)
    print "status:  ", res.status_code
    print "content: ", res.content
    print "headers: ", res.headers
    print ""


def put_obj_tag(bucket, obj, versionid=None):
    url = 'http://10.9.34.206:8000/' + bucket + '/' + obj + '?tagging'
    tagset = '<Tagging><TagSet>' \
           + '<Tag><Key>Project</Key><Value>X</Value></Tag>' \
           + '<Tag><Key>Hello00</Key><Value>World</Value></Tag>' \
           + '</TagSet></Tagging>'
    # calculate content-md5
    md5 = encodestring(hashlib.md5(tagset.encode('utf-8').strip()).digest()).strip()

    res = requests.put(url,
                       params={'versionId': versionid},
                       data=tagset,
                       #headers={'Content-MD5': '123'},
                       auth=authv2)
    print "status:  ", res.status_code
    print "content: ", res.content
    print "headers: ", res.headers
    print ""


def delete_obj_tag(bucket, obj, versionid=None):
    url = 'http://10.9.34.206:8000/' + bucket + '/' + obj + '?tagging'
    res = requests.delete(url,
                          params={'versionId': versionid},
                          auth=authv2)
    print "status:  ", res.status_code
    print "content: ", res.content
    print "headers: ", res.headers
    print ""


if __name__ == '__main__':
    put_obj_tag('tag-test', 'test', 'iKRL.3QmodCsf2yvq3Mh4v.H93fPvlr')
    put_obj_tag('tag-test', 'test')
    # put_obj_tag('s3-obj-tagging-test', 'test', 'xqLCfmLBqQ9eYr7BpfJ9yhEOcOwgw1c')
    # get_obj_tag('tag-test', 'test') # , 'iKRL.3QmodCsf2yvq3Mh4v.H93fPvlr')
    get_obj_tag('tag-test', 'test')
    # delete_obj_tag('s3-obj-tagging-test', 'test', 'xqLCfmLBqQ9eYr7BpfJ9yhEOcOwgw1c')
    # put_obj_tag('s3-tagging-test', 'test', 'nH.blPpZwlrX3yklMJqjrbeccU1HhWSP')
    # delete_obj_tag('s3-tagging-test', 'test', 'nH.blPpZwlrX3yklMJqjrbeccU1HhWSP')
