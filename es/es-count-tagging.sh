#!/bin/bash

curl -XGET 'http://localhost:9200/rgw-gold-6120da83/_count?pretty' -d '
{
    "query": {
        "nested": {
            "path": "tagging",
            "query": {
                "term": { "tagging": "tagging.key"}
            }
        }
    }
}' -H 'Content-Type: application/json'
