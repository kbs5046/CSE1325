// Khom B Sitaula (1001605046)

#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <vector>
#include "CokeMachine.h"
#include "CokeLib.h"
#include <cstdlib>

using namespace std;

void get_command_line_params(int argc, char *argv[], string &input, string &output);

int main(int argc, char *argv[]){
    string input,output;
    try{
        get_command_line_params(argc, argv, input, output);
    }
    catch(invalid_argument &ex) {
        cerr << "An exception occurred: " << ex.what() << endl;
        exit(0);
    }
    CokeMachine MyCokeMachine;

    vector <CokeMachine> SetOfCokeMachines;
    vector<string> ConstructorValues(4);
    ifstream CokeInputFile{input};
    ofstream CokeOutputFile{output, ios::out};
    int ch,i;

    string CokeMachineLine;
    int Linecounter = 0;
    if (CokeInputFile.is_open()){

        while(!CokeInputFile.eof()){
            getline(CokeInputFile, CokeMachineLine);
            if (ParseCokeLine(CokeMachineLine, ConstructorValues)){

                CokeMachine tempObject{ConstructorValues.at(0), stoi(ConstructorValues.at(1)), stoi(ConstructorValues.at(2)), stoi(ConstructorValues.at(3))};
                SetOfCokeMachines.push_back(tempObject);
            }

        }
        CokeInputFile.close();

    }
    else{
        cout<<"Unable to open file."<<endl;
        exit(0);
    }

    //bool contd = true;
    bool ifadd = false;
    int choice, payment, action, addNum, addChange;
    string change;
    string newName;
    int newPrice;
    do{
        cout<<"\nPick a Coke Machine"<<endl;
        cout << "0.\tExit" << endl;
        for (i = 0; i < SetOfCokeMachines.size(); i++) {
            cout << (i + 1) << ".\t" << SetOfCokeMachines.at(i).getMachineName() << endl;
        }
        cout << (SetOfCokeMachines.size() + 1) << ".\t" << "Add a new machine " << endl;
        cout << "\nEnter Choice: ";

        cin >> ch;
        if(ch == 0){
            for (i = 0; i < SetOfCokeMachines.size(); i++) {
                CokeOutputFile <<CreateCokeOutputLine(SetOfCokeMachines[i]);
            }
            //CokeOutputFile.close();
            return 0;

        }
        if (ch > 0 && ch <= SetOfCokeMachines.size()){
               // MyCokeMachine = SetOfCokeMachines.at(ch - 1);
                ifadd = false;

        }
        else if (ch == SetOfCokeMachines.size()+1){
            CokeMachine temp;
            SetOfCokeMachines.push_back(temp);
            cout <<"\nNew Machine added"<<endl;
            ifadd = true;

        }
    //}
    //while (ch > 0 && (ch == SetOfCokeMachines.size() && ifadd == true) );


    //int choice, payment, action, addNum, addChange;
    //string change;
    //string newName;
    //int newPrice;
    while (ifadd == false){
        cout <<"\n\nWelcome to "<<SetOfCokeMachines[ch-1].getMachineName()<<endl;
        cout << "\n0. Walk away" << endl;
        cout << "1. Buy a Coke" << endl;
        cout << "2. Restore Machine" << endl;
        cout << "3. Add Change" << endl;
        cout << "4. Display Machine Info" << endl;
        cout << "5. Update Machine Name" << endl;
        cout << "6. Update Coke Price" << endl;
        cout << "\nEnter choice " << endl;
        cin >> choice;
        cin.ignore();

        switch(choice){
            case 0:
                //contd = false;
                ifadd = true;break;
            case 1:
                cout <<"Insert Payment: "<<endl;
                cin >> payment;
                if(SetOfCokeMachines[ch-1].buyACoke(payment, &change, &action)){
                    if (action == 0){
                        cout <<"Here is your Coke and change of $"<<change<<endl;
                   }
                   else if (action == 1){
                        cout <<"Thanks for exact change\nHere is your Coke"<<endl;
                   }
                   else if (action == 2){
                        cout <<"Insufficient payment..... returning your payment of $"<<change<<endl;
                   }
                   else if (action == 3){
                        cout <<"Unable to give change at this time... returning your payment of $"<<change<<endl;
                   }
                }
                break;
            case 2:
                cout <<"How much product are you adding to the machine?  "<<endl;
                cin >> addNum;
                if (SetOfCokeMachines[ch-1].incrementInventory(addNum)){
                    cout <<"Your machine has been restocked"<<endl;
                    cout <<"Your inventory level is now "<<SetOfCokeMachines[ch-1].getInventoryLevel()<<endl;
                }
                else {
                    cout <<"You have exceeded your machine's max capacity"<<endl;
                    cout <<"Your inventory level is now "<<SetOfCokeMachines[ch].getInventoryLevel()<<endl;
                }

                break;
            case 3:
                cout <<"How much change are you adding to the machine?  "<<endl;
                cin >>addChange;
                if (SetOfCokeMachines[ch-1].incrementChangeLevel(addChange)){
                    cout <<"Your change has been updated"<<endl;
                    cout <<"Your change level is now "<<SetOfCokeMachines[ch-1].getChangeLevel()<<endl;
                }
                else {
                    cout <<"You have exceeded your machine's max change capacity"<<endl;
                    cout <<"Your change level is now "<<SetOfCokeMachines[ch-1].getChangeLevel()<<endl;
                }
                break;
            case 4:
                cout << SetOfCokeMachines[ch-1] <<endl;
                break;
            case 5:
                cout <<"\nEnter a new machine name: "<<endl;
                getline(cin, newName);
                //cin >> newName;
                //MyCokeMachine.setMachineName(newName);
                SetOfCokeMachines[ch-1].setMachineName(newName);
                cout <<"Machine name has been updated"<<endl;
                break;
            case 6:
                cout <<"\nEnter a new Coke price: "<<endl;
                cin >> newPrice;
                SetOfCokeMachines[ch-1].setCokePrice(newPrice);
                cout <<"Coke price has been updated"<<endl;
                break;
            default :
                cout <<"Are you sure you aren't really Thirsty and need a Coke?"<<endl;break;
                return 0;
        }
        cout <<"\n\n";

    }
    }
    while (ch > 0 && (ch == SetOfCokeMachines.size() || ifadd == true) && choice == 0 );


}

void get_command_line_params(int argc, char *argv[], string& input, string& output){
    int i,valid1 = 0, valid2 = 0;
    string cla;
    for (i=1; i<argc; i++){

        cla = argv[i];
        if (cla.substr(0,cla.find("=")) == "INPUTFILENAME"){
            input = cla.substr(cla.find("=")+1, cla.length());
            valid1 = 1;
        }

        if (cla.substr(0,cla.find("=")) == "OUTPUTFILENAME"){
            output = cla.substr(cla.find("=")+1, cla.length());
            valid2 = 1;
        }
    }
    if (!(valid1 && valid2)){
        throw invalid_argument("Missing command line parameters - - Usage : INPUTFILENAME= OUTPUTFILENAME=");

    }
}

