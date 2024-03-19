// MULITI_INHARIT_3.cpp : Defines the entry point for the application.
//

//#include "MULITI_INHARIT_3.h"
#include <iostream>

using namespace std;

// Вариант 13 Кулаков Никита Алексеевич КМБО-03-21
class A1 {
protected:
    double a1;
public:
    A1(double value = 0) { a1 = value; cout << "Class A1 constructor has been called" << "\n"; }
    void print() { cout << "Value of A1 class\n"; }
    virtual void show() { cout << "Value a1=" << a1 << "\n"; }
};

class A2 {
protected:
    double a2;
public:
    A2(double value = 0) { a2 = value; }
    virtual void print() { cout << "Value of A2 class\n"; }
    virtual void show() { cout << "Value a2=" << a2 << "\n"; }
};

class A3 {
protected:
    double a3;
public:
    A3(double value = 0) { a3 = value; }
    virtual void print() { cout << "Value of A3 class\n"; }
    virtual void show() { cout << "Value a3=" << a3 << "\n"; }
};

class B1 : virtual public A1, virtual public A2, virtual public A3 {
protected:
    double b1;
public:
    B1(double value1 = 0, double value2 = 0) : A1(value2), A2(value2), A3(value2) { b1 = value1; cout << "Calss B1 constructor has been called" << "\n"; }
    virtual void print() { cout << "Value of B1 class\n"; }
    virtual void show() { cout << "value b1=" << b1 << " " << "Value a1 = " << a1 << " " << "value a2 = " << a1 << " " << "value a3 = " << a3 << "\n"; }
};

class B2 : virtual public A1, virtual public A2, virtual public A3 {
protected:
    double b2;
public:
    B2(double value1 = 0, double value2 = 0) : A1(value2), A2(value2), A3(value2) { b2 = value1; cout << "Class B2 constructor has been called\n"; }
    virtual void print() { cout << "Value of B2 class\n"; }
    virtual void show() { cout << "value b2=" << b2 << " " << "Value a1 = " << a1 << " " << "value a2 = " << a2 << " " << "value a3 = " << a3 << "\n"; }
};

class C1 : virtual public B1, virtual public B2 {
protected:
    double c1;
public:
    C1(double value1 = 0, double value2 = 0, double value3 = 0) : B1(value2, value3), B2(value2, value3) { c1 = value1; cout << "Class C1 constructor has been called"; }
    virtual void print() { cout << "Value of C1 class\n"; }
    virtual void show() { cout << "value c1=" << c1 << " " << "Value b1 = " << b1 << " " << "value b2 = " << b2 << "Value a1 = " << a1 << " " << "value a2 = " << a2 << " " << "value a3 = " << a3 << "\n"; }
};

class C2 : virtual public B1, virtual public B2 {
protected:
    double c2;
public:
    C2(double value1 = 0, double value2 = 0, double value3 = 0) : B1(value2, value3), B2(value2, value3) { c2 = value1; }
    virtual void print() { cout << "Value of C2 class\n"; }
    virtual void show() { cout << "value c2=" << c2 << " " << "Value b1 = " << b1 << " " << "value b2 = " << b2 << "Value a1 = " << a1 << " " << "value a2 = " << a2 << " " << "value a3 = " << a3 << "\n"; }
};



using namespace std;


int main() {
    A1 ptr(1);

    ptr.print();
    B1 b1;
    
    b1.print();
    cout<< "TAB\n";
    A1 a(1);
    a.print();
    a.show();
    B1 b(2, 3);
    b.print();
    b.show();
    cout << "TAB\n";
    C2 c;
    c.print();
    c.show();

    C1 test(2, 5, 3);
    test.print();
    test.show();
    //B1* ptr = &test;
    cout << "-----------\n";
    B2 test2(2, 3);
    test2.print();
    test2.show();
    A1* ptr1 = &test2;
    ptr1->print();
    ptr1->show();
    return 0;
}

