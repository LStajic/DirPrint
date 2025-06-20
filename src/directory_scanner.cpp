#include "../h/directory_scanner.h"
#include "logger/logger_instance.h"
#include <filesystem>
#include <stdexcept>
#include <iostream>

namespace fs = std::filesystem;

directory_scanner::directory_scanner(database_handler& db_handler) : m_db_handler(db_handler){
    
}


//Scan and check for possible errors, checks if the given path exists, then runs directory_scanner
void directory_scanner::scan(const fs::path& root, const fs::path target_path){
    if(!fs::exists(root)){
        throw std::runtime_error("Directory does not exist");
    }
    const auto canonical_root = fs::canonical(root);
    process_directory(canonical_root,target_path);
}
//Iterate through directories using recursive_directory_iterator (TO BE CHANGED!) (with a recursive function of directory_iterator)
//povecava na svakom krugu id za jedan one vrednosti koja se nalazi na poziciju u nizu jednakoj vrednosti it.depth()
void directory_scanner::process_directory(const fs::path& path, const fs::path target_path){
    bool first_iteration = true;
    for(int i = 0; i < 2; ++i){
        if(first_iteration){
            try {
                for (auto it = fs::recursive_directory_iterator(path); it != fs::end(it); it++){
                    const auto& entry = *it; 
                    //if directory does the id logic and writes upper level tables
                    if(entry.is_directory()){
                        logger.log(std::string("Directory ") + entry.path().filename().string() + std::string(" found\n"), log_level::INFO);
                        if (it.depth() >= 3){
                            continue;
                        }
                        current_id[it.depth()]++;
                        //db_handler.run_insert_directory(it.depth(), it.depth() == 0 ? 0 : current_id[it.depth() - 1], entry.path().filename().string());
                        m_db_handler.command().command_insert_dir(m_db_handler.database(), current_id[it.depth() - 1], it.depth(), entry.path().filename().string());
                        logger.log(std::string("Insertion performed\n"), log_level::INFO);
                        continue;
                    }
                    //if xls run xls_handler
                    if(entry.path().extension().string() == ".xls"){
                        //uzmi current_id[it.depth() - 1] kao parent id za povezivanje
                        //onda pokreni read_xls kao argument db_handler poziva
                        logger.log(std::string("XLS file ") + entry.path().filename().string() + std::string(" found\n"), log_level::INFO);
                        m_xls_handler.set_workbook(entry.path());
                        logger.log(std::string("set_workbook works\n"), log_level::INFO);
                        m_xls_handler.get_xls_data();
                        logger.log(std::string("get_xls_data works\n"), log_level::INFO); 
                        m_db_handler.command().command_write_xls_data(m_db_handler.database(), m_xls_handler.get_results(), current_id[it.depth() - 1], current_id[it.depth()]);
                        m_xls_handler.clear_results();
                        logger.log(std::string("Insertion performed\n"), log_level::INFO);
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
            first_iteration = false;
        }
        else {
            try {
                std::cout << "Beginning second iteration" << std::endl;
                for (auto it = fs::recursive_directory_iterator(path); it != fs::end(it); it++){
                    const auto& entry = *it; 
                    //if image pokrece organize_images
                    // if(entry.path().extension().string() == ".jpg"){
                    //     m_db_handler.command().command_organize_images(m_db_handler.database(), entry.path(), target_path);
                    //     continue;
                    // }
                    //if txt pokreni comments
                    if(entry.path().extension().string() == ".txt"){
                        m_db_handler.command().command_insert_comments(m_db_handler.database(), entry.path());
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
    }
} 