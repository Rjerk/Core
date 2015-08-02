#include <iostream>
using namespace std;

void Time (int h, int min)
{
	cout << "Time: " << h << " : " << min << endl;
}

int main ()
{
	int h, min;
	cout << "Enter the number of hours :";
	cin  >> h;
	cout << "Enter the number of minutes :";
	cin  >> min;
	Time (h, min);
	return 0;
}

