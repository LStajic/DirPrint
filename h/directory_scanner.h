#pragma once
#ifndef DIRECTORY_SCANNER_H
#define DIRECTORY_SCANNER_H

#include <filesystem>
#include "../h/database_handler.h"

namespace fs = std::filesystem;

class directory_scanner{
    public:
    directory_scanner(database_handler& db_handler);
    void scan(const fs::path& root);

    private:
    void process_directory(const fs::path& path);
    database_handler& db_handler;
};



#endif