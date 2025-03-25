#ifndef DATA_EXPLORE_H
#define DATA_EXPLORE_H

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

bool loadCSV(string &filename,vector<vector<string>> csvData,vector<string> headers);


vector<string> getColumn(string columnName,vector<vector<string>> csvData,vector<string> headers);


vector<string> splitString(string str);


vector<string> specifyOperation(string &operation);


string findHead(vector<string> vec);


string findTail(vector<string> vec);


double getMax(vector<string> &x);


double getMin(vector<string> &x);


string calculateShape(vector< vector< string> > csvData);
#endif