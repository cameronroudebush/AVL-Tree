// Project3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AVLTree.h"
#include <iostream>
#include  <vector>

using namespace std;

int main()
{
	AVLTree a1;
	a1.insert(40, 12);
	a1.insert(20, 16);
	a1.insert(50, 11);
	
	a1.insert(10, 54);
	a1.insert(30, 16);
	a1.insert(45, 72);
	
	a1.print();
	vector<int> temp = a1.findRange(0, 45);
	for (int i = 0; i < temp.size(); i++) {
		cout << temp.at(i) << " ";
	}
	cout << endl;

	system("PAUSE");
    return 0;
}

