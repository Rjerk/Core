#!/bin/bash

g++ main.cpp sntp_proc.cpp sock_set_wild.cpp sock_set_addr.cpp ../mcast_join.cpp ../family_to_level.cpp ../../unp.cpp ../../ioctl/get_ifi_info.cpp ../../udp_client.cpp -o ssntp
