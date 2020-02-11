// Khom B Sitaula (1001605046)

#ifndef COKE_MACHINE_H
#define COKE_MACHINE_H

#include<iostream>
#include<vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

class CokeMachine{

    public:
        CokeMachine(std::string name = "New Machine", int cost = 50, int change = 500, int inventory = 100);

        ~CokeMachine();

        std::string getMachineName(void) const;

        bool buyACoke(int payment, std::string* change, int* action);

        int getInventoryLevel();

        int getMaxInventoryCapacity();

        bool incrementInventory(int amountToAdd);

        std::string getChangeLevel();

        bool incrementChangeLevel(int amountToAdd);

        std::string getMaxChangeCapacity(void);

        std::string getCokePrice(void);

        std::string displayMoney(int amount);

        void setMachineName(std::string N_name);

        void setCokePrice(int price);

        friend std::ostream& operator<<(std::ostream& out, CokeMachine& temp);

        friend std::string CreateCokeOutputLine(const CokeMachine& temp);


    private :
        std::string machineName;
        int changeLevel;
        int maxChangeCapacity;
        int CokePrice;
        int inventoryLevel;
        int maxInventoryCapacity;

};
#endif
