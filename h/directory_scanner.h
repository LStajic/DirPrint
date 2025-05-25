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
    void scan(const fs::path& root);

    private:
    void process_directory(const fs::path& path);
    database_handler& m_db_handler;
    xls_handler m_xls_handler;
};



#endif