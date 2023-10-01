#pragma once

//#include "pch.h"

#include <iostream>

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
	
	friend bool operator <(C obj1, C obj2);
	friend bool operator >(C obj1, C obj2); 
	


	friend std::ostream& operator << (std::ostream& s, const C& autoinf) {
		s << autoinf.price << " " << autoinf.year << " " << autoinf.doors << " " << autoinf.number << " " << autoinf.colour << " " << autoinf.name << "\n";
		return s;
	}

};

bool operator <(C obj1,C obj2) {
	if (obj1.price < obj2.price || (obj1.price == obj2.price && obj1.name < obj2.name) || (obj1.name == obj2.name && obj1.number < obj2.number))  return true;
	else false;
}

bool operator >(C obj1,C obj2) {
	if (obj1.price < obj2.price || (obj1.price == obj2.price && obj1.name < obj2.name) || (obj1.name == obj2.name && obj1.number < obj2.number))  return false;
	else true;
}


template <class T>
class Node
{
private:
	T value;
public:
	T getValue() { return value; }
	void setValue(T v) { value = v; }

	//сравнение узлов
	bool operator < (Node<T>& N){
		return (N.getValue() > value);
	}

	bool operator >(Node<T>& N){
		return (value > N.getValue());
	}

	//вывод содержимого одного узла
	void print(){
		cout << value;
	}

};

template <class T>
void print(Node<T>* N)
{
	cout << N->getValue() << "\n";
}

//куча (heap)
template <class T>
class Heap{
private:
	Node<T>* arr;
	int len; // сколько элементов добавлено
	int size; // сколько памяти выделено
public:

	//доступ к вспомогательным полям кучи и оператор индекса
	int getCapacity() { return size; }
	int getCount() { return len; }

	Node<T>* operator[](int index){
		if (index < 0 || index >= len) throw exception("Wrong index");
		return &arr[index];
	}

	Heap<T>(int MemorySize = 1000){
		arr = new Node<T> [MemorySize];
		len = 0;
		size = MemorySize;
	}

	//поменять местами элементы arr[index1], arr[index2]
	void Swap(int index1, int index2){

		Node<T> temp;
		temp = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = temp;
	}

	//скопировать данные между двумя узлами
	void Copy(Node<T>* dest, Node<T>* source){
		dest->setValue(source->getValue());
	}

	//функции получения левого, правого дочернего элемента, родителя или их индексов в массиве
	Node<T>* GetLeftChild(int index){

		return &arr[index * 2 + 1];
	}

	Node<T>* GetRightChild(int index){
		return &arr[index * 2 + 2];
	}

	Node<T>* GetParent(int index){

		if (index % 2 == 0)
			return &arr[index / 2 - 1];
		return &arr[index / 2];
	}

	int GetLeftChildIndex(int index){

		return index * 2 + 1;
	}

	int GetRightChildIndex(int index){
		if (index < 0 || index * 2 >= len) throw exception("Wrong index");
		return index * 2 + 2;
	}

	int GetParentIndex(int index){
		//if (index <= 0 || index >= len) throw exception("Wrong index");
		if (index % 2 == 0)
			return index / 2 - 1;
		return index / 2;
	}

	void Heapify(int index = 0);
		
	//просеить элемент вверх
	void SifUp(int index = -1)
	{
		if (index == -1) index = len - 1;
		int parent_index = GetParentIndex(index);
		if ( index > 0 && arr[parent_index] < arr[index]) {
			Swap(parent_index, index);
			SifUp(parent_index);
		}
	}

	void SifDown(int index = -1) {
		if (index == -1) { index = len - 1; }
		int childindex;

		if (GetLeftChildIndex(index) >= len) { return; }
		else if (GetRightChildIndex(index) >= len) { 
			childindex = GetLeftChildIndex(index); 
		}
		else if (GetRightChildIndex(index) < len && arr[GetRightChildIndex(index)] > arr[GetLeftChildIndex(index)]) { childindex = GetRightChildIndex(index); }
		else  
			childindex = GetLeftChildIndex(index); 
		if (arr[childindex] > arr[index]){
			Swap(index, childindex);
			SifDown(childindex);
		}
	}

	//удобный интерфейс для пользователя 
	template <class T>
	void push(T v){
		Node<T>* N = new Node<T>;
		N->setValue(v);
		push(N);
	}

	//добавление элемента - вставляем его в конец массива и просеиваем вверх
	template <class T>
	void push(Node<T>* N){
		if (len < size){
			arr[len++] = *N;
			SifUp(len-1);
		}
	}
	
	void pop(int index) {
		Swap(index, len - 1);
		len--;
		SifDown(index);
	}
	T ExtractMax(){ //исключить максимум и запустить просеивание кучи
		T extr = arr[0].getValue();
		arr[0] = arr[len - 1];
		len--;
		SifDown(0);
		return extr;
	}

	//перечислить элементы кучи и применить к ним функцию
	void Straight(void(*f)(Node<T>*)){
		int i;
		for (i = 0; i < len; i++){
			f(&arr[i]);
		}
	}

	//перебор элементов, аналогичный проходам бинарного дерева
	void PreOrder(void(*f)(Node<T>*), int index = 0)
	{
		if (index >= 0 && index < len) f(&arr[index]);
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
	}

	void InOrder(void(*f)(Node<T>*), int index = 0)
	{
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (index >= 0 && index < len)
			f(&arr[index]);
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
	}

	void PostOrder(void(*f)(Node<T>*), int index = 0)
	{
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
		if (index >= 0 && index < len)
			f(&arr[index]);
	}
};

int main()
{
	
	Heap<int> Tree(15);

	Tree.push(1);
	Tree.push(-1);
	Tree.push(-2);
	Tree.push(2);
	Tree.push(5);
	Tree.push(6);
	Tree.push(-3);
	Tree.push(-4);
	Tree.push(4);
	Tree.push(3);

	//cout << "\n-----\nStraight:";
	void(*f_ptr)(Node<int>*); f_ptr = print;
	//Tree.Straight(f_ptr);
	//cout << "\n-----\nExtractMax:\n";
	int i = 0;
	
	while (i < Tree.getCount()){
		auto N = Tree.ExtractMax();
		cout << "extracted:" << N << endl;
		Tree.Straight(f_ptr);
		cout << endl;
	}
	cout << "\n______________TREE with C_____________\n";
	Heap<C> TreeC(100);
	C auto0("BMW", "Black", 1133, 4, 2000, 1000);
	C auto1("Mustang", "Yellow", 1234, 2, 1965, 3000);
	C auto2("Chevrolet", "DarkGrey", 1456, 4, 2015, 750);
	C auto3("Lada", "DarkBrown", 1678, 4, 1978, 500);
	C auto4("Suzuki", "Grey", 1131, 2, 2005, 670);
	C auto5("Subaru", "Blue", 1005, 4, 2001, 3000);

	TreeC.push(auto0);
	TreeC.push(auto1);
	TreeC.push(auto2);
	TreeC.push(auto3);
	TreeC.push(auto4);
	TreeC.push(auto5);
	
	void(*f_ptrr)(Node<C>*); f_ptrr = print;
	int j = 0;

	while (j < TreeC.getCount()) {
		auto node = TreeC.ExtractMax();
		cout << "Extracted:" << node << "\n";
		TreeC.Straight(f_ptrr);
		cout << "\n";
	}
	
	char c; cin >> c;
	return 0;
}

