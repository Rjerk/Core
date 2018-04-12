# -*- coding: utf-8 -*-

import boto3

s3 = boto3.resource('s3')

bucket_versioning = s3.BucketVersioning('s3-obj-tagging-test')
print "Current: ", bucket_versioning.status

if bucket_versioning.status == "Suspended":
    bucket_versioning.enable()
    print "Versioning: ", bucket_versioning.status
