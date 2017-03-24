#include <iostream>
using namespace std;

extern char** environ;

int main()
{
    char** var;
    for (var = environ; *var != NULL; ++var)
        cout << *var << endl;

    return 0;
}
