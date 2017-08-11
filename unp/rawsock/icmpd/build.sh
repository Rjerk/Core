g++ client.cpp  ../../unp.cpp ../../udp_client.cpp ../../write_fd.cpp ../../sock_bind_wild.cpp -o client
g++ icmpd.cpp ../../unp.cpp ../../udp_client.cpp ../../sock_bind_wild.cpp ../../write_fd.cpp  ../../read_fd.cpp ../../sock_get_port.cpp -o icmpd
