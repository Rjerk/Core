#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cassert>
#include <cstdio>
#include <windows.h>
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS in VS2015
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

class Note {
public:
    Note() = default;
    Note(string name) : fname(name) {}
	~Note() {};
    void Process();
    void NewNote();
    void ReadNote();
    void StoreNoteName();
    bool CheckNoteName();
    void UpdateNameContent();
	void DeleteLineInFile(fstream&, const string&);
    const string GetTime();
private:
    string fname;
};

void Note::Process()
{
	UpdateNameContent();
    if (CheckNoteName()) {
        ReadNote();
    } else {
        NewNote();
        StoreNoteName();
    }
}

void Note::UpdateNameContent()
{
	fstream nameContent("AllNoteName.nt", ofstream::out | ofstream::app | ofstream::in);
	string filename;
	while (getline(nameContent, filename)) {
		ifstream checkfile(filename+".nt", ifstream::in);
		if (!checkfile.is_open()) { //if file doesn't exist then delete the file name in content
			cout << "Where is file " << filename << endl;
			DeleteLineInFile(nameContent, filename);
		}
	}
	return ;
}

void Note::DeleteLineInFile(fstream& oldfile, const string& deleteline)
{
	string otherline;
	oldfile.close();
	oldfile.open("AllNoteName.nt", ifstream::in);
	ofstream temp("temp");
	cout << "deleteline: " << deleteline << endl;
	while (getline(oldfile, otherline)) {
		if (otherline != deleteline) {
			temp << otherline << endl;
			cout << otherline << endl;
		}
	}
	if (DeleteFile("AllNoteName.nt")) {
		perror("Error deleting file");
	} else {
		puts("File successfully deleted");
	}
	if (rename("temp", "AllNoteName.nt")) {
		perror("Error renaming file");
	} else {
		puts("File successfully renamed");
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
    cout << "store name : " << fname << endl;
}

void Note::NewNote()
{
    string line;
    ofstream out(fname + ".nt");
    assert(out.is_open());
    
    cout << "Input Note Content:" << endl;
    out << "----This note is created in " << GetTime() << "----" << endl;
    while (getline(cin, line)) {
       out << line << endl;
    }
}

const string Note::GetTime()
{
    time_t now = time(0);
    char buf[80];
    struct tm ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &ts);
    return buf;
}

int main()
{
    string name;
    cout << "Input note name: ";
    cin >> name;
    Note nt(name);
    nt.Process();
    return 0;
}
