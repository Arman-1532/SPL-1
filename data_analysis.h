#ifndef DATA_ANALYSIS_H
#define DATA_ANALYSIS_H

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

double calculateMean(vector<string> &x);

int partition(vector<double> &vec, int low, int high);

void quickSort(vector<double> &vec, int low, int high);

double calculateMedian(vector<string> &x);

vector<double> calculateMode(vector<string> &x);

double calculateSum(vector<string> &x);

double calculateVariance(vector<string> &x);

double calculateStandardDeviation(vector<string> &x);

double calculateCoefficientOfVariation(vector<string> &x);

bool isInteger(double position);

double calculatePercentile(vector<string> &x, double percentile);

vector<double> calculateDeciles(vector<string> &x);

vector<double> calculateQuartiles(vector<string> &x);

vector<double> detectOutliers(vector<string> &x);

int maxOf(int num1, int num2);

#endif