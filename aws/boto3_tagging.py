# -*- coding: utf-8 -*-

import boto3

# Get resource
# s3 = boto3.resource('s3')
#
# # S3 object
# obj = s3.Object(bucket_name='s3-obj-tagging-test', key='test-s3-file')
#
# print (obj.bucket_name)
# print (obj.key)

# print (obj.e_tag)

# Upload a new file
# data = open('test-s3-file', 'rb')
# s3.Bucket('s3-obj-tagging-test').put_object(Key='test-s3-file', Body=data)


client = boto3.client('s3')

resp = client.put_object(Body='123',
                         Bucket='s3-obj-tagging-test',
                         Key='put-obj-test',
                         Tagging='two=2&Project=X'
                         )

# response = client.get_object_tagging(Bucket='s3-obj-tagging-test',
#                                      Key='test-s3-file',
#                                      VersionId='eVQkyDiNOUF.ipmMi7Tawtk5GQslpHtK')
# print (response)

# response = client.delete_object_tagging(Bucket='s3-obj-tagging-test',
#                                         Key='test-s3-file',
#                                         VersionId='jk.ArjftY0Htz7weCNXNhX34YmSzJo73')
# print response

# response = client.put_object_tagging(Bucket='s3-obj-tagging-test',
#                                      Key='test-s3-file',
#                                      Tagging={
#                                         'TagSet': [
#                                             { 'Key': 'Owner1', 'Value': '1'}
#                                         ]
#                                      })
# print response

# response = client.get_object_tagging(Bucket='s3-obj-tagging-test',
#                                      Key='test-s3-file')
# print (response)

# response = client.put_object_tagging(Bucket='s3-obj-tagging-test',
#                                      Key='test',
#                                      Tagging={
#                                         'TagSet': [
#                                             { 'Key': 'first1', 'Value': '1'},
#                                             { 'Key': 'second2', 'Value': '2'}
#                                         ]
#                                      })
# print response
#
# response = client.get_object_tagging(Bucket='s3-obj-tagging-test', Key='test')
# print (response)
