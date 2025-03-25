#ifndef DATA_EXPLORE_CPP
#define DATA_EXPLORE_CPP

#include "combined.h"

using namespace std;

// bool loadCSV(string &filename,vector<vector<string>> csvData,vector<string> headers) 
// {
//     ifstream file;
//     file.open("../../"+filename);
//     if (!file)
//     {
//         cout << "unable to open file : " << filename << endl;
//         return false;
//     }

//     string line;
//     bool isHeader = true;

//     while (!file.eof())
//     {
//         getline(file, line);
//         stringstream ss(line);
//         vector<string> row;
//         string value;

//         while (getline(ss, value, ','))
//         {
//             row.push_back(value);
//         }

//         if (isHeader)
//         {
//             headers = row;
//             isHeader = false;
//         }
//         else
//         {
//             csvData.push_back(row);
//         }
//     }
//     file.close();
//     return true;
// }
// vector<string> getColumn(string columnName,vector<vector<string>> csvData,vector<string> headers) 
// {
//     int colIndex;
//     int flag = 0;

//     for (colIndex = 0; colIndex < headers.size(); colIndex++)
//     {
//         if (columnName == headers[colIndex])
//         {
//             flag = 1;
//             break;
//         }
//     }
//     vector<string> column;
//     if (flag == 1)
//     {
//         for (int i = 0; i < csvData.size(); i++)
//         {
//             column.push_back(csvData[i][colIndex]);
//         }
//     }
//     else
//     {
//         cout << "invalid name of column" << endl;
//     }
//     return column;
// }
// vector<string> splitString(string str) 
// {
//     vector<string> tokens;
//     string str1, str2;
//     int size = str.size();
//     int i;

//     for (i = 0; i < size; i++)
//     {
//         if (str[i] != '.')
//         {
//             str1.push_back(str[i]);
//         }
//         else
//         {
//             break;
//         }
//     }
//     for (i++; i < size; i++)
//     {
//         str2.push_back(str[i]);
//     }
//     if(str.find(".") == -1){
//         str2 = "empty";
//     }
//     tokens.push_back(str1);
//     tokens.push_back(str2);

//     return tokens;
// }
// vector<string> specifyOperation(string &operation)
// {
//     string metric;
//     string num;
//     vector<string> specifyFunction;
//     int size = operation.size();
//     for (int i = 0; i < size; i++)
//     {
//         if (operation[i] == '(')
//         {
//             if (operation[i + 1] == ')')
//             {
//                 break;
//             }
//             else
//             {
//                 for (i++; i < size; i++)
//                 {
//                     if (operation[i] == ')')
//                     {
//                         break;
//                     }
//                     num.push_back(operation[i]);
//                 }
//             }
//         }
//         else
//         {
//             metric.push_back(operation[i]);
//         }
//     }

//     specifyFunction.push_back(metric);
//     specifyFunction.push_back(num);

//     return specifyFunction;
// }
string findHead(vector<string> vec){ 
    string head;
    auto it = vec.begin();
    
    head = *it;
    return head;
}
string findTail(vector<string> vec){ 
    string tail;
    auto it = vec.end() - 1;
    
    tail = *it;
    return tail;
}
double getMax(vector<string> &x){ 
    vector<double> vec;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == "NULL")
        {
            x[i] = handleNullValues(x);
        }
        vec.push_back(stod(x[i]));
    }

    double max = DBL_MIN;
    for(double value : vec){
        if(value > max){
            max = value;
        }
    }
    
    return max;
}
double getMin(vector<string> &x){ 
    vector<double> vec;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == "NULL")
        {
            x[i] = handleNullValues(x);
        }
        vec.push_back(stod(x[i]));
    }

    double min = DBL_MAX;
    for(double value : vec){
        if(value < min){
            min = value;
        }
    }

    return min;
}
string calculateShape(vector< vector< string> > csvData){ 
    string shape;
    int row = csvData.size();
    int column = csvData[0].size();
    string str1 = to_string(row);
    string str2 = to_string(column);
    shape = str1 + " * " + str2;

    return shape; 
}

#endif