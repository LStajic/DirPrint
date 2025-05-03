#include "../h/database_handler.h"
#include "../h/sql_config.h"

database_handler::database_handler(std::filesystem::path& path) : m_db(path.string(), SQLite::OPEN_READWRITE){}

void database_handler::run_insert(const int& curr_depth,const int& parent_id, const std::string& inserted_value){
    //optimized!
    SQLite::Statement query(m_db,STRING_QUERY_ARR[curr_depth]);
    switch (curr_depth) {
    case 1: {
        query.bind(1, inserted_value.substr(0,4));
        query.bind(2,inserted_value.substr(3));
        break;
    }
    case 2: {
        query.bind(1, parent_id);
        query.bind(2,inserted_value.substr(0,4));
        query.bind(3,inserted_value.substr(4,3));
        query.bind(4,inserted_value.substr(7,1));
        query.bind(5,inserted_value.substr(8,3));
        break;
    }
    case 3: {
        query.bind(1, parent_id);
        query.bind(2,inserted_value.substr(0,2));
        query.bind(3,inserted_value.substr(2,4));
        query.bind(4,inserted_value.substr(6,3));
        query.bind(5,inserted_value.substr(9,1));
        break;
    }
    }
}