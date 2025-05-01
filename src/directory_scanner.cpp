#include "../h/directory_scanner.h"
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace fs = std::filesystem;


//Scan and check for possible errors,write root data etc.
void directory_scanner::scan(const fs::path& root){
    if(!fs::exists(root)){
        throw std::runtime_error("Directory does not exist");
    }
    const auto canonical_root = fs::canonical(root);
    process_directory(canonical_root);
}

//Iterate through directories
void directory_scanner::process_directory(const fs::path& path){
    int parent_depth = -1;
    try {
        std::ofstream out_file("output");
        
        if (!out_file.is_open()) {
            std::cerr << "Failed to open output file: "  << std::endl;
            return;
        }
        for (auto it = fs::recursive_directory_iterator(path); it != fs::end(it); it++){
            const auto& entry = *it; 
            if(entry.is_symlink()) continue;
    
            //TYPE LOGIC GOES HERE
            out_file << entry.path().filename().string() << "\n";
        }
        
    }
    catch(fs::filesystem_error& e){
        std::cerr << "Filesystem error" << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}