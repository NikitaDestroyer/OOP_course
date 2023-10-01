// AbstractClassList.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

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
	bool operator >(C& obj) {
		if (price > obj.price  || (price==obj.price && name < obj.name) || (name==obj.name && number < obj.number))  return true;
		else false;
	}
	bool operator <(C& obj) { return obj > *this; }
		
	friend std::ostream& operator << (std::ostream& s, const C& autoinf) { 
		s << autoinf.price << " " << autoinf.year << " " << autoinf.doors << " " << autoinf.number << " " << autoinf.colour << " " << autoinf.name << "\n";
		return s;
	}

};

template <class T>
class Element
{   //элемент связного списка
private:
	//указатель на предыдущий и следующий элемент
	Element* next;
	Element* prev;
	//информация, хранимая в поле
	T field;
public:
	//доступ к полю *next
	virtual Element* getNext() { return next; }
	virtual void setNext(Element* value) { next = value; }

	//доступ к полю *prev
	virtual Element* getPrevious() { return prev; }
	virtual void setPrevious(Element* value) { prev = value; }

	//доступ к полю с хранимой информацией field
	virtual T getValue() { return field; }
	virtual void setValue(T value) { field = value; }

	friend ostream& operator<< (ostream& ustream, Element<T>& obj) {
			ustream << obj.field;
			return ustream;
	}
	Element(T value) { field = value; next = prev = NULL; }
	Element(const Element& el){
		field = el.field; next = el.next; prev = el.prev;
	}
};


template <class T>
class LinkedListParent
{
protected:
	//достаточно хранить начало и конец
	Element<T>* head;
	Element<T>* tail;
	//для удобства храним количество элементов
	int num;
public:
	virtual int Number() { return num; }
	virtual Element<T>* getBegin() { return head; }
	virtual Element<T>* getEnd() { return tail; }

	LinkedListParent() {
		//конструктор без параметров
		cout << "\nParent constructor";
		head = NULL; tail = NULL;
		num = 0;
	}
	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление
	virtual Element<T>* push(T value) = 0;
	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление
	virtual Element<T>* pop() = 0;

	virtual ~LinkedListParent() {
		//деструктор - освобождение памяти
		cout << "\nParent destructor";
		if (head != NULL) {
			Element<T>* current = head;
			Element<T>* temp = head->getNext();
			for (; current != tail; current = temp, temp = temp->getNext()) {
				delete current;
			}
			head = tail = NULL;
		}
	}
	//получение элемента по индексу - какова асимптотическая оценка этого действия?
	virtual Element<T>* operator[](int i){
		//индексация
		if (i<0 || i>num) return NULL;
		int k = 0;
		//ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
		Element<T>* cur = head;
		for (k = 0; k < i; k++){
			cur = cur->getNext();
		}
		return cur;
	}

    friend istream& operator>> (istream& ustream, LinkedListParent<T>& obj);
    friend ostream& operator<< (ostream& ustream, LinkedListParent<T>& obj);
};


template<class T>
ostream& operator << (ostream& ustream, LinkedListParent<T>& obj){
	if (typeid(ustream).name() == typeid(ofstream).name()){
		ustream << obj.num << "\n";
		for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext())
			ustream << current->getValue() << " ";
		return ustream;
	}

	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext(), i++)
		ustream << "arr[" << i << "] = " << current->getValue() << "\n";

	return ustream;
	
}

template<class T>
istream& operator >> (istream& ustream, LinkedListParent<T>& obj){
	//чтение из файла и консоли совпадают
	int len;
	ustream >> len;
	//здесь надо очистить память под obj, установить obj.num = 0
	double v = 0;
	for (int i = 0; i < len; i++){
		ustream >> v;
		obj.push(v);
	}
	return ustream;
}


template<typename ValueType>
class ListIterator : public std::iterator<std::input_iterator_tag, ValueType>{
private:
	//текущий элемент
	Element<ValueType>* ptr;
public:
	//конструкторы
	ListIterator() { ptr = NULL; }
	ListIterator(Element<ValueType>* p) { ptr = p; }
	ListIterator(const ListIterator& it) { ptr = it.ptr; }

