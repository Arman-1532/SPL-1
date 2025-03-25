#ifndef DATA_ANALYSIS_CPP
#define DATA_ANALYSIS_CPP

#include "combined.h"

using namespace std;

double calculateMean(vector<string> &x)
{
    vector<double> vec;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == "NULL")
        {
            x[i] = handleNullValues(x);
        }
        vec.push_back(stod(x[i]));
    }
    double total = 0;
    int sizeOfSample = vec.size();
    double mean;
    for (int i = 0; i < sizeOfSample; i++)
    {
        total += vec[i];
    }

    mean = total / sizeOfSample;

    return mean;
}
int partition(vector<double> &vec, int low, int high)
{
    int pivot = vec[high];
    int i = low - 1;

    for (int j = low; j < high; ++j)
    {
        if (vec[j] <= pivot)
        {
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
void quickSort(vector<double> &vec, int low, int high)
{
    if (low < high)
    {
        int pi = partition(vec, low, high);

        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}
double calculateMedian(vector<string> &x)
{
    vector<double> vec;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == "NULL")
        {
            x[i] = handleNullValues(x);
        }
        vec.push_back(stod(x[i]));
    }
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
int maxOf(int num1, int num2){
    if(num1 > num2){
        return num1;
    }
    
    return num2;
}
vector<double> calculateMode(vector<string> &x)
{
    vector<double> vec;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == "NULL")
        {
            x[i] = handleNullValues(x);
        }
        vec.push_back(stod(x[i]));
    }
    vector<int> freq;
    vector<float> data;
    vector<double> mode;
    int sizeOfSample = vec.size();

    for (int i = 0; i < sizeOfSample; i++)
    {
        int count = 1;
        if (vec[i] != -99999)
        {
            data.push_back(vec[i]);
        }
        else
            continue;

        for (int j = i + 1; j < sizeOfSample; j++)
        {
            if (vec[i] == vec[j] && vec[j] != -99999)
            {
                count++;
                vec[j] = -99999;
            }
        }
        freq.push_back(count);
    }

    int max = 0;
    for (int i = 0; i < freq.size(); i++)
    {
        if (freq[i] > max)
        {
            max = freq[i];
        }
    }
    for (int i = 0; i < freq.size(); i++)
    {
        if (max == freq[i])
        {
            mode.push_back(data[i]);
        }
    }

    return mode;
}
double calculateSum(vector<string> &x)
{
    vector<double> vec;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == "NULL")
        {
            x[i] = handleNullValues(x);
        }
        vec.push_back(stod(x[i]));
    }

    double sum = 0.0;
    for (auto value : vec)
    {
        sum += value;
    }
    return sum;
}
double calculateVariance(vector<string> &x){
    vector<double> vec;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == "NULL")
        {
            x[i] = handleNullValues(x);
        }
        vec.push_back(stod(x[i]));
    }
    int sizeOfSample = vec.size();
    double variance;
    double total = 0;

    for(int i = 0; i<sizeOfSample; i++)
    {
        total += vec[i] * vec[i];
    }
    double mean = calculateMean(x);

    double numerator = total - (sizeOfSample * mean * mean);
    double denominator = sizeOfSample - 1;
    variance = numerator / denominator;

    return variance;
}
double calculateStandardDeviation(vector<string> &x){
    double variance = calculateVariance(x);
    double standardDeviation = sqrt(variance);

    return standardDeviation;
}
double calculateCoefficientOfVariation(vector<string> &x){

    double standardDeviation = calculateStandardDeviation(x);
    double mean = calculateMean(x);
    double coefficientOfVariation = ( standardDeviation / mean ) * 100.0;
    return coefficientOfVariation;
}
bool isInteger(double position){
    if(position - floor(position) == 0.0){
        return true;
    }

    return false;
}
double calculatePercentile(vector<string> &x, double percentile){
    vector<double> vec;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == "NULL")
        {
            x[i] = handleNullValues(x);
        }
        vec.push_back(stod(x[i]));
    }
    int low = 0;
    int high = vec.size() - 1;
    quickSort(vec, low, high);

    double percentileValue;
    int sizeOfSample = x.size();
    if(percentile == 0){
        percentileValue = -1;
    }
    else if(percentile == 100)
    {
        percentileValue = *(vec.end() - 1);
    }
    else{
        double position = sizeOfSample * (percentile / 100.0);
        if(isInteger(position)){
            percentileValue = vec[position - 1];
        }
        else if(position < 1){
            percentileValue = vec[0] / 2;
        }
        else
        {
            int floorValue = floor(position);
            int ceiling = ceil(position);
            percentileValue = (vec[floorValue - 1] + vec[ceiling - 1]) / 2;
        }
    }

    return percentileValue;
}
vector<double> calculateDeciles(vector<string> &x){
    vector<double> deciles;
    double percentile = 10;

    while(percentile <= 90){
        deciles.push_back(calculatePercentile(x, percentile));
        percentile += 10;
    }

    return deciles;
}
vector<double> calculateQuartiles(vector<string> &x){
    vector<double> quartiles;
    double quartile = 25;

    while(quartile <= 75){
        quartiles.push_back(calculatePercentile(x, quartile));
        quartile += 25.0;
    }

    return quartiles;
}
vector<double> detectOutliers(vector<string> &x){  
    vector<double> outliersUsingIQR;
    vector<double> quartiles = calculateQuartiles(x);
    
    double q1 = *(quartiles.begin());
    double q3 = *(quartiles.end() - 1);

    double IQR = q3 - q1;
    double lowerBound = q1 - 1.5 * IQR;
    double upperBound = q3 + 1.5 * IQR;
    
    vector<double> vec;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == "NULL")
        {
            x[i] = handleNullValues(x);
        }
        vec.push_back(stod(x[i]));
    }
    for (double value : vec) {
        if (value < lowerBound || value > upperBound) {
            outliersUsingIQR.push_back(value);
        }
    }
    
    return outliersUsingIQR;
}
#endif