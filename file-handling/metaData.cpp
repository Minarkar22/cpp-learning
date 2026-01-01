#include<iostream>
#include<sys/stat.h>
#include<unistd.h>
#include<pwd.h>  //for user name
#include<grp.h>  //for group
#include<ctime> //for timestamps

using namespace std;

int main()
{
	const char* path = "test.pdf";
	struct stat fileStat;

	if (stat(path, &fileStat) < 0)
	{
		perror("stat");
		exit(1);
	}

	cout << "File: " << path << endl;
	cout << "Size: " << fileStat.st_size << " bytes." << endl;
	cout << "Number of Links: " << fileStat.st_nlink << endl;

	struct passwd *pw = getpwuid(fileStat.st_uid);
	struct group *gr  = getgrgid(fileStat.st_gid);

	cout << "Owner: " << (pw ? pw->pw_name : to_string(fileStat.st_uid)) << endl;
	cout << "Group: " << (gr ? gr->gr_name : to_string(fileStat.st_gid)) << endl;

	cout << "last access: " << ctime(&fileStat.st_atime) << endl;
	cout << "Last modification: " << ctime(&fileStat.st_mtime) << endl;
	cout << "Last status change: " << ctime(&fileStat.st_ctime) << endl;
	
	cout << "Type : ";
	if(S_ISREG(fileStat.st_mode)) cout << "Regular File\n";
	else if(S_ISDIR(fileStat.st_mode)) cout << "Directory\n";
	else if(S_ISLNK(fileStat.st_mode)) cout << "Symbolic link\n";
	else cout << "Other\n";


	cout << "Permission : ";
	cout << ((fileStat.st_mode & S_IRUSR) ? "r" : "-");	      cout << ((fileStat.st_mode & S_IWUSR) ? "w" : "-");
	cout << ((fileStat.st_mode & S_IXUSR) ? "x" : "-");
	cout << endl;


	return 0;
}
