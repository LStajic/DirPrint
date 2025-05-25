#include "../h/database_handler.h"
#include "../h/sql_config.h"
#include <iostream>

database_handler::database_handler(std::filesystem::path& path) : m_db(path.string(), SQLite::OPEN_READWRITE){}
//Metod koji uzima trenutni depth i ime direktorijuma da unese podatke koji su zavisni od dubine
void database_handler::run_insert_directory(const int& curr_depth,const int& parent_id, const std::string& inserted_value){
    //optimizovano!
    SQLite::Statement query(m_db,STRING_QUERY_ARR[curr_depth]);
        switch (curr_depth) {
            case 0: {
                if(inserted_value.length() < 5) {
                    std::cout << inserted_value << " ignored" << std::endl;
                    return;
                }
                query.bind(1, inserted_value.substr(0,4));
                query.bind(2,inserted_value.substr(4, 2));
                break;
            }
            case 1: {
                if(inserted_value.length() < 17) {
                    std::cout << inserted_value << " ignored" << std::endl;
                    return;
                }
                query.bind(1, parent_id);
                query.bind(2,inserted_value.substr(6,4));
                query.bind(3,inserted_value.substr(10,3));
                query.bind(4,inserted_value.substr(13,1));
                query.bind(5,inserted_value.substr(16));
                break;
            }
            //nikad se nece pokrenuti
            case 2: {
                if(inserted_value.length() < 10) {
                    std::cout << inserted_value << " ignored" << std::endl;
                    return;
                }
                query.bind(1, parent_id);
                query.bind(2,inserted_value.substr(0,2));
                query.bind(3,inserted_value.substr(2,4));
                query.bind(4,inserted_value.substr(6,3));
                query.bind(5,inserted_value.substr(9,1));
                break; 
            }
        }
    query.exec();
}

int database_handler::get_parent_id(int depth){
    if (depth == 2) {
        SQLite::Statement get_parent_id(m_db, SQL_COMMANDS.at("get_id_lokalitet"));
    }
    else if (depth == 3) {
        SQLite::Statement get_parent_id(m_db, SQL_COMMANDS.at("get_id_blizi_lokalitet"));
    }
    return 0;
}

void database_handler::begin_transaction(){
    if(m_transaction) throw std::runtime_error("Transaction already active");
    m_transaction = std::make_unique<SQLite::Transaction>(m_db);
}

void database_handler::commit(){
    if(!m_transaction) throw std::runtime_error("No active transaction");
    m_transaction->commit();
    m_transaction.reset();
}

database_handler::~database_handler() = default;