#pragma once
#ifndef SQL_CONFIG_H
#define SQL_CONFIG_H
#include <unordered_map>
#include <string>

//TEMPORARY: HASHTABLE sa svim sql komandama
const std::unordered_map<std::string, std::string> SQL_COMMANDS = {
    {"REBUILD_DB",R"(
            PRAGMA foreign_keys = ON;

			CREATE TABLE lokalitet (
				id INTEGER PRIMARY KEY AUTOINCREMENT,
				godina TEXT,
				ime TEXT
			);

			CREATE TABLE blizi_lokalitet (
				id INTEGER PRIMARY KEY AUTOINCREMENT,
				id_lokalitet INTEGER,
				gazdinska_jedinica TEXT,
				odeljenje TEXT,
				odsek TEXT,
				op TEXT,
				FOREIGN KEY (id_lokalitet) REFERENCES lokalitet(id) ON DELETE CASCADE
			);

			CREATE TABLE stablo (
				id INTEGER PRIMARY KEY AUTOINCREMENT,
				id_blizi_lokalitet INTEGER,
				broj TEXT,
				visina TEXT,
				pravac TEXT,
				FOREIGN KEY (id_blizi_lokalitet) REFERENCES blizi_lokalitet(id) ON DELETE CASCADE
			);

			CREATE TABLE stablo_godina (
				id INTEGER PRIMARY KEY AUTOINCREMENT,
				id_stablo INTEGER,
				godina TEXT,
				vrednost TEXT,
				FOREIGN KEY (id_stablo) REFERENCES stablo(id) ON DELETE CASCADE
			);

			CREATE TABLE stablo_komentari (
				id INTEGER PRIMARY KEY AUTOINCREMENT,
				id_stablo INTEGER,
				Comment TEXT,
				SiteId TEXT,
				Location TEXT,
				EarthCoord TEXT,
				Elev TEXT,
				State TEXT,
				SpeciesCode TEXT,
				SpeciesName TEXT,
				DistanceToPith TEXT,
				Project TEXT,
				Personal_ID TEXT,
				DateOfSampling TEXT,
				Name TEXT,
				YearsToPith TEXT,
				Written TEXT,
				DBH TEXT,
				CooRecorder TEXT,
				LicencedTo TEXT,
				WaldKante TEXT,
				Sapwood TEXT,
				Interpretation TEXT,
				LocationCharacteristics TEXT,
				SoilType TEXT,
				DeTrend TEXT,
				Radius TEXT,
				CalcRadius TEXT,
				PithCoordinates TEXT,
				FOREIGN KEY (id_stablo) REFERENCES stablo(id) ON DELETE CASCADE
			);
        )"},
    {"Directory_insert_lokalitet", R"(
            INSERT INTO lokalitet (godina, ime)
            VALUES (?, ?)
        )"},
    {"Directory_insert_blizi_lokalitet", R"(
            INSERT INTO blizi_lokalitet (id_lokalitet, gazdinska_jedinica, odeljenje, odsek, op)
            VALUES (?, ?, ?, ?, ?)
        )"},
    {"XLS_insert_stablo", R"(
            INSERT INTO stablo (id_blizi_lokalitet, broj, visina, pravac)
            VALUES (?, ?, ?, ?)
        )"},
    {"XLS_insert_stablo_godina", R"(
            INSERT INTO stablo_godina (id_stablo, godina, vrednost)
            VALUES (?, ?, ?)
        )"},
    {
        "GET_BLIZI_LOKALITET_ID", R"(
            SELECT stablo.id
            FROM lokalitet
            JOIN blizi_lokalitet ON lokalitet.id = blizi_lokalitet.id
            JOIN stablo ON blizi_lokalitet.id
            WHERE lokalitet.godina = ?
            AND lokalitet.ime = ?
            AND blizi_lokalitet.gazdinska_jedinica = ?
            AND blizi_lokalitet.odeljenje = ?
            AND blizi_lokalitet.odsek = ?
            AND blizi_lokalitet.op = ?
        )"
        },
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
            AND blizi_lokalitet.op = ?
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