#include <iostream>
#include <string>

#include "CokeMachine.h"

using namespace std;

int main(){
    CokeMachine MyCokeMachine{"CSE 1325 Coke Machine", 50, 500, 100};
    int choice, payment, action, addNum, addChange;
    string change;
    do{
        cout <<"CSE 1325 Coke Machine\n"<<endl;
        cout << "0. Walk away" << endl;
        cout << "1. Buy a Coke" << endl;
        cout << "2. Restore Machine" << endl;
        cout << "3. Add Change" << endl;
        cout << "4. Display Machine Info" << endl;
        cout << "\nEnter choice " << endl;
        cin >> choice;

        switch(choice){
            case 1:
                cout <<"Insert Payment: "<<endl;
                cin >> payment;
                if(MyCokeMachine.buyACoke(payment, &change, &action)){
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
                if (MyCokeMachine.incrementInventory(addNum)){
                    cout <<"Your machine has been restocked"<<endl;
                    cout <<"Your inventory level is now "<<MyCokeMachine.getInventoryLevel()<<endl;
                }
                else {
                    cout <<"You have exceeded your machine's max capacity"<<endl;
                    cout <<"Your inventory level is now "<<MyCokeMachine.getInventoryLevel()<<endl;
                }

                break;
            case 3:
                cout <<"How much change are you adding to the machine?  "<<endl;
                cin >>addChange;
                if (MyCokeMachine.incrementChangeLevel(addChange)){
                    cout <<"Your change has been updated"<<endl;
                    cout <<"Your change level is now "<<MyCokeMachine.getChangeLevel()<<endl;
                }
                else {
                    cout <<"You have exceeded your machine's max change capacity"<<endl;
                    cout <<"Your change level is now "<<MyCokeMachine.getChangeLevel()<<endl;
                }
                break;
            case 4:
                cout <<"\n\nCurrent Inventory Level\t"<<MyCokeMachine.getInventoryLevel()<<endl;
                cout <<"Max Inventory Capacity\t"<<MyCokeMachine.getMaxInventoryCapacity()<<endl;
                cout <<"\nCurrent Change Level\t$"<<MyCokeMachine.getChangeLevel()<<endl;
                cout <<"Max Change Capacity\t$"<<MyCokeMachine.getMaxChangeCapacity()<<endl;
                cout <<"\nCurrent Coke Price is\t$"<<MyCokeMachine.getCokePrice()<<endl;
                break;
            default :
                cout <<"Are you sure you aren't really Thirsty and need a Coke?"<<endl;break;
        }
        cout <<"\n\n";

    }
    while(choice != 0);

}
