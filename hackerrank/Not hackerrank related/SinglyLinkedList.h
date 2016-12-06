#pragma once

#include "SinglyLinkedListItem.h"

template <class T>
class SinglyLinkedList {
public:
	SinglyLinkedList() : head(NULL){}
	~SinglyLinkedList(){
		SinglyLinkedListItem<T>* currentItem = head;
		SinglyLinkedListItem<T>* temp;
		while (currentItem != NULL){
			temp = currentItem;
			currentItem = currentItem->getNext();
			delete temp;
		}
	}

	void insertFront(SinglyLinkedListItem<T>* item){
		if (head == NULL){
			head = item;
			return;
		}

		item->setNext(head);
		head = item;
	}

	void insertBack(SinglyLinkedListItem<T>* item){
		if (head == NULL){
			head = item;
			return;
		}
		
		SinglyLinkedListItem<T>* backItem = back();
		backItem->setNext(item);
	}

	void erase(SinglyLinkedListItem<T>* toDelete){
		if (head == NULL) return;
		if (toDelete == head){
			SinglyLinkedListItem<T>* temp = head;
			head = head->getNext();
			delete temp;
			return;
		}

		SinglyLinkedListItem<T>* previous = findPrevious(toDelete);
		if (previous != NULL){
			SinglyLinkedListItem<T>* temp = previous->getNext();
			previous->setNext(temp->getNext());
			delete temp;
		}
	}

	SinglyLinkedListItem<T>* getHead(){
		return head;
	}

	SinglyLinkedListItem<T>* back(){
		SinglyLinkedListItem<T>* currentItem = head;
		while (currentItem != NULL && currentItem->getNext() != NULL){
			currentItem = currentItem->getNext();
		}
		return currentItem;
	}

	SinglyLinkedListItem<T>* find(const T& data){
		SinglyLinkedListItem<T>* currentItem = head;
		while (currentItem != NULL && currentItem->getData() != data){
			currentItem = currentItem->getNext();
		}
		return currentItem;
	}

	SinglyLinkedListItem<T>* findPrevious(const T& data){
		if (head != NULL && head->getData() == data)
			return head;

		SinglyLinkedListItem<T>* currentItem = head;
		while (currentItem != NULL && currentItem->getNext() != NULL && currentItem->getNext()->getData() != data){
			currentItem = currentItem->getNext();
		}
		return currentItem;
	}

private:
	SinglyLinkedListItem<T>* findPrevious(SinglyLinkedListItem<T>* item){
		if (head == item)
			return head;

		SinglyLinkedListItem<T>* currentItem = head;
		while (currentItem != NULL && currentItem->getNext() != item){
			currentItem = currentItem->getNext();
		}
		return currentItem;
	}

	SinglyLinkedListItem<T>* head;
};