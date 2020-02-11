// Khom B Sitaula (1001605046)

#ifndef COKE_MACHINE_H
#define COKE_MACHINE_H

#include<iostream>
#include<vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "VendingMachine.h"

class CokeMachine : public VendingMachine{

    public:
        CokeMachine(std::string name = "New Machine", int cost = 50, int change = 500, int inventory = 100);

        ~CokeMachine();

        bool buyACoke(int payment, std::string* change, int* action);

        int getInventoryLevel();

        int getMaxInventoryCapacity();

        bool incrementInventory(int amountToAdd);

        std::string getCokePrice(void);

        void setCokePrice(int price);

        friend std::ostream& operator<<(std::ostream& out, CokeMachine& temp);

        friend std::string CreateCokeOutputLine(CokeMachine& temp);


    private :
        int CokePrice;
        int inventoryLevel;
        int maxInventoryCapacity{100};

};
#endif

