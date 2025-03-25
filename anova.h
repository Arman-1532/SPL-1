#ifndef ANOVA_H
#define ANOVA_H

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

void read_groups(vector<vector<double>>& groups,string filename);


void anova_test(vector<vector<double>> &groups);

#endif