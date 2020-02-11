// Khom B Sitaula (1001605046)

#include <iostream>
#include <string>
#include "VendingMachine.h"

using namespace std;

VendingMachine::VendingMachine(std::string name, int change)
                    : machineName{name}, changeLevel{change}
                    {

                    }
VendingMachine::~VendingMachine(){

}

std::string VendingMachine ::getMachineName(void) const{
            return machineName;
}

int VendingMachine ::getChangeLevel()const{
            return changeLevel;
}

bool VendingMachine ::incrementChangeLevel(int amountToAdd){
            if ((changeLevel + amountToAdd) < maxChangeCapacity){
                changeLevel = changeLevel + amountToAdd;
                return 1;
            }
            else {
                return 0;
            }
}

int VendingMachine ::getMaxChangeCapacity(void) const{
            return maxChangeCapacity;
}

std::string VendingMachine ::displayMoney(int amount){
            std::string dollars{std::to_string(amount/100)};
            std::string cents{std::to_string(std::abs(amount%100))};
            return ((dollars.size()==1 ? "0":"")+dollars+"."+(cents.size()==1 ? "0":"")+cents);
}

void VendingMachine ::setMachineName(std::string N_name){
            machineName = N_name;
}


