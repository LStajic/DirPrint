#pragma once
#ifndef DIRECTORY_SCANNER_H
#define DIRECTORY_SCANNER_H

#include <filesystem>

namespace fs = std::filesystem;

class directory_scanner{
    public:

    void scan(const fs::path& root);

    private:
    void process_directory(const fs::path& path);
};



#endif