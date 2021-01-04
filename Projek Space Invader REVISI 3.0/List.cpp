#include "List.h"

Node::Node(int data) {
	this->data = data;
}

int Node::getData() {
	return this->data;
}

Node::~Node() { }

List::List() {
	this->head = NULL;
	this->tail = NULL;
	this->list_size = 0;
}

Node* List::getHead() {
	return this->head;
}

Node* List::getTail() {
	return this->tail;
}

void List::addNodeAsTail(Node* new_node) {
	new_node->next = NULL;
	new_node->previous = NULL;

	if (this->head == NULL) {
		this->head = new_node;
		this->tail = this->head;
		this->list_size = this->list_size + 1;
	}
	else {
		this->tail->next = new_node;
		new_node->previous = this->tail;
		this->tail = new_node;
		this->list_size = this->list_size + 1;
	}
}

void List::push(Node* new_node) {
	this->addNodeAsTail(new_node);
}

void List::printList() {
	cout << "DATA: ";
	Node* temp = this->head;
	while (temp) {
		cout << temp->getData() << " -> ";
		temp = temp->next;
	}
}

int List::pop() {
	int temp = this->head->getData();
	this->head = this->head->next;
	this->head->previous = NULL;
	this->list_size = this->list_size - 1;
	return temp;
}

void List::reset()
{
	Node* temp = this->head;
	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
}