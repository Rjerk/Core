g++ tcpcli01.cpp sourceroute.cpp ../unp.cpp ../str_cli.cpp ../host_serv.cpp ../readline.cpp -o cli
g++ tcpserv01.cpp sourceroute.cpp ../unp.cpp ../sig_chld.cpp ../str_echo.cpp ../host_serv.cpp -o serv
