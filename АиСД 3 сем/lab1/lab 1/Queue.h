#pragma once
#include "Node.h"

class Queue {
	Node* head;
	Node* tail;
public:
	Queue();
	void push(int data);
	int pop();
	bool length();
};