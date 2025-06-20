#include "../h/database_handler.h"
#include "../h/database/sql_config.h"
#include <iostream>
#include <vector>


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

void database_handler::drop_tables(){
    try {
        SQLite::Statement query(m_db, "SELECT name FROM sqlite_master WHERE type='table' AND name NOT LIKE 'sqlite_%';");

        std::vector<std::string> tables;
        while (query.executeStep()) {
            tables.push_back(query.getColumn(0).getString());
        }

        m_db.exec("PRAGMA foreign_keys = OFF;");

        for (const auto& table : tables) {
            std::string dropQuery = "DROP TABLE IF EXISTS \"" + table + "\";";
            m_db.exec(dropQuery);
            std::cout << "Dropped table: " << table << std::endl;
        }
        m_db.exec("DELETE FROM sqlite_sequence;");
        m_db.exec("PRAGMA foreign_keys = ON;");
    } catch (const std::exception& e) {
        std::cerr << "SQLite error: " << e.what() << std::endl;
    }

}

void database_handler::rebuild_tables(){
    m_db.exec(SQL_COMMANDS.find("REBUILD_DB")->second);
}

database_handler::~database_handler() = default;