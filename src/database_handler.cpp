#include "../h/database_handler.h"


database_handler::database_handler(std::filesystem::path& path) : m_db(path.string(), SQLite::OPEN_READWRITE){}
 

void database_handler::begin_transaction(){
    if(m_transaction) throw std::runtime_error("Transaction already active");
    m_transaction = std::make_unique<SQLite::Transaction>(m_db);
}

void database_handler::commit(){
    if(!m_transaction) throw std::runtime_error("No active transaction");
    m_transaction->commit();
    m_transaction.reset();
}

void database_handler::create_directory(std::filesystem::path target_directory){
    if (!std::filesystem::exists(target_directory)){
        std::filesystem::create_directories(target_directory / "images");
    }
}

database_handler::~database_handler() = default;