	//методы работы с итераторами
	//присваивание
	ListIterator& operator=(const ListIterator& it) { ptr = it.ptr; return *this; }
	ListIterator& operator=(Element<ValueType>* p) { ptr = p; return *this; }

	//проверка итераторов на равенство
	bool operator!=(ListIterator const& other) const { return ptr == other.ptr ? false : true; }
	bool operator==(ListIterator const& other) const { return ptr == other.ptr ? true :false; }
	
	//получить значение
	Element<ValueType>& operator*(){ return *ptr; }
	
	//перемещение с помощью итераторов
	ListIterator& operator++() { ptr = ptr->getNext(); return *this; }
	ListIterator operator++(int v) { 
		auto temp = *this;
		ptr = ptr->getNext();
		return temp; 
	}
	ListIterator& operator--() { ptr->getPrevious(); return *this;}
	ListIterator operator--(int)  {
		auto temp = *this;
		--this;
		return temp;
	}
};


//класс итерируемый список - наследник связного списка, родитель для Очереди и Стека
template <class T>
class IteratedLinkedList : public LinkedListParent<T>{
public:
	IteratedLinkedList() : LinkedListParent<T>() { cout << "\nIteratedLinkedList constructor"; }
	virtual ~IteratedLinkedList() { cout << "\nIteratedLinkedList destructor"; }

	ListIterator<T> iterator;

	ListIterator<T> begin() { ListIterator<T> it = LinkedListParent<T>::head; return it; }
	ListIterator<T> end() { ListIterator<T> it = LinkedListParent<T>::tail; return it; }
};





template<class T>
class Stack : public IteratedLinkedList<T> {
public:
	Stack() : IteratedLinkedList<T>() { std::cout << "Constructor Stack\n"; }
	virtual ~Stack() { }

	virtual Element<T>* push(T value)  {
		Element<T>* newElem = new Element<T>(value);
		if (LinkedListParent<T>::head == NULL) {
			LinkedListParent<T>::tail = newElem;
			LinkedListParent<T>::head = newElem;
		}
		else {
			Element<T>* newElem = new Element<T>(value);
			Element<T>* q = LinkedListParent<T>::tail;
			q->setNext(newElem);
			LinkedListParent<T>::tail = q->getNext();
		}
		LinkedListParent<T>::num++;
		return LinkedListParent<T>::tail;
	}

	virtual Element<T>* pop() {
		if (LinkedListParent<T>::head == NULL) {
			return NULL;
		}

		Element<T>* elem = LinkedListParent<T>::tail;
		if (LinkedListParent<T>::tail == LinkedListParent<T>::head) {

			LinkedListParent<T>::tail = NULL;
			LinkedListParent<T>::head = NULL;
		}
		else {
			Element<T>* p = LinkedListParent<T>::head;
			while (p->getNext() != LinkedListParent<T>::tail) p = p->getNext();
			p->setNext(NULL);
			
		}

		LinkedListParent<T>::num--; return elem;
	}

	friend ostream& operator <<(ostream& s, Stack<T>& obj) {
        ListIterator<T> iter = obj.begin();
        if (typeid(s).name() == typeid(ofstream).name()) {
            s << obj.num << "\n";
            while (iter != NULL) {
                s << (*iter++).getValue() << " ";
            }
            return s;
        } else {
            s << "\nLength: " << obj.num << "\n";
            int i = 0;
            while (iter != NULL) {
                s << "arr[" << i++ << "] = " << (*iter++).getValue() << "\n";
            }
            return s;
        }
    }
};


