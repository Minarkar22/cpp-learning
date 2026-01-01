#include<iostream>
#include<fstream>

using namespace std;
int main()
{
	ifstream fin;
	fin.open("/home/zeon/Documents/Nmap.txt");
	if(!fin)
	{
		cout << "File can not open!"<< endl;
		exit(1);
	}

	string line;
	while(getline(fin, line))
	{
		cout << line <<endl;
	}

	fin.close();

	return 0;
}
