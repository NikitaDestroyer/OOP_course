﻿#include <iostream>
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
		if (price > obj.price || (price == obj.price && name < obj.name) || (name == obj.name && number < obj.number))  return true;
		else false;
	}
	bool operator <(C& obj) { return obj > *this; }

	friend std::ostream& operator << (std::ostream& s, const C& autoinf) {
		s << autoinf.price << " " << autoinf.year << " " << autoinf.doors << " " << autoinf.number << " " << autoinf.colour << " " << autoinf.name << "\n";
		return s;
	}

};


//узел
template<class K, class T>
class Node
{
protected:
	//закрытые переменные Node N; N.data = 10 вызовет ошибку
	T data;
	K key;
	//не можем хранить Node, но имеем право хранить указатель
	Node* left;
	Node* right;
	Node* parent;
	//переменная, необходимая для поддержания баланса дерева
	int height;
public:
	//доступные извне переменные и функции
	virtual void setData(T d) { data = d; }
	virtual T getData() { return data; }

	virtual void setKey(K k) { key = k; }
	virtual K getKey() { return key; }
	int getHeight() { return height; }
	virtual Node* getLeft() { return left; }
	virtual Node* getRight() { return right; }
	virtual Node* getParent() { return parent; }
	virtual void setLeft(Node* N) { left = N; }
	virtual void setRight(Node* N) { right = N; }
	virtual void setParent(Node* N) { parent = N; }
	virtual void changeParentS(Node* N) {
		if (this->getParent()->getLeft() == this)
			this->getParent()->setLeft(N);
		else
			this->getParent()->setRight(N);
	}
	virtual int getBf() { return (left != NULL ? left->getHeight() : -1) - (right != NULL ? right->getHeight() : -1); }
	virtual bool isLeaf() { return left == NULL && right == NULL; }
	//Конструктор. Устанавливаем стартовые значения для указателей

	Node<K, T>() {
		left = NULL;
		right = NULL;
		parent = NULL;
		data = 0;
		key = 0;
		height = 0;
	}

	virtual void print()
	{
		cout << "\n" << data;
	}

	virtual void setHeight(int h)
	{
		height = h;
	}

	template<class K, class T> friend ostream& operator<<(ostream& stream, Node<K, T>& N)
	{
		stream << "Node data: " << N.data << ", height: " << N.height << endl;
		return stream;
	}

	virtual void updateHeight()
	{
		int leftSubtreeHeight, rightSubtreeHeight;
		if (left == NULL)
			leftSubtreeHeight = -1;
		else
			leftSubtreeHeight = left->getHeight();
		if (right == NULL)
			rightSubtreeHeight = -1;
		else
			rightSubtreeHeight = right->getHeight();
		this->setHeight(1 + max(leftSubtreeHeight, rightSubtreeHeight));
	}
};



template<class K, class T>
void print(Node<K, T>* N) { cout << N->getData() << endl; }
template<typename K, typename T>
class TreeIterator : public std::iterator<std::input_iterator_tag, T> {
private:
	Node<K, T>* ptr;
public:
	TreeIterator() { ptr = NULL; }
	TreeIterator(Node<K, T>* p) { ptr = p; }
	TreeIterator(const TreeIterator& it) { ptr = it.ptr; }

	TreeIterator& operator=(const TreeIterator& it) { ptr = it.ptr; return *this; }
	TreeIterator& operator=(Node<K, T>* p) { ptr = p; return *this; }

	bool operator!=(TreeIterator const& other) const { return ptr != other.ptr; }
	bool operator==(TreeIterator const& other) const { return ptr == other.ptr; }


	T operator*() {
		if (ptr == NULL)
			throw exception("nullptr");
		return ptr->getData();
	}

	TreeIterator& operator++() {
		if (ptr->getRight() != NULL) {
			ptr = ptr->getRight();
			while (ptr->getLeft() != NULL)
				ptr = ptr->getLeft();
		}
		else {
			while (ptr->getParent() && ptr->getParent()->getRight() == ptr)
				ptr = ptr->getParent();
			ptr = ptr->getParent();
		}
		return *this;
	}
	TreeIterator operator++(int) {
		auto temp = *this;
		++(*this);
		return temp;

	}
	TreeIterator& operator--() {
		if (ptr->getLeft()) {
			ptr = ptr->getLeft();
			while (ptr->getRight())
				ptr = ptr->getRight();
		}
		else {
			while (ptr->getParent() && ptr->getParent()->getLeft() == ptr)
				ptr = ptr->getParent();
			ptr = ptr->getParent();
		}
		return *this;
	}
	TreeIterator operator--(int) {
		auto temp = *this;
		--(*this);
		return temp;
	}


};


