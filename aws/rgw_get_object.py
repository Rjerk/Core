# -*- coding: utf-8 -*-

import requests
from awsauth import S3Auth

authv2 = S3Auth('admin',
                'admin',
                '10.9.34.206:8000')

def get_object(bucket, obj, versionid='null'):
    url = 'http://10.9.34.206:8000/' + bucket + '/' + obj
    resp = requests.get(url=url,
                        params={'versionId': versionid},
                        auth=authv2)
    print resp.status_code
    print resp.content
    print resp.headers


get_object('tag-test', 'bobo')
