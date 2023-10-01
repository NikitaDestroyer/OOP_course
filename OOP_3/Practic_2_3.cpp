#include <iostream>
#include <queue>

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
		name = p.name;
		number = p.number;
		colour = p.colour;
		year = p.year;
		price = p.price;
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
	bool operator >(const C& obj) const  {
		if (price > obj.price || (price == obj.price && name < obj.name) || (name == obj.name && number < obj.number))  return true;
		else false;
	}
	bool operator <(const C& obj) const { return *this > obj; }

	friend std::ostream& operator << (std::ostream& s, const C& autoinf) {
		s << autoinf.price << " " << autoinf.year << " " << autoinf.doors << " " << autoinf.number << " " << autoinf.colour << " " << autoinf.name << "\n";
		return s;
	}

};


template<class T> 
void print_queue(T& q) {
	while (!q.empty()) {
		std::cout << "Element: ";
		std::cout << "{";
		std::cout << q.top() << "} ";
		q.pop();
	}
	std::cout << "n";
}

int main(){
	std::priority_queue<C> q;
	C auto0("BMW", "Black", 1133, 4, 2000, 1000);
	C auto1("Mustang", "Yellow", 1234, 2, 1965, 3000);
	C auto2("Chevrolet", "DarkGrey", 1456, 4, 2015, 750);
	C auto3("Lada", "DarkBrown", 1678, 4, 1978, 500);
	C auto4("Suzuki", "Grey", 1131, 2, 2005, 670);
	C auto5("Subaru", "Blue", 1005, 4, 2001, 3000);

	q.push(auto0);
	q.push(auto1);
	q.push(auto2);
	q.push(auto3);
	q.push(auto4);
	q.push(auto5);
	print_queue(q);
}


