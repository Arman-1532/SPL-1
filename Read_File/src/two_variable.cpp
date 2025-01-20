#ifndef TWO_VARIABLE_CPP
#define TWO_VARIABLE_CPP

#include<fstream>
#include<sstream>
#include "../include/two_variable.h"

void readTwoVariableFromTxtFile(vector<double> &x, vector<double> &y){
    fstream in;
    in.open("input_TwoVariable.txt");
    if(!in){
        cout << "unable to open file: input_TwoVariable.txt" << endl;
        return;
    }

    double num;
    while(!in.eof()){
        in >> num;
        x.push_back(num);
        in >> num;
        y.push_back(num);
    }
    in.close();
}
void readTwoVariableFromCsvFile(vector<double> &x,vector<double> &y){
    fstream in;
    in.open("input_twoVariable.csv");
    if(!in){
        cout << "unable to open file: input_twoVariable.txt" << endl;
        return;
    }
    string str;
    while(!in.eof()){
        getline(in,str);
        stringstream ss(str);
        string value;
        int i = 0;
        while(getline(ss, value, ',')){
            double num = stod(value);
            if(i % 2 == 0){
                x.push_back(num);
            }
            else{
                y.push_back(num);
            }
            i++;
        }
    }
    in.close();
}

#endif