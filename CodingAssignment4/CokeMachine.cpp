// Khom B Sitaula (1001605046)

#include <iostream>
#include <string>

#include "CokeMachine.h"
#include "CokeLib.h"
#include "VendingMachine.h"

using namespace std;

CokeMachine::CokeMachine(std::string name, int cost, int change, int inventory)
                    : CokePrice{cost}, inventoryLevel{inventory}
                    {
                        setMachineName(name);
                        incrementChangeLevel(change);
                    }

CokeMachine::~CokeMachine(){

}

bool CokeMachine ::buyACoke(int payment, std::string* change, int* action){
            int x = getChangeLevel();
            if (payment > CokePrice && (payment-CokePrice)<=x){
                *action = 0;
                --inventoryLevel;
                //x = x + CokePrice;
                incrementChangeLevel(CokePrice);
                *change = displayMoney(payment-CokePrice);
                return 1;
            }
            else if (payment == CokePrice && (payment-CokePrice)<=x){
                *action = 1;
                --inventoryLevel;
                //x = x + CokePrice;
                incrementChangeLevel(CokePrice);
                *change = displayMoney(payment-CokePrice);
                return 1;
            }
            else if (payment < CokePrice){
                *action = 2;
                *change = displayMoney(payment);
                return 1;
            }
            else if (payment > x){
                *action = 3;
                *change = displayMoney(payment);
                return 1;
            }
            else{
                return 0;
            }
}

int CokeMachine ::getInventoryLevel(){
            return inventoryLevel;
}

int CokeMachine ::getMaxInventoryCapacity(){
            return maxInventoryCapacity;
}

bool CokeMachine ::incrementInventory(int amountToAdd){
            if ((getInventoryLevel() + amountToAdd) <= maxInventoryCapacity){
                    inventoryLevel = inventoryLevel + amountToAdd;
                return 1;
            }
            else{
                return 0;
            }
}

std::string CokeMachine ::getCokePrice(void){
            return displayMoney(CokePrice);
}

void CokeMachine ::setCokePrice(int price){
            CokePrice = price;
}

ostream& operator<<(ostream& out, CokeMachine& temp){
         out <<"\n\nCurrent Inventory Level:\t"<< temp.inventoryLevel << endl;
		 out <<"Max Inventory Capacity:\t"<< temp.maxInventoryCapacity << endl << endl;
         out <<"Current Change Level:\t$"<< temp.displayMoney(temp.getChangeLevel()) << endl;
		 out <<"Max Change Capacity:\t$"<< temp.displayMoney(temp.getMaxChangeCapacity()) << endl << endl;
		 out <<"Current Coke Price is:\t$"<< temp.displayMoney(temp.CokePrice) << endl;
		return out;
}

std::string  CreateCokeOutputLine (CokeMachine& temp){
         ostringstream getout;
         getout << temp.getMachineName() <<" | "<< temp.CokePrice <<" | "<< temp.getChangeLevel() <<" | "<< temp.inventoryLevel << endl;
         return getout.str();
}


