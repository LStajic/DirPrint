#pragma once
#ifndef SQL_CONFIG_H
#define SQL_CONFIG_H
#include <vector>
#include <string>
#include <array>

//TEMPORARY: Commands for directory search
const std::array<std::string, 3> STRING_QUERY_ARR = {
    R"(
            INSERT INTO lokalitet (godina, ime)
            VALUES (?, ?)
        )",
    R"(
            INSERT INTO blizi_lokalitet (id_lokalitet, gazdinska_jedinica, odeljenje, odsek, op)
            VALUES (?, ?, ?, ?, ?)
        )",
    R"(
            INSERT INTO stablo (id_blizi_lokalitet, vrsta, broj, visina, pravac)
            VALUES (?, ?, ?, ?, ?)
        )"
};

//Comand name - Command pairs
const std::vector<std::pair<std::string, std::string>> SQL_COMMANDS = {
    {"get_user",R"(
            INSERT INTO lokalitet (godina, ime)
            VALUES (?, ?)
        )"},
    {"add_user",    "INSERT INTO users VALUES (?, ?, ?);"},
    {"delete_user", "DELETE FROM users WHERE id = ?;"},
};
#endif