template<class K, class T>
class Tree
{
protected:
	//корень - его достаточно для хранения всего дерева
	Node<K, T>* root;
public:
	virtual Node<K, T>* getRoot() { return root; }

	Tree<K, T>() { root = NULL; }

	//функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual void push(K key, T n)
	{
		Node<K, T>* N = new Node<K, T>;
		N->setData(n);
		N->setKey(key);
		Add_R(N, root);
	}

	virtual Node<K, T>* Add_R(Node<K, T>* N, Node<K, T>* Current)
	{
		if (root == NULL)
		{
			root = N;
			return root;
		}
		else if (N->getKey() < Current->getKey())
		{
			//идем влево
			if (Current->getLeft() != NULL) { Current->setLeft(Add_R(N, Current->getLeft())); }
			else { Current->setLeft(N); }
			Current->getLeft()->setParent(Current);
		}
		else if (N->getKey() > Current->getKey())
		{
			//идем вправо
			if (Current->getRight() != NULL) { Current->setRight(Add_R(N, Current->getRight())); }
			else { Current->setRight(N); }
			Current->getRight()->setParent(Current);
		}
		if (Current->getKey() == N->getKey()) {
			Current->setRight(N);
			Current->getRight()->setParent(Current);
		}
		Current->updateHeight();
		return Current;
	}


	virtual T pop(K key)
	{
		Node<K, T>* current = FindNodeByKey(key, root);
		T data = current->getData();
		if (current == NULL)
			return NULL;
		else if (current->isLeaf())
		{
			if (current != root) {
				Node<K, T>* currentP = current->getParent();
				current->changeParentS(NULL);
				current->setParent(NULL);
				this->fixHeights(currentP);
			}
			else { root = NULL; }
			delete current;
			return data;
		}
		else if (current->getLeft() != NULL && current->getRight() != NULL)
		{
			Node<K, T>* replacement = MinNode(current->getRight());
			Node<K, T>* replacementP;

			if (replacement->isLeaf())
			{
				replacementP = replacement->getParent();
				replacement->changeParentS(NULL);
			}
			else if (replacement != current->getRight())
			{
				replacementP = replacement->getParent();
				replacement->changeParentS(replacement->getRight());
				replacement->getRight()->setParent(replacement->getParent());
				replacement->setRight(current->getRight());
				current->getRight()->setParent(replacement);
			}
			else
			{
				replacementP = current->getParent();
			}
			replacement->setLeft(current->getLeft());
			current->getLeft()->setParent(replacement);


			if (current != root)
			{
				current->changeParentS(replacement);
				replacement->setParent(current->getParent());
			}
			else
			{
				replacement->setParent(NULL);
				root = replacement;
			}

			delete current;
			this->fixHeights(replacementP);
			return data;
		}
		else if (current->getLeft() != NULL)
		{
			Node<K, T>* replacement = current->getLeft();
			if (current != root)
			{
				current->changeParentS(replacement);
				replacement->setParent(current->getParent());
			}
			else {
				replacement->setParent(NULL);
				root = replacement;
			}
			delete current;
			this->fixHeights(replacement->getParent());
			return data;
		}
		else if (current->getRight() != NULL)
		{
			Node<K, T>* replacement = current->getRight();
			if (current != root)
			{
				current->changeParentS(replacement);
				replacement->setParent(current->getParent());
			}
			else {
				replacement->setParent(NULL);
				root = replacement;
			}
			delete current;
			this->fixHeights(replacement->getParent());
			return data;
		}
	}

	virtual T Min(Node<K, T>* Current = NULL)
	{
		//минимум - это самый "левый" узел. Идём по дереву всегда влево
		if (root == NULL) { return NULL; }
		if (Current == NULL) { Current = root; }
		while (Current->getLeft() != NULL) { Current = Current->getLeft(); }
		return Current->getData();
	}

