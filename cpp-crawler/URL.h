#ifndef URL_H
#define URL_H

#include <string>
using std::string;

class URL {
public:
    URL();
    URL(const string& url);
    ~URL();
    void parseURL(const string& url);
    string getHost();
    string getPath();
    string getURL();
    string encode(const string& value);
private:
    string m_url;
    string m_host;
    string m_path;
};

#endif
