#include <bits/stdc++.h>
using namespace std;
#define int long long
class BreadBaker{
    public:
        void bakeBread(){
            cout<<"Baking Bread"<<endl;
        }
}; 

class InventoryManager{
    public:
        void manageInventory(){
            cout<<"Managing Inventory"<<endl;
        }
};

class SupplyOrder{
    public:
        void placeSupplyOrder(){
            cout<<"Placing Supply Order"<<endl;
        }
};

class CustomerService{
    public:
        void CustomerService(){
            cout<<"Customer Service"<<endl;
        }
};

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;cin>>T;
    while(T--){ 
        BreadBaker breadBaker;
        InventoryManager inventoryManager;
        SupplyOrder supplyOrder;
        CustomerService customerService;

        //Each class has single responsibility
        //Maintalability one class has no influence on the other class
        breadBaker.bakeBread();
        inventoryManager.manageInventory();
        supplyOrder.placeSupplyOrder();
        customerService.CustomerService();

    }
}