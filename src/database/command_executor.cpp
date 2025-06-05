#include "../h/database/command_executor.h"
#include "database/sql_config.h"
#include <iostream>

void command_executor::command_recreate_database(const std::string path){
    try {
    if(std::filesystem::exists(path)){
        std::filesystem::remove(path);
    }
    } catch (const std::exception& e) {
        std::cerr << "Database recreation failed: " << e.what() << std::endl;
        throw; // Re-throw for test framework
    }
}

void command_executor::command_insert_dir(SQLite::Database& db, const long int parent_id, const int depth, const std::string name){
    switch (depth) {
            case 0: {
                SQLite::Statement query(db, SQL_COMMANDS.find("Directory_insert_lokalitet")->second);
                if(name.length() < 5) {
                    std::cout << name << " ignored" << std::endl;
                    return;
                }
                query.bind(1, name.substr(0,4));
                query.bind(2,name.substr(4, 2));
                query.exec();
                break;
            }
            case 1: {
                SQLite::Statement query(db, SQL_COMMANDS.find("Directory_insert_blizi_lokalitet")->second);
                if(name.length() < 17) {
                    std::cout << name << " ignored" << std::endl;
                    return;
                }
                query.bind(1, parent_id);
                query.bind(2,name.substr(6,4));
                query.bind(3,name.substr(10,3));
                query.bind(4,name.substr(13,1));
                query.bind(5,name.substr(16));
                query.exec();
                break;
            }
            }
};

void command_executor::command_write_xls_data(SQLite::Database& db, const std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data,long int& parent_id,long int& current_id){
    SQLite::Statement query(db,SQL_COMMANDS.find("XLS_insert_stablo")->second);
    SQLite::Statement query2(db,SQL_COMMANDS.find("XLS_insert_stablo_godina")->second); //dont care
    //obavezno uvedi neki nacin da se prati id ako se dodaju nove vrednosti
    for (auto it = data.begin(); it != data.end(); ++it){
        query.clearBindings();
        query.bind(1,parent_id);
        std::cout << "Parent_id: " << parent_id << std::endl;
        query.bind(2,it->first.substr(0,2));
        query.bind(3,it->first.substr(2,4));
        query.bind(4,it->first.substr(4,6));
        query.bind(5,it->first.substr(6));
        query.exec();
        query.reset();
        for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2){
            query2.clearBindings();
            query2.bind(1,current_id);
            std::cout << "Current_id: " << current_id << std::endl;
            query2.bind(2,it2->first);
            query2.bind(3,it2->second);
            query2.exec();
            query2.reset();
        }
        ++current_id;
    }
}
