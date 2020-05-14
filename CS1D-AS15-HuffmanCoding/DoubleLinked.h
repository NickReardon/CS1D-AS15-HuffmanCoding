/*****************************************************************************
 * AUTHOR 	  		: Nick Reardon
 * Assignment #15	: Huffman Coding
 * CLASS			: CS1D
 * SECTION			: MW - 2:30p
 * DUE DATE			: 05 / 13 / 20
 *****************************************************************************/
#ifndef DOUBLELINKED_H_
#define DOUBLELINKED_H_

#include "DLNode.h"
template <class Type>
class DoubleLinked
{
	typedef DLLNode<Type> node;

private:
	node* head;
	node* tail;
	int   size;

protected:

public:
	DoubleLinked()
	{
		head = new node;
		tail = new node;

		head->SetNext(tail);
		tail->SetPrev(head);

		size = 0;
	}

	node* GetHead() const
	{
		return head->GetNext();
	}

	node* GetTail() const
	{
		return tail->GetPrev();
	}


	bool  IsEmpty() const
	{
		return size == 0;
	}

	int   Size()    const
	{
		return size;
	}

	Type& Front() const
	{
		return head->GetNext()->ModType();
	}

	const Type& Back()  const
	{
		return tail->GetPrev()->GetType();
	}

	void Add(const Type& newType, node* beforeHere)
	{

		node* newNode = new node;
		newNode->SetNext(beforeHere);
		newNode->SetPrev(beforeHere->GetPrev());
		newNode->SetType(newType);

		beforeHere->GetPrev()->SetNext(newNode);
		beforeHere->SetPrev(newNode);

		size++;
	}

	void AddFront(const Type& newType)
	{
		Add(newType, head->GetNext());
	}

	void AddBack(const Type& newType)
	{
		Add(newType, tail);
	}

	void Delete(node* toDelete)
	{

		toDelete->GetNext()->SetPrev(toDelete->GetPrev());
		toDelete->GetPrev()->SetNext(toDelete->GetNext());

		size--;

		delete toDelete;
	}

	void DeleteFront()
	{
		if (head->GetNext() != tail)
		{
			Delete(head->GetNext());
		}

	}

	void DeleteBack()
	{
		{
			Delete(tail->GetPrev());
		}
	}

};


#endif /* DOUBLELINKED_H_ */
