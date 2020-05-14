/*****************************************************************************
 * AUTHOR 	  		: Nick Reardon
 * Assignment #15	: Huffman Coding
 * CLASS			: CS1D
 * SECTION			: MW - 2:30p
 * DUE DATE			: 05 / 13 / 20
 *****************************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_

 //Standard includes
#include <iostream>
#include <iomanip>
#include <string>
#include "PrintHeader.h"

//Program Specific
#include "BinaryTree.h"
#include "List.h"

struct HuffCode
{
	HuffCode()
	{
		symbol = ' '; weight = 32000;
	}

	HuffCode(char symbolInit, int weightInit)
	{
		symbol = symbolInit; weight = weightInit;
	}

	bool operator==(const HuffCode& compareTo) const 
	{
		return symbol == compareTo.symbol; 
	}

	char symbol;
	int  weight;
};

List<BTNode<HuffCode>* >::Iterator SmallestWeight(const List<BTNode<HuffCode>* >& codes);

void OutputHuffCodes(string alphabet, const HuffmanTree<HuffCode>& huffTree, int frequencyMatrix[]);

void CompressFile(const HuffmanTree<HuffCode>& huffTree,
	string& originalFile);

void DecompressFile(HuffmanTree<HuffCode>* huffTree);

string WordWrap(string toWrap, int lineLength);




#endif // _HEADER_H_

