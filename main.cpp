#include "data_analysis.cpp"
#include "data_clean.cpp"
#include "data_explore.cpp"
#include "data_manipulation.cpp"
#include "anova.cpp"
#include "hypothesis_testing.cpp"
#include "simple_linear_regression.cpp"

using namespace std;

vector<vector<string>> csvData;
vector<vector<double>> groups;
vector<string> headers;
vector<double> x;
vector<double> y;
bool outerloop_again = true;
bool innerloop_again = true;
char option;
vector<string> column;
vector<string> column_2;
string filepath;
string null_hypo;
string alter_hypo;
double null_hypothesis;
double sigma;
string method;

void layout();
void begin();
void display();
void features();
vector<string> specifyOperation(string &operation);
bool loadCSV(string &filename);
vector<string> splitString(string str);
vector<string> getColumn(string columnName);

int main()
{
    layout();

    begin();
    cout << endl << "\033[1;35m" << "Thanks for using ProbStat Prodigy" << "\033[0m"<< endl;
    return 0;
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
void begin()
{
    start_here_outer:
    csvData.clear();
    headers.clear();
    while (outerloop_again)
    {
    start_here_inner:
        csvData.clear();
        headers.clear();
        features();
        cout << "enter your choice : ";
        cin >> option;
        vector<string> splitedString;
        vector<string> specifyFunction;
        switch (option)
        {
            case 'a':
                csvData.clear();
                headers.clear();
                cout << "enter the file path" << endl;
                cin >> filepath;
                if (!loadCSV(filepath))
                {
                    return;
                }
                while (innerloop_again)
                {
                    cout << endl << "\t\t   " << "Analyzing Data" << endl;
                    cout << "\t\t   " << string( 14 , '-')  << endl;
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
                            median = calculateMedian(column);
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
                csvData.clear();
                headers.clear();
                cout << "enter the file path" << endl;
                cin >> filepath;
                if (!loadCSV(filepath))
                {
                    return;
                }   
                while (innerloop_again)
                {
                    cout << endl << "\t\t   " << "Cleaning Data" << endl;
                    cout << "\t\t   " << string( 13 , '-')  << endl;
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
                csvData.clear();
                headers.clear();
                cout << "enter the file path" << endl;
                cin >> filepath;
                if (!loadCSV(filepath))
                {
                    return;
                }
                while (innerloop_again)
                {
                    cout << endl << "\t\t   " << "Exploring Data" << endl;
                    cout << "\t\t   " << string( 14 , '-')  << endl;
                    display();
                    cout << "write down the statistical metric you want to implement " << endl;
                    cout << "or press 'q' to go back" << endl;
                    cin >> method;
                    cout << endl;
                    if (method == "q")
                    {
                        goto start_here_inner;
                    }
                    if(method == "shape()"){
                        string shape = calculateShape(csvData);
                        cout << "shape of data : " << shape << endl;
                        continue;
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
                csvData.clear();
                headers.clear();
                cout << "enter the file path" << endl;
                cin >> filepath;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (!loadCSV(filepath))
                {
                    return;
                }
                while (innerloop_again)
                {
                    cout << endl << "\t\t   " << "Manipulating Data" << endl;
                    cout << "\t\t   " << string( 17 , '-')  << endl;
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

                        resizedTable(csvData,headers,str);
                    }
                    // cgpa > 2
                    stringstream ss(method);
                    vector<string> filter;
                    while(getline(ss, temp, ' ')){
                        filter.push_back(temp);
                    }
                    
                    if(filter.size() == 3){
                        vector<string> filteredColumn;
                        filteredColumn = filterColumn( csvData,headers,filter[0], filter[1], filter[2]);

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
                    cout << endl << "\t\t   " << "Test of Hypothesis" << endl;
                    cout << "\t\t   " << string( 18 , '-')  << endl;

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
                    cout << endl << "\t\t   " << "Simple Linear Regression" << endl;
                    cout << "\t\t   " << string( 24 , '-')  << endl;
                    headers.clear();
                    csvData.clear();
                    cout << "enter the path of dataset :" << endl;
                    cout << "(press 'q' to quit)" << endl;
                    string filename;
                    cin >> filename;
                    if(filename == "q"){
                        goto start_here_inner;
                    }
                    if (!loadCSV(filename))
                    {
                        return;
                    }
                    display();

                    string dep_variable, indep_variable;
                    printf("enter the dependent and independent variables : \n");
                    cin >> dep_variable >> indep_variable;
                    column.clear();
                    column_2.clear();
                    column = getColumn(dep_variable);
                    column_2 = getColumn(indep_variable);

                    x.clear();
                    y.clear();
                    for(int i = 0; i < column.size(); i++){
                        x.push_back(stod(column_2[i]));
                        y.push_back(stod(column[i]));
                    }
                    simple_linear_regression(indep_variable,dep_variable,x,y);
                }
            case 'g': 
                while(innerloop_again){
                    cout << endl << "\t\t   " << "Anova" << endl;
                    cout << "\t\t   " << string( 5 , '-')  << endl;
                    cout << "enter the path of dataset :" << endl;
                    cout << "(press 'q' to quit)" << endl;
                    string filename;
                    cin >> filename;

                    if(filename == "q"){
                        goto start_here_inner;
                    }
                    groups.clear();
                    read_groups(groups,filename);
                    anova_test(groups);
                }
                break;
            case 'q':
                outerloop_again = false;
                break;
        }
    }
}
void display(){
    vector<int> colWidths(headers.size(), 0);

    for (int i = 0; i < headers.size(); i++) {
        colWidths[i] = headers[i].length();
    }

    for ( auto& row : csvData) {
        for (int i = 0; i < row.size() && i < colWidths.size(); i++) {
            colWidths[i] = maxOf(colWidths[i], row[i].length());
        }
    }

    for (int i = 0; i < headers.size(); i++) {
        cout << left << setw(colWidths[i] + 2) << headers[i];
    }
    cout << "\n";

    for (auto& row : csvData) {
        for (int i = 0; i < row.size() && i < colWidths.size(); i++) {
            cout << left << setw(colWidths[i] + 2) << row[i];
        }
        cout << "\n";
    }
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
    cout << "h. Quit(Press 'q' to quit)\n" << "\033[1;0m";
}