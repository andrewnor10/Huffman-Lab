// HuffmanCoding.cpp : Defines the entry point for the console application.
//


#include <string>
#include <fstream>
#include <streambuf>
#include <queue>
#include <functional>

#include "HuffmanTree.h"

using namespace std;

int main() {

	// example code for priority_queue....play with it and then remove/comment out
	/*cout << "priority_queue test area: \n";
	priority_queue<int, vector<int>, greater<int> > pq;

	pq.push(111);
	pq.push(1111);
	pq.push(1011);
	pq.push(100);
	pq.push(1110);
	pq.push(101);

	cout << "Top: " << pq.top() << endl;
	pq.push(10);
	cout << "New Top: " << pq.top() << endl;

	while (!pq.empty()) {
		cout << pq.top() << endl;
		pq.pop();
	}
	cout << endl << endl;
	*/

	// example code for unordered_map....play with it and then remove/comment out
	//  an unordered_map can be used to store the char and its encoded 
	//  values after you have built the tree
	/*cout << "unordered_map test area: \n";
	unordered_map<char, string> exampleMap;
	exampleMap['a'] = "apple";			// creates a new entry if 'a' is not in the map and associates "apple" with 'a'
	exampleMap['b'] = "ballon";
	exampleMap['c'] = "compiler";
	exampleMap['d'] = "10010";

	cout << "c has: " << exampleMap['c'] << endl;

	exampleMap['c'] = "changed";
	for (auto pair : exampleMap) {
		cout << pair.first << " = " << pair.second << endl;
	}
	cout << "Number of items stored in map: " << exampleMap.size();
	cout << endl << endl;
	*/

	// SUGGESTION: write and test the functions in the order called below
	//         (some of the functions may need to call other private functions)

	//Test 1        
/*	cout << "\n\nTest 1\n";
	cout << "\n\nBuilding the tree from: HHHHEELLLLLLLOO WOOOOORRLLLLLLDP\n";
	HuffmanTree tree("HHHHEELLLLLLLOO WOOOOORRLLLLLLDP");
	
	cout << "\n\nprintTree: \n";
	tree.printTree();
	
	cout << "\n\nprintCodes:\n";
	tree.printCodes();
	cout << endl << endl; 

	cout << "Code L :" <<tree.getCode('L') << endl;
	cout << "Code D :" << tree.getCode('D') << endl;


	
	cout << "\n\nTest 2\n";
	vector<char> encoded = tree.encode("HELP"); 
	tree.printCodes();
	 tree.printBinary(encoded);  // for lab, instead output chars inside encoded
	cout << endl;
	//
	cout << tree.decode(encoded) << ":" << endl;
	system("pause");  // LAB 3: Should run up to here with the above functions working with chars '1' and '0' 
						//			instead of making the changes at the binary level
*/
	//Test 3
	cout << "\n\nTest 3\n";
	std::ifstream frequencyStream("BigO.txt");
	HuffmanTree tree2(frequencyStream);
//	tree2.printTree();
//	tree2.printCodes();

	tree2.compressFile("BigO.bin", "BigO.txt");
//	tree2.printCodes();
	tree2.uncompressFile("BigO.bin", "BigORebuilt.txt");
// 	tree2.printTree();
//	tree2.printCodes();

	//Test 4
	
	cout << "\n\nTest 4\n";
	std::ifstream frequencyStream2("20000leagues.txt");
	HuffmanTree tree3(frequencyStream2);
	// tree3.printTree();
	// tree3.printCodes();
	cout << "Code L :" << tree3.getCode('L') << endl;
	tree3.compressFile("20000leaguesComp.bin" ,"20000leagues.txt",true);
	tree3.uncompressFile("20000leaguesComp.bin", "20000leaguesRebuilt.txt");
	tree3.printTree();
	tree3.printCodes();
	
	// Try Other Files

	//// read in text file create string - might be useful
	//std::ifstream bigtext("20000leagues.txt");
	//std::string big((std::istreambuf_iterator<char>(bigtext)), 
	//				   std::istreambuf_iterator<char>());

	cout << endl;
	system("pause");
	return 0;
}

