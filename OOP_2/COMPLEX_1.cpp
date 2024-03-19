//#include "COMPLEX_1.h"
// Complex.cpp: определяет точку входа для консольного приложения.
// First Practic
// КМБО - 03 -21 Кулаков Никита Выполняю 1 вариант, потому что 30 варинтов занято, я взял следующий 
#include <iostream>
#include <math.h>

using namespace std;

class Complex
{
private:
	double real;
	double image;
public:
	//конструктор Complex z;
	Complex() {
		cout << "Base Complex construcor\n";
		real = 0; image = 0;
	}
	Complex(double a) {
		cout << " Complex construcor 1 value\n";
		real = image = a;
	}
	Complex(double a, double b) {
		cout << "Complex constructor 2 values\n";
		real = a; image = b;
	}
	~Complex() { cout << "Object Complex destructor\n"; }

	// Компл сопряжение
	Complex operator+() { return Complex(real, -image); }

	// Умножение на комплексное
	Complex operator*(Complex i) { return Complex(real * i.real - image * i.image, image * i.real + real * i.image); }


	double getReal() { return real; }
	double getImage() { return image; }

	double Module() { return sqrt(real * real + image * image); }

	void print()
	{
		if (image == 0)
		{
			cout << "\n" << real << "\n";
			return;
		}
		if (real == 0)
		{
			cout << "\n" << image << "i\n";
			return;
		}
		if (image > 0)
			cout << "\n" << real << " + " << image << "i" << "\n";
		else
			cout << "\n" << real << " - " << -image << "i" << "\n";
	}
	friend Complex operator *(double r, Complex c);
	friend Complex operator *(Complex c, double r);
};

Complex operator *(double r, Complex c) {
	return Complex(c.real * r, c.image * r);
}
Complex operator *(Complex c, double r) {
	return Complex(c.real * r, c.image * r);
}

//Complex operator*(Complex c, double r) {
	//return Complex(c.getReal() * r , c.getImage() * r);
//}
//Complex operator*(double r,Complex c) {
	//return Complex(c.getReal() * r , c.getImage() * r);
//}


using namespace std;

int main()
{
	Complex Z(10, 5), W(3, -2), T(4,-9);
	double R; cin >> R;
	Complex h = +W, r = Z * W, j = Z * R, p = R * Z;
	h.print();
	r.print();
	j.print();
	p.print();
	cout << "\n";
	cout << "Successfuly implemented" << "\n";
	char c;cin >> c;
	return 0;
}
