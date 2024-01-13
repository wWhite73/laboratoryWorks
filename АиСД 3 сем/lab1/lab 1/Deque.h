#pragma once
#include "Node.h"

class Deque {
	DequeNode* head;
	DequeNode* tail;
public:
	Deque();
	void push_front(int data);
	void push_back(int data);
	int pop_front();
	int pop_back();
	bool length();
};
