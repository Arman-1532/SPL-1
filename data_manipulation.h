#ifndef DATA_MANIPULATION_H
#define DATA_MANIPULATION_H

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <cfloat>
#include <iomanip>

using namespace std;

vector<string> getColumn(vector<vector<string>> csvData, vector<string> headers,string columnName);


vector<string> filterColumn(vector<vector<string>> csvData, vector<string> headers,string &columnName, string &condition, string val);


void resizedTable(vector<vector<string>> csvData, vector<string> headers,string shape);

#endif