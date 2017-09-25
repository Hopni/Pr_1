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
	test.Insert(2);
	test += test1;
	test.Display();
	Test<int> test2;
	Element<int> *el[] = { &test, &test2 };
	Visitor<int> v;
	test.accept(v);
	cout << endl << v.a << endl;
	test2.accept(v);
	cout << v.sum << endl;
}