#include "note.h"
#include <string>
#include <cstdlib>

int main(int argc, char** argv)
{
    assert(argc == 3);
    string file = argv[1];
    unsigned int deltline = stoi(string(argv[2]));
    Note deleteLine(file, deltline);
    deleteLine.DeleteSpecificLine();

    return 0;
}
