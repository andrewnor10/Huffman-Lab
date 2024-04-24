//#include "stdafx.h"

#include <string>
#include <vector>
#include <fstream> 
#include <iostream>
#include <queue>    
#include <algorithm>
#include <iomanip> 
#include <bitset>
#include <unordered_map>
#include <sstream>

#include "HuffmanTree.h"

using namespace std;

inline bool HuffmanTree::getBit(unsigned char byte, int position) const
{
	return (byte & BITMASK[position]);
}

// Usage
// mybyte = setBit(mybyte,4);
// This sets the bit in position 4
inline unsigned char HuffmanTree::setBit(unsigned char byte, int position) const
{
	return  byte | BITMASK[position];
}

void HuffmanTree::printBits(char binary, std::ostream& out) const
{
	for (size_t i = 0; i < sizeof(char) * 8; i++) {
		if (getBit(binary, i)) {
			out << 1;
		}
		else {
			out << 0;
		}
	}
}

void HuffmanTree::printBinary(vector<char> bytes, std::ostream& out) const
{
	for (char byte : bytes)
	{
		printBits(byte, out);
		out << "-";
	}

}

string HuffmanTree::getCode(char letter) const
{
	string code = "";


	code = codeLookup.at(letter);

	return code;
}

	/*BinaryNode* current = root;
	while (current != nullptr)
	{
		if (current->element.size() == 1)
		{
			if (current->element[0] == letter)
			{
				return code;
			}
		}
		else
		{
			if (current->left->element.find(letter) != string::npos)
			{
				code += "0";
				current = current->left;
			}
			else
			{
				code += "1";
				current = current->right;
			}
		}
	}


	return code;
}
*/




void HuffmanTree::makeEmpty(BinaryNode*& t) {
	// need to write code
}

void HuffmanTree::printTree(BinaryNode* node, std::ostream& out) const
{

	if (node != nullptr)
	{
		printTree(node->left, out); // Left branch
		out << "Element: " << node->element << ' ' << "Frequency: " << node->frequency << endl; // Output
		printTree(node->right, out); // Right branch
	}

}

void HuffmanTree::printCodes(BinaryNode* node, std::ostream& out, string code) const
{
	if (node != nullptr)
	{
		printCodes(node->left, out, code + "0"); // Left branch
		out << "Element: " << node->element << ' ' << "Code: " << code << endl;
		printCodes(node->right, out, code + "1"); // Right branch
	}
}


void HuffmanTree::saveTree(BinaryNode* current, string code)
{
	// need to write code
	// save to file
	if (current != nullptr)
	{
		saveTree(current->left, code + "0"); // Left branch
		if (current->element.size() == 1 && codeLookup.find(current->element.front()) == codeLookup.end())
		{
			codeLookup[current->element.front()] = code;
		}
		saveTree(current->right, code + "1"); // Right branch

	}


}

// writes tree information to file so the tree can be rebuilt when unzipping
void HuffmanTree::saveTree(std::ostream& compressedFileStream)
{
	// need to write code
	// calls recursive function
	saveTree(root, string());
}


void HuffmanTree::rebuildTree(BinaryNode* node, string element, string codedRoute)
{
	// need to write code

}

void HuffmanTree::rebuildTree(ifstream& compressedFile) {
	// read info from file
	// use info to build tree

	// need to write code
	// calls recursive function
}

HuffmanTree::BinaryNode* HuffmanTree::buildTree(string frequencyText) {
	priority_queue<HuffmanTree::BinaryNode*,		// element type
		vector<HuffmanTree::BinaryNode*>, // container the queue uses
		compareBinaryNodes > nodes;		// comparison function (functor)

	vector<int> freq(128, 0);

	for (int i = 0; i < frequencyText.size(); i++)
	{
		freq[static_cast<int>(frequencyText[i])]++;
	}


	for (int i = 0; i < 128; i++)
	{
		string temp;
		if (freq[i] > 0)
		{
			temp.push_back(static_cast<char>(i));
			nodes.push(new BinaryNode(temp, freq[i]));
			temp.pop_back();
		}
	}
	while (nodes.size() != 1)
	{
		BinaryNode* Internal;
		BinaryNode* left;
		BinaryNode* right;
		int freqSum;
		string elemSum;

		// Pull lowest 2 frequencies out
		left = nodes.top();
		nodes.pop();

		right = nodes.top();
		nodes.pop();

		// Combine their data into a new node
		freqSum = left->frequency + right->frequency;
		elemSum = left->element + ',' + right->element;
		Internal = new BinaryNode(elemSum, freqSum);

		// Assign new nodes pointers to them
		Internal->left = left;
		Internal->right = right;

		// Push node back into queue
		nodes.push(Internal);
	}

	root = nodes.top();
	saveTree(root, string());
	return nodes.top();
}

HuffmanTree::HuffmanTree(string frequencyText)
{
	root = buildTree(frequencyText);
	saveTree(root, string());   // build the lookupTable for codes...can write later
}

HuffmanTree::HuffmanTree(ifstream& frequencyStream) {

	std::string frequencyText((std::istreambuf_iterator<char>(frequencyStream)),
		std::istreambuf_iterator<char>());    // builds the frequencyText by using STL iterators
	frequencyStream.close();
	if (frequencyText.size() > 0) {
		root = buildTree(frequencyText);
		saveTree(root, string());   // build the lookupTable for codes
	}
}

HuffmanTree::~HuffmanTree()
{
	// need to write code	
}

// print out the char and its encoding
void HuffmanTree::printCodes(std::ostream& out) const
{
	string code;
	printCodes(root, out, code);
}

// prints out the char and frequency
void HuffmanTree::printTree(std::ostream& out) const
{
	// need to write code
	printTree(root, out);
}

void HuffmanTree::makeEmpty()
{
	// need to write code
	// calls recursive function	
}

string HuffmanTree::decode(vector<char> encodedBytes) {
	string decoded;

	BinaryNode* current = root;
	// need to write code
	for (int i = 0; i < encodedBytes.size(); i++)
	{
		if (current->element.size() == 1)
		{
			decoded += current->element;
		}
		if (encodedBytes[i] == 0)
		{
			current = current->left;
		}
		else if (encodedBytes[i] == 1)
		{
			current = current->right;
		}
	}

	return decoded;
}

vector<char> HuffmanTree::encode(string stringToEncode)
{
	stringToEncode.push_back(EOFCharacter); // needed when encoding message for file I/O
	saveTree(root, string());
	vector<char> encoded;
	char temp;
	string str;
	for (int i = 0; i < stringToEncode.size() - 1; i++)
	{
		temp = stringToEncode[i];
		str = getCode(temp);
		for (int j = 0; j < str.size(); j++)
		{
			encoded.push_back(str[j]);
		}
	}
	for (char ele : encoded)
	{
		cout << ele;
	}

	cout << endl;
	return encoded;
}

void HuffmanTree::uncompressFile(string compressedFileName,
	string uncompressedToFileName) {
	// need to write code	

	// NOTE: when opening the compressedFile, you need to open in 
	//  binary mode for reading..hmmm..why is that?
}

void HuffmanTree::compressFile(string compressToFileName,
	string uncompressedFileName, bool buildNewTree) {
	// need to write code	

	// NOTE: when opening the compressedFile, you need to open in 
	//  binary mode for writing..hmmm..why is that?
}

