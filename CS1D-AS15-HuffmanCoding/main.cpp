/*****************************************************************************
 * AUTHOR 	  		: Nick Reardon
 * Assignment #15	: Huffman Coding
 * CLASS			: CS1D
 * SECTION			: MW - 2:30p
 * DUE DATE			: 05 / 13 / 20
 *****************************************************************************/
#include "main.h"
#include <queue>
using std::cout; using std::endl;


int main()
{

	/*
	 * HEADER OUTPUT
	 */
	PrintHeader(cout, "Prompt.txt");

	/********************************************************************/

	string gettysburgAddress = "";
	string letters = "";
	string temp;
	string::iterator frequencyItr;
	int fMatrix[127] = { 0 };
	int frequency;

	List<BTNode<HuffCode>* > codeList;
	List<BTNode<HuffCode>* >::Iterator smallestOne;
	List<BTNode<HuffCode>* >::Iterator smallestTwo;

	BTNode<HuffCode>* nodePtrOne;
	BTNode<HuffCode>* nodePtrTwo;

	HuffCode* codePtr;

	BTNode<HuffCode>* newNodePtr = NULL;
	HuffmanTree<HuffCode>* hTree = NULL;

	ifstream iFile;
	iFile.open("input.txt");


	cout << endl << "Reading text from file..." << endl;

	while (iFile)
	{
		getline(iFile, temp);

		frequencyItr = temp.begin();
		while (frequencyItr != temp.end())
		{
			if (fMatrix[int(*frequencyItr)] == 0)
			{
				letters = letters + *frequencyItr;
			}

			++fMatrix[int(*frequencyItr)];
			++frequencyItr;
		}
		gettysburgAddress += temp;
	}

	cout << endl << "Inserting into frequency tree..." << endl;

	for (int i = 0; i < 127; ++i)
	{
		frequency = fMatrix[i];
		if (frequency > 0)
		{
			codePtr = new HuffCode(char(i), frequency);
			nodePtrOne = new BTNode<HuffCode>(*codePtr);
			codeList.InsertBack(nodePtrOne);
		}
	}

	while (codeList.Size() > 1)
	{
		smallestOne = SmallestWeight(codeList);
		nodePtrOne = (*smallestOne);
		codeList.Erase(smallestOne);

		smallestTwo = SmallestWeight(codeList);
		nodePtrTwo = (*smallestTwo);
		codeList.Erase(smallestTwo);

		codePtr = new HuffCode(0, nodePtrOne->GetType().weight + nodePtrTwo->GetType().weight);

		if (nodePtrOne->GetType().weight < nodePtrTwo->GetType().weight)
		{
			newNodePtr = new BTNode<HuffCode>(nodePtrOne, nodePtrTwo, NULL, *codePtr);
		}
		else
		{
			newNodePtr = new BTNode<HuffCode>(nodePtrTwo, nodePtrOne, NULL, *codePtr);
		}

		nodePtrOne->SetParent(newNodePtr);
		nodePtrTwo->SetParent(newNodePtr);

		codeList.InsertBack(newNodePtr);
	}

	hTree = new HuffmanTree<HuffCode>(newNodePtr);

	cout << endl << "Outputting huffman code..." << endl;

	OutputHuffCodes(letters, *hTree, fMatrix);
	cout << endl;


	cout << endl << "Printing tree..." << endl;

	cout << "Huffman Tree\n";
	hTree->Print();
	cout << endl;


	cout << endl << "Compressing file..." << endl;

	CompressFile(*hTree, gettysburgAddress);
	cout << endl;


	cout << endl << "Decompressing file..." << endl;

	cout << "Decompressed File\n";
	DecompressFile(hTree);

	system("pause");
	return 0;
}

