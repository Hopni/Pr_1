// Pr1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Header.h"
#include <iostream>	
#include <algorithm>

using namespace std;

int main()

{
	KSet<int> a{ 1, 2, 3, 5, 7 }, b{ 0, 1, 3, 4, 5 };
	cout << a.get_pos(5) << " " << b.get_size();
	a.display();
	b.display();
	//a[b];
	//a.Swap(b);
	//a.display();
	//b.display();
}

