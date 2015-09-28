#include <fstream>
#include <string>
#include <iomanip>
//previously had istream not iostream.
#include <iostream>
#include <queue>
#include <map>
#include <climits> // for CHAR_BIT
#include <iterator>
#include <algorithm>

using namespace std;

const int UniqueSymbols = 1 << CHAR_BIT;
string readChar;
vector<bool> encoding;
vector<bool>encodingmap;


//reads in the data into a string so that it may be used as an array of characters.
class node
{
public: 
	const int f;
	virtual ~node();
protected:
	node(int f) : f(f){};
};

class inode : public node
{
public: 
	const node *left;
	const node *right;
	inode(node* l0, node* r0) : node(l0->f + r0->f), left(l0), right(r0) {}


	~inode() { delete left; delete right; }
};

class leaves : public node {
	public:
		const char c;

		leaves(int f, char c) : node(f), c(c) {}
};

struct NodeTree{ 
	
	bool operator() (const node* lhs, const node* rhs)  const { return lhs->f > rhs->f; }

};

node* Builder(const int(&frequencies)[UniqueSymbols]) {
	priority_queue<node*, vector<node*>, NodeTree> trees; 

	for (int i = 0; i < UniqueSymbols; ++i) {
		if (frequencies[i] != 0) trees.push(new leaves(frequencies[i], (char)i));
	}


}

void read(ifstream &inf){
	string temp;

	while (!inf.eof()){
		getline(inf, temp);
		readChar += temp + "\n";
	}
}

int main(int argc, char const *argv[])
{
	string file;
	ifstream inf;
	int lengthofstring;
	cout << "type location of file: " << endl;
	cin >> file;
	inf.open(file);
	read(inf);

	//how many characters do we have in the string?
	lengthofstring = readChar.length();
	//---------------------------------------------


	/*simple print for us to see what characters that we have
	(Only shows the number associated with the character. EXE: A=0, B=1...)
	From here we need to actually sort by amount of chars and print them.

	Note: It would be best if we had MORE characters to search from.
	EXE: Spaces, colons, semicolons, commas. etc. Currently we only have the alphabet.
	(Possibility we need the ascii table and how many we have??)

	Stopped for the night as it is 3:00AM.(I got home at 10 and played wow for a hour haha)
	*/
	/*
	for (int i = 0; i < 52; i++)
	{
		if (alphabet[i] != 0)
			cout << alphabet[i] << " for the letter of alphabet: " << i << endl;
	}*/
	cout << readChar;
	//compress structure huffman tree

	system("Pause");
	return 0;
}