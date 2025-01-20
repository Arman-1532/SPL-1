#ifndef DATA_OVERVIEW_CPP
#define DATA_OVERVIEW_CPP
#include<iostream>
#include<vector>
#include<cfloat>
#include "data_overview.h"

using namespace std;

double calculateMean(vector<double> &vec){
    double total = 0;
    int sizeOfSample = vec.size();
    double mean;
    for(int i = 0; i< sizeOfSample; i++){
        total += vec[i];
    }

    mean = total / sizeOfSample;

    return mean;
}
// partition will be used in quicksort
int partition(vector<double>& vec, int low, int high) {
    int pivot = vec[high]; 
    int i = low - 1;       

    for (int j = low; j < high; ++j) 
    {
        if (vec[j] <= pivot) {
            ++i;
            
            int temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
        }
    }

    int temp = vec[i + 1];
    vec[i + 1] = vec[high];
    vec[high] = temp;

    return i + 1; 
}

void quickSort(vector<double>& vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high);

        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

double calculateMedian(vector<double> &vec){
    double median;
    int sizeOfSample = vec.size();
    int low = 0, high = sizeOfSample - 1;

    quickSort(vec, low, high);

    if (sizeOfSample % 2)
        median = vec[vec.size() / 2];
    else
    {
        int sum;
        sum = vec[sizeOfSample / 2] + vec[(sizeOfSample / 2) + 1];
        median = sum / 2;
    }

    return median;
}
vector<double> calculateMode(vector<double> vec){
    vector<int> freq;
    vector<float> data;
    vector<double> mode;
    int sizeOfSample = vec.size();

    for (int i = 0; i < sizeOfSample; i++){
        int count = 1;
        if (vec[i] != -99999)
        {
            data.push_back(vec[i]);
        }
        else
            continue;

        for (int j = i + 1; j < sizeOfSample; j++){
            if (vec[i] == vec[j] && vec[j] != -99999)
            {
                count++;
                vec[j] = -99999;
            }
        }
        freq.push_back(count);
    }

    int max = 0;
    for(int i = 0; i<freq.size(); i++){
        if(freq[i] > max){
            max = freq[i];
        }
    }
    for(int i = 0; i<freq.size(); i++){
        if(max == freq[i])
        {
            mode.push_back(data[i]);
        }
    }

    return mode;
}
double calculateVariance(vector<double> &vec){
    int sizeOfSample = vec.size();
    double variance;
    double total = 0;

    for(int i = 0; i<sizeOfSample; i++)
    {
        total += vec[i] * vec[i];
    }
    double mean = calculateMean(vec);

    double numerator = total - (sizeOfSample * mean * mean);
    double denominator = sizeOfSample - 1;
    variance = numerator / denominator;

    return variance;
}
double calculateStandardDeviation(vector<double> &vec){
    double variance = calculateVariance(vec);
    double standardDeviation = sqrt(variance);

    return standardDeviation;
}
double getMax(vector<double> &vec){
    double max = DBL_MIN;

    for(double value : vec){
        if(value > max){
            max = value;
        }
    }
    
    return max;
}
double getMin(vector<double> &vec){
    double min = DBL_MAX;

    for(double value : vec){
        if(value < min){
            min = value;
        }
    }

    return min;
}
// ratio of std deviation and mean
double calculateCoefficientOfVariation(vector<double> &vec){
    double standardDeviation = calculateStandardDeviation(vec);
    double mean = calculateMean(vec);
    double coefficientOfVariation = ( standardDeviation / mean ) * 100.0;
    return coefficientOfVariation;
}
bool isInteger(double position){
    if(position - floor(position) == 0.0){
        return true;
    }

    return false;
}
double calculatePercentile(vector<double> &vec, double percentile){
    int low = 0;
    int high = vec.size() - 1;
    quickSort(vec, low, high);

    double percentileValue;
    int sizeOfSample = vec.size();
    if(percentile == 0){
        percentileValue = *(vec.begin());
    }
    else if(percentile == 100)
    {
        percentileValue = *(vec.end() - 1);
    }
    else{
        double position = sizeOfSample * (percentile / 100.0);
        if(isInteger(position)){
            percentileValue = vec[position];
        }
        else
        {
            percentileValue = (vec[position] + vec[position + 1]) / 2;
        }
    }

    return percentileValue;
}
vector<double> calculateDeciles(vector<double> &vec){
    vector<double> deciles;
    double percentile = 10;

    while(percentile <= 90){
        deciles.push_back(calculatePercentile(vec, percentile));
        percentile += 10.0;
    }

    return deciles;
}
vector<double> calculateQuartiles(vector<double> &vec){
    vector<double> quartiles;
    quartiles.resize(3);
    double quartile = 25;

    while(quartile <= 75){
        quartiles.push_back(calculatePercentile(vec, quartile));
        quartile += 25.0;
    }

    return quartiles;
}
double range(vector<double> &vec){
    int low = 0;
    int high = vec.size() - 1;
    quickSort(vec, low , high);
    double range = *(vec.end() - 1) - *(vec.begin());

    return range;
}
#endif