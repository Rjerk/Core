# -*- coding: utf-8 -*-

import requests
from awsauth import S3Auth

authv2 = S3Auth('admin',
                'admin',
                '10.9.34.206:8000')


def get_version_id(bucket, obj):
    url = 'http://10.9.34.206:8000/' + bucket + '/' + obj
    resp = requests.head(url=url,
                         auth=authv2)
    if 'x-amz-version-id' in resp.headers:
        print "current versionid: ", resp.headers['x-amz-version-id']
    else:
        print "versionid never be set."


get_version_id('tag-test', 'test')
