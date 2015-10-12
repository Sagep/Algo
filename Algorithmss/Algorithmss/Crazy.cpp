#include <iostream>
#include <queue>
#include <map>
#include <climits> // for CHAR_BIT
#include <iterator>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

const string magicNum = "7771234777";
const int asciiVal = 256;
int charCount[asciiVal];
string str_code[asciiVal];

class huffMap {
public:
	unsigned char* c;
	int codeBuffer;
	string NODE;

	huffMap();
	void INode(string _X);
	int insertBits(ofstream& outf);
	string getBits(unsigned char _X);
	void writeBits(ofstream& outf);
	~huffMap();
};

huffMap::huffMap()
{
	codeBuffer = 0;
	c = (unsigned char*)calloc(1, sizeof(char));
}

void huffMap::INode(string _X)
{
	NODE = _X;
}

//Returns number of bits inserted
int huffMap::insertBits(ofstream& outf)
{
	int total = 0;

	while (NODE.length())
	{
		if (NODE[0] == '1')
			*c |= 1;
		*c <<= 1;
		++codeBuffer;
		++total;
		NODE.erase(0, 1);

		if (codeBuffer == 7)
		{
			writeBits(outf);
			codeBuffer = 0;
			free(c);
			c = (unsigned char*)calloc(1, sizeof(char));
		}
	}

	//Account for any trailing bits and push them over
	if (codeBuffer > 0)
	{
		*c <<= (8 - codeBuffer);
		writeBits(outf);
		free(c);
		c = (unsigned char*)calloc(1, sizeof(char));
	}

	return total;
}

//Outputs a char in binary format
string huffMap::getBits(unsigned char _X)
{
	stringstream _itoa;

	int _size = sizeof(unsigned char) * 8;

	for (unsigned _s = 0; _s < _size - 1; ++_s)
	{
		_itoa << ((_X >> (_size - 1 - _s)) & 1);
	}

	return _itoa.str();
}

void huffMap::writeBits(ofstream& outf)
{
	outf << *c;
}

huffMap::~huffMap()
{
	if (c)
		free(c);
}
struct node {
	char ch;
	int count;
	node* left;
	node* right;
};

class cmp {
public:
	bool operator()(const node* lhs, const node* rhs) const
	{
		return lhs->count > rhs->count;
	}
};

node* makeNode(char ch, int count)
{
	node* tmp = new node;
	tmp->ch = ch;
	tmp->count = count;
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
};

typedef priority_queue<node*, vector<node*>, cmp> mypq;

void trie(mypq& _X)
{
	while (_X.size() > 1)
	{
		node* holder = new node;
		holder->left = _X.top(); _X.pop();
		holder->right = _X.top(); _X.pop();
		holder->count = holder->left->count + holder->right->count;
		holder->ch = -1;
		_X.push(holder);
	}
}

//Create bit codes by recursively traversing the trie, adding a 0 for left and 1 for right, the key is to remove the end char when the recursion breaks and you have to go up a level
void code(node* _X)
{
	static string bits = "";
	if (_X->right != NULL)
	{
		bits += "1";
		code(_X->right);
		bits = bits.substr(0, bits.size() - 1);
	}
	if (_X->left != NULL)
	{
		bits += "0";
		code(_X->left);
		bits = bits.substr(0, bits.size() - 1);
	}
	if (!_X->left && !_X->right)
	{
		str_code[_X->ch] = bits;
	}
}

void count(string file, int& _X) {
	char letter;
	ifstream inf(file.c_str());

	inf >> noskipws;

	//Clears array
	for (int i = 0;i < asciiVal; ++i)
		charCount[i] = 0;

	//Goes through text and counts
	while (inf >> letter) {
		if (letter >= 0 && letter < asciiVal)
		{
			++charCount[letter];
			++_X;
		}
	}
	inf.close();
}

//Generates a string of the bit codes in the order they appear in the file
//Used during encoding
string NODEstring(string inFile)
{
	char input;
	string NODE = "";

	//Open input stream and create NODE string of entire file
	ifstream inf(inFile.c_str());
	inf >> noskipws;

	while (inf >> input)
	{
		NODE += str_code[input];
	}

	inf.close();

	//Append ascii 3 EOT character to signify end of text
	NODE += str_code[3];

	return NODE;
}

