#!/bin/bash

curl -XGET 'http://localhost:9200/_search?pretty' -d '{}' -H 'Content-Type: application/json'
