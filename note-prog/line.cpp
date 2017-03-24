#include "note.h"

int main(int argc, char** argv)
{
    assert(argc == 2);
    string file(argv[1]);
    Note line(file);
    if (!line.CheckNoteName()) {
        cerr << "Unknown Name!" << endl;
        exit(1);
    }
    line.WithLineVersion();

    return 0;
}
