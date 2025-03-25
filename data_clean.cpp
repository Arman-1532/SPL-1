#ifndef DATA_CLEAN_CPP
#define DATA_CLEAN_CPP

#include "combined.h"

using namespace std;

vector<string> fillString(vector<string> &vec) {
    vector<string> filledVec = vec; 
  
    for (int i = 0; i<vec.size(); i++) {
        if (vec[i] == "NULL") {
            filledVec[i] = handleNullValues(vec);
        }
    }

    return filledVec;
}
vector<string> dropDuplicates(vector<string> col){
    for(int i = 0; i<col.size(); i++){
        for(int j = i+1; j<col.size(); j++){
            if(col[i] == col[j]){
                col.erase(col.begin() + j);
            }
        }
    }

    return col;
}
string handleNullValues(vector<string>& data) {
    vector<double> validNumbers;
    for (string& str : data) {
        if (str != "NULL") {
            double value = stod(str); 
            validNumbers.push_back(value);
        }
    }

    string imputedValueStr;
    bool hasOutliers = false;

    if (validNumbers.size() > 1) { 
        sort(validNumbers.begin(), validNumbers.end());
        int n = validNumbers.size();

        double Q1 = validNumbers[n / 4]; 
        double Q3 = validNumbers[(3 * n) / 4]; 
        double IQR = Q3 - Q1;
        double lowerBound = Q1 - 1.5 * IQR;
        double upperBound = Q3 + 1.5 * IQR;

        for (double val : validNumbers) {
            if (val < lowerBound || val > upperBound) {
                hasOutliers = true;
                break;
            }
        }
    }

    if (hasOutliers) { 
        sort(validNumbers.begin(), validNumbers.end());
        int n = validNumbers.size();
        double median;
        if (n % 2 == 0) {
            median = (validNumbers[n/2 - 1] + validNumbers[n/2]) / 2.0;
        } else {
            median = validNumbers[n/2];
        }
        imputedValueStr = to_string(median);
    } 
    else { // Use mean if no outliers
        double sum = 0.0;
        for (double val : validNumbers) {
            sum += val;
        }
        double mean = sum / validNumbers.size();
        imputedValueStr = to_string(mean);
    }

    return imputedValueStr;
}
#endif