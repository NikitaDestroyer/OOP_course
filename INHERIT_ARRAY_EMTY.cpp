// INHERIT_ARRAY_EMTY.cpp : Defines the entry point for the application.
//

#include "INHERIT_ARRAY_EMTY.h"

using namespace std;

int main()
{
	if (true) {
		cout << "TASK 2.1\n";
		MyArrayParent arr, arr1;
		for (int i = 1; i < 11; i++) {
			arr1.push(i + 5);
			arr.push(i + 2);
		}
		arr1 = arr;
		arr1.print();
		arr1.push(2);
		arr1.print();
		arr1.RemoveLastValue();
		arr1.print();
		cout << "\nTASK 2.2\n";
		MyArrayChild arr2;
		for (int i = 10; i < 21; i++) {
			arr2.push((i * 2 - 4) % 26);
		}
		arr2.print();
		arr2.InsertAt(1000, 10);
		arr2.print();
		cout << "\n" << arr2.IndexOf(1000);
		cout << "\nTASK 2.3\n";

		MyArrayParent* cool;
		MySortedArray sarr1(40);
		cool = &sarr1;
		for (int i = -10; i < 10; i++)
		{
			cool->push(i);
		}
		sarr1.print();

		MyArrayChild* cool1;

		cool1 = &sarr1;
		cout << cool1->IndexOf(5);

		cout << "\n";
	}
	cout << "\n--------------" << "Successfuly implemented" << "-----------------\n";
	char c; cin >> c;
	return 0;
}
