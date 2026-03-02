#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cctype>
#include <vector>
#include <map>

namespace fs = std::filesystem; 

void prasing_File (const fs::path& path, const std::vector<std::string>& keywords, std::map<std::string, std::vector<int>>& keywordLines){
    std::ifstream log_file(path);
    if (!log_file){
        std::cerr << "Error.File can not open.\n";
        return;
    } 

    // int errorCount = 0;
    // int warningCount = 0;
    int lineNumber = 0;
    //int totalLines = 0;
    std::string line;

    while (std::getline(log_file, line)){
        //totalLines ++;
        lineNumber ++;
        std::transform(line.begin(), line.end(), line.begin(),
                        [](unsigned char c) { return std::tolower(c);});

        for (const std::string& keyword : keywords){
            // std::string lowercase_keyword = keyword;
            // std::transform(lowercase_keyword.begin(), lowercase_keyword.end(), lowercase_keyword.begin(), 
            //             [](unsigned char c) { return std::tolower(c); });
            // change to lowercase in main function, to avoid repeat case in loop, not necessary
            
            if (line.find(keyword) != std::string::npos)
                keywordLines[keyword].emplace_back(lineNumber);
        }

        // if (line.find("error") != std::string::npos)
        //     errorCount++;
        
        // if (line.find("warning") != std::string::npos)
        //     warningCount++;
    }

    log_file.close();

    std::cout << "---------Log File Prase---------\n";
    std::cout << "Total Lines : " << lineNumber << " lines processed.\n";
    //std::cout << "\n";
    
    for (const std::string& keyword : keywords){
        std::cout << "Keyword : " << keyword << "\n";
        std::cout << "Occurences : " << keywordLines[keyword].size() << "\n";
        if (keywordLines[keyword].size() > 0){
            std::cout << "Line Numbers : ";
            for (int i = 0; i < keywordLines[keyword].size(); i++) {
                if (i > 0) std::cout << ", ";
                std::cout << keywordLines[keyword][i];
            }
            std::cout << "\n";
        }
        else {
            std::cout << "No occurrences Found.\n";
        }
        std::cout << "=======================================\n";
    }

}


int main(int argc, char* argv[]){
    if (argc < 3){
        std::cerr << "Usage : " << argv[0] << " <directory_path> <keyword1> <keyword2> ...\n";
        return 1;
    }

    fs::path path(argv[1]);
    if (!fs::exists(path)){
        std::cerr << "File Not Exist.\n";
        return 1;   
    }

    std::vector<std::string> keywords;   // ["error", "warning", "timeout"]
    for (int i = 2; i < (argc); i++){
        keywords.emplace_back(argv[i]);
    }

    for (std::string& keyword : keywords){
        std::transform(keyword.begin(), keyword.end(), keyword.begin(), 
                        [](unsigned char c) { return std::tolower(c);});
    }
    // { "error"   -> [3, 7, 12, 45, 99],
    //   "warning" -> [6, 20],
    //   "timeout" -> [] }
    std::map<std::string, std::vector<int>> keywordLines;  
    // for (std::string keyword : keywords){
    //     keywordLines[keyword] = {};
    // }
    // no need, map auto create empty vector on first access
    prasing_File(path, keywords, keywordLines);


    return 0;
}