//#include "String_empty_last.h"
#include <iostream>

using namespace std;

#include <iostream>

using namespace std;

//Кулаков Никита Алексеевич Вараинт 31 КМБО-03-21
class BaseString {
protected:
    char* p;
    int len;
    int capacity;
public:

    //Конструктор получающий на вход готовый объект: массив char
    BaseString(char* ptr) {
        cout << "\nBase Constructor 1\n";
        int itt = 0;
        while (ptr[itt] != '\0') {
            itt++;
        }
        len = itt;
        capacity = 4 * itt;
        p = new char[capacity];

        for (int i = 0; i < len; ++i) {
            p[i] = ptr[i];
        }
        p[len] = '\0';
    }
    //Конструктор получающий на вход готовый объект: строку
    BaseString(const char* ptr) {
        cout << "\nBase Constructor 1\n";
        int itt = 0;
        while (ptr[itt] != '\0') {
            itt++;
        }
        len = itt;
        capacity = 4 * itt;

        p = new char[capacity];

        for (int i = 0; i < len; ++i) {
            p[i] = ptr[i];
        }
        p[len] = '\0';
    }

    // Конструктор коппирования
    BaseString(const BaseString& ptr) {
        cout << "Base copy constructor\n";
        capacity = ptr.capacity;
        len = ptr.len;

        p = new char[capacity];

        for (int i = 0;i < len;i++) {
            p[i] = ptr.p[i];
        }
        p[len] = '\0';
    }


    BaseString(int Capacity = 256) {
        cout << "\nBase Constructor 0\n";
        capacity = Capacity;
        p = new char[capacity];
        len = 0;
    }

    ~BaseString() {
        cout << "\nBase Destructor\n";
        if (p != NULL)
            delete[] p;
        len = 0;
    }

    int Length() { return len; }
    int Capacity() { return capacity; }
    char* get() { return p; }
    char& operator[](int i) { return p[i]; }

    BaseString& operator=(const BaseString& s) {
        cout << "BaseOperator `=` \n";
        if (capacity >= s.capacity) {
            len = s.len;
            for (int i = 0; i <= len; i++)
            {
                p[i] = s.p[i];
            }
        }
        else {
            delete[] p;
            capacity = s.capacity;

            p = new char[capacity];
            len = s.len;
            
            for (int i = 0; i <= len; i++) {
                p[i] = s.p[i];
            }
        }
        return *this;
    }

    virtual void print() {
        int i = 0;
        cout << "The console out the string iternals:" << " ";
        while (p[i] != '\0') {
            cout << p[i];
            i++;
        }
        cout << "\n";
    }
};



class String : public BaseString {
public:
    String(int capacity = 256) : BaseString(capacity) { cout << "String constructor 0 \n"; }
    String(char* ptr) : BaseString(ptr) { cout << "String constructor 1\n"; }
    String(const char* ptr) : BaseString(ptr) { cout << "String constructor 1\n"; }

    //Конструктор копий
    String(const String& ptr) {
        cout << "String copy constructor\n";
        capacity = ptr.capacity;
        len = ptr.len;

        delete[] p;
        p = new char[capacity];

        for (int i = 0;i <= len;i++) {
            p[i] = ptr.p[i];
        }
        p[len] = '\0';
    }
       

    ~String() { cout << "String destructor\n"; }

    String operator+(String& s)
    {
        String res((capacity + s.capacity) >= 256 ? capacity + s.capacity : 256);
        res.len = len + s.len;
        for (int i = 0; i < len; i++)
        {
            res.p[i] = p[i];
        }
        for (int i = len; i < res.len; i++)
        {
            res.p[i] = s.p[i - len];
        }
        res.p[res.len] = '\0';
        return res;
    }

    String& operator=(const String& s) {
        cout << "StringOperator`=` \n";
        if (capacity >= s.capacity) {
            len = s.len;
            for (int i = 0; i <= len; i++)
            {
                p[i] = s.p[i];
            }
        }
        else {
            delete[] p;
            capacity = s.capacity;

            p = new char[capacity];
            len = s.len;

            for (int i = 0; i <= len; i++) {
                p[i] = s.p[i];
            }
        }
        return *this;
    }

    int IndexOf(char c, bool FindFromStart) {
        if (FindFromStart) {
            for (int i = 0; i < len; ++i) {
                if (p[i] == c) { return i; }
            }
        }
        else {
            for (int i = len - 1;i > 0;--i) {
                if (p[i] == c) { return i; }
            }
        }
        return -1;
    }

    String& tolower_(String& s) {
        for (int i = 0; i < s.len - 1; i++) {
            if (s[i] > 'A' && s[i] < 'Z') s[i] += 'z' - 'Z';
        }
        return *this;
    }
};




int main() {
    
    String s("test");
    s.print();
    String s1("hehent");
    String s4;
    s4 = s + s1;
    cout << "\n";
    s4.print();
    cout << "---------------------\n";
   
    String S("ReGISter");
    S.tolower_(S);
    S.print();
    int res = S.IndexOf('t', false);
    cout << res;
    cout << "------------------------\n";
    BaseString s5("DIY");
    s5.print();
    String s6("second");
    s6.print();

    return 0;
}
