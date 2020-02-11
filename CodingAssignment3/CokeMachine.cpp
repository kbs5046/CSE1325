// Khom B Sitaula (1001605046)

#include <iostream>
#include <string>

#include "CokeMachine.h"
#include "CokeLib.h"

using namespace std;

CokeMachine::CokeMachine(std::string name, int cost, int change, int inventory)
                    : machineName{name}, CokePrice{cost}, changeLevel{change}, inventoryLevel{inventory}
                    {
                        maxChangeCapacity = 5000;
                        maxInventoryCapacity = 100;
                    }

CokeMachine::~CokeMachine(){
    std::cout <<"CokeMachine "<<machineName<< " has been destroyed"<<std::endl;

}

std::string CokeMachine ::getMachineName(void) const{
            return machineName;
}

bool CokeMachine ::buyACoke(int payment, std::string* change, int* action){
            if (payment > CokePrice && (payment-CokePrice)<=changeLevel){
                *action = 0;
                --inventoryLevel;
                changeLevel = changeLevel + CokePrice;
                *change = displayMoney(payment-CokePrice);
                return 1;
            }
            else if (payment == CokePrice && (payment-CokePrice)<=changeLevel){
                *action = 1;
                --inventoryLevel;
                changeLevel = changeLevel + CokePrice;
                *change = displayMoney(payment-CokePrice);
                return 1;
            }
            else if (payment < CokePrice){
                *action = 2;
                *change = displayMoney(payment);
                return 1;
            }
            else if (payment > changeLevel){
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

std::string CokeMachine ::getChangeLevel(){
            return displayMoney(changeLevel);
}

bool CokeMachine ::incrementChangeLevel(int amountToAdd){
            if ((changeLevel + amountToAdd) < maxChangeCapacity){
                changeLevel = changeLevel + amountToAdd;
                return 1;
            }
            else {
                return 0;
            }
}

std::string CokeMachine ::getMaxChangeCapacity(void){
            return displayMoney(maxChangeCapacity);
}

std::string CokeMachine ::getCokePrice(void){
            return displayMoney(CokePrice);
}

std::string CokeMachine ::displayMoney(int amount){
            std::string dollars{std::to_string(amount/100)};
            std::string cents{std::to_string(std::abs(amount%100))};
            return ((dollars.size()==1 ? "0":"")+dollars+"."+(cents.size()==1 ? "0":"")+cents);
}

void CokeMachine ::setMachineName(std::string N_name){
            machineName = N_name;
}

void CokeMachine ::setCokePrice(int price){
            CokePrice = price;
}

ostream& operator<<(ostream& out, CokeMachine& temp){
         out <<"\n\nCurrent Inventory Level:\t"<< temp.inventoryLevel << endl;
		 out <<"Max Inventory Capacity:\t"<< temp.maxInventoryCapacity << endl << endl;
         out <<"Current Change Level:\t$"<< temp.displayMoney(temp.changeLevel) << endl;
		 out <<"Max Change Capacity:\t$"<< temp.displayMoney(temp.maxChangeCapacity) << endl << endl;
		 out <<"Current Coke Price is:\t$"<< temp.displayMoney(temp.CokePrice) << endl;
		return out;
}

std::string  CreateCokeOutputLine (const CokeMachine& temp){
         ostringstream getout;
         getout << temp.machineName <<" | "<< temp.CokePrice <<" | "<< temp.changeLevel <<" | "<< temp.inventoryLevel << endl;
         return getout.str();
		// return machineName << "|" << cokePrice << "|" << changeLevel << "|" << inventoryLevel << endl;
}



