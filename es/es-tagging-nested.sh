#!/bin/bash

#                                   index
curl -XPUT 'http://localhost:9200/rgw-gold-120fc766' -d '
{
    "mappings": {
        "object": {
            "properties": {
                "user": {
                    "type": "nested"
                }
            }
        }
    }
}' -H 'Content-Type: application/json'
