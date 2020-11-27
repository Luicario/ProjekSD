#include<iostream>

using namespace std;

class Node{

public:
	int data;
	Node* next;

};

class cstack{
public:

	void push(Node** head, int n)
	{
		Node* new_node = new Node();
		new_node->data = n;
		new_node->next = (*head);
		(*head) = new_node;
	}

	void printList(Node* node)
	{
		while (node != NULL)
		{
			cout << node->data << " ";
			node = node->next;
		}
		cout << endl;
	}

	void deleteNode(Node** head, int n)
	{
		Node* Temp = *head;
		Node* x = NULL;

		if (Temp != NULL && Temp->data == n)
		{
			*head = Temp->next;
			delete Temp;
			return;
		}

		while (Temp != NULL && Temp->data != n)
		{
			x = Temp;
			Temp = Temp->next;
		}

		if (Temp == NULL){
			return;
		}

		x->next = Temp->next;

		delete Temp;
	}


};

void main(){
	cstack arrlist;
	Node* head = NULL;
	int x, y;

	cout << "Input banyak angka yang mau di masukkan : ";
	cin >> x;
	for (int i = 0; i < x; i++){
		cout << "Input Angka : ";
		cin >> y;
		arrlist.push(&head, y);
	}

	cout << "Linked list yang sudah terbentuk : ";
	arrlist.printList(head);


	int z;
	cout << "Input angka yang mau di delete : ";
	cin >> z;

	arrlist.deleteNode(&head, z);

	arrlist.printList(head);
}