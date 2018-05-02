#!/bin/bash

curl -XGET 'http://localhost:9200/_count?pretty' -d '
{
    "query": {
        "bool": {
            "must": {
                "nested": {
                    "path": "tagging",
                    "query": {
                        "exists": {
                            "field": "tagging"
                        }
                    }
                }
            }
        }
    }
}'
