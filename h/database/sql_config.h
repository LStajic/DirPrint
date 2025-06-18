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
        )"},
    {"GET_STABLO_ID", R"(
            SELECT stablo.id
            FROM lokalitet
            JOIN blizi_lokalitet ON lokalitet.id = blizi_lokalitet.id
            JOIN stablo ON blizi_lokalitet.id
            WHERE lokalitet.godina = ?
            AND lokalitet.ime = ?
            AND blizi_lokalitet.gazdinska_jedinica = ?
            AND blizi_lokalitet.odeljenje = ?
            AND blizi_lokalitet.odsek = ?
            AND stablo.vrsta = ?
            AND stablo.broj = ?
            AND stablo.visina = ?
            AND stablo.pravac = ?
        )"},
    {"INSERT_COMMENTS", R"(
            INSERT INTO stablo_komentari (id_stablo, Comment, SiteId, Location, EarthCoord, Elev, State, SpeciesCode, SpeciesName, DistanceToPith, Project, Personal_ID, DateOfSampling, Name, YearsToPith, Written, DBH, CooRecorder, LicencedTo, WaldKante, Sapwood, Interpretation, LocationCharacteristics, SoilType, DeTrend, Radius, CalcRadius, PithCoordinates)
            VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)    
        )"}
};

#endif