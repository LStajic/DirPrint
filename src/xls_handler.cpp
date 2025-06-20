#include "../h/xls_handler.h"
#include "logger/logger_instance.h"

void xls_handler::set_workbook(std::string path) {
  m_workbook = xls::xls_open(path.c_str(), "UTF-8");
}

void xls_handler::convert_to_map(std::vector<std::vector<std::string>> data) {
  for (int i = 1; i < data.size(); i++) {
    for (int j = 1; j < data[i].size(); j++) {
      if (data[i][j] == "0") {
        continue;
      }
      // //if a pair exists, we write another year/value pair
      // if (export_data.count(data[0][j])){
      //     export_data.find(data[0][j])->second.insert(data[i][0],data[i][j]);
      // }
      // //if it doeznt exist, we create one with the first pair
      // else{
      //     export_data.insert({data[0][j], {data[i][0],data[i][j]}});
      // }
      m_results[data[0][j]][data[i][0]] = data[i][j];
    }
  }
  logger.log(std::string("conversion to map performed\n"), log_level::INFO);

}

// WARNING: This functiion closes the workbook on finish
void xls_handler::get_xls_data() {
  m_worksheet = xls::xls_getWorkSheet(m_workbook, 0);
  xls::xls_parseWorkSheet(m_worksheet);
  int row_count = m_worksheet->rows.lastrow + 1;
  int col_count = m_worksheet->rows.lastcol + 1;
  std::vector<std::vector<std::string>> matrix(
      row_count, std::vector<std::string>(col_count, "0"));
  logger.log(std::string("data parsing performed\n"), log_level::INFO);

  for (xls::DWORD row = 0; row <= m_worksheet->rows.lastrow; ++row) {
    for (xls::DWORD col = 0; col <= m_worksheet->rows.lastcol; ++col) {

      xls::xlsCell *cell = xls::xls_cell(m_worksheet, row, col);
      if (!cell)
        continue;
      if (cell->id == XLS_RECORD_BLANK) {
        matrix[row][col] = "0";
      }
      // Handle string cells
      else if (cell->id == XLS_RECORD_LABELSST) {
        if (!cell->str) {
          // NULL string pointer
          matrix[row][col] = "0";
        } else if (cell->str[0] == '\0') {
          // Empty string
          matrix[row][col] = "0";
        } else {
          // Valid string
          matrix[row][col] = cell->str;
        }
      }
      // Handle other cell types (numbers, formulas, etc.)
      else if (cell->str) {
        matrix[row][col] = cell->str;
      } else {
        // Fallback for other cases
        matrix[row][col] = "0";
      }
    }
  }
  logger.log(std::string("finished grabbing cell data\n"), log_level::INFO);
  convert_to_map(matrix);
  xls::xls_close_WS(m_worksheet);
  xls::xls_close_WB(m_workbook);
}