template<typename T>
class OrderStack : public Stack<T> {
public:
	OrderStack() : Stack<T>() { std::cout << "\nConstructor OrderStack\n"; }
	virtual ~OrderStack() {}
	virtual Element<T>* push(T value) {
		// when stack empty
		Element<T>* elem = new Element<T>(value);
		if (LinkedListParent<T>::tail == NULL) {
			LinkedListParent<T>::tail = elem;
			LinkedListParent<T>::head = elem;
		}
		else {

			Element<T>* p = LinkedListParent<T>::head;

			if (p->getValue() > value) {
				elem->setNext(p);
				p->setPrevious(elem);
				LinkedListParent<T>::head = elem;
				// вставили вперед 
			}
			else {
				p->getNext();
				while (p->getValue() < value && p != LinkedListParent<T>::tail) p = p->getNext();
				//идем пока меньше, если вдруг больше то все/ тепрь указывает на элемент который больше либо на хвост
				if (p->getValue() < value) { //insert in the back
					p->setNext(elem);
					elem->setPrevious(p);
					LinkedListParent<T>::tail = elem;
				}
				else { //insert in specific place,разорвать две связи, р указывает на элемнт который больше
					elem->setNext(p);
					elem->setPrevious(p->getPrevious());
					p->getPrevious()->setNext(elem);
					p->setPrevious(elem);
				}
			}
		}
		LinkedListParent<T>::num++; return elem; 
	}
	friend ostream& operator <<(ostream& s, OrderStack<T>& obj) {
		auto iter = obj.begin();
		if (typeid(s).name() == typeid(ofstream).name()) {
			s << obj.num << "\n";
			while (iter != NULL) {
				s << (*iter++).getValue() << " ";
			}
			return s;
		}
		else {
			s << "\nLength: " << obj.num << "\n";
			int i = 0;
			while (iter != NULL) {
				s << "arr[" << i++ << "] = " << (*iter++).getValue() << "\n";
			}
			return s;
		}
	}
};


template <class T, template<typename> class R_O, template<typename> class R_I> // R_O - random output;R_i - random input; //параметр Т, вложенный шаблон клааса R_O, и шаблон класса R_I
R_O<T> filter(R_I<T>& dest, bool (*cmp)(T)) {
	R_O<T>* new_list = new R_O<T>;
	ListIterator<T> p = dest.begin();

	while (p != NULL) {
		if (cmp((*p).getValue())) {
			new_list->push((*p).getValue());
		}
		p++;
	}
	return *new_list;
}

bool test1(int value) {
	return value > 0;
}

int main()
{

	Stack<int> S;

	S.push(1);
	S.push(10);
	S.push(2);
	S.push(3);
	S.push(-2);
	cout << S;
	Element<int>* e1 = S.pop();
	cout << *e1;
	cout << "Stack - tested";
	OrderStack<int> OStack;
	OStack.push(1);
	OStack.push(10);
	OStack.push(6);
	OStack.push(-10);
	OStack.push(-6);
	cout << OStack;
	OStack.push(5);
	cout << OStack;
	cout << "\n Pushed new value\n"; 
	
	auto SS = filter<int,OrderStack,Stack>(S, test1);
	cout << SS;
	cout << "\n ------Filter worked, filtered by positive values-----\n";
	
	OrderStack<C> Cars;
	C auto0("BMW", "Black", 1133, 4, 2000, 1000);
	C auto1("Mustang", "Yellow", 1234, 2, 1965, 3000);
	C auto2("Chevrolet", "DarkGrey", 1456, 4, 2015, 750);
	C auto3("Lada", "DarkBrown", 1678, 4, 1978, 500);
	C auto4("Suzuki", "Grey", 1131, 2, 2005, 670);
	C auto5("Subaru", "Blue", 1005, 4, 2001, 3000);
	
	Cars.push(auto5);
	Cars.push(auto4);
	Cars.push(auto0);
	Cars.push(auto2);
	Cars.push(auto4);
	Cars.push(auto3);
	cout << Cars;

	C auto_new("Machina", "Black", 999, 2, 2000, 3000);
	Cars.push(auto_new);
	cout << Cars;
	
	char c; cin >> c;
	return 0;
	
}

