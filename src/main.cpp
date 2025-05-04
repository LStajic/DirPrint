#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include "../h/directory_scanner.h"
#include "../h/database_handler.h"

int main(int argc, char* argv[]){
    try {
        if(argc != 3) {
            std::cerr << "Usage: " << argv[0] << " <directory> <database>\n";
            return 1;
        }
        std::filesystem::path path = argv[2];
        database_handler db_handler(path);
        directory_scanner ds1(db_handler);
    
        db_handler.begin_transaction();
        ds1.scan(argv[1]);
        db_handler.commit();
    } catch (const std::exception& e) {
        std::cerr << "Error" << e.what() << "\n";
        return 1;
    }

    return 0;
}

