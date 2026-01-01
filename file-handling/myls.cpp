#include<iostream>
#include<sys/stat.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<iomanip>
#include<unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
	const char * dirPath = ".";
	if (argc > 1)
	{
		dirPath = argv[1];
	}
	DIR *dir = opendir(dirPath);  //open dir
	if (!dir)
	{
		perror("opendir");
		exit(1);
	}

	
	struct dirent * entry;
	while((entry = readdir(dir)) != NULL)
	{
		string name = entry->d_name;
		string path = string(dirPath)+"/" + name;

		struct stat st;
		if (stat(path.c_str(), &st))
		{
			perror("stat");
			exit(1);
		}
		
		//File Type
		cout << (S_ISDIR(st.st_mode) ? "d" : "-");

		//Permission
		cout << ((st.st_mode & S_IRUSR) ? "r" : "-");
		cout << ((st.st_mode & S_IWUSR) ? "w" : "-");
		cout << ((st.st_mode & S_IXUSR) ? "x" : "-");
		cout << ((st.st_mode & S_IRGRP) ? "r" : "-");
		cout << ((st.st_mode & S_IWGRP) ? "w" : "-");
		cout << ((st.st_mode & S_IXGRP) ? "x" : "-");
		cout << ((st.st_mode & S_IROTH) ? "r" : "-");
		cout << ((st.st_mode & S_IWOTH) ? "w" : "-");
		cout << ((st.st_mode & S_IXOTH) ? "x" : "-");	
		
		struct passwd *pw = getpwuid(st.st_uid);
		struct group *gr  = getgrgid(st.st_gid);
		tm * tm_info      = localtime(&st.st_mtime);
		
		cout << " " << st.st_nlink;
		cout << " " << pw->pw_name;
		cout << " " << gr->gr_name;
		cout << " " << st.st_size;
		cout << " " << put_time(tm_info, "%b %d %H:%M");
		cout << " " << name << endl;
		
	}

	closedir(dir);

	return 0;
}
