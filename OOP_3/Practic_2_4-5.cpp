#include <iostream>
#include<math.h>
using namespace std;


class C {
public:
	std::string name;
	std::string surname;
	int number_register;
	std::string date;
	int number;
	//Конструктор класса
	C(std::string Name = "", std::string  Surname = "", std::string  Date = "", int Number_register=0,int Number= 0 ) {
		std::cout << "C Constructor\n";
		name = Name;
		surname = Surname;
		number = Number;
		number_register = Number_register;
		date = Date;
	}
	C(const C &p) {
		std::cout << "C Constructor\n";
		name = p.name;
		surname = p.surname;
		number = p.number;
		number_register = p.number_register;
		date = p.date;
	}
	
	~C()
	{
		std::cout << "C Destructor\n";
		std::string name = "";
		std::string surname = "";
		number = 0;
		number_register = 0;
		date = "";
	}

	friend ostream& operator <<(ostream& s, const C& info) {
		s << info.name << " " << info.surname << " " << info.date << " " << info.number_register << " " << info.number<<"\n";
	}
};


//key is register number of auto
//узел
template<typename K,class T>
class Node{
protected:
	T data;
	K key;

	Node* left;
	Node* right;
	Node* parent;
	
	int height;
public:
	virtual T getKey() { return key; }
	virtual void setKey(K Key) { key = Key; }
	virtual void setData(T d) { data = d; }
	virtual T getData() { return data; }
	int getHeight() { return height; }
	virtual Node* getLeft() { return left; }
	virtual Node* getRight() { return right; }
	virtual Node* getParent() { return parent; }
	virtual void setLeft(Node* N) { left = N; }
	virtual void setRight(Node* N) { right = N; }
	virtual void setParent(Node* N) { parent = N; }
	//Конструктор. Устанавливаем стартовые значения для указателей
/*	Node<K, T>(T n) {
		data = n.data;
		key = n.key;
		left = right = parent = NULL;
		height = 1;
	}*/
	Node<K,T>(){
		left = NULL;
		right = NULL;
		parent = NULL;
		data = 0;
		key = 0;
		height = 1;
	}
	virtual void print(){
		cout << "\n" << data;
	}
	virtual void setHeight(int h){
		height = h;
	}

	bool isLeaf() {
		if (!(this->getLeft() && this->getRight())) return true;
		return false;
	}
	int bfactor() { return (left != NULL ? left->getHeight() : -1) - (right != NULL ? right->getHeight() : -1); }
	
	void fixHeight() {
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
	

	template<typename K, class T> friend ostream& operator<< (ostream& stream, Node<K,T>& N);
};


template<typename K,class T>
ostream& operator<< (ostream& stream, Node<K,T>& N){
	stream << "\nNode data: " << N.data << ", height: " << N.height;
	return stream;
}


template<typename K,class T>
void print(Node<K,T>* N) { cout << "\n" << N->getData(); }



//класс итератор по дереву
template<typename K,class T>
class TreeIterator : public std::iterator<std::input_iterator_tag, K> {
private:
	Node<K, T>* ptr;
public:
	TreeIterator() { ptr = NULL;  }
	TreeIterator(Node<K,T>* p) { ptr = p; }
	TreeIterator(const TreeIterator& it) { ptr = it.ptr;  }

	TreeIterator& operator=(const TreeIterator& it) { ptr = it.ptr; return *this; }
	TreeIterator& operator=(Node<K,T>* p) { ptr = p.ptr; return *this; }

	bool operator!=(TreeIterator const& other) const { return other.ptr != ptr ? true : false; }
	bool operator==(TreeIterator const& other) const { return other.ptr == ptr ? true : false; }
	Node<K, T>& operator*() { return *ptr; }

	TreeIterator& operator++() {
		if (ptr->getRight()) {
			ptr = ptr->getRight();
			while (ptr->getLeft())
				ptr = ptr->getLeft();
		}
		else {
			while (ptr->getParent() && ptr->getParent()->getRight() == ptr)
				ptr = ptr->getParent();
			ptr = ptr->getParent();
		}
		return *this;
	}
	TreeIterator operator++(int v) {  //ссылка не нужна, тк temp удлаяется из памяти
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
	TreeIterator operator--(int v) {
		auto temp = *this;
		--(*this);
		return temp;
	}
};


template<typename K, class T>
class Tree {
protected:
	Node<K, T>* root;
public:
	virtual Node<K, T>* getRoot() { return root; }
	Tree<K, T>() { root = NULL; }
	
