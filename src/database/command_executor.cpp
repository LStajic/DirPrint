#include "../h/database/command_executor.h"
#include "database/sql_config.h"
#include "logger/logger_instance.h"
#include <iostream>
#include <fstream>
#include <vector>

void command_executor::command_recreate_database(const std::string path){
    try {
    if(std::filesystem::exists(path)){
        std::filesystem::remove(path);
    }
    } catch (const std::exception& e) {
        logger.log(std::string("FATAL ERROR: ") + e.what() + std::string("\n"), log_level::ERROR);
        throw; // Re-throw for test framework
    }
}

void command_executor::command_insert_dir(SQLite::Database& db, const long int parent_id, const int depth, const std::string name){
    switch (depth) {
            case 0: {
                SQLite::Statement query(db, SQL_COMMANDS.find("Directory_insert_lokalitet")->second);
                if(name.length() < 6) {
                    logger.log(std::string("Warning ") + name + std::string(" is shorter than expected, ignoring\n"), log_level::WARNING);
                    return;
                }
                query.bind(1, name.substr(0,4));
                query.bind(2,name.substr(4, 2));
                query.exec();
                break;
            }
            case 1: {
                SQLite::Statement query(db, SQL_COMMANDS.find("Directory_insert_blizi_lokalitet")->second);
                //preverava da li je kraci od 17 jer bi onda izazvao segfault greske
                if(name.length() < 17) {
                    logger.log(std::string("Warning ") + name + std::string(" is shorter than expected, ignoring\n"),log_level::WARNING);
                    return;
                }
                query.bind(1, parent_id);
                query.bind(2,name.substr(6,4));
                query.bind(3,name.substr(10,3));
                query.bind(4,name.substr(13,1));
                query.bind(5,name.substr(14,3));
                query.exec();
                break;
            }
            }
};

void command_executor::command_write_xls_data(SQLite::Database& db, const std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data,long int& parent_id,long int& current_id){
    SQLite::Statement query(db,SQL_COMMANDS.find("XLS_insert_stablo")->second);
    SQLite::Statement query2(db,SQL_COMMANDS.find("XLS_insert_stablo_godina")->second); //dont care
    //obavezno uvedi neki nacin da se prati id ako se dodaju nove vrednosti <-- ignore, nije potrebno za sada
    for (auto it = data.begin(); it != data.end(); ++it){
        logger.log(std::string("Writing data: parent id = " + std::to_string(parent_id) + " inserted string = " + it->first), log_level::INFO);
        query.clearBindings();
        query.bind(1,parent_id);
        query.bind(2,it->first.substr(0,4));
        query.bind(3,it->first.substr(4,3));
        query.bind(4,it->first.substr(7,1));
        query.exec();
        query.clearBindings();
        query.reset();
        ++current_id;

        for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2){
            logger.log(std::string("Writing data: current id = " + std::to_string(current_id) + " inserted string 1 = " + it2->first + " inserted string 2 = " + it2->second), log_level::INFO);
            query2.clearBindings();
            query2.bind(1,current_id);
            query2.bind(2,it2->first);
            query2.bind(3,it2->second);
            query2.exec();
            query2.clearBindings();
            query2.reset();
        }
    }
}
//DO NOT USE
void command_executor::command_organize_images(SQLite::Database& db, const std::filesystem::path image_path, const std::filesystem::path target_path){
    std::string image_name = image_path.filename().string().substr(17);
    int id;
    SQLite::Statement query(db,SQL_COMMANDS.find("GET_BLIZI_LOKALITET_ID")->second);
    try {
        
        query.bind(1, image_name.substr(0,4));  //godina
        query.bind(2, image_name.substr(4,2));  //ime
        query.bind(3, image_name.substr(6,4));  //gazdinska_jedinica
        query.bind(4, image_name.substr(10,3)); //odeljenje
        query.bind(5, image_name.substr(13,1)); //odsek
        query.bind(6,image_name.substr(14,3));  //op
        if(query.executeStep()){
            id = query.getColumn(0).getInt();
        }
    } catch (const std::exception& e) {
        std::cerr << "SQLite error" << e.what() << std::endl;
    }
    if(!std::filesystem::exists(target_path / std::to_string(id)))
    {
        std::filesystem::create_directory(target_path / std::to_string(id));
    }
    std::filesystem::copy_file(image_path,target_path / std::to_string(id),std::filesystem::copy_options::overwrite_existing);

}

