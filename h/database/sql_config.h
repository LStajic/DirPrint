#pragma once
#ifndef SQL_CONFIG_H
#define SQL_CONFIG_H
#include <unordered_map>
#include <string>

//TEMPORARY: HASHTABLE sa svim sql komandama
const std::unordered_map<std::string, std::string> SQL_COMMANDS = {
    {"Directory_insert_lokalitet", R"(
            INSERT INTO lokalitet (godina, ime)
            VALUES (?, ?)
        )"},
    {"Directory_insert_blizi_lokalitet", R"(
            INSERT INTO blizi_lokalitet (id_lokalitet, gazdinska_jedinica, odeljenje, odsek, op)
            VALUES (?, ?, ?, ?, ?)
        )"},
    {"XLS_insert_stablo", R"(
            INSERT INTO stablo (id_blizi_lokalitet, vrsta, broj, visina, pravac)
            VALUES (?, ?, ?, ?, ?)
        )"},
    {"XLS_insert_stablo_godina", R"(
            INSERT INTO stablo_godina (id_stablo, godina, vrednost)
            VALUES (?, ?, ?)
        )"}
};

#endif