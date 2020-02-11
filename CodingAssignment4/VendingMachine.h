// Khom B Sitaula (1001605046)

#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include<iostream>
#include<vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

class VendingMachine{

    public:
        VendingMachine(std::string name = "", int change = 0);

        ~VendingMachine();

        std::string getMachineName(void) const;

        int getChangeLevel()const;

        bool incrementChangeLevel(int amountToAdd);

        int getMaxChangeCapacity(void) const;

        std::string displayMoney(int amount);

        void setMachineName(std::string N_name);

        virtual int getInventoryLevel() = 0;

        virtual int getMaxInventoryCapacity() = 0;

        virtual bool incrementInventory(int amountToAdd) = 0;

    private :
        std::string machineName;
        int changeLevel;
        int maxChangeCapacity{5000};

};
#endif
