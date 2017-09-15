// Pr1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "KSet.h"
#include <iostream>	
#include <algorithm>

using namespace std;

int main()
{
	KSet<int> test{ 1, 2, 3 }, test1{ 1, 2, 5 };
	test.Display();
	test1.Display();
	test += test1;
	test.Display();
	test.Swap(test1);
	test.Display();
	cout << endl << endl;
	KSet<int> res(test);
	res = test + test1;
	res.Display();;
}