#pragma once
#ifndef DIRECTORY_SCANNER_H
#define DIRECTORY_SCANNER_H

#include <filesystem>
#include "../h/database_handler.h"
#include "../h/xls_handler.h"

namespace fs = std::filesystem;

class directory_scanner{
    public:
    directory_scanner(database_handler& db_handler);
    void scan(const fs::path& root, const fs::path target_path);

    private:
    void process_directory(const fs::path& path, const fs::path target_path);
    void read_xls_file(const fs::path& path);
    database_handler& m_db_handler;
    xls_handler m_xls_handler;
    long int current_id[4] = {0,0,0,0};
};



#endif