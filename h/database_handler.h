#pragma once
#ifndef DATABASE_HANDLER_H
#define DATABASE_HANDLER_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <filesystem>


class database_handler {
    public:
    database_handler(std::filesystem::path& path);
    ~database_handler();
    void begin_transaction();
    void commit();
    void run_insert(const int& curr_depth,const int& parent_id, const std::string& inserted_value);
    int get_parent_id(int depth);

    private:
    SQLite::Database m_db;
    std::unique_ptr<SQLite::Transaction> m_transaction;
};
#endif