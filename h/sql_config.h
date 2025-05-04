#pragma once
#ifndef SQL_CONFIG_H
#define SQL_CONFIG_H
#include <unordered_map>
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
const std::unordered_map<std::string, std::string> SQL_COMMANDS = {
    {"get_id_lokalitet",R"(
            SELECT id FROM lokalitet
        )"},
    {"get_id_blizi_lokalitet",R"(
            SELECT id FROM blizi_lokalitet
        )"},
    {"delete_user", "DELETE FROM users WHERE id = ?;"},
};
#endif