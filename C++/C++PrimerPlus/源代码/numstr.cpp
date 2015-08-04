#include <iostream>

int main ()
{
	using namespace std;
	cout << "What year was your house built?\n";
	int year;
	cin  >> year;
	cin.get ();
	cout << "What is its street address?\n";
	char address[90];
	cin.getline (address, 90);
	cout << "Year built : " << year << endl;
	cout << "Address : " << address << endl;
	cout << "Done!\n";
	return 0;
}

