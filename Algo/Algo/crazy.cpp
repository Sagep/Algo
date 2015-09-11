#include <fstream>
#include <string>
#include <iomanip>
//previously had istream not iostream.
#include <iostream>

using namespace std;

int alphabet[52];
//reads in the data into a string so that it may be used as an array of characters.
void read(ifstream &inf, string &readChar){
	string temp;

	while (!inf.eof()){

		getline(inf, temp);
		readChar += temp;
	}

}

void initialize()
{
	for (int i = 0; i < 26; i++)
	{
		alphabet[i] = 0;
	}
}

void sort(string readchar, int lengthofstring)
{

	for (int i = 0; i < lengthofstring; i++)
	{

		switch (readchar[i]){
			case 'A':
			alphabet[0] +=1;
			break;
		case 'B':
			alphabet[1] += 1;
			break;
		case 'C':
			alphabet[2] += 1;
			break;
		case 'D':
			alphabet[3] += 1;
			break;
		case 'E':
			alphabet[4] += 1;
			break;
		case 'F':
			alphabet[5] += 1;
			break;
		case 'G':
			alphabet[6] += 1;
			break;
		case 'H':
			alphabet[7] += 1;
			break;
		case 'I':
			alphabet[8] += 1;
			break;
		case 'J':
			alphabet[9] += 1;
			break;
		case 'K':
			alphabet[10] += 1;
			break;
		case 'L':
			alphabet[11] += 1;
			break;
		case 'M':
			alphabet[12] += 1;
			break;
		case 'N':
			alphabet[13] += 1;
			break;
		case 'O':
			alphabet[14] += 1;
			break;
		case 'P':
			alphabet[15] += 1;
			break;
		case 'Q':
			alphabet[16] += 1;
			break;
		case 'R':
			alphabet[17] += 1;
			break;
		case 'S':
			alphabet[18] += 1;
			break;
		case 'T':
			alphabet[19] += 1;
			break;
		case 'U':
			alphabet[20] += 1;
			break;
		case 'V':
			alphabet[21] += 1;
			break;
		case 'W':
			alphabet[22] += 1;
			break;
		case 'X':
			alphabet[23] += 1;
			break;
		case 'Y':
			alphabet[24] += 1;
			break;
		case 'Z':
			alphabet[25] += 1;
			break;
		case 'a':
			alphabet[26] += 1;
			break;
		case 'b':
			alphabet[27] += 1;
			break;
		case 'c':
			alphabet[28] += 1;
			break;
		case 'd':
			alphabet[29] += 1;
			break;
		case 'e':
			alphabet[30] += 1;
			break;
		case 'f':
			alphabet[31] += 1;
			break;
		case 'g':
			alphabet[32] += 1;
			break;
		case 'h':
			alphabet[33] += 1;
			break;
		case 'i':
			alphabet[34] += 1;
			break;
		case 'j':
			alphabet[35] += 1;
			break;
		case 'k':
			alphabet[36] += 1;
			break;
		case 'l':
			alphabet[37] += 1;
			break;
		case 'm':
			alphabet[38] += 1;
			break;
		case 'n':
			alphabet[39] += 1;
			break;
		case 'o':
			alphabet[40] += 1;
			break;
		case 'p':
			alphabet[41] += 1;
			break;
		case 'q':
			alphabet[42] += 1;
			break;
		case 'r':
			alphabet[43] += 1;
			break;
		case 's':
			alphabet[44] += 1;
			break;
		case 't':
			alphabet[45] += 1;
			break;
		case 'u':
			alphabet[46] += 1;
			break;
		case 'v':
			alphabet[47] += 1;
			break;
		case 'w':
			alphabet[48] += 1;
			break;
		case 'x':
			alphabet[49] += 1;
			break;
		case 'y':
			alphabet[50] += 1;
			break;
		case 'z':
			alphabet[51] += 1;
			break;
		}
	}
}

int main(int argc, char const *argv[])
{
	string file, readChar;
	ifstream inf;
	int lengthofstring;
	cout << "type location of file: " << endl;
	cin >> file;
	inf.open(file);
	read(inf, readChar);

	initialize();

	
	//how many characters do we have in the string?
	lengthofstring = readChar.length();
	//---------------------------------------------

	//this is creates an array of ints which count how many of what we have.
	//(EXE: 4 A's and 1 a, 10 B's and one c etc.)
	sort(readChar, lengthofstring);
	//--------------------------------------------


	/*simple print for us to see what characters that we have 
	(Only shows the number associated with the character. EXE: A=0, B=1...)
	From here we need to actually sort by amount of chars and print them. 

	Note: It would be best if we had MORE characters to search from. 
	EXE: Spaces, colons, semicolons, commas. etc. Currently we only have the alphabet. 
	(Possibility we need the ascii table and how many we have??)

	Stopped for the night as it is 3:00AM.(I got home at 10 and played wow for a hour haha)
	*/
	for (int i = 0; i < 52; i++)
	{
		if (alphabet[i] != 0)
			cout << alphabet[i] << " for the letter of alphabet: " << i<<endl;
	}

	system("Pause");
	return 0;
}