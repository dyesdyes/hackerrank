#pragma once

template <class T>
class SinglyLinkedListItem {

public:
	SinglyLinkedListItem(T& data) : next(NULL),data(data){}
	~SinglyLinkedListItem(){}

	SinglyLinkedListItem* getNext(){return next;}
	const T& getData(){return data;}
	void setNext(SinglyLinkedListItem* n){ next = n;}
	void setData(const T& d){data = d;}

private:
	SinglyLinkedListItem* next;
	T data;
};