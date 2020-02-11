// Khom B Sitaula (1001605046)

#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include "CokeMachine.h"
#include "CokeLib.h"
#include <cstdlib>
#include "VendingMachine.h"
#include <map>
#include <gtkmm.h>

using namespace std;

void get_command_line_params(int argc, char *argv[], string &input, string &output);
int printMenu();
int getPayment();
int getRestock();
int getChangeAmount();
string getNewName();
int getNewPrice();

int main(int argc, char *argv[]){
    Gtk::Main kit(argc, argv);
    string input,output;
    try{
        get_command_line_params(argc, argv, input, output);
    }
    catch(invalid_argument &ex) {
        cerr << "An exception occurred: " << ex.what() << endl;
        exit(0);
    }

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
    bool ifadd = false;
    int choice, payment, action, addNum, addChange;
    string change;
    string newName;
    int newPrice;
    map <string,int> mapReceipt;
    do{
        int n = 0;
        cout<<"\nPick a Coke Machine"<<endl;
        cout << "0.\tExit" << endl;
        for (auto Set: SetOfCokeMachines) {
            cout << (n + 1) << ".\t" << Set.getMachineName() << endl;
            n++;
        }
        cout << (SetOfCokeMachines.size() + 1) << ".\t" << "Add a new machine " << endl;
        cout << "\nEnter Choice: ";

        cin >> ch;
        if(ch == 0){
            for (i = 0; i < SetOfCokeMachines.size(); i++) {
                CokeOutputFile <<CreateCokeOutputLine(SetOfCokeMachines[i]);
            }
            cout <<"\nYour Coke Receipt:"<<endl;
            for (auto mapItem: mapReceipt){
                cout <<mapItem.first<<":\t"<<mapItem.second<<endl;

            }

            return 0;

        }
        if (ch > 0 && ch <= SetOfCokeMachines.size()){
                ifadd = false;

        }
        else if (ch == SetOfCokeMachines.size()+1){
            CokeMachine temp;
            SetOfCokeMachines.push_back(temp);
            cout <<"\nNew Machine added"<<endl;
            ifadd = true;

        }
        int sale = 0;
        while (ifadd == false){
            choice = printMenu();
            switch(choice){
                case 0:
                //contd = false;
                    ifadd = true;break;
                case 1:{
                    payment = getPayment();
                    if(SetOfCokeMachines[ch-1].buyACoke(payment, &change, &action)){
                        if (action == 0){
                            string message {"Here is your Coke and change of $"+change};
                            sale= sale +1;
                            mapReceipt[SetOfCokeMachines[ch-1].getMachineName()] = sale;

                            Gtk::MessageDialog *MyMessageDialog  = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                            MyMessageDialog->run();
                            MyMessageDialog->close();
                            delete MyMessageDialog;
                        }
                        else if (action == 1){
                            string message {"Thanks for exact change\nHere is your Coke"};
                            sale = sale +1;
                            mapReceipt[SetOfCokeMachines[ch-1].getMachineName()] = sale;

                            Gtk::MessageDialog *MyMessageDialog  = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                            MyMessageDialog->run();
                            MyMessageDialog->close();
                            delete MyMessageDialog;
                        }
                        else if (action == 2){
                            string message {"Insufficient payment..... returning your payment of $"+change};

                            Gtk::MessageDialog *MyMessageDialog  = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                            MyMessageDialog->run();
                            MyMessageDialog->close();
                            delete MyMessageDialog;
                        }
                        else if (action == 3){
                            string message {"Unable to give change at this time... returning your payment of $" +change};

                            Gtk::MessageDialog *MyMessageDialog  = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                            MyMessageDialog->run();
                            MyMessageDialog->close();
                            delete MyMessageDialog;
                        }
                    }
                }
                    break;
                case 2:{
                    addNum = getRestock();
                    if (addNum != 0){
                        if (SetOfCokeMachines[ch-1].incrementInventory(addNum)){
                            string message1{"Your machine has been restocked"};
                            string message2{"Your inventory level is now "+ to_string(SetOfCokeMachines[ch-1].getInventoryLevel())};

                            Gtk::MessageDialog *MyMessageDialog  = new Gtk::MessageDialog{message1, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                            MyMessageDialog->set_secondary_text (message2,true);
                            MyMessageDialog->run();
                            MyMessageDialog->close();
                            delete MyMessageDialog;

                        }
                        else {
                            string message1{"You have exceeded your machine's max capacity"};
                            string message2{"Your inventory level is now "+ to_string(SetOfCokeMachines[ch-1].getInventoryLevel())};

                            Gtk::MessageDialog *MyMessageDialog  = new Gtk::MessageDialog{message1, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                            MyMessageDialog->set_secondary_text (message2,true);
                            MyMessageDialog->run();
                            MyMessageDialog->close();
                            delete MyMessageDialog;
                        }
                    }
                }

                    break;
                case 3:{
                    int addChange = getChangeAmount();
                    if(addChange != 0){
                        if (SetOfCokeMachines[ch-1].incrementChangeLevel(addChange)){
                            string message{"Your change has been updated"};

                            Gtk::MessageDialog *MyMessageDialog  = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                            MyMessageDialog->run();
                            MyMessageDialog->close();
                            delete MyMessageDialog;
                        }
                        else {
                            string message{"You have exceeded your machine's max change capacity"};

                            Gtk::MessageDialog *MyMessageDialog  = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                            MyMessageDialog->run();
                            MyMessageDialog->close();
                            delete MyMessageDialog;
                        }
                    }
                }
                    break;
                case 4:{
                    ostringstream m1;
                    m1 << SetOfCokeMachines[ch-1]<<endl;
                    string message =m1.str();

                    Gtk::MessageDialog *MyMessageDialog  = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                    MyMessageDialog->run();
                    MyMessageDialog->close();
                    delete MyMessageDialog;

                }
                    break;
                case 5:{
                    newName = getNewName();
                    SetOfCokeMachines[ch-1].setMachineName(newName);
                    string message{"Machine name has been updated"};

                    Gtk::MessageDialog *MyMessageDialog  = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                    MyMessageDialog->run();
                    MyMessageDialog->close();
                    delete MyMessageDialog;
                }
                    break;
                case 6:{
                    newPrice = getNewPrice();
                    SetOfCokeMachines[ch-1].setCokePrice(newPrice);
                    string message{"Coke price has been updated"};

                    Gtk::MessageDialog *MyMessageDialog  = new Gtk::MessageDialog{message, true,Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false};
                    MyMessageDialog->run();
                    MyMessageDialog->close();
                    delete MyMessageDialog;
                }
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

int printMenu(){

    Gtk::Dialog *MyDialog = new Gtk::Dialog();
    MyDialog->set_title("CSE1325 Coke Machine");
    std::vector<std::string> buttons = {"Cancel", "Buya Coke", "Restore Machine", "Add Change", "Display Machine Info", "Update Machine Name", "Update Coke Price"};
    for (int i = 0; i < buttons.size(); i++)
           MyDialog->add_button(buttons[i], i);

    Gtk::Label *MyLabel = Gtk::manage(new Gtk::Label("What is your decision?"));
    MyDialog->get_vbox()->pack_start(*MyLabel);
    MyLabel->show();

    int result = MyDialog->run();

    MyDialog->close();
    delete MyDialog;



    return result;
}

int getPayment(){
    int payment;
    Gtk::Dialog *MyDialog = new Gtk::Dialog();
    MyDialog->set_title("Payment");
    std::vector<std::string> buttons = {"OK"};
    for (int i = 0; i < buttons.size(); i++)
           MyDialog->add_button(buttons[i], i);

    Gtk::Entry *MyEntry = Gtk::manage(new Gtk::Entry());
    MyEntry->set_text("Enter Payment");
    MyEntry->set_max_length(50);
    MyEntry->show();
    MyDialog->get_vbox()->pack_start(*MyEntry);

    int result = MyDialog->run();


    payment = stoi(MyEntry->get_text());

    MyDialog->close();
    delete MyDialog;

    return payment;
}

int getRestock(){
    int addNum;
    Gtk::Dialog *MyDialog = new Gtk::Dialog();
    MyDialog->set_title("Restock");
    std::vector<std::string> buttons = {"OK", "Cancel"};
    for (int i = 0; i < buttons.size(); i++)
           MyDialog->add_button(buttons[i], i);

    Gtk::Entry *MyEntry = Gtk::manage(new Gtk::Entry());
    MyEntry->set_text("Restock Quantity");
    MyEntry->set_max_length(50);
    MyEntry->show();
    MyDialog->get_vbox()->pack_start(*MyEntry);

    int result = MyDialog->run();

    if (result==1){
        addNum = 0;
    }
    else{
        addNum = stoi(MyEntry->get_text());
    }
    MyDialog->close();
    delete MyDialog;


    return addNum;
}

int getChangeAmount(){
    int addChange;
    Gtk::Dialog *MyDialog = new Gtk::Dialog();
    MyDialog->set_title("Add Change");
    std::vector<std::string> buttons = {"OK", "Cancel"};
    for (int i = 0; i < buttons.size(); i++)
           MyDialog->add_button(buttons[i], i);

    Gtk::Entry *MyEntry = Gtk::manage(new Gtk::Entry());
    MyEntry->set_text("Adding to Machine?");
    MyEntry->set_max_length(50);
    MyEntry->show();
    MyDialog->get_vbox()->pack_start(*MyEntry);

    int result = MyDialog->run();

    if (result==1){
        addChange = 0;
    }
    else{
        addChange = stoi(MyEntry->get_text());
    }
    MyDialog->close();
    delete MyDialog;

    return addChange;
}

string getNewName(){
    string newName;
    Gtk::Dialog *MyDialog = new Gtk::Dialog();
    MyDialog->set_title("New Name");
    std::vector<std::string> buttons = {"OK"};
    for (int i = 0; i < buttons.size(); i++)
           MyDialog->add_button(buttons[i], i);

    Gtk::Entry *MyEntry = Gtk::manage(new Gtk::Entry());
    MyEntry->set_text("Enter new name");
    MyEntry->set_max_length(50);
    MyEntry->show();
    MyDialog->get_vbox()->pack_start(*MyEntry);

    int result = MyDialog->run();


    newName = MyEntry->get_text();

    MyDialog->close();
    delete MyDialog;


    return newName;
}

int getNewPrice(){
    int newPrice;
    Gtk::Dialog *MyDialog = new Gtk::Dialog();
    MyDialog->set_title("New Price");
    std::vector<std::string> buttons = {"OK"};
    for (int i = 0; i < buttons.size(); i++)
           MyDialog->add_button(buttons[i], i);

    Gtk::Entry *MyEntry = Gtk::manage(new Gtk::Entry());
    MyEntry->set_text("Enter new Coke Price");
    MyEntry->set_max_length(50);
    MyEntry->show();
    MyDialog->get_vbox()->pack_start(*MyEntry);

    int result = MyDialog->run();


    newPrice = stoi(MyEntry->get_text());

    MyDialog->close();
    delete MyDialog;

    return newPrice;
}
