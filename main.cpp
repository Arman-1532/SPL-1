#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <cfloat>
#include <iomanip>

using namespace std;

vector<vector<string>> csvData;
vector<string> headers;
vector<double> x;
vector<double> y;
bool outerloop_again = true;
bool innerloop_again = true;
char option;
vector<string> column;
string filepath;
string null_hypo;
string alter_hypo;
double null_hypothesis;
double sigma;

double calculateSum(vector<string> x)
{
    vector<double> vec;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == "NULL")
        {
            continue;
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
bool loadCSV(string &filename) 
{
    ifstream file;
    file.open(filename);
    if (!file)
    {
        cout << "unable to open file : " << filename << endl;
        return false;
    }

    string line;
    bool isHeader = true;

    while (!file.eof())
    {
        getline(file, line);
        stringstream ss(line);
        vector<string> row;
        string value;

        while (getline(ss, value, ','))
        {
            row.push_back(value);
        }

        if (isHeader)
        {
            headers = row;
            isHeader = false;
        }
        else
        {
            csvData.push_back(row);
        }
    }
    file.close();
    return true;
}
double calculateMean(vector<string> x)
{
    vector<double> vec;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == "NULL")
        {
            continue;
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
void display()
{
    for (int i = 0; i < headers.size(); i++)
    {
        cout << headers[i] << "\t";
    }
    cout << "\n";

    for (auto row : csvData)
    {
        for (auto cell : row)
        {
            cout << cell << "\t";
        }
        cout << "\n";
    }
}
void display_1(vector<vector<string>> csvData,vector<string> headers)
{
    for (int i = 0; i < headers.size(); i++)
    {
        cout << headers[i] << "\t";
    }
    cout << "\n";

    for (auto row : csvData)
    {
        for (auto cell : row)
        {
            cout << cell << "\t";
        }
        cout << "\n";
    }
}
vector<string> getColumn(string columnName) 
{
    int colIndex;
    int flag = 0;

    for (colIndex = 0; colIndex < headers.size(); colIndex++)
    {
        if (columnName == headers[colIndex])
        {
            flag = 1;
            break;
        }
    }
    vector<string> column;
    if (flag == 1)
    {
        for (int i = 0; i < csvData.size(); i++)
        {
            column.push_back(csvData[i][colIndex]);
        }
    }
    else
    {
        cout << "invalid name of column" << endl;
    }
    return column;
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
double calculateMedian(vector<string> x)
{
    vector<double> vec;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == "NULL")
        {
            continue;
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
vector<double> calculateMode(vector<string> x)
{
    vector<double> vec;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == "NULL")
        {
            continue;
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
double calculateVariance(vector<string> x){
    vector<double> vec;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == "NULL")
        {
            continue;
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
vector<string> fillString(vector<string> &vec) {
    vector<string> filledVec = vec; 
  
    for (int i = 0; i<vec.size(); i++) {
        if (vec[i] == "NULL") {
            filledVec[i] = "0";
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
string findHead(vector<string> vec){ 
    string head;
    auto it = vec.begin();
    
    head = *it;
    return head;
}
string findTail(vector<string> vec){ 
    string tail;
    auto it = vec.end() - 1;
    
    tail = *it;
    return tail;
}
string calculateShape(vector< vector< string> > csvData){ 
    string shape;
    int row = csvData.size();
    int column = csvData[0].size();
    string str1 = to_string(row);
    string str2 = to_string(column);
    shape = str1 + " * " + str2;

    return shape; 
}
vector<string> filterColumn(string &columnName, string &condition, string val) //
{
    double value = stod(val);
    auto column = getColumn(columnName);
    vector<string> filteredColumn;

    for (int i = 0; i < column.size(); ++i)
    {
        try
        {
            double cellValue = stod(column[i]);
            if ((condition == ">" && cellValue > value) ||
                (condition == "<" && cellValue < value) ||
                (condition == ">=" && cellValue >= value) ||
                (condition == "<=" && cellValue <= value) ||
                (condition == "==" && cellValue == value))
            {
                filteredColumn.push_back(column[i]);
            }
        }
        catch (...)
        {
            continue; // Skip non-numeric values
        }
    }

    return filteredColumn;
}
double getMax(vector<string> x){ 
    vector<double> vec;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == "NULL")
        {
            continue;
        }
        vec.push_back(stod(x[i]));
    }

    double max = DBL_MIN;
    for(double value : vec){
        if(value > max){
            max = value;
        }
    }
    
    return max;
}
double getMin(vector<string> x){ 
    vector<double> vec;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == "NULL")
        {
            continue;
        }
        vec.push_back(stod(x[i]));
    }

    double min = DBL_MAX;
    for(double value : vec){
        if(value < min){
            min = value;
        }
    }

    return min;
}
// ratio of std deviation and mean
double calculateCoefficientOfVariation(vector<string> x){

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
double calculatePercentile(vector<string> x, double percentile){
    vector<double> vec;
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == "NULL")
        {
            vec.push_back(0);
            continue;
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
vector<double> calculateDeciles(vector<string> x){
    vector<double> deciles;
    double percentile = 10;

    while(percentile <= 90){
        deciles.push_back(calculatePercentile(x, percentile));
        percentile += 10;
    }

    return deciles;
}
vector<double> calculateQuartiles(vector<string> x){
    vector<double> quartiles;
    double quartile = 25;

    while(quartile <= 75){
        quartiles.push_back(calculatePercentile(x, quartile));
        quartile += 25.0;
    }

    return quartiles;
}
vector<double> detectOutliers(vector<string> x){  // inter quartile range
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
            vec.push_back(0);
            continue;
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
void resizedTable(string shape){ //
    int row = shape[0] - '0';
    int column = shape[2] - '0';
    for(int i = 0; i< column; i++){
        cout << headers[i] << '\t';
    }
    cout << endl;

    for(int i = 0; i<row; i++){
        for(int j = 0; j<column; j++){
            cout << csvData[i][j] << '\t';
        }
        cout << endl;
    }
}

vector<string> splitString(string str) 
{
    vector<string> tokens;
    string str1, str2;
    int size = str.size();
    int i;

    for (i = 0; i < size; i++)
    {
        if (str[i] != '.')
        {
            str1.push_back(str[i]);
        }
        else
        {
            break;
        }
    }
    for (i++; i < size; i++)
    {
        str2.push_back(str[i]);
    }
    if(str.find(".") == -1){
        str2 = "empty";
    }
    tokens.push_back(str1);
    tokens.push_back(str2);

    return tokens;
}

void layout()
{
    string titleOfProject = "ProbStat Prodigy: Data Meets Decision";
    int boxWidth = titleOfProject.length() + 6;
    cout << "\n\n\t\t" << '+' << string(boxWidth - 2, '-') << '+' << endl;
    cout << "\t\t" << "|" << string(boxWidth - 2, ' ') << "|" << endl;
    cout << "\t\t|  " << "\033[1;35m" << titleOfProject << "\033[1;0m";
    cout << string(boxWidth - 4 - titleOfProject.length(), ' ');
    cout << "|" << endl;
    cout << "\t\t" << "|" << string(boxWidth - 2, ' ') << "|" << endl;
    cout << "\t\t" << '+' << string(boxWidth - 2, '-') << '+' << endl;
}
void features()
{
    cout << "\n\n\033[1m" << "a. Analyzing Data\n";
    cout << "b. Cleaning Data\n";
    cout << "c. Exploring Data\n";
    cout << "d. Manipulating Data\n";
    cout << "e. Test of Hypothesis\n";
    cout << "f. Simple Linear Regression\n";
    cout << "g. Anova\n";
    cout << "e. Quit(Press 'q' to quit)\n" << "\033[1;0m";
}
vector<string> specifyOperation(string &operation) //
{
    string metric;
    string num;
    vector<string> specifyFunction;
    int size = operation.size();
    for (int i = 0; i < size; i++)
    {
        if (operation[i] == '(')
        {
            if (operation[i + 1] == ')')
            {
                break;
            }
            else
            {
                for (i++; i < size; i++)
                {
                    if (operation[i] == ')')
                    {
                        break;
                    }
                    num.push_back(operation[i]);
                }
            }
        }
        else
        {
            metric.push_back(operation[i]);
        }
    }

    specifyFunction.push_back(metric);
    specifyFunction.push_back(num);

    return specifyFunction;
}
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
        cout << "We can reject the Null hypothesis that the population mean is: " << null_hypothesis << " using two sided z test." << endl;
    }else{
        cout << "We fail to reject the Null hypothesis that the population mean is: " << null_hypothesis << " using two sided z test." << endl;  
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
void simple_linear_regression(string dep_variable, string indep_variable, vector<double> &x, vector<double> &y){
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
void begin()
{
    start_here_outer:
    while (outerloop_again)
    {
    start_here_inner:
        features();
        cout << "enter your choice : ";
        cin >> option;
        string method;
        vector<string> splitedString;
        vector<string> specifyFunction;
        switch (option)
        {
            case 'a':
                cout << "enter the file path" << endl;
                cin >> filepath;
                if (!loadCSV(filepath))
                {
                    return;
                }
                while (innerloop_again)
                {
                    display();
                    cout << "write down the statistical metric you want to implement " << endl;
                    cout << "or press 'q' to go back" << endl;
                    cin >> method;
                    cout << endl;
                    if (method == "q")
                    {
                        goto start_here_inner;
                    }
                    splitedString = splitString(method);

                    column = getColumn(splitedString[0]);
                    cout << splitedString[0] << endl;
                    for (auto value : column)
                    {
                        cout << value << "\n";
                    }
                    cout << endl;
                    if(splitedString[1] != "empty"){
                        specifyFunction = specifyOperation(splitedString[1]);
                        if (specifyFunction[0] == "mean")
                        {
                            double mean;
                            mean = calculateMean(column);
                            cout << "mean is : " << mean << endl << endl;
                        }
                        else if (specifyFunction[0] == "median")
                        {
                            double median;
                            median = calculateMean(column);
                            cout << "median is : " << median << endl << endl;
                        }
                        else if (specifyFunction[0] == "mode")
                        {
                            vector<double> modes = calculateMode(column);
                            cout << "modes are : ";
                            for (auto mode : modes)
                            {
                                cout << mode << "  ";
                            }
                            cout << endl;
                                if (modes.size() == 1){
                                cout << splitedString[0] << " is a uni-modal column" << endl << endl;
                            }
                            else if (modes.size() == 2)
                            {
                                cout << splitedString[0] << " is a bi-modal column" << endl << endl;
                            }
                            else if (modes.size() == 3)
                            {
                                cout << splitedString[0] << " is a tri-modal column" << endl << endl;
                            }
                            else
                            {
                                cout << splitedString[0] << " is a multi-modal column" << endl << endl;
                            }
                        }
                        else if (specifyFunction[0] == "sum")
                        {
                            double sum;
                            sum = calculateSum(column);
                            cout << "sum is : " << sum << endl << endl;
                        }
                        else if(specifyFunction[0] == "variance"){
                            double variance;
                            variance = calculateVariance(column);
                            cout << "variance is : " << variance << endl << endl;
                        }
                        else if(specifyFunction[0] == "standardDeviation"){
                            double standardDeviation;
                            standardDeviation = calculateStandardDeviation(column);
                            cout << "Standard Deviation is : " << standardDeviation << endl << endl;
                        }
                        else if(specifyFunction[0] == "coefficientOfVariation"){
                            double cov;
                            cov = calculateCoefficientOfVariation(column);
                            cout << "coefficient of variation is : " << cov << endl << endl;
                        }
                        else if(specifyFunction[0] == "percentile"){
                            double percentile;
                            percentile =calculatePercentile(column, stod(specifyFunction[1]));
                            if(percentile == -1){
                                cout << "0 percentile is invalid" << endl << endl;
                            }
                            else{
                                cout << specifyFunction[1] << " percentile is : " << percentile << endl << endl;
                            }
                        }
                        else if(specifyFunction[0] == "deciles"){
                            vector <double> deciles;
                            deciles = calculateDeciles(column);
                            for(int i = 10, j = 0; i<= 90; i = i+10, j++){
                                cout << i << " percentile : " << deciles[j] << endl;
                            }
                            cout << endl;
                        }
                        else if(specifyFunction[0] == "quartiles"){
                            vector <double> quartiles;
                            quartiles = calculateQuartiles(column);
                            for(int i = 25, j = 0; i<=75; j++, i = i+25){
                                cout << i << " percentile : " << quartiles[j] << endl;
                            }
                        }
                        else if(specifyFunction[0] == "outliers"){
                            vector<double> outliers;
                            outliers = detectOutliers(column);
                            if(outliers.size() == 0){
                                cout << "No outliers" << endl << endl;
                            }
                            else{
                                cout << "outliers : ";
                                for(int i = 0; i<outliers.size(); i++){
                                    cout << outliers[i] << " ";
                                }
                                cout << endl << endl;
                            }
                        }
                    }
                }
                break;

            case 'b':
                cout << "enter the file path" << endl;
                cin >> filepath;
                if (!loadCSV(filepath))
                {
                    return;
                }   
                while (innerloop_again)
                {
                    display();
                    cout << "write down the statistical metric you want to implement " << endl;
                    cout << "or press 'q' to go back" << endl;
                    cin >> method;
                    cout << endl;
                    if (method == "q")
                    {
                        goto start_here_inner;
                    }
                    splitedString = splitString(method);

                    column = getColumn(splitedString[0]);
                    cout << splitedString[0] << endl;
                    for (auto value : column)
                    {
                        cout << value << "\n";
                    }
                    cout << endl;
                    if(splitedString[1] != "empty"){
                        specifyFunction = specifyOperation(splitedString[1]);
                        if (specifyFunction[0] == "drop_duplicates")
                        {
                            vector<string> avoidDuplicates;
                            avoidDuplicates = dropDuplicates(column);
                            cout << splitedString[0] << endl;
                            for (auto value : avoidDuplicates)
                            {
                                cout << value << "\n";
                            }
                        }
                        else if(specifyFunction[0] == "fill"){
                            vector<string> filledString;
                            filledString = fillString(column);
                            cout<< endl << endl << splitedString[0] << endl;
                            for(int i = 0; i<filledString.size(); i++){
                                cout << filledString[i] << endl;
                            }
                        }
                    }
                }
                break;
            case 'c':
                cout << "enter the file path" << endl;
                cin >> filepath;
                if (!loadCSV(filepath))
                {
                    return;
                }
                while (innerloop_again)
                {
                    display();
                    cout << "write down the statistical metric you want to implement " << endl;
                    cout << "or press 'q' to go back" << endl;
                    cin >> method;
                    cout << endl;
                    if (method == "q")
                    {
                        goto start_here_inner;
                    }
                    splitedString = splitString(method);

                    column = getColumn(splitedString[0]);
                    cout << splitedString[0] << endl;
                    for (auto value : column)
                    {
                        cout << value << "\n";
                    }
                    cout << endl;
                    if(splitedString[1] != "empty"){
                        specifyFunction = specifyOperation(splitedString[1]);
                        if (specifyFunction[0] == "head")
                        {
                            string headValue;
                            headValue = findHead(column);
                            cout << "head value of " << splitedString[0] << " is : " << headValue << endl;
                        }
                        else if(specifyFunction[0] == "tail"){
                            string tailValue;
                            tailValue = findTail(column);
                            cout << "tail value of " << splitedString[0] << " is : " << tailValue << endl;
                        }
                        else if(method == "shape()"){
                            string shape = calculateShape(csvData);
                            cout << "shape of data : " << shape << endl;
                        }
                        else if(specifyFunction[0] == "min"){
                            double min;
                            min = getMin(column);
                            cout << "min is : " << min << endl << endl;
                        }
                        else if(specifyFunction[0] == "max"){
                            double max;
                            max = getMax(column);
                            cout << "max is : " << max << endl << endl;
                        }
                    }
                }
                break;
            case 'd':
                cout << "enter the file path" << endl;
                cin >> filepath;
                if (!loadCSV(filepath))
                {
                    return;
                }
                while (innerloop_again)
                {
                    display();
                    cout << "write down the statistical metric you want to implement " << endl;
                    cout << "or press 'q' to go back" << endl;
                    getline(cin,method);
                    cout << endl;
                    if (method == "q")
                    {
                        goto start_here_inner;
                    }
                    string temp = "resize";
                    int flag = 1;
                    for(int i = 0; i<temp.size(); i++){
                        if(temp[i] == method[i]){
                            flag = 1;
                        }
                        else{
                            flag = 0;
                            break;
                        }
                    }
                    if(flag){
                        string str;
                        str.push_back(method[7]);
                        str.push_back(method[8]);
                        str.push_back(method[9]);

                        resizedTable(str);
                    }
                    // cgpa > 2
                    stringstream ss(method);
                    vector<string> filter;
                    while(getline(ss, temp, ' ')){
                        filter.push_back(temp);
                    }
                    
                    if(filter.size() == 3){
                        vector<string> filteredColumn;
                        filteredColumn = filterColumn( filter[0], filter[1], filter[2]);

                        cout << endl << filter[0] << endl;
                        for(int i = 0; i<filteredColumn.size(); i++){
                            cout << filteredColumn[i] << endl;
                        }
                        cout<< endl;
                    }
                }
                break;
            
            case 'e':
                while(innerloop_again){
                    cout << "\n\033[1m" << "1.Z-Test\n2.T-Test\n3.Chi-Square Test\n4.F-Test\n" << "\033[1;0m" << endl;
                    cout << "enter your choice : " << endl;
                    cout << "(press 'q' to quit)" << endl;
                    char option;
                    cin >> option;
                    cout << endl;
                    if(option == 'q'){
                        goto start_here_inner;
                    }
                    else if(option == '1'){
                        x.clear();
                        readOneVariableDataSet(x);
                        cout << "enter the null and alternative hypothesis" << endl;
                        cout << "H\u2080 : ";
                        cin >> null_hypo;
                        cout << "H\u2081 : ";
                        cin >> alter_hypo;
                        cout << "enter the population variance : ∂ = ";
                        cin >> sigma;

                        string str = null_hypo.substr(3,4);   
                        null_hypothesis = stod(str);
                        char ch = alter_hypo.at(1); 
                        if(ch == '<' || ch == '>'){
                            oneSided_Ztest(x,null_hypothesis,sigma, alter_hypo[1]);
                        }
                        else{
                            twoSided_Ztest(x,null_hypothesis,sigma);
                        }
                    }
                    else if(option == '2'){
                        x.clear();
                        readOneVariableDataSet(x);
                        cout << "enter the null and alternative hypothesis" << endl;
                        cout << "H\u2080 : ";
                        cin >> null_hypo;
                        cout << "H\u2081 : ";
                        cin >> alter_hypo;

                        string str = null_hypo.substr(3,4);
                        null_hypothesis = stod(str);
                        char ch = alter_hypo.at(1); 
                        if(ch == '<' || ch == '>'){
                            oneSided_Ttest(x,null_hypothesis,alter_hypo[1]);
                        }
                        else{
                            twoSided_Ttest(x,null_hypothesis);
                        }
                    }
                    else if(option == '3'){
                        x.clear();
                        readOneVariableDataSet(x);
                        cout << "enter the null hypothesis" << endl;
                        cout << "H\u2080 : ∂\u00B2 = ";
                        cin >> null_hypo;
                    
                        null_hypothesis = stod(null_hypo);
                        chi_Square_test(x,null_hypothesis);
                    }
                    else if(option == '4'){
                        x.clear();
                        y.clear();
                        readTwoVariableDataSet(x,y);

                        f_test(x,y);
                    }
                }
                break;
            case 'f':
                while(innerloop_again){
                    cout << "enter the path of dataset :" << endl;
                    cout << "(press 'q' to quit)" << endl;
                    string filename;
                    cin >> filename;

                    if(filename == "q"){
                        goto start_here_inner;
                    }
                    string dep_variable, indep_variable;
                    x.clear();
                    y.clear();
                    readFileForRegression(filename,dep_variable,indep_variable,x,y);
                    simple_linear_regression(dep_variable,indep_variable,x,y);
                }
            case 'q':
                outerloop_again = false;
                break;
        }
    }
}
int main()
{
    layout();

    begin();
    cout << endl << "\033[1;35m" << "Thanks for using ProbStat Prodigy" << "\033[0m"<< endl;
    return 0;
}