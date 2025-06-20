#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include "../h/directory_scanner.h"
#include "../h/database_handler.h"
#include "logger/logger_instance.h"

int main(int argc, char* argv[]){
    try {
        auto start_time = std::chrono::steady_clock::now();
        if(argc != 3) {
            std::cerr << "Usage: " << argv[0] << " <directory> <database>\n";
            return 1;
        }
        std::filesystem::path path = argv[2];
        database_handler db_handler(path);
        directory_scanner ds1(db_handler);

        db_handler.drop_tables();
        db_handler.rebuild_tables();
        db_handler.begin_transaction();
        ds1.scan(argv[1],argv[2]);
        db_handler.commit();

        auto end_time = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
        logger.log("The program finished in " + std::to_string(duration) + " seconds\n",log_level::INFO);
    } catch (const std::exception& e) {
        logger.log(std::string("Error in main: ") + e.what() + std::string("\n"), log_level::ERROR);
        return 1;
    }

    return 0;
}

