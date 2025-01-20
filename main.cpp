#include <iostream>
#include "Read_File/src/one_variable.cpp"
#include "Read_File/src/two_variable.cpp"
using namespace std;

void layout();
void features();
void begin();

vector<double> x(300);
vector<double> y(300);

int main(){
    layout();

    begin();

    return 0;
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
void features(){
    cout << "\n\n\033[1m" << "a.Summarize Data\n";
    cout << "b.Test Of Hypothesis\n";
    cout << "c.Quit(Press 'q' to quit)\n"<< "\033[1;0m";
}
void begin(){
    bool outerLoop_again = true,innerLoop_again = true;
    while(outerLoop_again){
        features();
        char option;
        cout << "enter your choice : " << endl;
        cin >> option;

        switch(option){
            case 'a':
                while(innerLoop_again){
                    summarize_data:
                    cout << "\033[1m" << "\033[4m" << "\n\n\t\tData Summarization" << "\033[0m" << endl << endl;
                    cout << "\033[1m" << "a.Descriptive Statistics for Single-Variable Data" << endl;
                    cout << "b.Descriptive Statistics for Paired Data" << endl;
                    cout << "c.Go to Main Menu(Press 'q' to quit)" << "\033[1;0m" << endl;
                    cout << "Enter your choice:";
                    cin >> option;
                    string file_type;
                    
                    switch(option){
                        case 'a' :
                            cout << "enter the format of file(txt or csv) : " << endl;
                            do{
                                cin >> file_type;
                                if(file_type == "txt" || file_type == "csv"){
                                    break;
                                }
                                else{
                                    cout << "invalid file type.\nenter the format of file again" << endl;
                                }
                            }while(true);
                            if(file_type == "txt"){
                                x.clear();
                                string filepath;
                                cout << "Enter .txt file path : ";
                                cin >> filepath;
                                readOneVariableFromTxtFile(x,filepath);
                                int one_variable_dataset_size = x.size();
                            }
                            else if(file_type == "csv"){
                                x.clear();
                                string filepath;
                                cout << "Enter .csv file path : ";
                                cin >> filepath;
                                readOneVariableFromCsvFile(x,filepath);
                                int one_variable_dataset_size = x.size();
                            }

                            cout << "a. Full Summarization" << endl;
                            cout << "b. Individual Metric Finder" << endl;
                            cout << "c. Back(press 'q' to quit)" << endl;
                            cin >> option;

                            if(option == 'a'){
                                
                            }
                            break;
                        case 'b':
                            cout << 'b' << endl;
                            break;
                        default:
                            cout << "back" << endl;
                            innerLoop_again = false;
                        

                    }

                }
                break;
            case 'b':
                cout << "hypothesis" << endl;
                break;
            default :
                cout << "back" << endl;
                outerLoop_again = false;
        }
    }
}
