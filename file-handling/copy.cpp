#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("/home/zeon/Documents/Exam2.pdf");
	if (! fin)
	{
		cout << "Source file can not find!\n";
		exit(1);
	}
	fout.open("/home/zeon/Desktop/Learning/file_open_read/test.pdf");
	if (! fout)
	{
		cout << "Destiantion file can not find!\n";
		exit(1);
	}
	
	char buffer[1024];  // create 1 KB memory block
	
	while (fin.read(buffer, sizeof(buffer)))
	{
		fout.write(buffer, fin.gcount());
	}

	//Write remaining bytes after last read
	fout.write(buffer, fin.gcount());

	fin.close();
	fout.close();
	cout << "File copied successfully!\n";
	return 0;

	
}
