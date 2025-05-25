#include "../h/xls_handler.h"

void xls_handler::set_workbook(std::string path){
    m_workbook = xls::xls_open(path.c_str(), "UTF-8");
}

void xls_handler::get_data(){
    m_worksheet = xls::xls_getWorkSheet(m_workbook, 0);
    xls::xls_parseWorkSheet(m_worksheet);

    for (xls::DWORD row = 0; row <= m_worksheet->rows.lastrow; ++row) {
        for (xls::DWORD col = 0; col <= m_worksheet->rows.lastcol; ++col) {
            xls::xlsCell *cell = xls::xls_cell(m_worksheet, row, col);
            if(cell == nullptr){
                
            }
            std::string value = cell->str;

        }
    }
}