#pragma once
#ifndef XLS_HANDLER_H
#define XLS_HANDLER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <xls.h>


//probaj da deklarises kao static
class xls_handler{
    public:

    void set_workbook(std::string path);
    void get_xls_data();
    void clear_results(){m_results.clear();};
    const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& get_results() const {return m_results;};


    private:
    void convert_to_map(std::vector<std::vector<std::string>> data);
    xls::xlsWorkBook* m_workbook;
    xls::xlsWorkSheet* m_worksheet;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_results;
};

#endif