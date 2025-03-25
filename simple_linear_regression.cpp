#ifndef SIMPLE_LINEAR_REGRESSION_CPP
#define SIMPLE_LINEAR_REGRESSION_CPP

#include "combined.h"

using namespace std;

void readFileForRegression(string filename,string &dep_var, string &indep_var, vector<double> &x, vector<double> &y){
    ifstream in;
    in.open(filename);

    if(!in){
        cout << "unable to open file - " << filename << endl;
    }

    string str;
    in >> str;
    indep_var = str;
    in >> str;
    dep_var = str;

    while(!in.eof()){
        double value;
        in >> value;
        x.push_back(value);
        in >> value;
        y.push_back(value);
    }
}
void drawScatterPlot(const vector<double>& x, const vector<double>& y) {
    const int height = 20; 
    const int width = 40; 
    char plot[height][width] = {0}; 

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            plot[i][j] = ' ';
        }
    }

    double xMin = *min_element(x.begin(), x.end());
    double xMax = *max_element(x.begin(), x.end());
    double yMin = *min_element(y.begin(), y.end());
    double yMax = *max_element(y.begin(), y.end());

    for (size_t i = 0; i < x.size(); i++) {
        int xPos = static_cast<int>((x[i] - xMin) / (xMax - xMin) * (width - 1));
        int yPos = height - 1 - static_cast<int>((y[i] - yMin) / (yMax - yMin) * (height - 1));
        if (xPos >= 0 && xPos < width && yPos >= 0 && yPos < height) {
            plot[yPos][xPos] = '*';
        }
    }

    // int xAxisPos = height - 1 - static_cast<int>((0 - yMin) / (yMax - yMin) * (height - 1));
    // if (xAxisPos >= 0 && xAxisPos < height) {
    //     for (int j = 0; j < width; j++) {
    //         if (plot[xAxisPos][j] == ' ') {  // Only draw '-' if no point is there
    //             plot[xAxisPos][j] = '-';
    //         }
    //     }
    // }

    cout << "\nScatter Plot (Independent vs Dependent Variable)\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << plot[i][j];
        }
        cout << "\n";
    }
    cout << string( 50 , '-')  << endl;
}
void simple_linear_regression(string indep_variable, string dep_variable, vector<double> &x, vector<double> &y){
    drawScatterPlot(x,y);
    double beta0_hat;
    double beta1_hat;
    vector<double> estimates;
    double x_bar = calc_Mean(x);
    double y_bar = calc_Mean(y);
    int n = x.size();
    double sum_of_x_sq = 0.0;
    double sum_of_xy = 0.0;

    for(int i = 0; i < n; ++i){
        sum_of_xy += (x[i] * y[i]);
    }

    double Sxy;
    double Sxx;

    Sxy = sum_of_xy - (n * x_bar * y_bar);

    for(int i = 0; i < n; ++i){
        sum_of_x_sq += (x[i] * x[i]);
    }

    Sxx = sum_of_x_sq - (n * x_bar * x_bar);

    beta1_hat = Sxy / Sxx;
    beta0_hat = y_bar - (beta1_hat * x_bar);
    estimates.push_back(beta0_hat);
    estimates.push_back(beta1_hat);

    cout << "\nLinear Regression Model, Y = " <<  "\u03b2" << "\u2080 + " << "\u03b2" << "\u2081x + " << "\u03b5" << endl;
    cout << "The Fitted Model, Y_hat = " << beta0_hat << " + " << beta1_hat << "x" << endl;  

    double Syy;
    double sum_of_y_sq = 0.0;
    for(int i = 0; i < n; ++i){
        sum_of_y_sq += (y[i] * y[i]);
    }

    Syy = sum_of_y_sq - (n * y_bar * y_bar);
    double SSr = 0.0;
    SSr = Syy - (beta1_hat * beta0_hat * Sxy);
    double R_Sq;
    R_Sq = 1 - SSr/Syy;

    cout << "The " << dep_variable << " is expected to increase " << beta1_hat << " unit ";
    cout << "for each 1 unit increase in " << indep_variable << endl;
    cout << "Average of " << dep_variable << " is " << beta0_hat << " unit when " << endl;
    cout << indep_variable << " is 0." << endl;
    cout << "This simple linear regression model explains " << R_Sq << "%" << " of the variation in the response values\n";
}
#endif