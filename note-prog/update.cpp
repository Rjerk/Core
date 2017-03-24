#include "note.h"

int main(int argv, char** argc)
{
    string file = argc[1];
    Note update(file);
    if (!update.CheckNoteName()) {
        cerr << "Unknown File!" << endl;
        exit(1);
    }
    update.AppendNote();
    update.GetFileLineNum();
    return 0;
}