	virtual Node<K, T>* MinNode(Node<K, T>* Current = NULL)
	{
		//минимум - это самый "левый" узел. Идём по дереву всегда влево
		if (root == NULL) { return NULL; }
		if (Current == NULL) { Current = root; }
		while (Current->getLeft() != NULL) { Current = Current->getLeft(); }
		return Current;
	}

	virtual T Max(Node<K, T>* Current = NULL)
	{
		//минимум - это самый "правый" узел. Идём по дереву всегда вправо
		if (root == NULL) { return NULL; }
		if (Current == NULL) { Current = root; }
		while (Current->getRight() != NULL) { Current = Current->getRight(); }
		return Current->getData();
	}

	virtual Node<K, T>* MaxNode(Node<K, T>* Current = NULL)
	{
		//минимум - это самый "правый" узел. Идём по дереву всегда вправо
		if (root == NULL) { return NULL; }
		if (Current == NULL) { Current = root; }
		while (Current->getRight() != NULL) { Current = Current->getRight(); }
		return Current;
	}

	//поиск узла в дереве по значению. Второй параметр - в каком поддереве искать, первый - что искать
	virtual Node<K, T>* FindNodeByData(T data, Node<K, T>* Current)
	{
		//база рекурсии
		if (Current == NULL) { return NULL; }
		if (Current->getData() == data) { return Current; }
		//рекурсивный вызов
		if (Current->getData() > data) { return FindNodeByData(data, Current->getLeft()); }
		if (Current->getData() < data) { return FindNodeByData(data, Current->getRight()); }
	}

	//поиск узла в дереве по ключу. Второй параметр - в каком поддереве искать, первый - что искать
	virtual Node<K, T>* FindNodeByKey(K key, Node<K, T>* Current)
	{
		//база рекурсии
		if (Current == NULL) { return NULL; }
		if (Current->getKey() == key) { return Current; }
		//рекурсивный вызов
		if (Current->getKey() > key) { return FindNodeByKey(key, Current->getLeft()); }
		if (Current->getKey() < key) { return FindNodeByKey(key, Current->getRight()); }
	}




	//три обхода дерева
	virtual void PreOrder(Node<K, T>* N, void (*f)(Node<K, T>*))
	{
		if (N != NULL) { f(N); }
		if (N != NULL && N->getLeft() != NULL) { PreOrder(N->getLeft(), f); }
		if (N != NULL && N->getRight() != NULL) { PreOrder(N->getRight(), f); }
	}

	//InOrder-обход даст отсортированную последовательность
	virtual void InOrder(Node<K, T>* N, void (*f)(Node<K, T>*))
	{
		if (N != NULL && N->getLeft() != NULL) { InOrder(N->getLeft(), f); }
		if (N != NULL) { f(N); }
		if (N != NULL && N->getRight() != NULL) { InOrder(N->getRight(), f); }
	}

	virtual void PostOrder(Node<K, T>* N, void (*f)(Node<K, T>*))
	{
		if (N != NULL && N->getLeft() != NULL) { PostOrder(N->getLeft(), f); }
		if (N != NULL && N->getRight() != NULL) { PostOrder(N->getRight(), f); }
		if (N != NULL) { f(N); }
	}
	virtual void fixHeights(Node<K, T>* N)
	{
		if (N != NULL) {
			N->updateHeight();
			if (N->getParent() != NULL)
			{
				fixHeights(N->getParent());
			}
		}
	}

};


//класс итерируемое дерево поиска
template<class K, class T>
class IteratedTree : public Tree<K, T>
{
public:
	IteratedTree<K, T>() : Tree<K, T>() { cout << "\nIteratedTree constructor\n"; }
	virtual ~IteratedTree<K, T>() { cout << "\nIteratedTree desructor\n"; }

	TreeIterator<K, T> begin() {
		if (Tree<K, T>::root == NULL) { return NULL; }
		Node<K, T>* Current = Tree<K, T>::root;
		while (Current->getLeft() != NULL) { Current = Current->getLeft(); }
		TreeIterator<K, T> it = Current;
		return it;
	}
	TreeIterator<K, T> end() {
		if (Tree<K, T>::root == NULL) { return NULL; }
		Node<K, T>* Current = Tree<K, T>::root;
		while (Current->getRight() != NULL) { Current = Current->getRight(); }
		TreeIterator<K, T> it = Current;
		return it;
	}
};


template<class K, class T>
class Multi_Tree : public IteratedTree<K, T>  // ничерта не работает
{
public:
	Multi_Tree() : IteratedTree<K, T>() { cout << "smth"; }
	virtual ~Multi_Tree() {}

