# -*- coding: utf-8 -*-

import requests
from awsauth import S3Auth


authv2 = S3Auth('tester',
                'tester',
                '127.0.0.1:8002')


def get_an_elasticsearch_query(bucket, query_expr=''):
    # url = 'http://127.0.0.1:8000/' + bucket + '?query=' + query_expr
    url = 'http://127.0.0.1:8002/buck?query=name==bobo'
    ret = requests.get(url,
                       auth=authv2)
    print ret.status_code
    print ret.content
    print ret.headers
    print ""


def get_custom_metadata_bucket_config(bucket):
    url = 'http://127.0.0.1:8000/' + bucket + '?mdsearch'
    ret = requests.get(url,
                       auth=authv2)
    print ret.status_code
    print ret.content
    print ret.headers
    print ""


def post_custom_metadata_bucket_config(bucket):
    url = 'http://127.0.0.1:8000/' + bucket + '?mdsearch'
    ret = requests.post(url,
                        headers={'x-amz-meta-search': 'x-amz-meta-year;int,'
                                                      'x-amz-meta-release-date;date,'
                                                      ' x-amz-meta-title;string'},
                        auth=authv2)
    print ret.status_code
    print ret.content
    print ret.headers
    print ""


def delete_custom_metadata_bucket_config(bucket):
    url = 'http://127.0.0.1:8000/' + bucket + '?mdsearch'
    ret = requests.delete(url,
                          auth=authv2)
    print ret.status_code
    print ret.content
    print ret.headers
    print ""


if __name__ == '__main__':
    get_an_elasticsearch_query('buck')
    # post_custom_metadata_bucket_config('buck')
    # get_custom_metadata_bucket_config('buck')
