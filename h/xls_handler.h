#pragma once
#ifndef XLS_HANDLER_H
#define XLS_HANDLER_H

#include <string>
#include <vector>
#include <xls.h>

struct results{
    std::vector<std::vector<std::string>> data;

};
//probaj da deklarises kao static
class xls_handler{
    public:
    std::string get_row(int row_number);
    std::string get_column(int column_number);
    void set_workbook(std::string path);
    void get_data();

    private:
    xls::xlsWorkBook* m_workbook;
    xls::xlsWorkSheet* m_worksheet;
    results m_results;
};
//Rezultat je po godini


#endif