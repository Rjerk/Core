#include "String.h"
#include <ios>

int main()
{
	{
		String s; // String();
		cout << s << "\n\n";

		String s1("1234567890");
		cout << s1 << "\n\n";

		String s2(s1);
		cout << s2 << "\n\n";

		String s3 = s1;
		cout << s3 << "\n\n";

		String bemoved1("123321123");
		String s4 = std::move(bemoved1);
		cout << s4 << "\n\n";

		String bemoved2("123123123");
		String s5(std::move(bemoved2));
		cout << s5 << "\n\n";

		String s6(s1, 1, 4);
		cout << s6 << "\n\n";

		//String s7(s1, 10, 4); // out_of_range error
		//cout << s7 << "\n\n";

		String s8(s1, 3);
		cout << s8 << "\n\n";

		String s9("1234567890", 3);
		cout << s9 << "\n\n";

		String s10(3, 'c');
		cout << s10 << "\n\n";
		
		String s11(s1.begin(), s1.end());
		cout << s11 << "\n\n";
		
		String s12({'1', '2', '3', 'a', 'b'});
		cout << s12 << "\n\n";
	}
	{
		String s("abcde");
		cout << s << endl;
		cout << "front(): " << s.front() << endl;
		cout << "back(): " << s.back() << endl;
		cout << "c_str(): " << s.c_str() << endl;
		cout << "empty(): " << std::boolalpha << s.empty() << endl;
		cout << "length(): " << s.length() << endl;
		cout << "size(): " << s.size() << endl;
		cout << "at(2): " << s.at(2) << endl;
		cout << "data(): " << s.data() << endl;
		cout << "maxsize(): " << s.max_size() << endl;
		cout << "npos: " << s.npos << "\n\n";
	}
	{
		String s1("abcd");
		String s2("1234");
	}
	{
		String s("1234567890000");
		cout << s << endl;
		cout << "capacity(): " << s.capacity() << endl;
		s.reserve(20);
		cout << "capacity(): " << s.capacity() << endl;
		s.resize(15);
		cout << s << endl;
		cout << "capacity(): " << s.capacity() << endl;
		s.resize(20, 'c');
		cout << s << endl;
		s.clear();
		cout << s << endl;
		cout << "capacity(): " << s.capacity() << endl;
		s.shrink_to_fit();
		cout << "capacity(): " << s.capacity() << "\n\n";
	}
	{
		String s("1234");
		String s1("abcdef");
		s.append(s1, 0, 2);
		cout << s << endl;
		s.insert(1, 1, 'c');
		cout << s << endl;
		s.insert(1, 10, 'a');
		cout << s << "\n\n";
	}
	{
		String s("1234");
		cout << *s.begin() << endl;
		*(s.end()-1) = 'a';
		cout << s << "\n\n";
	}
	{
		String s;
		s.assign(std::move(String("123123")));
		cout << s << endl;
		s.assign(10, 'c');
		cout << s << endl;
		s.resize(1);
		String s1("1234567890");
		s.assign(s1, 1, 100);
		cout << s << endl;
		String s2;
		s2.assign("abcdefg", 3);
		cout << s2 << "\n\n";
	}
}
