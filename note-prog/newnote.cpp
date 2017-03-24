#include "note.h"

int main(int argc, char** argv)
{
    assert(argc == 2);
    string file = argv[1];
    Note newnote(file);
    newnote.NewNote();

    return 0;
}
