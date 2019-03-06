#include <iostream>
#include "LinkedList.hpp"
#include <time.h>

bool compareMethod(float, float);
void showTest(float);
void tempShow(float);

int main() {
	srand(time(NULL));
	LinkedList<float> *list = new LinkedList<float>();

	for (int i = 0; i < 10; i++) {
		list->push(rand() % 100);
		//float t;
		//std::cin >> t;
		//list->pushToEnd(t);
	}


	std::cout << "\n\n";

	list->show();


	std::cout << "AFTER SORTING:\n";
	list->sort();
	list->show();

	std::cout << "After assigning default methods:\n";
	list->setDefaultCompareMethod(&compareMethod);
	list->setDefaultShowMethod(&showTest);
	list->sort();
	list->show();

	std::cout << "\n\n";
	list->setDefaultShowMethod(nullptr);
	list->show();
	//	std::cout << list->pop();

	delete list;

	std::cin.get();
	std::cin.get();
	return 0;
}

void tempShow(float val) {
	std::cout << "hai Arek" << val << "\n";
}
void showTest(float val) {
	std::cout << "AAA " << val << "\n";
}

bool compareMethod(float a, float b) {

	return a > b;

}