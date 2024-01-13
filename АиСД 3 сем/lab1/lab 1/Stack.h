#pragma once
#include "Node.h"

class Stack {
	Node* tail;
public:
	Stack();
	void push(int data);
	int pop();
	bool length();
};