#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <utility>
#include <iomanip>
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ostringstream;
using std::ios_base;
using std::vector;
using std::pair;

class Note {
public:
    Note() = default;
    Note(const string& name) : fname(name) {}
    Note(const string& name, unsigned int li): fname(name), deltline(li) {}
    ~Note() {};
    void Process();
    void NewNote();
    void ReadNote();
    void GetFileLineNum();
    void AppendNote();
    void StoreNoteName();
    bool CheckNoteName();
    void DeleteSpecificLine();
    void WithLineVersion();
    void DeliminateCopy();
    void UpdateNameContent();
    void DeleteFileName(fstream&, const string&);
    const string GetTime();
private:
    string fname;
    unsigned int line = 0;
    unsigned int deltline = 0;
};

void Note::WithLineVersion()
{
    ifstream in(fname+".nt");
    unsigned int line_no = 1;
    vector<pair<string, unsigned int>> fm;
    string aline;
    while (getline(in, aline)) {
        fm.push_back(std::make_pair(aline, line_no));
        ++line_no;
    }
    for (const auto& str : fm) {
        cout << "(" << std::setw(2) << str.second << ") " << str.first << endl;
    }
}

void Note::AppendNote()
{
    ofstream out(fname+".nt", ofstream::app);
    out << "----This content are updated in "
        << GetTime() << "----" << endl;
    string line;
    while (getline(cin, line)) {
        out << line << endl;
    }
}

void Note::Process()
{
    UpdateNameContent();
    if (CheckNoteName()) {
        cerr << "This file have existed " << fname << ".nt:" << endl;
        ReadNote();
        exit(0);
    }
}

void Note::GetFileLineNum()
{
    fstream forline(fname+".nt", ifstream::in);
    string str;
    while (getline(forline, str)) {
        ++line;
    }
    cout << line << endl;
}

void Note::DeliminateCopy()
{

}

void Note::DeleteSpecificLine()
{
    fstream in(fname+".nt", ifstream::in);
    assert(in.is_open());
    string fileline;
    ofstream tmp("tmp");
    for (int i = 1; i < deltline; ++i) {
        getline(in, fileline);
        tmp << fileline << endl;
    }
    getline(in, fileline);
    while (getline(in, fileline)) {
        tmp << fileline << endl;
    }
    fname += ".nt";
    if (remove(fname.c_str())) {
        perror("Error removing file");
    }
    if (rename("tmp", fname.c_str())) {
        perror("Error renaming file");
    }
    cout << "Delete Line." << deltline << " completed." << endl;
}

void Note::UpdateNameContent()
{
    fstream nameContent("AllNoteName.nt", ofstream::out | ofstream::app | ofstream::in);
    string filename;
    while (getline(nameContent, filename)) {
	    ifstream checkfile(filename+".nt");
	    if (!checkfile.is_open()) { //if file doesn't exist then delete the file name in content
 	        DeleteFileName(nameContent, filename);
	    }
    }
    return ;
}

void Note::DeleteFileName(fstream& oldfile, const string& deleteline)
{
    string otherline;
    oldfile.close();
    oldfile.open("AllNoteName.nt", ifstream::in);
    ofstream temp("temp");
    while (getline(oldfile, otherline)) {
        if (otherline != deleteline) {
	        temp << otherline << endl;
	    }
    }
    if (remove("AllNoteName.nt")) {
        perror("Error deleting file");
    }
    if (rename("temp", "AllNoteName.nt")) {
        perror("Error renaming file");
    }
}

void Note::ReadNote()
{
    fstream in(fname + ".nt");
    string line;
    if (in.is_open()) {
        while (getline(in, line)) {
            cout << line << endl;
        }
    }
}

bool Note::CheckNoteName()
{
    string name;
    fstream nameContent("AllNoteName.nt", ifstream::in);
    assert(nameContent.is_open());
    while (getline(nameContent, name)) {
        if (name == fname) {
            return true;
        }
    }
    return false;
}

void Note::StoreNoteName()
{
    fstream nameContent("AllNoteName.nt", ofstream::app | ofstream::out);
    assert(nameContent.is_open());
    nameContent << fname << endl;
}

void Note::NewNote()
{
    Process();
    string line;
    ofstream out(fname + ".nt");
    assert(out.is_open());

    cout << "Input Note Content:" << endl;
    out << "----This note is created in " << GetTime() << "----" << endl;
    while (getline(cin, line)) {
       out << line << endl;
    }
    StoreNoteName();
}

const string Note::GetTime()
{
    time_t now = time(0);
    char buf[80];
    struct tm ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &ts);
    return buf;
}

