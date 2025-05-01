#include <SQLiteCpp/Database.h>
#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>
#include "../h/directory_scanner.h"


int main(){
//    const std::string db_path = "/home/lukas/Random/sqlite/testdb.db";
//    SQLite::Database db(db_path, SQLite::OPEN_READWRITE);
    directory_scanner ds1;
    ds1.scan("/home/lukas/Random");
    return 0;
}

//vrati .vscode, resi probleme sa ekstenzijama