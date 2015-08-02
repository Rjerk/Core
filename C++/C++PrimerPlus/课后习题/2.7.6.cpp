#include <iostream>

using namespace std;

int LightYear (double n)
{
	return n * 63240;
}

int main ()
{
	double num;
	cout << "Enter the number of light years: ";
	cin  >> num;
	cout << num << " light years = " << LightYear(num) << " astronomical units." << endl;
	return 0;
}

