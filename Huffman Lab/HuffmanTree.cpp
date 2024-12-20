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
	if (t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
		t = nullptr;
	}
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
			numCodes++;
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


void HuffmanTree::rebuildTree(BinaryNode*& node, string element, string codedRoute)
{
	// Rebuild a huffman tree from a file
	if (node == nullptr)
	{
		node = new BinaryNode("empty");
	}
	if (codedRoute.size() == 0)
	{
		node->element = element;
	}
	else
	{
		if (codedRoute[0] == '0')
		{
			rebuildTree(node->left, element, codedRoute.substr(1));
		}
		else
		{
			rebuildTree(node->right, element, codedRoute.substr(1));
		}
	}
	


}

void HuffmanTree::rebuildTree(ifstream& compressedFile) {
    // read info from file
    // use info to build tree
	makeEmpty(root);
    unordered_map<char, string> uncompressedCodes;

    ostringstream input;
    input << compressedFile.rdbuf();
    const string s = input.str();
    vector<char> vec(s.begin(), s.end());
    string temp;
    int uniqueChars;
    int keyPos = 0;
    char mapKey;


    unordered_map<char, string> decryptedCodes;
    for (int i = 0; vec[i] != '~'; i++) // Get unqiue chars number
    {
        temp.push_back(vec[i]);
        keyPos = i;
    }
    keyPos += 2; // +1 sets pos to the tilda, +2 sets pos to character after tilda
    uniqueChars = stoi(temp);

    // Build table of codes

    for (int i = 0; decryptedCodes.size() < uniqueChars; i++)
    {   // getline(input, temp, '~');
        string mapCode;
        mapKey = vec[keyPos];
        for (; vec[keyPos + 1] != '~'; keyPos++)
        {
            mapCode.push_back(vec[keyPos + 1]);

        }
        keyPos += 2; // +1 sets pos to the tilda, +2 sets pos to character after tilda
        decryptedCodes[mapKey] = mapCode;
    }
    codeLookup = decryptedCodes;
    
    // Remove the key from the ifstream
	compressedFile.seekg(keyPos, ios::beg);
	


	for (unordered_map<char, string>::iterator it = codeLookup.begin(); it != codeLookup.end(); ++it)
	{
		rebuildTree(root, string(1, it->first), it->second);
	}

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
	makeEmpty(root);
}

string HuffmanTree::decode(vector<char> encodedBytes) {
	string decoded;
	char byte = 0;
	int bitCounter = 0;
	vector<char> codes;
	BinaryNode* current = root;

	for (int i = 0; i < encodedBytes.size(); i++)
	{
		
		byte = encodedBytes.at(i);
      
          
          if (byte == EOFCharacter)
            {
             // Check if there are more bytes after the EOFCharacter
             if (i + 1 < encodedBytes.size())
             {
                // Continue decoding the remaining bytes
                continue;
             }
             else
             {
               // Reached the end of the encoded bytes, return the decoded string
               return decoded;
             }
          }
            // Rest of the decoding logic...
       
		for (int bitCount = 0; bitCount < 8 && current != nullptr; bitCount++)
		{

			if (current->element.size() == 1)
			{
				decoded += current->element;
				cout << current->element;
				current = root;
			}
			if (getBit(byte, bitCount) == 0)
			{
				current = current->left;
			}
			else if (getBit(byte, bitCount) == 1)
			{
				current = current->right;
			}
		
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
	string code;
	int bitCounter = 0;
	char byte = 0;

	for (int i = 0; i < stringToEncode.size() - 1; i++)
	{
	
		temp = stringToEncode[i];
		code = getCode(temp);
		cout << temp << endl;
		for (int codePos = 0; codePos < code.size(); codePos++)
		{
			if (code[codePos] == '1')
			{
				byte = setBit(byte, bitCounter);
			}
			bitCounter++;
			if (bitCounter == 8)
			{
				encoded.push_back(byte);
				cout << endl;
				bitCounter = 0;
				byte = 0;
				
			}
		}
		
	
	}
	if (bitCounter != 0)
	{
		encoded.push_back(byte);
	}
	cout << endl;
	return encoded;
}

void HuffmanTree::uncompressFile(string compressedFileName,
	string uncompressedToFileName) {

	ifstream compressedFile(compressedFileName, ios::out | ios::binary);
	ofstream uncompressedFile(uncompressedToFileName, ios::in);
	ostringstream input;

	rebuildTree(compressedFile);
	input << compressedFile.rdbuf();
	const string s = input.str();
	vector<char> vec(s.begin(), s.end());
	string decoded = decode(vec);


	// Write data to the file
	uncompressedFile << decoded;
	compressedFile.close();
	uncompressedFile.close();
}
void HuffmanTree::compressFile(string compressToFileName,
	string uncompressedFileName, bool buildNewTree) {
	// need to write code	
	ifstream uncompressedFile(uncompressedFileName);
	ofstream compressedFile(compressToFileName, ios::out | ios::binary);
	ostringstream ss;

	// Write key value pairs first to the compressed file
	// Start with number of chars, then a colon to seperate
	compressedFile << numCodes << '~';
		for (unordered_map<char, string>::iterator it = codeLookup.begin(); it != codeLookup.end(); ++it)
		{

			compressedFile << (it->first);
			compressedFile << (it->second);
			compressedFile << '~'; // Seperator character

		}
	ss << uncompressedFile.rdbuf(); // Put the filestream buffer into the string stream
	const string& compressText = ss.str(); // make a const string out of the string stream
	vector<char> encoded = encode(compressText); // Encode the filestream into a char vector 


	//Write the encoded string Reinterpret cast to make the chars const, write to the amount of room the num of chars in encoded is
	compressedFile.write(reinterpret_cast<const char*>(&encoded[0]), encoded.size() * sizeof(char)); 
	

	// NOTE: when opening the compressedFile, you need to open in 
	//  binary mode for writing..hmmm..why is that?
	

	




}


