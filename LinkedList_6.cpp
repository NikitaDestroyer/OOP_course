// LinkedList_6.cpp : Defines the entry point for the application.
//

#include "LinkedList_6.h"

using namespace std;

int main() {
	//LinkedList<double>* p = new Stack<double>; //тут, деструктурируя, удалится только базовый класс, но не удалятся его дети, утечет пямять (при delete) очистить можем только делитом ((((
	//LinkedList<double>* p2; Stack<double> S; p2 = &S; //Это старый подход,здесь удаление работает нормально и очащяя память delete - не нужен !!!!

	Stack<double> S;

	//S.push(1);
	//S.push(2);
	cout << S;





	char c; cin >> c;
}