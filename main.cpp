#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <stdexcept>

using namespace std;

using namespace std;

vector<vector<string>> csvData;
vector<string> headers;
bool outerloop_again = true;
bool innerloop_again = true;
char option;
vector<string> column;

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
vector<string> filterColumn(string &columnName, string &condition, string val)
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

void resizedTable(string shape){
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
    cout << "e. Quit(Press 'q' to quit)\n"
         << "\033[1;0m";
}
vector<string> specifyOperation(string &operation)
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
void begin()
{
start_here_outer:
    cout << "enter the file path" << endl;
    string filepath;
    cin >> filepath;
    if (!loadCSV(filepath))
    {
        return;
    }
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
                    }
                }
                break;

            case 'b':
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
                        else if(specifyFunction[0] == "shape"){
                            string shape = calculateShape(csvData);
                            cout << "shape of data : " << shape << endl;
                        }
                    }
                }
            case 'd':
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