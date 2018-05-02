#!/bin/bash

curl -XGET 'http://localhost:9200/_search?pretty' -d '
{
    "aggs": {
        "count": {
            "nested": {
                "path": "tagging"
            },
            "aggs": {
                "tagging-key-value": {
                    "terms": {
                        "field": "tagging.key"
                    },
                    "aggs": {
                        "tagging-value": {
                            "terms": {
                                "field": "tagging.value"
                            }
                        }
                    }
                }
            }
        }
    }
}'
