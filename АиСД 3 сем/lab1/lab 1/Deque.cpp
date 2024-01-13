#include "Deque.h"
#include <iostream>


	Deque::Deque() {
		this->head = nullptr;
		this->tail = this->tail;
	}
	void Deque::push_front(int data) {
		if (this->head == nullptr) {
			DequeNode* new_head = new DequeNode;
			new_head->data = data;
			new_head->next = nullptr;
			new_head->prev = nullptr;

			this->head = new_head;
			this->tail = new_head;
		}
		else {
			DequeNode* new_head = new DequeNode;
			new_head->data = data;
			new_head->next = this->head;
			new_head->prev = nullptr;

			this->head->prev = new_head;
			this->head = new_head;
		}
	}

	void Deque::push_back(int data) {
		if (this->tail == nullptr) {
			DequeNode* new_head = new DequeNode;
			new_head->data = data;
			new_head->next = nullptr;
			new_head->prev = nullptr;

			this->head = new_head;
			this->tail = new_head;
		}
		else {
			DequeNode* new_tail = new DequeNode;
			new_tail->data = data;
			new_tail->next = nullptr;
			new_tail->prev = this->tail;

			this->tail->next = new_tail;
			this->tail = new_tail;
		}
	}

	int Deque::pop_front() {
		if (this->head == nullptr) {
			//throw "Deque is empty";
			std::cout << "fuck you deque\n";
			return -42;
		};
		int data = this->head->data;
		DequeNode* bin = this->head;
		this->head = this->head->next;
		delete bin;
		return data;
	}

	int Deque::pop_back() {
		if (this->tail == nullptr) {
			//throw "Deque is empty";
			std::cout << "fuck you\n";
			return -42;
		};
		int data = this->tail->data;
		DequeNode* bin = this->tail;
		this->tail = this->tail->prev;
		delete bin;
		return data;
	}

	bool Deque::length() {
		if (this->head == nullptr) return 0;
		return 1;
	}
