#ifndef ONE_VARIABLE_CPP
#define ONE_VARIABLE_CPP

#include<fstream>
#include<sstream>
#include "../include/one_variable.h"

void readOneVariableFromTxtFile(vector<double> &x,string filepath){
    fstream in;
    in.open("input_oneVariable.txt");
    if(!in){
        cout << "unable to open file: input_oneVariable.txt" << endl;
        return;
    }

    double num;
    while(!in.eof()){
        in >> num;
        x.push_back(num);
    }
    in.close();
}
void readOneVariableFromCsvFile(vector<double> &x,string filepath){
    fstream in;
    in.open("input_oneVariable.csv");
    if(!in){
        cout << "unable to open file: input_oneVariable.txt" << endl;
        return;
    }
    string str;
    while(!in.eof()){
        getline(in,str);
        stringstream ss(str);
        string value;
        while(getline(ss, value, ',')){
            double num = stod(value);
            x.push_back(num);
        }
    }
    in.close();
}

#endif