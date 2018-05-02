#!/bin/bash

curl -XGET 'http://localhost:9200/_search?pretty' -d '
{
    "query": {
        "bool": {
            "must": [
                {
                    "nested": {
                        "path": "tagging",
                        "query": {
                            "bool": {
                                "must": [
                                    { "match": {"tagging.key": "Company"} },
                                    { "match": {"tagging.value": "UMCloud"} }
                                ]
                            }
                        }
                    }
                },
                {
                    "nested": {
                        "path": "tagging",
                        "query": {
                            "bool": {
                                "must": [
                                    { "match": {"tagging.key": "Location"} },
                                    { "match": {"tagging.value": "Beijing"} }
                                ]
                            }
                        }
                    }
                }
            ]
        }
    }
}'
