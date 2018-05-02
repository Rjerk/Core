#!/bin/bash

curl -XDELETE 'http://localhost:9200/rgw-gold-6120da83' \
    -H 'Content-Type: application/json'
