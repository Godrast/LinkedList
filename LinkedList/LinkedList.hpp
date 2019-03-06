#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T>
struct Node {
	T val;
	Node *next;
};


template <typename T>
class LinkedList {


public:
	LinkedList();
	~LinkedList();
	void push(T value);
	void pushToEnd(T value);
	T pop();
	T top();
	void sort();
	void show();
	void show(void(*showFunction)(T));
	void sort(bool(*compare)(T, T));
	Node<T> *getHead();

	void setDefaultShowMethod(void(*func)(T));
	void setDefaultCompareMethod(bool(*func)(T, T));

private:
	Node<T> *head = nullptr;

	void(*defaultShow)(T) = nullptr;
	bool(*defaultCompare)(T, T) = nullptr;

	void privateSort(Node<T> **headTemp);
	void privateSort(Node<T> **headTemp, bool(*compare)(T, T));
	void splitList(Node<T> *source, Node<T> **front, Node<T> **end);
	Node<T>* sortedMerge(Node<T> *head1, Node<T> *head2);
	Node<T>* sortedMerge(Node<T> *head1, Node<T> *head2, bool(*compare)(T, T));
	void moveNode(Node<T> **dest, Node<T> **source);
	void show(Node<T> *head);
};

template <typename T>
void LinkedList<T>::setDefaultCompareMethod(bool(*func)(T, T)) {
	defaultCompare = func;
}

template <typename T>
void LinkedList<T>::setDefaultShowMethod(void(*func)(T)) {
	defaultShow = func;
}

template <typename T>
Node<T> *LinkedList<T>::getHead() {
	return head;
}

template <typename T>
void LinkedList<T>::show(void(*showFunction)(T)) {
	Node<T> *next = head;

	while (next) {
		(*showFunction)(next->val);
		next = next->next;
	}
}

template <typename T>
Node<T>* LinkedList<T>::sortedMerge(Node<T> *head1, Node<T> *head2, bool(*compare)(T, T)) {

	Node<T> dummyNode;
	Node<T> *tail = &dummyNode;
	dummyNode.next = nullptr;
	while (1) {
		if (head1 == nullptr) {
			tail->next = head2;
			break;
		} else if (head2 == nullptr) {
			tail->next = head1;
			break;
		}
		if ((*compare)(head1->val, head2->val)) {
			moveNode(&(tail->next), &head1);
		} else {
			moveNode(&(tail->next), &head2);
		}
		tail = tail->next;

	}

	return dummyNode.next;

}

template <typename T>
void LinkedList<T>::privateSort(Node<T> **headTemp, bool(*compare)(T, T)) {

	Node<T> *headRef = *headTemp;
	Node<T> *head1, *head2;
	if (headRef == nullptr || headRef->next == nullptr) {
		return;
	}

	splitList(headRef, &head1, &head2);

	privateSort(&head1, compare);
	privateSort(&head2, compare);

	*headTemp = sortedMerge(head1, head2, compare);
}

template <typename T>
void LinkedList<T>::sort(bool(*compare)(T, T)) {
	privateSort(&head, compare);
}


template <typename T>
void LinkedList<T>::show() {
	Node<T> *next = head;

	while (next) {
		if (defaultShow == nullptr) {
			std::cout << next->val << "\n";
		} else {
			(*defaultShow)(next->val);

		}
		next = next->next;
	}
	std::cout << "\n";
}

template <typename T>
void LinkedList<T>::show(Node<T> *head) {
	Node<T> *next = head;

	while (next) {
		std::cout << next->val << "\n";
		next = next->next;
	}
	std::cout << "\n\n";
}

template <typename T>
void LinkedList<T>::moveNode(Node<T> **dest, Node<T> **source) {
	Node<T> *newNode = *source;
	if (newNode == nullptr) return;

	*source = newNode->next;
	newNode->next = *dest;

	*dest = newNode;
}

template <typename T>
Node<T>* LinkedList<T>::sortedMerge(Node<T> *head1, Node<T> *head2) {

	Node<T> dummyNode;
	Node<T> *tail = &dummyNode;
	dummyNode.next = nullptr;
	while (1) {
		if (head1 == nullptr) {
			tail->next = head2;
			break;
		} else if (head2 == nullptr) {
			tail->next = head1;
			break;
		}
		bool temp;
		if (defaultCompare != nullptr) {
			temp = (*defaultCompare)(head1->val, head2->val);
		} else {
			temp = head1->val < head2->val;
		}
		if (temp) {
			moveNode(&(tail->next), &head1);
		} else {
			moveNode(&(tail->next), &head2);
		}
		tail = tail->next;

	}

	return dummyNode.next;

}

template <typename T>
void LinkedList<T>::splitList(Node<T> *source, Node<T> **front, Node<T> **end) {
	Node<T> *fast, *slow;

	slow = source;
	fast = source->next;

	while (fast != nullptr) {

		fast = fast->next;
		if (fast != nullptr) {

			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = source;
	*end = slow->next;
	slow->next = nullptr;
}


template <typename T>
void LinkedList<T>::privateSort(Node<T> **headTemp) {

	Node<T> *headRef = *headTemp;
	Node<T> *head1, *head2;
	if (headRef == nullptr || headRef->next == nullptr) {
		return;
	}

	splitList(headRef, &head1, &head2);

	privateSort(&head1);
	privateSort(&head2);

	*headTemp = sortedMerge(head1, head2);

}

template <typename T>
void LinkedList<T>::sort() {
	privateSort(&head);
}

template <typename T>
LinkedList<T>::LinkedList() {
	head = nullptr;

}


template <typename T>
LinkedList<T>::~LinkedList() {
	Node<T> *next = head;

	while (next) {
		Node<T> * temp = next;
		next = next->next;
		delete temp;
	}
}

template<typename T>
void LinkedList<T>::push(T value) {
	Node<T> * newNode = new Node<T>();
	newNode->val = value;
	newNode->next = head;
	head = newNode;
}

template<typename T>
void LinkedList<T>::pushToEnd(T value) {
	Node<T> * newNode = new Node<T>();
	newNode->val = value;
	newNode->next = nullptr;

	Node<T> * next = head;

	if (!next) {
		head = newNode;
		return;
	}

	while (next->next) {
		next = next->next;
	}
	next->next = newNode;



}


template <typename T>
T LinkedList<T>::pop() {
	if (head != nullptr) {
		Node<T> *temp = head;
		T ret = temp->val;
		head = head->next;

		delete temp;
		return ret;
	}
	return NULL;
}

template <typename T>
T LinkedList<T>::top() {
	if (head != nullptr)
		return head->val;
	return NULL;
}



#endif //!LINKEDLIST_H