#ifndef ANOVA_CPP
#define ANOVA_CPP

#include "combined.h"

using namespace std;

void read_groups(vector<vector<double>>& groups,string filename) {
    ifstream input;
    input.open(filename);
    
    if (!input.is_open()) {
        cout << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(input, line)) {
        vector<double> row;
        stringstream ss(line); 
        string value;
        while (ss >> value) {
            row.push_back(stod(value));
        }

        if (!row.empty()) {
            groups.push_back(row);
            row.clear();
        }
    }

    input.close();
}
void anova_test(vector<vector<double>> &groups){
    double overall_mean = 0;
    double sum = 0;
    int m = groups.size();
    int n = groups[0].size();
    int mn = m * n;
    for(auto row : groups){
        for(auto val : row){
            sum += val;
        }
    }
    overall_mean = sum / mn;
    vector<double> group_specific_mean;

    for(int i = 0; i <  n; ++i){
        sum = 0.0;
        for(int j = 0; j < m; ++j){
            sum += groups[j][i];
        }
        group_specific_mean.push_back(sum/m);
    }
    double SSb;
    double between_grp_ss = 0.0;
    for(auto mu_hat : group_specific_mean){
        between_grp_ss += pow((mu_hat - overall_mean),2);
    }
    SSb = n * between_grp_ss;

    double SSw;
    double SSt = 0.0;

    for(auto grp : groups){
        for(auto val : grp){
            SSt += pow((val - overall_mean),2);
        }
    }
    SSw = SSt - SSb;

    double MSb;
    double MSw;
    MSb = SSb / (m - 1);
    MSw = SSw / (mn - m);

    double f_statistic = MSb / MSw;
    double tabulated_f = f_valueFromTable((m-1) , (mn - m));

    cout << "\nANOVA Table\n";
    cout << setw(15) << left << "Source" 
         << setw(10) << "df" 
         << setw(15) << "SS" 
         << setw(15) << "MS" 
         << setw(15) << "F Statistic" << endl;
    cout << string(65, '-') << endl;

    cout << setw(15) << left << "Between" 
         << setw(10) << m - 1 
         << setw(15) << fixed << setprecision(2) << SSb 
         << setw(15) << MSb 
         << setw(15) << f_statistic << endl;

    cout << setw(15) << left << "Within" 
         << setw(10) << mn - m 
         << setw(15) << fixed << setprecision(2) << SSw 
         << setw(15) << MSw 
         << setw(15) << "-" << endl;

    cout << "Critical value: " << tabulated_f << endl;
    if(f_statistic < tabulated_f){
        cout << "We fail to reject the null hypothesis that all the groups have the mean!" << endl << endl;
    }else{
        cout << "We can reject the null hypothesis that all the groups have the mean!" << endl << endl;
    }
}
#endif