int main(int argc, char** argv)
{
	int rc;
	char choice;
	unsigned char inChar=0;
	string inFile = "", outFile = "", NODE = "", NODEsub = "", mn = "";
	ofstream outf;
	ifstream inf;
	mypq pq;
	huffMap bchar;
	int origSize = 0;

	cout << "Menu..." << endl << "e) Encode file" << endl << "d) Decode file" << endl;
	cin >> choice;

	switch (choice)
	{
	case 'e':
		//Get input filename and set output filename
		cout << "Enter File Name to Encode: " << endl;
		cin >> inFile;

		outFile = inFile + ".mpc";

		cout << left << setw(17);
		cout << "Input filename: " << inFile << endl;
		cout << left << setw(17);
		cout << "Output filename:" << outFile << endl;
		cout << endl;

		//Open output streams
		outf.open(outFile.c_str());

		//count and populate array of letter occurrences (charCount) and add one EOT char
		count(inFile, origSize);
		if (charCount[3] == 0)
			charCount[3] = 1;

		//Output compressed file header
		outf << magicNum << endl;
		outf << inFile << endl;
		for (int i = 0; i < asciiVal; ++i)
		{
			outf << charCount[i] << " ";
		}
		outf << endl;

		//Create nodes based on the available ascii characters and push them into the priority queue
		for (int i = 0; i < asciiVal; ++i)
		{
			if (charCount[i] > 0)
			{
				node* tmp = makeNode(i, charCount[i]);
				pq.push(tmp);
			}
		}

		//Create trie and bit codes
		trie(pq);
		code(pq.top());

		//Create string of bitcodes for actual huffman encoding and do it
		NODE = NODEstring(inFile);
		outf << '#';
		bchar.INode(NODE);
		outf << noskipws;
		rc = bchar.insertBits(outf);

		if (rc == NODE.length())
		{
			cout << "Encoding succsessful! :)" << endl;
			cout << "The compression ration is: " << (float)rc / ((float)origSize * 8.0) * 100.0 << "%" << endl;
		}
		else
		{
			cout << "There was an error writing the bits! :(" << endl;
			cout << "Expected: " << NODE.length() * 8 << " but got: " << rc << endl;
		}

		break;
	case 'd':
		//Get input filename and set output filename
		cout << "Enter File Name to Decode: " << endl;
		cin >> inFile;

		inf.open(inFile.c_str());
		inf >> mn;
		if (mn != magicNum)
		{
			cout << "Magic number does not match, this is not a valid file..." << endl;
			return 1;
		}

		inf >> outFile;
		if (outFile != inFile.substr(0, inFile.length() - 4))
		{
			cout << outFile << " " << inFile.substr(0, inFile.length() - 4) << endl;
			cout << "File names do not match but will attempt to decode anyway..." << endl;
		}
		outf.open(outFile.c_str());

		//Read in the letter count and add valid one to the priority queue
		for (int i = 0; i < asciiVal; ++i)
		{
			inf >> charCount[i];
			if (charCount[i] > 0)
			{
				node* tmp = makeNode(i, charCount[i]);
				pq.push(tmp);
			}
		}

		//Create trie and bit codes
		trie(pq);
		code(pq.top());

		while (inChar != '#')
		{
			inf >> inChar;
		}

		inf >> noskipws;
		//Read in encoded chars and create NODE
		while (inf >> inChar)
		{
			NODE += bchar.getBits(inChar);
		}

		inf.close();

		for (int i = 0; i < NODE.length(); ++i)
		{
			NODEsub += NODE[i];
			for (int j = 0; j < asciiVal; ++j)
			{
				if (NODEsub == str_code[j])
				{
					//End of text has been hit and file is over, write newline and exit
					if (j == 3)
					{
						outf << "\n";
						i = NODE.length();
						break;
					}
					outf << (char)j;
					NODEsub = "";
					break;
				}
			}
		}

		break;
	default:
		cout << "Invalid choice...." << endl;
		break;
	}

	outf.close();

	return 0;
}