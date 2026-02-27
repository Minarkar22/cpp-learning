#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <iomanip>

namespace fs = std::filesystem;  //For file handling

//Step-1 - Data Structure
struct Entry {
    std::string path;
    uintmax_t size;
    bool isDirectory;
};

// Step-2 - Calculate File size
/* IF path is file:
    return file_size

IF path is directory:
    total = 0
    FOR each entry inside directory:
        total += calculateSize(entry)
    return total
*/

uintmax_t calculateSize (const fs::path& path, std::vector<Entry>& entries){
    try{
        fs::file_status status = fs::symlink_status(path);

        if (fs::is_symlink(path)) return 0;
        if (fs::is_regular_file(path)){
            uintmax_t size = fs::file_size(path);
            entries.push_back({path.string(), size, false});
            return size;
        }
        if (fs::is_directory(path)){
            uintmax_t totalSize = 0;
            for (const auto& p: fs::directory_iterator(path)){
                totalSize += calculateSize(p.path(), entries);
            }
            entries.push_back({path.string(), totalSize, true});
            return totalSize;
        }
    }
    catch (fs::filesystem_error& e) {
        std::cerr << "Error accessing : "<< path << "(" << e.what() << ")\n";
    }

    return 0;
}

//Step-3 - Format size to human readable
std::string formatSize(uintmax_t size){
    double KB = 1024;
    double MB = KB * 1024;
    double GB = MB * 1024;

    std::ostringstream oss;

    if (size > GB){
        oss << std::fixed << std::setprecision(2) << size / GB << "GB";
    }
    else if (size > MB){
        oss << std::fixed << std::setprecision(2) << size / MB << "MB";
    }
    else if (size > KB){
        oss << std::fixed << std::setprecision(2) << size / KB << "KB";
    }else {
        oss << size << "B";
    }

    return oss.str();
}

int main(int argc, char* argv[]) {
    if (argc < 2){
        std::cerr << "Usage: " << argv[0] << " <directory_path>\n";
        return 1;
    }

    fs::path path(argv[1]);
    if(!fs::exists(path)){
        std::cerr << "File dose not exist.\n";
        return 1;
    }

    std::vector<Entry> entries;
    uintmax_t size = calculateSize(path, entries);

    std::cout << formatSize(size) << std::endl;

    std::sort(entries.begin(),entries.end(), 
             [](const Entry& a, const Entry& b){
                return a.size > b.size;
            });
    
    std::cout << "/-------Disk Usage Report--------/\n";
    std::cout << "-------------------------------------\n";
    for (const auto& e : entries){
        std::cout << (e.isDirectory ? "[Dir]" : "[File]")
                  << std::setw(10) << std::right << formatSize(e.size)
                  << "  " << e.path << "\n";
    }

    return 0;

}