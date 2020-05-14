/*****************************************************************************
 * AUTHOR 	  		: Nick Reardon
 * Assignment #15	: Huffman Coding
 * CLASS			: CS1D
 * SECTION			: MW - 2:30p
 * DUE DATE			: 05 / 13 / 20
 *****************************************************************************/
#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include "BinaryTreeNode.h"

template <typename Type>
class HuffmanTree
{
	protected:
		typedef BTNode<Type> node;

	public:
		HuffmanTree();

		HuffmanTree(BTNode<Type>* rootInit);

		virtual ~HuffmanTree();


		int Height() const;

		int Size() const;

		int LeafCount() const;

		bool Search(const Type& key) const;

		string HuffmanSearch(char key) const;

		void Print() const;

		node* GetRoot();

		void Add(const Type& newType);

		virtual bool Delete(const Type& toDelete);

		void Destroy();

	protected:
		node* root;

		int Max(int x, int y) const;

		int Height(node* rootNode) const;

		int Size(node* rootNode) const;

		virtual node* Search(const Type& key, node* rootNode) const;

		string HuffmanSearch(char key, node* rootNode) const;

		void PrintLevel(node* rootNode, int level) const;

		virtual void Add(const Type& newType, node* rootNode);

		void Destroy(node* rootNode);
};

template <typename Type>
HuffmanTree<Type>::HuffmanTree()
{
	root = NULL;
}

template <typename Type>
HuffmanTree<Type>::HuffmanTree(BTNode<Type>* rootInit)
{
	root = rootInit;
}

template <typename Type>
HuffmanTree<Type>::~HuffmanTree()
{
	Destroy();
	root = NULL;
}

template <typename Type>
int HuffmanTree<Type>::Height() const
{
	return Height(root);
}

template <typename Type>
int HuffmanTree<Type>::Height(node* rootNode) const
{
	int height;

	if (rootNode == NULL)
	{
		height = 0;
	}
	else
	{
		height = 1 + Max(Height(rootNode->GetLeft()), Height(rootNode->GetRight()));
	}

	return height;
}

template <typename Type>
int HuffmanTree<Type>::Size() const
{
	return Size(root);
}

template <typename Type>
int HuffmanTree<Type>::Size(node* rootNode) const
{
	int size;

	if (rootNode == NULL)
	{
		size = 0;
	}
	else
	{
		size = 1 + Size(rootNode->GetLeft()) + Size(rootNode->GetRight());
	}

	return size;
}
template <typename Type>
bool HuffmanTree<Type>::Search(const Type& key) const
{
	if(root->GetType() == key)
	{
		return true;
	}
	else
	{
		return Search(key, root->GetLeft()) !=  NULL ||Search(key, root->GetRight()) != NULL;
	}
}

template <typename Type>
BTNode<Type>* HuffmanTree<Type>::Search(const Type& key, node* rootNode) const
{
	node* returnPtr;

	if(rootNode->GetType() == key)
	{
		return rootNode;
	}
	else
	{
		returnPtr = Search(key, rootNode->GetLeft());
		if(returnPtr  == NULL)
		{
			return Search(key, rootNode->GetRight());
		}
		else
		{
			return returnPtr;
		}
	}
}

template <typename Type>
string HuffmanTree<Type>::HuffmanSearch(char key) const
{
	return HuffmanSearch(key, root);
}

template <typename Type>
string HuffmanTree<Type>::HuffmanSearch(char key, node* rootNode) const
{
	string code;
	node*  nodePtr;

	code = "";
	nodePtr = rootNode;

	if(rootNode->GetType().symbol == key)
	{
		while(nodePtr != root)
		{
			if(nodePtr->IsLeftChild())
			{
				code = "0" + code;
			}
			else
			{
				code = "1" + code;
			}

			nodePtr = nodePtr->GetParent();
		}
	}
	else if (rootNode->GetRight() != NULL)
	{
		code = HuffmanSearch(key, rootNode->GetRight());

		if(code == "")
		{
			code = HuffmanSearch(key, rootNode->GetLeft());
		}
	}
	else if (rootNode->GetLeft() != NULL)
	{
		code = HuffmanSearch(key, rootNode->GetLeft());
	}

	return code;
}

