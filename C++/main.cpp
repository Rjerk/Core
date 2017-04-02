#include "rstring.h"
#include <ios>

int main()
{
	{
		RString s; // RString();
		cout << s << "\n\n";
		
		RString s1("1234567890");
		cout << s1 << "\n\n";
		
		RString s2(s1);
		cout << s2 << "\n\n";
		
		RString s3 = s1;
		cout << s3 << "\n\n";
		
		RString bemoved1("123321123");
		RString s4 = std::move(bemoved1);
		cout << s4 << "\n\n";
		
		RString bemoved2("123123123");
		RString s5(std::move(bemoved2));
		cout << s5 << "\n\n";
		
		RString s6(s1, 1, 4);
		cout << s6 << "\n\n";
		
		//RString s7(s1, 10, 4); // out_of_range error
		//cout << s7 << "\n\n";
		
		RString s8(s1, 3);
		cout << s8 << "\n\n";
		
		RString s9("1234567890", 3);
		cout << s9 << "\n\n";
		
		RString s10(10, 'c');
		cout << s10 << "\n\n";
	}
	{
		RString s("abcde");
		cout << s << endl;
		cout << "front(): " << s.front() << endl;
		cout << "back(): " << s.back() << endl;
		cout << "c_str(): " << s.c_str() << endl;
		cout << "empty(): " << std::boolalpha << s.empty() << endl;
		cout << "length(): " << s.length() << endl;
		cout << "size(): " << s.size() << endl;
	}
}
