class CokeMachine{

    public:
        CokeMachine(std::string name, int cost, int change, int inventory)
            : machineName{name}
        {

            CokePrice = cost;
            changeLevel = change;
            inventoryLevel = inventory;
        }


        std::string getMachineName(void) const{
            return machineName;
        }

        bool buyACoke(int payment, std::string* change, int* action){
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

        int getInventoryLevel(){
            return inventoryLevel;
        }

        int getMaxInventoryCapacity(){
            return maxInventoryCapacity;
        }

        bool incrementInventory(int amountToAdd){
            if ((getInventoryLevel() + amountToAdd) <= maxInventoryCapacity){
                    inventoryLevel = inventoryLevel + amountToAdd;
                return 1;
            }
            else{
                return 0;
            }
        }

        std::string getChangeLevel(){
            return displayMoney(changeLevel);
        }

        bool incrementChangeLevel(int amountToAdd){
            if ((changeLevel + amountToAdd) < maxChangeCapacity){
                changeLevel = changeLevel + amountToAdd;
                return 1;
            }
            else {
                return 0;
            }
        }

        std::string getMaxChangeCapacity(void){
            return displayMoney(maxChangeCapacity);
        }

        std::string getCokePrice(void){
            return displayMoney(CokePrice);
        }

        std::string displayMoney(int amount){
            std::string dollars{std::to_string(amount/100)};
            std::string cents{std::to_string(std::abs(amount%100))};
            return ((dollars.size()==1 ? "0":"")+dollars+"."+(cents.size()==1 ? "0":"")+cents);
        }


    private :
        std::string machineName;
        int changeLevel;
        int maxChangeCapacity{5000};
        int CokePrice;
        int inventoryLevel;
        int maxInventoryCapacity{100};

};
