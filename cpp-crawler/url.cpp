#include "url.h"
#include <cstring>
#include <sstring>

const string& HTTP = "http://";

URL::URL()
{
}

URL::URL(const string& url):
    m_url(url)
{
    parseURL(url);
}

URL::~URL()
{
}

void URL::parseURL(const string& url)
{
    string::size_type pos = url.find(HTTP);
    if (pos == string::npos)
        m_url = HTTP + url;

    pos = url.find('/', strlen(HTTP));
    if (pos == string::npos) {
        m_host = url;
        m_path = "/";
    } else {
        m_host = m_url.substr(0, pos);
        m_path = m_url.substr(pos);
    }
}


string URL::getPath() const
{
    return m_path;
}

string URL::getHost() const
{
    return m_host.substr(strlen(HTTP));
}

string URL::getURL() const
{
    return m_url;
}

string URL::encode(const string& value)
{
    std::ostringstream oss;
    oss.fill('0');
    oss << std::hex;

    for (auto iter = value.cbegin(), end = value.cend();
            iter != end; ++iter) {
        string::value_type c = *iter;
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            oss << c;
            continue;
        }
        oss << "%" << std::setw(2) << int((unsigned char)c);
    }
    return oss.str();
}
