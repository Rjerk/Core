# -*- coding: utf-8 -*-

import requests
import hashlib
from awsauth import S3Auth
from base64 import encodestring
import os


endpoint = '127.0.0.1:8002'
access_key = 'tester'
secret_key = 'tester'


authv2 = S3Auth(access_key,
                secret_key,
                endpoint)

resp = requests.get(url='http://127.0.0.1:8002/es-test',
                    params={"query": "name==obj1"},
                    auth=authv2)

print resp.status_code
print resp.content
print resp.headers
