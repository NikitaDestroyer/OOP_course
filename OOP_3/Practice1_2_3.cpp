#include<iostream>
#include<list>
#include<algorithm>
#include<fstream>
#include<ostream>

class Fraction {
public:
    int denominator;
    int numerator;
    Fraction(int n, int d) {
        numerator = n;
        denominator = d;
    }
};

// 1.1 push так чтобы список осталвася отсортированным
template<class T> void push_back(const std::list<T>& list, T& element) {
    auto iter = list.begin();
    while (iter != list.end() && *iter > element) { iter++; }
    list.insert(iter, element); //insert - создает копию объекта
}
// 1.1 pop с конца
template<class T> void pop_back(const std::list<T>& list) {
    auto iter = list.begin();
    while (iter != list.end()) { iter++; }
    list.erase(iter);
}
// 1.1 filter on predicate P
template<class T> std::list<T> filter(const std::list<T>& dest, bool (*cmp)(T)) {
    auto iter = dest.begin();
    std::list<T> result;
    while (iter != dest.end()) {
        auto v = *iter++;
        if (cmp(v)) result.push_back(v);
    }
    return result;
}
//1.1 print_of iternals 
template<class T> void print_of(const std::list<T>& list) {
    auto iter = list.begin();
    while (iter != list.end()) {
        std::cout << *iter++;
    }
}
bool test(Fraction F) {
    int v = F.numerator;
    for (int i = 2; i <= sqrt(v); i++) {
        if (v % i == 0) return false;
    }
    return true;
}
bool test(Fraction F){

}
//Задание 1.2
//класс автомобиль,приоритет по убыванию: Цена, год выпуска,марка(по возврастанию),серийный номер(по возврастанию)
class C {
public:
    std::string name;
    std::string colour;
    int number;
    int doors;
    int year;
    int price;
    //Конструктор класса
    C(std::string Name = "", std::string  Colour = "", int Number = 0, int Doors = 0, int Year = 0, int Price = 0) {
        std::cout << "C Constructor\n";
        name = Name;
        colour = Colour;
        number = Number;
        doors = Doors;
        year = Year;
        price = Price;
    }
    C(const C& p) {
        std::cout << "Copies Constructor\n";
        price = p.price;
        name = p.name;
        number = p.number;
        colour = p.colour;
        year = p.year;
        doors = p.doors;
    }
    ~C()
    {
        std::cout << "C Destructor\n";
        std::string name = "";
        std::string colour = "";
        number = 0;
        doors = 0;
        year = 0;
        price = 0;
    }
    friend std::ostream& operator << (std::ostream& s, const C& autoinf);
   
};
template<class T>
T pop_pr(const std::list<T>& list) {
    auto iter = list.end();
    iter--;
    auto v = *iter;
    list.erase(iter);
    return v;
}


std::ostream& operator<<(std::ostream& s, const C& autoinf)
{
    s << autoinf.price <<" "<< autoinf.year<<" "<< autoinf.doors << " " << autoinf.number<<" " << autoinf.colour <<" "<< autoinf.name <<"\n";
    return s;
}





int main()
{
    //Убывание по приоритету Цена; год выпуска; марка(повозрастанию);серийный номер(повозрастанию)
    C auto0("BMW", "Black", 1133, 4, 2000, 1000);
    C auto1("Mustang", "Yellow", 1234, 2, 1965, 3000);
    C auto2("Chevrolet", "DarkGrey", 1456, 4, 2015, 750);
    C auto3("Lada", "DarkBrown", 1678, 4, 1978, 500);
    C auto4("Suzuki", "Grey", 1131, 2, 2005, 670);
    C auto5("Subaru", "Blue", 1005, 4, 2001, 3000);

    std::list<C> Cars;
    Cars.push_back(auto5);
    Cars.push_back(auto4);
    Cars.push_back(auto0);
    Cars.push_back(auto2);
    Cars.push_back(auto4);
    Cars.push_back(auto3);

    C elem = pop_pr(Cars);
    print_of(Cars);
    std::cout << elem <<"\n";
}

