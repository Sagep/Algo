#include <istream>
#include <fstream>
#include <string>
#include <iomanip>



using namespace std;





void read(ifstream inf, string & readChar){

	while(!inf.eof()){

		inf>>readChar;
	}

}

int main(int argc, char const *argv[])
{
	string file, readChar;
	ifstream inf;
	cout<<"type location of file: "<<endl;
	cin>>file;
	inf.open(file);
	read(inf, readChar);
	return 0;
}