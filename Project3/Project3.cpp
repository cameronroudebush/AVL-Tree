// Project3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AVLTree.h"
#include <iostream>
#include  <vector>

using namespace std;

int main()
{
	AVLTree a5;
	a5.insert(50, 12);
	a5.insert(25, 12);
	a5.insert(100, 12);
	a5.insert(20, 12);
	a5.insert(15, 12);
	a5.insert(10, 12);
	a5.insert(5, 12);
	a5.insert(4, 12);
	a5.insert(3, 12);
	a5.insert(2, 12);
	a5.insert(1, 12);
	a5.insert(110, 12);
	a5.insert(115, 12);
	a5.insert(120, 12);
	a5.insert(112, 12);
	a5.insert(113, 12);
	a5.insert(114, 12);
	a5.insert(102, 12);
	a5.insert(115, 12);
	a5.insert(100, 12);
	a5.insert(25, 12);
	a5.insert(22, 12);
	a5.insert(21, 12);
	a5.insert(17, 12);
	a5.insert(16, 12);
	a5.insert(116, 12);
	a5.insert(117, 12);
	a5.print();
	system("PAUSE");
    return 0;
}

