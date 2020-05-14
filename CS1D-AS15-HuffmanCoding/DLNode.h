/*****************************************************************************
 * AUTHOR 	  		: Nick Reardon
 * Assignment #15	: Huffman Coding
 * CLASS			: CS1D
 * SECTION			: MW - 2:30p
 * DUE DATE			: 05 / 13 / 20
 *****************************************************************************/
#ifndef DLNODE_H_
#define DLNODE_H_

template <class Type>
class DLLNode
{
	typedef DLLNode <Type> node;

private:
	node* next;
	node* prev;
	Type type;

protected:

public:

	DLLNode()
	{
		prev = NULL;
		next = NULL;
	}

	~DLLNode()
	{
		prev = NULL;
		next = NULL;
	}

	node* GetNext() const
	{
		return next;
	}

	node* GetPrev() const
	{
		return prev;
	}

	const Type& GetType() const
	{
		return type;
	}

	void SetNext(node* nextNode)
	{
		next = nextNode;
	}

	void SetPrev(node* prevNode)
	{
		prev = prevNode;
	}

	void SetType(const Type& data)
	{
		const Type* typePtr = &data;
		type = *typePtr;
	}

	Type& ModType()
	{
		return type;
	}

};



#endif /* DLNODE_H_ */

