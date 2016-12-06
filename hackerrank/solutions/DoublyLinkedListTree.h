#pragma once

#include <cstdlib>

class DoublyLinkedListTree {
public:
	struct Node {
		Node* next;
		Node* previous;
		Node* child;
		int value;
	};

	void flattenList(){
		if (head == NULL || tail == NULL)
			return;

		Node* current = tail;
		while (current){
			if (current->child){
				appendNodesToTail(current->child);
				current->child = NULL;
			}
			current = current->previous;
		}
	}

	void appendNodesToTail(Node* node){
		Node* current = node;
		while (current){
			tail->next = current;
			tail = current;
			if (current->child){
				appendNodesToTail(current->child);
				current->child = NULL;
			}
			current = current->next;
		}
	}

private:
	Node* head;
	Node* tail;
};