void command_executor::insert_pair(std::string text){
    int pos = text.find_first_of("=");
    std::string key = text.substr(0,pos);
    std::string value = text.substr(pos + 1);
    logger.log(std::string("Inserting as key: " + key + " , inserting as value: " + value), log_level::DEBUG);
    data_map.insert(std::make_pair(key, value));
}


void command_executor::command_insert_comments(SQLite::Database& db, const std::filesystem::path& text_path){
    SQLite::Statement query(db,SQL_COMMANDS.find("GET_STABLO_ID")->second);
    SQLite::Statement query2(db,SQL_COMMANDS.find("INSERT_COMMENTS")->second);
    std::ifstream text_file;
    std::string word, current_table;
    int id, bind_index;
    bool first_word, comment;
    std::vector<std::string> all_cols = {
    "Comment",
    "SiteId",
    "Location",
    "EarthCoord",
    "Elev",
    "State",
    "SpeciesCode",
    "SpeciesName",
    "DistanceToPith",
    "Project",
    "Personal_ID",
    "DateOfSampling",
    "Name",
    "YearsToPith",
    "Written",
    "DBH",
    "CooRecorder",
    "LicencedTo",
    "WaldKante",
    "Sapwood",
    "Interpretation",
    "LocationCharacteristics",
    "SoilType",
    "DeTrend",
    "Radius",
    "CalcRadius",
    "PithCoordinates"
};
    //preskace prve 3 linije
    text_file.open(text_path.string());
    for(int i = 0; i < 3; ++i){
        std::getline(text_file,word);
    }
    //prvi string koji uzima nakon toga postaje current_table
    text_file >> word;
    current_table = word;
    //pocinje loop kroz ostatak fajla
    while (text_file >> word) {
        if(first_word){
            first_word = false;
            comment = true;
            //proverava da li se i dalje radi na istom stablu
            if(word == current_table){
                continue;
            }
            //ako nije isto stablo, upisuje u tabelu sve komentare iz prethodnog stabla
            else {
                try {
                    //pronalazi potrebno stablo tako sto prvo upisuje podatke iz imena fajla (parent tabele)
                    query.bind(1, text_path.filename().string().substr(0,4));  //godina
                    query.bind(2, text_path.filename().string().substr(4,2));  //ime
                    query.bind(3, text_path.filename().string().substr(6,4));  //gazdinska_jedinica
                    query.bind(4, text_path.filename().string().substr(10,3));  //odeljenje
                    query.bind(5, text_path.filename().string().substr(13,1));  //odsek
                    query.bind(6, text_path.filename().string().substr(14,3));  //op
                    //upisuje podatke iz current_table
                    query.bind(7,current_table.substr(0,4));    //broj
                    query.bind(8,current_table.substr(4,3));    //visina
                    query.bind(9,current_table.substr(7,1));    //pravac

                    if(query.executeStep()){
                        id = query.getColumn(0).getInt();
                        current_table = word;
                    }
                    query.clearBindings();
                    query.reset();
                    //prelazi na upisivanje podataka iz data_map u novu tabelu sa komentarima
                    bind_index = 1;
                    query2.bind(bind_index,id);
                    ++bind_index;
                    for (const auto& col : all_cols) {
                        auto it = data_map.find(col);
                        if(it != data_map.end()){
                            query2.bind(bind_index, it->second);
                        } else {
                            query2.bind(bind_index,"empty");
                        }
                        ++bind_index;
                    }
                    query2.exec();
                    query2.clearBindings();
                    query2.reset();
                    data_map.clear();
                } catch (const std::exception& e) {
                    std::cerr << "SQLite error" << e.what() << std::endl;
                }
            }
        }
        //ukoliko nije first word onda upisuje ovaj string kao par u data_map
        //patched
        else {
            if(comment){
                insert_pair("Comment=" + word);
            }
            else{
                insert_pair(word);
            }
        }
        if (text_file.peek() == '\n' || text_file.peek() == '\r') {
            first_word = true;
        }
    }
    
}