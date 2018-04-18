# -*- coding: utf-8 -*-

import requests
import hashlib
from awsauth import S3Auth
from base64 import encodestring
import os


authv2 = S3Auth('ACCESS-KEY',
                'SECRET-KEY',
                's3.amazonaws.com')


def get_obj_tag(bucket, obj, versionid='null'):
    url = 'http://' + bucket + '.s3.amazonaws.com/' + obj + '?tagging'
    res = requests.get(url,
                       # params={'versionId': versionid},
                       auth=authv2)
    print "status:  ", res.status_code
    print "content: ", res.content
    print "headers: ", res.headers
    print ""


def put_obj_tag(bucket, obj, versionid='null'):
    url = 'http://' + bucket + '.s3.amazonaws.com/' + obj + '?tagging'
    tagset = '<Tagging><TagSet>' \
        + '<Tag><Key>Hello</Key><Value>World</Value></Tag>' \
        + '</TagSet></Tagging>'

    # calculate content-md5
    md5 = encodestring(hashlib.md5(tagset.encode('utf-8').strip()).digest()).strip()

    res = requests.put(url,
                       params={'versionId': versionid},
                       data=tagset,
                       headers={'Content-MD5': md5},
                       auth=authv2)
    print "status:  ", res.status_code
    print "content: ", res.content
    print "headers: ", res.headers
    print ""


def delete_obj_tag(bucket, obj, versionid='null'):
    url = 'http://' + bucket + '.s3.amazonaws.com/' + obj + '?tagging'
    res = requests.delete(url,
                          params={'versionId': versionid},
                          auth=authv2)
    print "status:  ", res.status_code
    print "content: ", res.content
    print "headers: ", res.headers
    print ""


def put_obj(bucket, obj):
    url = 'http://' + bucket + '.s3.amazonaws.com/' + obj
    res = requests.put(url,
                       data='123',
                       headers={'Content-Length': 3, 'x-amz-tagging': 'Project=ZZ'},
                       auth=authv2)
    print "status:  ", res.status_code
    print "content: ", res.content
    print "headers: ", res.headers
    print ""


def get_obj(bucket, obj, versionId='OZKXvzV.BOwodM6NAdFgW4yyF9L_arcV'):
    url = 'http://' + bucket + '.s3.amazonaws.com/' + obj + '?versionId=' + versionId
    print url
    res = requests.get(url,
                       auth=authv2)
    print "status:  ", res.status_code
    print "content: ", res.content
    print "headers: ", res.headers
    print ""


if __name__ == '__main__':
    # get_obj('s3-obj-tagging-test', 'test')
    # put_obj('s3-obj-tagging-test', 'test')
    # get_obj_tag('s3-obj-tagging-test', 'test', 'R_qyXkhmw91.a4v815o_MkxJ_ZOn6CD.')
    # delete_obj_tag('s3-obj-tagging-test', 'test')
    put_obj_tag('s3-obj-tagging-test', 'test')
    # get_obj_tag('s3-obj-tagging-test', 'test', 'LbtHetPVnp6WQaIazqf17TQ_56rmHfQn')
    # delete_obj_tag('s3-obj-tagging-test', 'test', 'nH.blPpZwlrX3yklMJqjrbeccU1HhWSP')
