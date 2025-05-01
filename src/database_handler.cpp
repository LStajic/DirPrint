#include "../h/database_handler.h"

database_handler::database_handler(std::filesystem::path& path) : m_db(path.string(), SQLite::OPEN_READWRITE){}

void database_handler::run_insert(const int& curr_depth, const std::string& inserted_value){
    SQLite::Statement query(m_db,R"(
        INSERT INTO lokalitet (id, godina, ime)
        VALUES (?, ?)
    )");
    switch (curr_depth) {
    case 1: {
        query.bind(1, inserted_value.substr(0,4));
        query.bind(2,inserted_value.substr(3));
        break;
        //NADJI NACIN DA UVEDES ID_LOKALITETA U FOREIGN KEY
    }
    case 2: 
        query.bind(1, inserted_value.substr(0,4));
        query.bind(2,inserted_value.substr(3));
        break;
    }
}