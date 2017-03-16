#include "client.h"
#include <iostream>

int main()
{
    const int port = 4000;
    const int rep = 10;
    Client test1("127.0.0.1", port, rep, 15, 100, 1);
    test1.runTest();
	/*
    Client test2("127.0.0.1", port, rep, 15, 100, 2);
    test2.runTest();
    Client test3("127.0.0.1", port, rep, 15, 100, 3);
    test3.runTest();
    Client test4("127.0.0.1", port, rep, 30, 50, 1);
    test4.runTest();
    Client test5("127.0.0.1", port, rep, 30, 50, 2);
    test5.runTest();
    Client test6("127.0.0.1", port, rep, 30, 50, 3);
    test6.runTest();
    Client test7("127.0.0.1", port, rep, 60, 25, 1);
    test7.runTest();
    Client test8("127.0.0.1", port, rep, 60, 25, 2);
    test8.runTest();
    Client test9("127.0.0.1", port, rep, 60, 25, 3);
    test9.runTest();
    Client test10("127.0.0.1", port, rep, 100, 15, 1);
    test10.runTest();
    Client test11("127.0.0.1", port, rep, 100, 15, 2);
    test11.runTest();
    Client test12("127.0.0.1", port, rep, 100, 15, 3);
    test12.runTest();
	*/
	return 0;
}
