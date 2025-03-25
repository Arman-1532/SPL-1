#ifndef DATA_MANIPULATION_CPP
#define DATA_MANIPULATION_CPP

#include "combined.h"

using namespace std;

vector<string> getColumn(vector<vector<string>> csvData, vector<string> headers,string columnName)
{
    int colIndex;
    // auto it = find(headers.begin(), headers.end(), columnName);
    int flag = 0;

    for (colIndex = 0; colIndex < headers.size(); colIndex++)
    {
        if (columnName == headers[colIndex])
        {
            flag = 1;
            break;
        }
    }
    vector<string> column;
    if (flag == 1)
    {
        for (int i = 0; i < csvData.size(); i++)
        {
            column.push_back(csvData[i][colIndex]);
        }
    }
    else
    {
        cout << "invalid name of column" << endl;
    }
    return column;
}
vector<string> filterColumn(vector<vector<string>> csvData, vector<string> headers,string &columnName, string &condition, string val) //
{
    double value = stod(val);
    auto column = getColumn(csvData,headers,columnName);
    vector<string> filteredColumn;

    for (int i = 0; i < column.size(); ++i)
    {
        try
        {
            double cellValue = stod(column[i]);
            if ((condition == ">" && cellValue > value) ||
                (condition == "<" && cellValue < value) ||
                (condition == ">=" && cellValue >= value) ||
                (condition == "<=" && cellValue <= value) ||
                (condition == "==" && cellValue == value))
            {
                filteredColumn.push_back(column[i]);
            }
        }
        catch (...)
        {
            continue; // Skip non-numeric values
        }
    }

    return filteredColumn;
}
void resizedTable(vector<vector<string>> csvData, vector<string> headers,string shape){ //
    int row = shape[0] - '0';
    int column = shape[2] - '0';
    for(int i = 0; i< column; i++){
        cout << headers[i] << '\t';
    }
    cout << endl;

    for(int i = 0; i<row; i++){
        for(int j = 0; j<column; j++){
            cout << csvData[i][j] << '\t';
        }
        cout << endl;
    }
}

#endif