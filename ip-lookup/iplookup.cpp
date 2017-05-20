#include <vector>
#include <string>
#include <array>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <sstream>
#include <algorithm>
#include <exception>

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;
using std::array;
using std::pair;

struct IPAddressMapping {
	IPAddressMapping(): country(""), ip(0) {}
	string country;
	unsigned ip;
};


size_t convertToIndex(unsigned ip)
{
	return ip >> 24;
}

template <typename T>
T stringTo(const string& str)
{
	T ret;
	std::stringstream ss(str);
	ss >> ret;
	return ret; 
}

vector<string> split(const string& ip, char delim)
{
	std::stringstream ss(ip);
	string item;
	vector<string> ret;
	while (getline(ss, item, delim))
		ret.push_back(item);
	return ret;
}

IPAddressMapping parseOneLine(const string& line)
{
	IPAddressMapping mp;
	auto tokens = split(line, ',');
	mp.ip = stringTo<unsigned>(tokens[0].substr(1, tokens[0].length()-2));
	mp.country = tokens[6].substr(1, tokens[6].length()-2);
	return mp;
}

unsigned ipToInteger(const string& ip)
{
	vector<string> tokens = split(ip, '.');
	unsigned ret = 0;
	for (int i = 0; i < 4; ++i)
		ret += (std::stoi(tokens[i]) << ((3 - i ) * 8));
	return ret;
}

class IPToCountry {
public:
	IPToCountry(const string& filename = "IpToCountry.csv")
	{
		vector<vector<IPAddressMapping>> tmp(256, vector<IPAddressMapping>());
		tmp.swap(ip_list);
		std::ifstream infile(filename);
		while (infile.good() && !infile.eof()) {
			string line;
			getline(infile, line);
			// skip all comments and parse one line to hashtable.
			if (line.find_first_of('#') == string::npos && line.length() > 0) {
				IPAddressMapping mp = parseOneLine(line);
				ip_list[convertToIndex(mp.ip)].push_back(mp);
			}
		}
	}

	string indexIPToCountry(unsigned ip)
	{
		auto mp_vec = ip_list[convertToIndex(ip)];
		auto it = std::find_if(mp_vec.crbegin(), mp_vec.crend(), [ip] (IPAddressMapping mp) { return mp.ip <= ip; });
		if (it == mp_vec.rend())
			throw std::runtime_error("Not Found.");
		return it->country;
	}

	string getCountryFromIP(const string& ip)
	{
		return indexIPToCountry(ipToInteger(ip));
	}

	string getFile(const string& filename)
	{
		std::ifstream infile(filename);
		std::stringstream ss;
		while (infile.good() && !infile.eof()) {
			string ip;
			getline(infile, ip);
			if (ip.length() >= 7)
				ss << ip << " " << getCountryFromIP(ip) << "\n";
		}
		return ss.str();
	}
private:
	vector<vector<IPAddressMapping>> ip_list;
};

void Usage()
{
	cerr << "Usage:\n";
	cerr << "1. Read IP from command: ./iplookup ip-address\n";
	cerr << "2. Read a bunch of IPs from file: ./iplookup -f file-name" << endl;
}

int main(int argc, char** argv)
{
	IPToCountry mp;
	if (argc == 2) {
		string ip = string(argv[1]);
		string country = mp.getCountryFromIP(ip);
		cout << ip << ": " << country << endl;
	} else if (argc == 3 && string(argv[1]) == "-f") {
		cout << mp.getFile(string(argv[2])) << endl;
	} else {
		Usage();
		return -1;
	}
	return 0;
}
