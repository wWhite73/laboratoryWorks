#include "Stack.h"
#include <iostream>

Stack::Stack() {
	this->tail = nullptr;
}
void Stack::push(int data) {
	Node* head = new Node;
	head->data = data;
	head->next = this->tail;
	this->tail = head;
}
int Stack:: pop() {
	if (this->tail == nullptr) {
	//	throw "Stack is empty";
		std::cout << "fuck you stack\n";
		return -42;
	}
	Node* head;
	int data = this->tail->data;
	head = this->tail;
	this->tail = this->tail->next;
	delete head;
	return data;
}

bool Stack::length() {
	if (this->tail == nullptr) return 0;
	return 1;
}
