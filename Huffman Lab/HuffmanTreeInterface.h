#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using namespace std;

 class HuffmanTreeInterface  {
 private:	
 public:
	 HuffmanTreeInterface() {};
	 HuffmanTreeInterface(std::string frequecyText) {};
	 HuffmanTreeInterface(const HuffmanTreeInterface & rhs) {};
	 HuffmanTreeInterface(HuffmanTreeInterface && rhs) noexcept {};
	 virtual ~HuffmanTreeInterface() {};
	
	 /**
	 prints the code for all the ASCII values in the tree.

	 @param out the stream to send the output to.
	 by default it is standard cout
	 @return No return value
	 */
	virtual void printCodes(std::ostream & out = cout) const = 0;

	/**
	prints the code for the ASCII value parameter.

	@param letter the character you want the code for	
	@return the string the represents the code of the letter
	*/
	virtual string getCode(char letter) const = 0;

	/**
	Prints both the characters and frequency  (suggested)

	@param out -the stream to send the output to.
	by default it is standard cout
	@return No return value
	*/
	virtual void printTree(std::ostream & out = std::cout) const = 0;		
	
	/**
	deletes all nodes of the tree. Uses postorder traversal.

	@param None
	@return No return value
	*/
	virtual void makeEmpty() = 0;
	
	/**
	encodes the string into a text version of the binary
	based on the huffman tree.
    The '0' represents an off bit
	The '1'	represents an on bit
	
	@param the string to encode
	@return the encode version of the string
	*/
	virtual vector<char> encode(string stringToEncode) = 0;
	
	/**
	decodes the string into a series of chars 
	based on the huffman tree. The bits in each char should 
	be in the form of valid huffman prefix codes	

	@param the string to encode
	@return a vector with chars with the encoded version of the string
	*/
	virtual string decode(vector<char> encodedBytes) = 0;	

	/**
	decodes the contents of the compressedfile
	and saves its decompressed form in the target file 
	file should contain valid huffman prefix codes 
	in the form of binary (NOT text values 0 and 1)	

	@param compressedFileName -the file to uncompress
	@param uncompressedFileName -the file to store the decoded version in. 
	
	@return no return value
	*/
	virtual void uncompressFile(string compressedFileName, 
								string uncompressedFileName) = 0;		
	/**
	encodes the contents of the uncompressedfile
	and saves its compressed form in the target file
	file should contain valid huffman prefix codes
	in the form of binary (NOT text values 0 and 1)

	@param compressedFileName -the file the date will be encoded to
	@param uncompressedFileName -the normal file that will be read from
	@param rebuild tree before doing compression

	@return no return value
	*/
	virtual void compressFile(string compressedFileName, 
							  string uncompressedFileName, bool buildTree = true) = 0;	
};