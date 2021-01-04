#pragma once
#include "object.h"
#include <iostream>

using namespace std;

class Node {
public:
	int data;
	Node* next;
	Node* previous;
	Node(int data);
	int getData();
	~Node();
};

class List {
public:
	Node* head;
	Node* tail;
	int list_size;
	List();
	Node* getHead();
	Node* getTail();
	void addNodeAsTail(Node* new_node);
	void push(Node* new_node);
	void printList();
	int pop();
	void reset();
};


