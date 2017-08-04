#!/bin/bash

./serv 8888 &

./cli 127.0.0.1 8888 < ./tmpcap > ./temp.1 &
./cli 127.0.0.1 8888 < ./tmpcap > ./temp.2 &
./cli 127.0.0.1 8888 < ./tmpcap > ./temp.3 &
./cli 127.0.0.1 8888 < ./tmpcap > ./temp.4 &
./cli 127.0.0.1 8888 < ./tmpcap > ./temp.5 &

wait

