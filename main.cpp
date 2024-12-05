#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "mean.h"
using namespace std;

void frequency_table(vector<float> fvec, ofstream &out)
{
    vector<int> freq;
    vector<float> data;

    for (int i = 0; i < fvec.size(); i++)
    {
        int count = 1;
        if (fvec[i] != -99999)
        {
            data.push_back(fvec[i]);
        }
        else
            continue;

        for (int j = i + 1; j < fvec.size(); j++)
        {
            if (fvec[i] == fvec[j] && fvec[j] != -99999)
            {
                count++;
                fvec[j] = -99999;
            }
        }
        freq.push_back(count);
    }

    if (out.is_open())
    {
        out << "|    data" << "\t|    " << "frequency   |" << endl;
        out << "|=====" << "==========|" << "================|" << endl;
        for (int i = 0; i < freq.size(); i++)
        {
            out << "|  " << data[i] << "\t        |\t" << freq[i] << endl;
            out << "|---------------|-" << endl;
        }
    }
    else
        cout << "file is not opened" << endl;
}
float calculate_median(vector<float> fvec)
{
    sort(fvec.begin(), fvec.end());
    float median;

    if (fvec.size() % 2)
        median = fvec[fvec.size() / 2];
    else
    {
        int sum;
        sum = fvec[fvec.size() / 2] + fvec[(fvec.size() / 2) + 1];
        median = sum / 2;
    }

    return median;
}
int main()
{
    ifstream in;
    in.open("input.txt");

    string str;
    vector<float> fvec;
    while (!in.eof())
    {
        in >> str;
        float fnum = stof(str);
        fvec.push_back(fnum);
    }
    in.close();

    ofstream out;
    out.open("output.txt");

    frequency_table(fvec, out);

    float mean;
    mean = calculate_mean(fvec);
    out << "mean is : " << mean << endl;

    float median;
    median = calculate_median(fvec);
    out << "median is : " << median << endl;

    return 0;
}