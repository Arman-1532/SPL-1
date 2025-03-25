#ifndef HYPOTHESIS_TESTING_H
#define HYPOTHESIS_TESTING_H

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

void readOneVariableDataSet(vector<double> &x);


double calc_Mean(vector<double> x);


vector<string> split(const string &line, char delimiter);


double z_valueFromTable(double value);


void oneSided_Ztest(vector<double> x, double null_hypothesis, double sigma, char sign);


void twoSided_Ztest(vector<double> &x, double null_hypothesis, double sigma);


double calc_deviation(vector<double> x);


double t_valueFromTable(int dof, double alpha);


void oneSided_Ttest(vector<double> &x, double null_hypothesis, char sign);


void twoSided_Ttest(vector<double> &x, double null_hypothesis);


double chi_value_from_table(double dof,double alpha);


void chi_Square_test(vector<double> &x,double null_hypothesis);


void readTwoVariableDataSet(vector<double> &x , vector<double> &y);


double calc_var(vector<double> vec);


double f_valueFromTable(int df1, int df2);


void f_test(vector<double> &x, vector<double> &y);

#endif