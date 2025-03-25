#ifndef DATA_CLEAN_H
#define DATA_CLEAN_H

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

vector<string> fillString(vector<string> &vec);

vector<string> dropDuplicates( vector<string> col);

string handleNullValues(vector<string>& data);

#endif
