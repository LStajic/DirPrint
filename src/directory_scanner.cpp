#include "../h/directory_scanner.h"
#include <filesystem>
#include <stdexcept>
#include <iostream>

namespace fs = std::filesystem;

directory_scanner::directory_scanner(database_handler& db_handler) : m_db_handler(db_handler){}


//Scan and check for possible errors, checks if the given path exists, then runs directory_scanner
void directory_scanner::scan(const fs::path& root){
    if(!fs::exists(root)){
        throw std::runtime_error("Directory does not exist");
    }
    const auto canonical_root = fs::canonical(root);
    process_directory(canonical_root);
}

//Iterate through directories using recursive_directory_iterator (TO BE CHANGED!)
void directory_scanner::process_directory(const fs::path& path){
    long long int current_id[3] = {0, 0, 0};
    try {
        // auto it = fs::recursive_directory_iterator(path);
        // const auto end = fs::recursive_directory_iterator();
        // while(it != end){
        //     ++it
        // }
        for (auto it = fs::recursive_directory_iterator(path); it != fs::end(it); it++){
            const auto& entry = *it; 
            //if directory does the id logic and writes upper level tables
            if(entry.is_directory()){
                if (it.depth() >= 3){
                    continue;
                }
                current_id[it.depth()]++;
                //db_handler.run_insert_directory(it.depth(), it.depth() == 0 ? 0 : current_id[it.depth() - 1], entry.path().filename().string());
                std::cout << "ID: " << current_id[it.depth()] << ", PARENT ID: " << (it.depth() == 0 ? 0 : current_id[it.depth() - 1]) << ", Name: " << entry.path().filename().string() << std::endl;
                continue;
            }
            //if xls run xls_handler
            if(entry.path().extension().string() == ".xls"){
                std::cout << entry.path().filename().string();
                continue;
            }

        }
        
    }
    catch(fs::filesystem_error& e){
        std::cerr << "Filesystem error" << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
} 