# -*- coding: utf-8 -*-

import requests
from awsauth import S3Auth
from mimetools import Message
from StringIO import StringIO
import json

authv2 = S3Auth('admin',
                'admin',
                '10.9.34.206:8000')


def delete_version(bucket, obj, versionid):
    url = 'http://10.9.34.206:8000/' + bucket + '/' + obj
    resp = requests.delete(url=url,
                           params={'versionId': versionid},
                           auth=authv2)
    print resp.headers


delete_version('s3-obj-tagging-test', 'test', 'p6.N0kls2WMjq15h69.0luDUJANx0Ij')
