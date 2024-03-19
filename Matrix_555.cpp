// Matrix_555.cpp : Defines the entry point for the application.
//

#include "Matrix_555.h"

using namespace std;

int main()
{
	

	try {
		Derived<double> M(2, 2);
		M.random();
		cout << M;
		Derived<double> M_file(2, 2); M_file(0, 0) = 7; M_file(0, 1) = 2; M_file(1, 0) = 3; M_file(1, 1) = 4;
		Derived<double> m; m(0, 0) = 2; m(0, 1) = 2; m(1, 0) = 3; m(1, 1) = 1;
		
		cout << M_file << "Before streaming\n";
		ofstream fout("test.txt");
		if (fout) {
			fout << m ;
			fout.close();
		}
		ifstream fin("test.txt");
		if (fin) {
			fin >> M_file;
			fin.close();
		}
		cout << "---------\n";
		cout <<  M_file  <<"\nAfter reading\n";

		cout << M_file(0, 0) << "\n";
		Derived<double> M2_copy = m;
		cout << M2_copy << "matrix after copying";
	}
	
	catch (UnEqualSizeException e) {
		e.print();
	}
	catch (IndexOutOfBoundException e) {
		e.print();
	}
	catch (DevisionByZero e) {
		e.print();
	}
	catch (Exception e) {
		e.print();
	}

	char c; cin >> c;
	return 0;
}
