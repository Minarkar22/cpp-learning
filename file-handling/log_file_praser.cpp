#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cctype>
#include <vector>
#include <map>
#include <set>

namespace fs = std::filesystem; 

//Predefined flags
const std::map<std::string, std::string> FLAG_MAP = {
    {"-err",     "error"},
    {"-error",   "error"},
    {"-warn",    "warning"},
    {"-warning", "warning"},
    {"-info",    "info"},
    {"-debug",   "debug"},
    {"-fatal",   "fatal"},
    {"-crit",    "critical"},
};

void print_help(const char* program_name) {
    std::cout << "Usage:\n";
    std::cout << "  " << program_name << " <path> [flags/keywords...]\n\n";
    std::cout << "Arguments:\n";
    std::cout << "  <path>          Path to a log file or directory of log files\n\n";
    std::cout << "Predefined Flags:\n";
    std::cout << "  -err, -error    Search for 'error'\n";
    std::cout << "  -warn, -warning Search for 'warning'\n";
    std::cout << "  -info           Search for 'info'\n";
    std::cout << "  -debug          Search for 'debug'\n";
    std::cout << "  -fatal          Search for 'fatal'\n";
    std::cout << "  -crit           Search for 'critical'\n\n";
    std::cout << "Options:\n";
    std::cout << "  --help          Show this help message\n\n";
    std::cout << "Examples:\n";
    std::cout << "  " << program_name << " app.log -err -warn\n";
    std::cout << "  " << program_name << " /var/logs -err -debug\n";
    std::cout << "  " << program_name << " app.log myCustomKeyword\n";
    std::cout << "  " << program_name << " app.log -err timeout\n";
}

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
    std::cout << "==============================================\n";
    std::cout << "---------Log File Prase---------\n";
    std::cout << "File        : " << path.filename().string() << "\n";
    std::cout << "Total Lines : " << lineNumber << " lines processed.\n";
    std::cout << "==============================================\n";
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
    // Check for --help anywhere in args
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--help" || std::string(argv[i]) == "-h") {
            print_help(argv[0]);
            return 0;
        }
    }

    if (argc < 3){
        std::cerr << "Usage : " << argv[0] << " <directory_path> <keyword1> <keyword2> ...\n";
        print_help(argv[0]);
        return 1;
    }

    fs::path path(argv[1]);
    if (!fs::exists(path)){
        std::cerr << "File Not Exist.\n";
        return 1;   
    }

    // std::vector<std::string> keywords;   // ["error", "warning", "timeout"]
    // for (int i = 2; i < (argc); i++){
    //     keywords.emplace_back(argv[i]);
    // }

    // for (std::string& keyword : keywords){
    //     std::transform(keyword.begin(), keyword.end(), keyword.begin(), 
    //                     [](unsigned char c) { return std::tolower(c);});
    // }
            // { "error"   -> [3, 7, 12, 45, 99],
            //   "warning" -> [6, 20],
            //   "timeout" -> [] }
    //std::map<std::string, std::vector<int>> keywordLines;  
            // for (std::string keyword : keywords){
            //     keywordLines[keyword] = {};
            // }
            // no need, map auto create empty vector on first access
    //prasing_File(path, keywords, keywordLines);

    std::set<std::string> keyword_set;
    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];

        auto it = FLAG_MAP.find(arg);
        if (it != FLAG_MAP.end()) {
            // Known flag -> map to its keyword
            keyword_set.insert(it->second);
        } else if (!arg.empty() && arg[0] == '-') {
            // Unknown flag
            std::cerr << "Warning: Unknown flag '" << arg << "'. Ignoring.\n";
        } else {
            // Treat as a raw keyword, lowercase it
            std::transform(arg.begin(), arg.end(), arg.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            keyword_set.insert(arg);
        }
    }
    if (keyword_set.empty()) {
        std::cerr << "Error: No valid keywords or flags provided.\n\n";
        print_help(argv[0]);
        return 1;
    }
    std::vector<std::string> keywords(keyword_set.begin(), keyword_set.end());

    // Handle single file vs directory
    if (fs::is_regular_file(path)) {
        std::map<std::string, std::vector<int>> keywordLines;
        prasing_File(path, keywords, keywordLines);
    } else if (fs::is_directory(path)) {
        for (const auto& entry : fs::recursive_directory_iterator(path)) {
            if (entry.is_regular_file()) {
                std::map<std::string, std::vector<int>> keywordLines;
                prasing_File(entry.path(), keywords, keywordLines);
            }
        }
    } else {
        std::cerr << "Error: Path is neither a file nor a directory.\n";
        return 1;
    }

    return 0;
}