/*****************************************************************************
 * AUTHOR 	  		: Nick Reardon
 * Assignment #15	: Huffman Coding
 * CLASS			: CS1D
 * SECTION			: MW - 2:30p
 * DUE DATE			: 05 / 13 / 20
 *****************************************************************************/
#ifndef BINARYTREENODE_H_
#define BINARYTREENODE_H_

#include <iostream>
using namespace std;

template <typename TypeType>
class BTNode
{
	private:
		typedef BTNode<TypeType> node;

	public:
		BTNode() {left = NULL; right = NULL; parent = NULL;}
		BTNode(const TypeType& elemInit) {left = NULL; right = NULL; parent = NULL; elem = elemInit;}
		BTNode(node* leftInit,   node* rightInit, node* parentInit, TypeType& elemInit)
		{
			left = leftInit; right = rightInit;
			parent = parentInit; elem = elemInit;
		}
		~BTNode(){}

		const TypeType& GetType() const {return elem;}

		node* GetLeft() const {return left;}

		node* GetRight() const {return right;}

		node* GetParent() const {return parent;}

		bool IsLeftChild() const {return parent != NULL ? parent->GetLeft() == this : false;}

		bool IsRightChild() const{return parent != NULL ? parent->GetRight() == this : false;}

		bool IsExternal() const {return left == NULL && right == NULL;}

		bool IsRoot() const {return parent == NULL;}


		void SetType(const TypeType& newType) {elem = newType;}

		void SetLeft(node* leftChild) {left = leftChild;}

		void SetRight(node* rightChild) {right = rightChild;}

		void SetParent(node* parentNode) {parent = parentNode;}

		TypeType& ModType() {return elem;}

	private:
		TypeType elem;
		node*  left;
		node*  right;
		node*  parent;
};

#endif /* BINARYTREENODE_H_ */
