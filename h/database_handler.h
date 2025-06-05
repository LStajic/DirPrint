#pragma once
#ifndef DATABASE_HANDLER_H
#define DATABASE_HANDLER_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <filesystem>
#include "database/command_executor.h"

class database_handler {
    public:
    database_handler(std::filesystem::path& path);
    ~database_handler();

    SQLite::Database& database() {return m_db;}
    command_executor& command() {return m_command_exectutor;}
    
    void create_directory(std::filesystem::path target_directory);
    void begin_transaction();
    void commit();
    int get_parent_id(int depth);

    private:
    SQLite::Database m_db;
    std::unique_ptr<SQLite::Transaction> m_transaction;
    command_executor m_command_exectutor;
};
#endif