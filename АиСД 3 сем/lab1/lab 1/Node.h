#pragma once

class Node {
public:
	int data;
	Node* next;
};

class DequeNode {
public:
	int data;
	DequeNode* next;
	DequeNode* prev;
};