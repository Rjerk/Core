# -*- coding: utf-8 -*-

import boto.s3.connection

conn = boto.s3.connection.S3Connection(aws_access_key_id='admin',
                                       aws_secret_access_key='admin',
                                       is_secure=False,
                                       port=8000,
                                       host='10.9.34.206:8000'
                                       )

resp = conn.make_request("GET", 's3-obj-tagging-test', 'test', query_args='tagging')

print resp.status
print resp.headers
print resp.content
