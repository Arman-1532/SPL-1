#ifndef HYPOTHESIS_TESTING_CPP
#define HYPOTHESIS_TESTING_CPP

#include "combined.h"

using namespace std;

void readOneVariableDataSet(vector<double> &x){
    ifstream in;
    in.open("oneVariable_dataset.txt");
    if(!in){
        cout << "unable to open file\n";
        return;
    }

    double value;
    while(!in.eof()){
        in >> value;
        x.push_back(value);
    }

    in.close();
}
double calc_Mean(vector<double> x){
    double sum;
    for(double value : x){
        sum += value;
    }

    return sum/x.size();
}
vector<string> split(const string &line, char delimiter) {
    vector<string> result;
    stringstream ss(line);
    string token;
    while (getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}
double z_valueFromTable(double value){
    value = floor(value * 100) /100;
    string filename = "Z_table.csv"; 
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "unable to open file" << endl;
        return 1;
    }

    vector<double> increments;  // Stores first row (0.00, 0.01, ..., 0.09)
    vector<vector<double>> table; // Stores Z-table values
    vector<double> baseValues; // Stores first column (0.0, 0.1, ..., 2.0)

    string line;
    bool isFirstRow = true;

    // Read the file line by line
    while (getline(file, line)) {
        vector<string> values = split(line, ',');

        if (isFirstRow) {
            for (size_t i = 1; i < values.size(); i++) {
                increments.push_back(stod(values[i]));
            }
            isFirstRow = false;
        } else {
            // Store first column (base Z-values)
            baseValues.push_back(stod(values[0]));

            // Store row values
            vector<double> rowValues;
            for (int i = 1; i < values.size(); i++) {
                rowValues.push_back(stod(values[i]));
            }
            table.push_back(rowValues);
        }
    }

    file.close();

    double baseZ = floor(value * 10) / 10;  // Example: 1.68 -> 1.60
    double increment = value - baseZ;       // Example: 1.68 - 1.60 = 0.08

    // Find the corresponding row
    double epsilon = 1e-9;
    int rowIndex = -1, colIndex = -1;
    for (int i = 0; i < baseValues.size(); i++) {
        if (fabs(baseValues[i] - baseZ) < epsilon) {
            rowIndex = i;
            break;
        }
    }

    // Find the corresponding column
    for (int i = 0; i < increments.size(); i++) {
        if (fabs(increments[i] - increment) < epsilon) {
            colIndex = i;
            break;
        }
    }
   
    // Output result
    if (rowIndex != -1 && colIndex != -1) {
        return table[rowIndex][colIndex];
    } else {
        return -1;
    }
}
void oneSided_Ztest(vector<double> x, double null_hypothesis, double sigma, char sign){
    double sample_mean = calc_Mean(x);
    int n = x.size();
    double numerator = sample_mean - null_hypothesis;
    double denominator = sigma / sqrt(n);
    double z_statistic = (numerator / denominator);
    double alpha = 0.05;
    double tabulated_z = z_valueFromTable(1-alpha);
    cout << "Z statistic, Z = " << z_statistic << endl;
    cout << "Critical Value, z alpha = " << tabulated_z << endl;
    if(sign == '>'){
        if(z_statistic > tabulated_z){
            cout << "We can reject the Null hypothesis that the population mean is: " << null_hypothesis << " using one sided z test." << endl;
        }else{
            cout << "We fail to reject the Null hypothesis that the population mean is: " << null_hypothesis << " using one sided z test." << endl;  
        }
    }
    else if(sign == '<'){
        if(z_statistic < (0-tabulated_z)){
            cout << "We can reject the Null hypothesis that the population mean is: " << null_hypothesis << " using one sided z test." << endl;
        }else{
            cout << "We fail to reject the Null hypothesis that the population mean is: " << null_hypothesis << " using one sided z test." << endl;  
        }
    }
}
void twoSided_Ztest(vector<double> &x, double null_hypothesis, double sigma){
    double sample_mean = calc_Mean(x);
    int n = x.size();
    double numerator = sample_mean - null_hypothesis;
    double denominator = sigma / sqrt(n);
    double z_statistic = fabs(numerator / denominator);
    double alpha = 0.05;
    double tabulated_z = z_valueFromTable(1 - alpha/2);
    cout << "Z statistic, Z = " << z_statistic << endl;
    cout << "Critical Value, z_alpha_by_2 = " << tabulated_z << endl;
    if(z_statistic > tabulated_z){
        cout << "We can reject the Null hypothesis that the population mean is: " << null_hypothesis << " using z test." << endl;
    }else{
        cout << "We fail to reject the Null hypothesis that the population mean is: " << null_hypothesis << " using z test." << endl;  
    }
}
double calc_deviation(vector<double> x){
    double sum = 0;
    double mean = calc_Mean(x);
    for(double value : x){
        sum += value * value;
    }
    sum -= x.size() * mean * mean;
    double deviation = sqrt(sum / (x.size() -1));
    return deviation;
}
double t_valueFromTable(int dof, double alpha){
    ifstream file;
    file.open("T_table.csv");

    if (!file.is_open()) {
        cout << "unable to open file - T_table.csv " << endl;
        return 1;
    }

    vector<double> significanceLevels;  // Stores first row (0.10, 0.05, ...)
    vector<vector<double>> table;       // Stores t-table values
    vector<int> degreesOfFreedom;       // Stores first column (df = 1, 2, ..., 30)

    string line;
    bool isFirstRow = true;

    // Read the file line by line
    while (getline(file, line)) {
        vector<string> values = split(line, ',');

        if (isFirstRow) {
            // Store first row (significance levels)
            for (size_t i = 1; i < values.size(); i++) {
                significanceLevels.push_back(stod(values[i]));
            }
            isFirstRow = false;
        } else {
            // Store first column (degrees of freedom)
            degreesOfFreedom.push_back(stoi(values[0]));

            // Store row values
            vector<double> rowValues;
            for (size_t i = 1; i < values.size(); i++) {
                rowValues.push_back(stod(values[i]));
            }
            table.push_back(rowValues);
        }
    }

    file.close();

    // Find the corresponding row (df)
    int rowIndex = -1, colIndex = -1;
    for (size_t i = 0; i < degreesOfFreedom.size(); i++) {
        if (degreesOfFreedom[i] == dof) {
            rowIndex = i;
            break;
        }
    }

    // Find the corresponding column (alpha)
    for (size_t i = 0; i < significanceLevels.size(); i++) {
        if (significanceLevels[i] == alpha) {
            colIndex = i;
            break;
        }
    }

    if (rowIndex != -1 && colIndex != -1) {
       return table[rowIndex][colIndex];
    } else {
        cout << "Value not found in the table!" << endl;
        return -1;
    }
}
void oneSided_Ttest(vector<double> &x, double null_hypothesis, char sign){
    double sample_mean = calc_Mean(x);
    int n = x.size();
    double std_devition = calc_deviation(x);
    double numerator = sample_mean - null_hypothesis;
    double denominator = std_devition / sqrt(n);
    double t_statistic = (numerator / denominator);
    double alpha = 0.05;
    int dof = n - 1;
    double tabulated_t = t_valueFromTable(dof, alpha);
    cout << "T statistic, T = " << t_statistic << endl;
    cout << "Critical Value, t (dof,alpha) = " << tabulated_t << endl;
    if(sign == '>'){
        if(t_statistic > tabulated_t){
            cout << "We can reject the Null hypothesis that the population mean is: " << null_hypothesis << " using one sided z test." << endl;
        }else{
            cout << "We fail to reject the Null hypothesis that the population mean is: " << null_hypothesis << " using one sided z test." << endl;  
        }
    }
    else if(sign == '<'){
        if(t_statistic < (0-tabulated_t)){
            cout << "We can reject the Null hypothesis that the population mean is: " << null_hypothesis << " using one sided z test." << endl;
        }else{
            cout << "We fail to reject the Null hypothesis that the population mean is: " << null_hypothesis << " using one sided z test." << endl;  
        }
    }
}
void twoSided_Ttest(vector<double> &x, double null_hypothesis){
    double sample_mean = calc_Mean(x);
    int n = x.size();
    double std_deviation = calc_deviation(x);
    double numerator = sample_mean - null_hypothesis;
    double denominator = std_deviation / sqrt(n);
    double t_statistic = fabs(numerator / denominator);
    double alpha = 0.05;
    int dof = n - 1;
    double tabulated_t = t_valueFromTable(dof,alpha/2);
    cout << "T statistic, T = " << t_statistic << endl;
    cout << "Critical Value, T (dof,alpha_by_2) = " << tabulated_t << endl;
    if(t_statistic > tabulated_t){
        cout << "We can reject the Null hypothesis that the population mean is: " << null_hypothesis << " using two sided z test." << endl;
    }else{
        cout << "We fail to reject the Null hypothesis that the population mean is: " << null_hypothesis << " using two sided z test." << endl;  
    }
}
double chi_value_from_table(double dof,double alpha){
    ifstream file;
    file.open("chi_square_table.csv");

    if (!file.is_open()) {
        cout << "unable to open file - Chi_Square_table.csv " << endl;
        return 1;
    }

    vector<double> significanceLevels;  // Stores first row (0.10, 0.05, ...)
    vector<vector<double>> table;       // Stores chi_square-table values
    vector<int> degreesOfFreedom;       // Stores first column (df = 1, 2, ..., 30)

    string line;
    bool isFirstRow = true;

    // Read the file line by line
    while (getline(file, line)) {
        vector<string> values = split(line, ',');

        if (isFirstRow) {
            // Store first row (significance levels)
            for (size_t i = 1; i < values.size(); i++) {
                significanceLevels.push_back(stod(values[i]));
            }
            isFirstRow = false;
        } else {
            // Store first column (degrees of freedom)
            degreesOfFreedom.push_back(stoi(values[0]));

            // Store row values
            vector<double> rowValues;
            for (size_t i = 1; i < values.size(); i++) {
                rowValues.push_back(stod(values[i]));
            }
            table.push_back(rowValues);
        }
    }

    file.close();

    // Find the corresponding row (df)
    int rowIndex = -1, colIndex = -1;
    for (size_t i = 0; i < degreesOfFreedom.size(); i++) {
        if (degreesOfFreedom[i] == dof) {
            rowIndex = i;
            break;
        }
    }

    // Find the corresponding column (alpha)
    for (size_t i = 0; i < significanceLevels.size(); i++) {
        if (significanceLevels[i] == alpha) {
            colIndex = i;
            break;
        }
    }
    if (rowIndex != -1 && colIndex != -1) {
       return table[rowIndex][colIndex];
    } else {
        cout << "Value not found in the table!" << endl;
        return -1;
    }
}
void chi_Square_test(vector<double> &x,double null_hypothesis){
    int n = x.size();
    double std_deviation = calc_deviation(x);
    double numerator = (n-1) * std_deviation * std_deviation;
    double denominator = null_hypothesis;
    double chi_square_value = numerator / denominator;
    double alpha = 0.01;
    double level_of_confidence = 1 - alpha;
    double dof = n-1;
    double lower_bound = chi_value_from_table(dof,(1-(alpha/2)));
    double upper_bound = chi_value_from_table(dof,alpha/2);

    cout << "Chi-Square Value : " << chi_square_value << endl;
    cout << "acceptance region : " << lower_bound << " - " << upper_bound << endl;

    if(lower_bound < chi_square_value && chi_square_value <= upper_bound){
        cout << "We fail to reject the Null hypothesis that the population variance is: " << null_hypothesis << endl;
    }
    else{
        cout << "We can reject the Null hypothesis that the population variance is: " << null_hypothesis << endl;
    }
}
void readTwoVariableDataSet(vector<double> &x , vector<double> &y){
    ifstream in;
    in.open("twoVariable_dataset.txt");

    if(!in){
        cout << "unable to open twoVariable_dataset.txt file" << endl;
        return;
    }

    while(!in.eof()){
        double val1, val2;
        in >> val1;
        x.push_back(val1);
        in >> val2;
        y.push_back(val2);
    }
    in.close();
}
double calc_var(vector<double> vec){
    double deviation = calc_deviation(vec);

    return deviation * deviation;
}
double f_valueFromTable(int df1, int df2){
    ifstream file;
    file.open("F_table.csv");

    if (!file.is_open()) {
        cout << "unable to open file - F_table.csv " << endl;
        return 1;
    }

    vector<int> df1_values;         // Stores first row (numerator degrees of freedom)
    vector<int> df2_values;         // Stores first column (denominator degrees of freedom)
    vector<vector<double>> table;   // Stores F-table values

    string line;
    bool isFirstRow = true;

    while (getline(file, line)) {
        vector<string> values = split(line, ',');

        if (isFirstRow) {
            // Store first row (numerator df)
            for (size_t i = 1; i < values.size(); i++) {
                df1_values.push_back(stoi(values[i]));
            }
            isFirstRow = false;
        } else {
            // Store first column (denominator df)
            df2_values.push_back(stoi(values[0]));

            // Store row values
            vector<double> rowValues;
            for (size_t i = 1; i < values.size(); i++) {
                rowValues.push_back(stod(values[i]));
            }
            table.push_back(rowValues);
        }
    }

    file.close();

    // Find the corresponding row (df2) and column (df1)
    int rowIndex = -1, colIndex = -1;
    for (size_t i = 0; i < df2_values.size(); i++) {
        if (df2_values[i] == df2) {
            rowIndex = i;
            break;
        }
    }

    for (size_t i = 0; i < df1_values.size(); i++) {
        if (df1_values[i] == df1) {
            colIndex = i;
            break;
        }
    }

    if (rowIndex != -1 && colIndex != -1) {
        return table[rowIndex][colIndex];
    } else {
        return -1;
    }
}
void f_test(vector<double> &x, vector<double> &y){
    double var_x = calc_var(x);
    double var_y = calc_var(y);
    double f_statistic = var_x/var_y; // if Ho -> population variances are equal
    int n = x.size() - 1;
    int m = y.size() - 1;
    double tabulated_f = f_valueFromTable(m, n);
    cout << "f statistic, F = " << f_statistic << endl;
    cout << "Critical Value, f alpha = " << tabulated_f << endl;
    if(f_statistic > tabulated_f){
        cout << "We can reject the null hypothesis that two groups has the same variance!" << endl;
    }else{
        cout << "We fail to reject the null hypothesis that two groups has the same variance!" << endl;
    }
}

#endif