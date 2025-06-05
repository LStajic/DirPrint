#pragma once
#include <unordered_map>
#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Statement.h>


class command_executor{
    public:
    void command_recreate_database(std::string path);
    void command_insert_dir(SQLite::Database& db, const long int parent_id, const int depth, const std::string name);
    void command_write_xls_data(SQLite::Database& db, const std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data, long int& parent_id, long int& current_id);
    //samo napisi kako da prebacis sliku i sta vec
    void command_organize_images();
    //napravi novu tabelu za komentare i dodaj sve parove i sta vec
    void command_insert_comments();
};



#endif