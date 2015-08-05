#include <iostream>
#include <cctype>

int main ()
{
	using namespace std;
	cout << "Enter text for analysis, and type @"
		"to terminates input.\n";
	char ch;
	int whitespaces = 0, digits = 0, chars = 0, punct = 0, others = 0;
	cin.get (ch);

	while (ch != '@')
	{
		if (isalpha (ch))
			chars++;
		else if (isspace (ch))
			whitespaces++;
		else if (isdigit (ch))
			digits++;
		else if (ispunct (ch))
			punct++;
		else
			others++;
		cin.get (ch);
	}
	cout << chars << " letters, "
	     << whitespaces << " whitespaces, "
	     << digits << " digits, "
	     << punct << " punctuations, "
	     << others << " others.\n";
	return 0;
}