	virtual void push(K key, T n) {
		Node<K, T>* N = new Node<K, T>;
		N->setData(n);
		N->setKey(key);
		push_r(N, root);
	}

	virtual Node<K, T>* push_r(Node<K, T>* N, Node<K, T>* Current) {
		if (root == NULL) {
			root = N;
			return N;
		}
		if (Current->getKey() > N->getKey()) { //идем влево
			if (Current->getLeft() != NULL)
				Current->setLeft(push_r(N, Current->getLeft()));
			else 
				Current->setLeft(N);
			Current->getLeft()->setParent(Current);
		}
		if (Current->getKey() < N->getKey()) {
			//идем вправо
			if (Current->getRight() != NULL) 
				Current->setRight(push_r(N, Current->getRight()));
			else 
				Current->setRight(N);
			Current->getRight()->setParent(Current);
		}
		if (Current->getKey() == N->getKey()) { throw exception("Keys are similiar\n"); };
		Current->fixHeight();
		return Current;
	}



	virtual T pop(K key) {
		Node<K, T>* node = FindKey(key, root);
		T data = node->getData();
		if (node == NULL) return NULL;

		else if (node->isLeaf()) {
			if (node != root) {
				Node<K, T>* curr = node->getParent();
				if (node->getParent()->getLeft() == node)
					node->getParent()->setLeft(NULL);
				else
					node->getParent()->setRight(NULL);
				node->setParent(NULL);
				fixHeights(curr);
			}
			else { root = NULL; }
			delete node;
			return data;
		}
		else  if (node->getLeft() && node->getRight() == NULL) {
			Node<K, T>* repl = node->getLeft();
			if (node != root) {
				if (node->getParent()->getLeft() == node)
					node->getParent()->setLeft(repl);
				else
					node->getParent()->setRight(repl);
				repl->setParent(node->getParent());
			}
			else {
				repl->setParent(NULL);
				root = repl;
			}
			delete node;
			fixHeights(repl->getParent());
			return data;
		}
		else if (node->getRight() && node->getLeft() == NULL) {  // правый лист0к
			Node<K, T>* repl = node->getRight();
			if (node != root) {
				if (node->getParent()->getRight() == node)
					node->getParent()->setRight(repl);
				else
					node->getParent()->setLeft(repl);
				repl->setParent(node->getParent());
			}
			else {
				repl->setParent(NULL);
				root = repl;
			}
			delete node;
			fixHeights(repl->getParent());
			return data;

		}
		else if (node->getLeft() && node->getRight()) {
			Node<K, T>* repl = Min(node->getRight());

			if (repl->isLeaf()) {
				if (node->getParent()->getLeft() == node)
					node->getParent()->setLeft(NULL);
				else
					node->getParent()->setRight(NULL);
			}
			else if (repl != node->getRight()) {
				if (node->getParent()->getLeft() == node)
					node->getParent()->setLeft(repl->getRight());
				else
					node->getParent()->setRight(repl->getRight());
				repl->getRight()->setParent(repl->getParent());
				repl->setRight(node->getRight());
				node->getRight()->setParent(repl);
			}
			repl->setLeft(node->getLeft());
			node->getLeft()->setParent(repl);

			if (node != root)
			{
				if (node->getParent()->getLeft() == node)
					node->getParent()->setLeft(repl);
				else
					node->getParent()->setRight(repl);
				repl->setParent(node->getParent());
			}
			else
			{
				repl->setParent(NULL);
				root = repl;
			}
			delete node;
			fixHeights(repl->getParent());
			return data;
		}
	}
	
	
	virtual Node<K, T>* Min(Node<K, T>* Current = NULL) {
		//минимум - это самый "левый" узел. Идём по дереву всегда влево
		if (root == NULL) return NULL;
		if (Current == NULL)
			Current = root;
		while (Current->getLeft() != NULL)
			Current = Current->getLeft();
		return Current;
	}