string WordWrap(string toWrap, int lineLength)
{
	int charCount;
	int stringLength;
	string word;
	string line;
	string wrapped;

	stringLength = toWrap.length();
	word = "";
	line = "";
	wrapped = "";

	for (charCount = 0; charCount < stringLength; charCount++)
	{
		if (toWrap[charCount] != ' ')
		{
			word = word + toWrap[charCount];
		}
		else
		{

			if (line.length() + word.length() > lineLength)
			{
				wrapped = wrapped + line + '\n';
				line.clear();
			}
			line = line + word + ' ';
			word.clear();
		}
	}

	if (line.length() + word.length() > lineLength)
	{
		wrapped = wrapped + line + '\n';
		line.clear();
	}
	wrapped = wrapped + line + word;

	return wrapped;
}

List<BTNode<HuffCode>* >::Iterator SmallestWeight(const List<BTNode<HuffCode>* >& codes)
{
	List<BTNode<HuffCode>* >::Iterator returnIt;
	List<BTNode<HuffCode>* >::Iterator iterator;

	returnIt = codes.Begin();
	iterator = codes.Begin();

	while (iterator != codes.End())
	{
		if ((*iterator)->GetType().weight < (*returnIt)->GetType().weight)
		{
			returnIt = iterator;
		}

		++iterator;
	}

	return returnIt;
}

void CompressFile(const HuffmanTree<HuffCode>& hTree, string& oFile)
{
	string::iterator iter;
	ofstream outFile;
	string huffCode;
	string compressedFile;
	int count = 0;
	outFile.open("output.txt");

	iter = oFile.begin();
	huffCode = hTree.HuffmanSearch(*iter);
	compressedFile = compressedFile + huffCode;
	++iter;

	while (iter != oFile.end())
	{
		huffCode = hTree.HuffmanSearch(*iter);

		if (count < 15)
		{
			compressedFile = compressedFile + huffCode;
			++count;
		}
		else
		{
			outFile << compressedFile << endl;
			compressedFile = huffCode;
			count = 0;
		}

		++iter;
	}

	if (count != 0)
	{
		outFile << compressedFile;
	}

	outFile.close();
}

void DecompressFile(HuffmanTree<HuffCode>* hTree)
{
	ifstream iFile;
	string codes;
	string::iterator iter;
	BTNode<HuffCode>* treePtr;
	bool decoding;
	string decoded;

	decoded = "";
	iFile.open("output.txt");

	while (iFile)
	{
		getline(iFile, codes);

		iter = codes.begin();
		while (iter != codes.end())
		{
			decoding = true;
			treePtr = hTree->GetRoot();

			while (decoding)
			{
				if (treePtr->GetType().symbol == 0)
				{
					if ((*iter) == '0')
					{
						treePtr = treePtr->GetLeft();
					}
					else
					{
						treePtr = treePtr->GetRight();
					}
					++iter;
				}
				else
				{
					decoded += treePtr->GetType().symbol;
					decoding = false;
				}
			}
		}
	}
	cout << WordWrap(decoded, 70) << endl << endl;
}

void OutputHuffCodes(string letters, const HuffmanTree<HuffCode>& hTree, int frequencyMatrix[])
{
	string::iterator iter;
	int compressed = 0;
	int uncompressed = 0;


	cout << left << "  Letter" << " | " << "Frequency " << " | " << "Code" << endl
		<< string(50, '-') << endl;

	iter = letters.begin();
	while (iter != letters.end())
	{
		if ((*iter) == ' ')
		{
			cout << left << "  " << setw(3) << "space" << " | ";
		}
		else
		{
			cout << left << "    " << setw(4) << (*iter) << " | ";
		}
		 cout << "    " << setw(6) << frequencyMatrix[(*iter)] << " | "
			<< hTree.HuffmanSearch(*iter) << endl;


		compressed += frequencyMatrix[(*iter)] * hTree.HuffmanSearch(*iter).size();

		uncompressed += frequencyMatrix[(*iter)] * 7;

		++iter;
	}

	cout << endl;

	cout << left << "  Compressed (KB)" << " | " << "Uncompressed (KB) " << " | " << "Ratio" << endl
		<< string(50, '-') << endl
		<< "     " << setw(12) << (compressed / float(1024))
		<< " |     " << setw(14) << (uncompressed / float(1024))
		<< " | " << setw(10) << (uncompressed * 1.00 / compressed) << endl << endl;
}