#ifndef SIMPLE_LINEAR_REGRESSION_H
#define SIMPLE_LINEAR_REGRESSION_H

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

void readFileForRegression(string filename,string &dep_var, string &indep_var, vector<double> &x, vector<double> &y);


void simple_linear_regression(string indep_variable, string dep_variable, vector<double> &x, vector<double> &y);

#endif