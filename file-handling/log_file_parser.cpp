#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cctype>

namespace fs = std::filesystem; 

void prasing_File (const fs::path& path){
    std::ifstream log_file(path);
    if (!log_file){
        std::cerr << "Error.File can not open.\n";
        return;
    } 

    int errorCount = 0;
    int warningCount = 0;
    int totalLines = 0;
    std::string line;

    while (std::getline(log_file, line)){
        totalLines ++;
        std::transform(line.begin(), line.end(), line.begin(),
                        [](unsigned char c) { return std::tolower(c);});

        if (line.find("error") != std::string::npos)
            errorCount++;
        
        if (line.find("warning") != std::string::npos)
            warningCount++;
    }

    log_file.close();

    std::cout << "---------Log File Prase---------\n";
    std::cout << "Total Lines : " << totalLines << " lines processed.\n";
    std::cout << "Total errors : " << errorCount << " occured.\n";
    std::cout << "Total warning : " << warningCount << " occured.\n";

}


int main(int argc, char* argv[]){
    if (argc < 2){
        std::cerr << "Usage : " << argv[0] << " <directory_path>\n";
        return 1;
    }

    fs::path path(argv[1]);
    if (!fs::exists(path)){
        std::cerr << "File Not Exist.\n";
        return 1;   
    }

    prasing_File(path);


    return 0;
}