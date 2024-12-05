#include<iostream>
#include<vector>
using namespace std;

float calculate_mean(vector<float> fvec)
{
    float sum = 0;

    for (int i = 0; i < fvec.size(); i++)
    {
        sum += fvec[i];
    }

    float mean;
    mean = sum / fvec.size();

    return mean;
}