	virtual Node<K, T>* Max(Node<K, T>* Current = NULL) {
		//минимум - это самый "правый" узел. Идём по дереву всегда вправо
		if (root == NULL) return NULL;
		if (Current == NULL)
			Current = root;
		while (Current->getRight() != NULL)
			Current = Current->getRight();
		return Current;
	}

	//поиск узла в дереве по значению. Второй параметр - в каком поддереве искать, первый - что искать
	virtual Node<K, T>* FindData(T data, Node<K, T>* Current) {
		//база рекурсии
		if (Current == NULL) return NULL;
		if (Current->getData() == data) return Current;
		//рекурсивный вызов
		if (Current->getData() > data) return FindData(data, Current->getLeft());
		if (Current->getData() < data) return FindData(data, Current->getRight());
	}

	virtual Node<K, T>* FindKey(K key, Node<K, T>* Current) {
		if (Current == NULL) return NULL;
		if (key == Current->getKey()) return Current;

		if (key < Current->getKey()) return FindKey(key, Current->getLeft());
		if (key > Current->getKey())  return FindKey(key, Current->getRight());
	}

	//три обхода дерева
	virtual void PreOrder(Node<K, T>* N, void (*f)(Node<K, T>*)) {
		if (N != NULL) f(N);
		if (N != NULL && N->getLeft() != NULL) PreOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL) PreOrder(N->getRight(), f);
	}

	//InOrder-обход даст отсортированную последовательность
	virtual void InOrder(Node<K, T>* N, void (*f)(Node<K, T>*)) {
		if (N != NULL && N->getLeft() != NULL) InOrder(N->getLeft(), f);

		if (N != NULL) f(N);

		if (N != NULL && N->getRight() != NULL) InOrder(N->getRight(), f);
	}

	virtual void PostOrder(Node<K, T>* N, void (*f)(Node<K, T>*)) {
		if (N != NULL && N->getLeft() != NULL) PostOrder(N->getLeft(), f);

		if (N != NULL && N->getRight() != NULL) PostOrder(N->getRight(), f);

		if (N != NULL) f(N);
	}
	void fixHeights(Node<K, T>* node) {
		if (node) {
			node->fixHeight();
			if (node->getParent() != NULL)
				fixHeights(node->getParent());
		}
	}
	
};
	
template<typename K,class T> 
Node<K,T>* print(Node<K, T>* node) {
	cout << node << "\n";
}



//класс итерируемое дерево поиска
template<typename K, class T>
class IteratedTree : public Tree<K, T> {
public:
	IteratedTree<K, T>() : Tree<K, T>() { cout << "\nIteratedTree constructor\n"; }
	virtual ~IteratedTree<K, T>() { cout << "\nIteratedTree desructor\n"; }

	TreeIterator<K, T> iterator;

	

	TreeIterator<K, T> begin() {                                            //Node<K, T>* node = Tree<K, T>::root; node = Tree<K, T>::Min(node); TreeIterator<K, T> it(node); return it;
		if (Tree<K, T>::root == NULL)  return NULL; 
		Node<K, T>* Current = Tree<K, T>::root;
		while (Current->getLeft() != NULL)  Current = Current->getLeft(); 
		TreeIterator<K, T> it = Current;
		return it;  
	}           
	TreeIterator<K, T> end() {
		if (Tree<K, T>::root == NULL) return NULL; 
		Node<K, T>* Current = Tree<K, T>::root;
		while (Current->getRight() != NULL)  Current = Current->getRight(); 
		TreeIterator<K, T> it = Current;
		return it;
	}
};




//AVL_Tree - потомок класса Tree, АВЛ-дерево (сбалансированное дерево поиска)
template<typename K,class T>
class AVL_Tree : public IteratedTree<K,T>{
public:
	