	virtual void push(K key, T data) {
		Node<K, T>* node = IteratedTree<K, T>::FindNodeByKey(key, IteratedTree<K, T>::getRoot());
		if (node != NULL) {
			IteratedTree<K, T>::push(key, data);
		}
		else {
			Node<K, T>* nd = new Node<K, T>;
			nd->setData(data);
			nd->setKey(key);

			IteratedTree<K,T>::Add_R(nd, IteratedTree<K, T>::root);
			Node<K, T>* node = IteratedTree<K, T>::FindNodeByKey(key, IteratedTree<K, T>::getRoot());
			node = node->getParent();
			if (nd == NULL)
				nd = this->getRoot();
			BalanceSubTree(nd);
		}
	}
	virtual T pop(K key) {
		Node<K, T>* node = IteratedTree<K, T>::FindNodeByKey(key, IteratedTree<K, T>::getRoot());
		T data = node->getData();
		if (node != NULL) {
			IteratedTree<K, T>::pop(key);
		}
		else {
			exception("No items to pop");
		}
		return data;
	}
private:
	Node<K, T>* RotateRight(Node<K, T>* p) // правый поворот вокруг p
	{
		Node<K, T>* q = p->getLeft();

		if (this->getRoot() == p)
			this->root = q;
		else
			p->changeParentS(q);


		p->setLeft(q->getRight());
		if (q->getRight() != NULL) {
			p->getLeft()->setParent(p);
		}

		q->setParent(p->getParent());
		p->setParent(q);
		q->setRight(p);

		this->fixHeights(p);
		this->fixHeights(q);
		return q;
	}

	Node<K, T>* RotateLeft(Node<K, T>* q) // левый поворот вокруг q
	{
		Node<K, T>* p = q->getRight();
		if (this->getRoot() == q)
			this->root = p;
		else
		{
			q->changeParentS(p);
		}
		q->setRight(p->getLeft());
		if (p->getLeft() != NULL)
		{
			q->getRight()->setParent(q);
		}

		p->setParent(q->getParent());
		q->setParent(p);
		p->setLeft(q);

		this->fixHeights(p);
		this->fixHeights(q);
		return p;
	}
	virtual void BalanceSubTree(Node<K, T>* N)
	{
		if (N != NULL) {
			if (abs(N->getBf()) == 2)
			{
				BalanceNode(N);
				if (N->getParent() != NULL)
					BalanceSubTree(N->getParent()->getParent());
			}
			else
				BalanceSubTree(N->getParent());
		}
	}


	void BalanceNode(Node<K, T>* node)
	{
		int bf = node->getBf();
		if (bf == 2) {
			int leftBf = node->getLeft()->getBf();
			if (leftBf > 0) {
				RotateRight(node);
				cout << endl << "Right Rotation" << *node << endl;
			}
			else {
				RotateLeft(node->getLeft());
				RotateRight(node);
			}
		}
		else if (bf == -2) {
			int rightBf = node->getRight()->getBf();
			if (rightBf < 0) {
				RotateLeft(node);
				cout << endl << "Left Rotation" << *node << endl;

			}
			else {
				RotateRight(node->getRight());
				RotateLeft(node);
			}
		}
	}
};






int main()
{
	C auto0("BMW", "Black", 1133, 4, 2000, 1000);
	C auto1("Mustang", "Yellow", 1234, 2, 1965, 3000);
	C auto2("Chevrolet", "DarkGrey", 1456, 4, 2015, 750);
	C auto3("Lada", "DarkBrown", 1678, 4, 1978, 500);
	C auto4("Suzuki", "Grey", 1131, 2, 2005, 670);
	C auto5("Subaru", "Blue", 1005, 4, 2001, 3000);

	Multi_Tree<double, double> T;

	T.push(6, 6);
	T.push(7, 7);
	T.push(4, 4);
	T.push(3, 3);
	T.push(5, 5);
	T.push(2, 2);
	T.push(1, 1);
	T.push(1, 1);

	for (auto it = T.begin(); it != NULL; it++) { cout << *it<<"\n"; }
	cout << endl << "---------------------------" << endl;
	T.pop(1);
	for (auto it = T.begin(); it != NULL; it++) { cout << *it << "\n"; }

	char c; cin >> c;
	return 0;

};