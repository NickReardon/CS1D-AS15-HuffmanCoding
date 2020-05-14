/*****************************************************************************
 * AUTHOR 	  		: Nick Reardon
 * Assignment #15	: Huffman Coding
 * CLASS			: CS1D
 * SECTION			: MW - 2:30p
 * DUE DATE			: 05 / 13 / 20
 *****************************************************************************/
#ifndef LIST_H_
#define LIST_H_

#include "DoubleLinked.h"
template <typename Type>
class List
{
public:
	class Iterator;


	Iterator  Begin() const;
	Iterator  End()   const;
	int       Size()  const;
	bool      Empty() const;
	Type& Front();
	Iterator  Search(const Type& key) const;

 

	void Insert(const Type& newType,     
			    const Iterator& beforeHere);
	void InsertFront(const Type& newType);
	void InsertBack(const Type& newType); 
	void Erase(Iterator toErase); 
	void Erase(const Type& toErase);

private:
	DoubleLinked<Type> D;
};

template <typename Type>
class List<Type>::Iterator
{
	typedef DLLNode<Type> node;

	public:
		Iterator(){currentNode = NULL; endNode = new node;}
		~Iterator(){currentNode = NULL;endNode = NULL;}

		bool operator==(const Iterator& compareTo) const{return currentNode == compareTo.currentNode &&endNode == compareTo.IsEnd();}
		bool operator!=(const Iterator& compareTo) const{return currentNode != compareTo.currentNode ||endNode != compareTo.IsEnd();}

		Type& operator*() const{return currentNode->ModType();}
		node* operator->() const{return currentNode;}

		Iterator& operator++()
		{
			if(currentNode->GetNext()->GetNext() != NULL)
				currentNode = currentNode->GetNext();
			else
				endNode = true;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator saveState = *this;
			if(currentNode->GetNext()->GetNext() != NULL)
				currentNode = currentNode->GetNext();
			else
				endNode = true;
			return saveState;
		}
		Iterator& operator--()
		{
			if(endNode)
				endNode = false;
			else if(currentNode->GetPrev() != NULL)
				currentNode = currentNode->GetPrev();
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator saveState = *this;
			if(endNode)
				endNode = false;
			else if(currentNode->GetPrev() != NULL)
				currentNode = currentNode->GetPrev();
			return saveState;
		}

	private:
		friend class List<Type>;

		Iterator(node* pointHere, bool endFlag){currentNode = pointHere;  endNode = endFlag;}
		node* GetCurrentNode() const {return currentNode;}
		bool IsEnd() const {return endNode;}

		node* currentNode;
		bool  endNode;
};

template <typename Type>
typename List<Type>::Iterator List<Type>::Begin() const
{
	if(!D.IsEmpty())
	{
		return Iterator(D.GetHead(), false);
	}
	else
	{
		return End();
	}

}

template <typename Type>
typename List<Type>::Iterator List<Type>::End() const
{
	return Iterator(D.GetTail(), true);
}

template <typename Type>
int List<Type>::Size() const
{
	return D.Size();
}

template <typename Type>
bool List<Type>::Empty() const
{
	return D.IsEmpty();
}

template <typename Type>
typename List<Type>::Iterator List<Type>::Search(const Type& key) const
{
	Iterator searchIt;

	searchIt = Begin();
	while(searchIt != End() && (*searchIt) != key)
	{
		++searchIt;
	}

	return searchIt;
}

template <typename Type>
Type& List<Type>::Front()
{
	return D.Front();
}

template <typename Type>
void List<Type>::Insert(const Type& newType,
		                    const Iterator& beforeHere)
{
	D.Add(newType, beforeHere.GetCurrentNode());
}

template <typename Type>
void List<Type>::InsertFront(const Type& newType)
{
	D.AddFront(newType);
}

template <typename Type>
void List<Type>::InsertBack(const Type& newType)
{
	D.AddBack(newType);
}

template <typename Type>
void List<Type>::Erase(const Type& toErase)
{
	D.Delete(Search(toErase).GetCurrentNode());
}

template <typename Type>
void List<Type>::Erase(List<Type>::Iterator toErase)
{
	D.Delete(toErase.GetCurrentNode());
}

#endif /* LIST_H_ */