template <typename Type>
void HuffmanTree<Type>::Print() const
{
	if(root->GetLeft() == NULL && root->GetRight() == NULL)
	{
		cout << "ROOT: " << root->GetType().symbol << endl;
	}
	else
	{
		for(int i = 1; i <= Height(); ++i)
		{
			cout << "Level " << i-1 << ": ";
			PrintLevel(root, i);
			cout << endl;
		}
	}
}

template <typename Type>
void HuffmanTree<Type>::PrintLevel(node* rootNode, int level) const
{
	if(root == NULL)
	{
		return;
	}
	else if (level == 1)
	{
		if (rootNode->GetType().symbol == ' ')
		{
			cout << '(' << "space" << " ";
			cout << rootNode->GetType().weight << ')' << " ";
		}
		else if(rootNode->GetType().symbol != 0)
		{
			cout << '(' << rootNode->GetType().symbol << " ";
			cout << rootNode->GetType().weight << ')' << " ";
		}
		else
		{
			cout << '(' << rootNode->GetType().weight << ')' << " ";
		}
	}
	else if(level > 1)
	{
		if(rootNode->GetLeft() != NULL)
		{
			PrintLevel(rootNode->GetLeft(),  level - 1);
		}

		if(rootNode->GetRight() != NULL)
		{
			PrintLevel(rootNode->GetRight(), level - 1);
		}

	}
}

template <typename Type>
BTNode<Type>* HuffmanTree<Type>::GetRoot()
{
	return root;
}


template <typename Type>
void HuffmanTree<Type>::Add(const Type& newType)
{
	 if (root == NULL)
	 {
		 root = new node;
		 root->elem   = newType;
		 root->left   = NULL;
		 root->right  = NULL;
		 root->parent = NULL;
	 }
	 else
	 {
		 Add(newType, root);
	 }
}

template <typename Type>
void HuffmanTree<Type>::Add(const Type& newType, node* rootNode)
{
	if(rootNode->GetLeft() == NULL)
	{
		rootNode->SetLeft(new node);
		rootNode->GetLeft()->SetType(newType);
		rootNode->GetLeft()->SetLeft(NULL);
		rootNode->GetLeft()->SetRight(NULL);
		rootNode->GetLeft()->SetParent(rootNode);
	}
	else if(rootNode->GetRight() == NULL)
	{
		rootNode->SetRight(new node);
		rootNode->GetRight()->SetType(newType);
		rootNode->GetRight()->SetLeft(NULL);
		rootNode->GetRight()->SetRight(NULL);
		rootNode->GetRight()->SetParent(rootNode);
	}
	else
	{
		if (Size(rootNode->GetLeft()) <= Size(rootNode->GetRight()))
		{
			Add(newType, rootNode->GetLeft());
		}
		else
		{
			Add(newType, rootNode->GetRight());
		}
	}
}


template <typename Type>
bool HuffmanTree<Type>::Delete(const Type& toDelete)
{
	node* replacePtr;
	node* delPtr;
	bool  success;

	replacePtr  = root;
	delPtr      = Search(toDelete, root);
	success     = delPtr != NULL;

	if (success && !delPtr->IsExternal())
	{
		while (replacePtr->GetLeft() != NULL)
		{
			replacePtr = replacePtr->GetLeft();
		}

		if (replacePtr->GetRight() != NULL)
		{
			replacePtr = replacePtr->GetRight();
		}


		if (replacePtr->IsLeftChild())
		{
			replacePtr->GetParent()->SetLeft(NULL);
		}
		else
		{
			replacePtr->GetParent()->SetRight(NULL);
		}

		replacePtr->SetParent(delPtr->GetParent());
		replacePtr->SetLeft(delPtr->GetLeft());
		replacePtr->SetRight(delPtr->GetRight());
	}

	if (success)
	{
		delete delPtr;
	}

	return success;
}

template <typename Type>
void HuffmanTree<Type>::Destroy()
{
	if (root != NULL)
	{
		Destroy(root);
		root = NULL;
	}
}

template <typename Type>
void HuffmanTree<Type>::Destroy(node* rootNode)
{
	if (rootNode->GetLeft() != NULL)
	{
		Destroy(rootNode->GetLeft());
	}

	if (rootNode->GetRight() != NULL)
	{
		Destroy(rootNode->GetRight());
	}

	delete rootNode;
}

template <typename Type>
int HuffmanTree<Type>::Max(int x, int y) const
{
	if (x > y)
	{
		return x;
	}
	else
	{
		return y;
	}
}

#endif /* BINARYTREE_H_ */
