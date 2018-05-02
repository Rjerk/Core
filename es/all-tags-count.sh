#!/bin/bash

curl -XGET 'http://localhost:9200/_search?pretty' -d '
{
    "aggs": {
        "tag-count": {
            "nested": {
                "path": "tagging"
            }
        }
    }
}'
