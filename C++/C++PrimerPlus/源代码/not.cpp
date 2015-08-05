#include <iostream>
#include <climits>
bool is_int (double x);

int main ()
{
	using namespace std;
	double num;

	cout << "Yo, dude; Enter an integer values: ";
	cin  >> num;
	while (!is_int(num))
	{
		cout << "Out of range -- please try again: ";
		cin  >> num;
	}
	int val = int (num);
	cout << "you've entered the integer " << val << "\nBye\n";
	return 0;
}

bool is_int (double x)
{
	if (x <= INT_MAX && x >= INT_MIN)
		return true;
	else
		return false;
}

