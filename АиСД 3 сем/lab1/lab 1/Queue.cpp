#include "Queue.h"
#include <iostream>
	Queue::Queue() {
		this->head = nullptr;
		this->tail = nullptr;
	}
	void Queue::push(int data) {
		if (this->head == nullptr) {
			Node* new_head = new Node;
			new_head->data = data;
			new_head->next = nullptr;

			this->head = new_head;
			this->tail = this->head;
		}
		else {
			Node* new_tail = new Node;
			new_tail->data = data;
			new_tail->next = nullptr;

			//	this->head->next = new_tail;
			this->tail->next = new_tail;
			this->tail = new_tail;
		}
	}
	int Queue::pop() {
		if (this->head == nullptr) {
			//throw "Queue is empty";
			std::cout << "fuck you queue\n";
			return -42;
		}
		int data = this->head->data;
		this->head = this->head->next;
		return data;
	}
	bool Queue::length() {
		if (this->head == nullptr) return 0;
		return 1;
	}