	Node<K, T>* RotateRight(Node<K,T>* p) {
		Node<K, T>* q = p->getLeft();

		p->setLeft(q->getRight());
		if (q->getRight())  p->getLeft()->setParent(p);
		

		q->setParent(p->getParent());
		p->setParent(q);
		q->setRight(p);
		if (this->getRoot() == p) 
			this->root = q;
		else
			q->getParent()->setLeft(q);
		this->fixHeights(p);
		//this->fixHeights(q);
		return q;
	}

	Node<K, T>* RotateLeft(Node<K, T>* q) {
		Node<K, T>* p = q->getRight();
		q->setRight(p->getLeft());
		
		if (p->getLeft()) q->getRight()->setParent(q);
		
		p->setParent(q->getParent());
		q->setParent(p);
		p->setLeft(q);
		if (this->getRoot() == q)
			this->root = p;
		else
			p->getParent()->setRight(p);
		this->fixHeights(p);
		this->fixHeights(q);
		return p;
	}
	

	virtual void BalanceSubTree(Node<K, T>* node)
	{
		if (node) {
			if (abs(node->bfactor()) == 2)
			{
				Balance(node);
				if (node->getParent() != NULL)
					BalanceSubTree(node->getParent()->getParent());
			}
			else
				BalanceSubTree(node->getParent());
		}
	}

	
	
	void Balance(Node<K, T>* node)
	{
		int bf = node->bfactor();
		if (bf == 2) {
			int leftBf = node->getLeft()->bfactor();
			if (leftBf > 0) {
				RotateRight(node);
				cout << endl << "Right Rotation" << *node << endl;
			}
			else {
				Node<K, T>* newNode = RotateLeft(node->getLeft());
				node->setLeft(newNode);
				RotateRight(newNode);
			}
		}
		else if (bf == -2) {
			int rightBf = node->getRight()->bfactor();
			if (rightBf < 0) {
				RotateLeft(node);
				cout << endl << "Left Rotation" << *node << endl;

			}
			else {
				Node<K, T>* newNode = RotateRight(node->getRight());
				node->setRight(newNode);
				RotateLeft(node);
			}
		}
	}
	

public:
	AVL_Tree<K, T>() : IteratedTree<K, T>() {};

	virtual void push(K key, T data) {
		IteratedTree<K, T>::push(key, data);
		Node<K, T>* node = this->FindKey(key,this->getRoot()) ;
		node = node->getParent();
		if (node == NULL)
			node = this->getRoot();
		BalanceSubTree(node);
	}

	virtual  T  pop(K key){ 
		Node<K, T>* node = this->FindKey(key, this->getRoot());
		node = node->getParent();
		if (!node)
			node = this->getRoot();
		T data = node->getData();
		IteratedTree<K, T>::pop(key);
		BalanceSubTree(node);
		return data;
	}
	
};



int main(){
	
	IteratedTree<double, double> T;
	T.push(8, 8);
	T.push(3, 3);
	T.push(1, 1);
	T.push(4, 4);
	T.push(7, 7);
	T.push(10, 10);
	T.push(14, 14);
	T.push(13, 13);
	//T.InOrder(T.getRoot(), print);
	cout << "\n---------\n";
	for (auto i = T.begin(); i != NULL; i++) { cout << *i << endl; }
	// 1) Delete leaf
	T.pop(13);

	// 2) Delete with one leaf
	T.pop(14);

	// 3) Delete with two kids
	T.pop(3);
	
	cout << "\n_Thats all_\n";
	for (auto i = T.begin(); i != NULL; i++) { cout << *i << endl; }
	cout << "Post Order\n";
	T.PostOrder(T.getRoot(), print);
	cout << "\nPre Order\n";
	T.PreOrder(T.getRoot(), print);
	
	cout << "\nAVL TREE TESTING" << "\n";
	
	AVL_Tree<double, double> AVL_T;
	
	AVL_T.push(6, 6);
	AVL_T.push(7, 7);
	AVL_T.push(4, 4);
	AVL_T.push(3, 3);
	AVL_T.push(5, 5);
	AVL_T.push(2, 2);
	AVL_T.push(1, 1);
	
	for (auto i = AVL_T.begin(); i != NULL;i++) {
		cout << *i << "\n";
	}
	
	
	char c; cin >> c;
	return 0;
}

