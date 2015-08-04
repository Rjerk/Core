#include <iostream>

int main ()
{
	using namespace std;
	double wages[3] = {1000.0, 2000.0, 3000.0};
	short stack[3] = {3, 2, 1};

	double *pw = wages;
	short *ps = &stack[0];

	cout << "pw = " << pw << ", *pw = " << *pw << endl;
	pw = pw + 1;
	cout << "add 1 to the pw pointer:\n";
	cout << "pw = " << pw << ", *pw = " << *pw << "\n\n";
	cout << "ps = " << ps << ", *ps = " << *ps << endl;
	ps = ps + 1;
	cout << "add 1 to the ps pointer:\n";
	cout << "ps = " << ps << ", *ps = " << *ps << "\n\n";

	cout << "access two elements with array notation\n";
	cout << "stack[0] = " << stack[0] 
	     << ", stack[1] = "<< stack[1] << endl;
	cout << "access two elements with array notation\n";
	cout << "*stack = " << *stack 
	     << ", *(stack + 1) = " << *(stack + 1) << endl;
	cout << sizeof (wages) << " = size of wages array\n";
	cout << sizeof (pw) << " = size of pw pointer\n";
	return 0;
}

