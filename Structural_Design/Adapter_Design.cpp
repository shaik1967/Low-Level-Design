 // connection's method can be different but the interface is same 
 // we had the functionality but we can adopt to the method that we want 

#include <iostream>
#include <string>
using namespace std;

class AirConditioner{
    public:
        void ConnectViaBluetooth(){
            cout<<"Air Conditioner Connected via Bluetooth"<<endl;
        }
        void ConnectViaWiFi(){
            cout<<"Air Conditioner Connected via WiFi"<<endl;
        }
        void DisconnectviaBluetooth(){
            cout<<"Air Conditioner Disconnected via Bluetooth"<<endl;
        }
        void DisconnectviaWiFi(){
            cout<<"Air Conditioner Disconnected via WiFi"<<endl;
        }
};

class SmartDevice{
    public:
        virtual void turnOn()=0;
        virtual void turnOff()=0;
};

class AirConditionerAdapter{
    public:
        AirConditioner *airConditioner;
        AirConditionerAdapter(AirConditioner* airConditioner){
            this->airConditioner = airConditioner;
        }
        void Connect(){
            airConditioner->ConnectViaBluetooth();
            cout<<"Air Conditioner Connected"<<endl;
        }
        void Disconnect(){
            airConditioner->DisconnectviaBluetooth();
            cout<<"Air Conditioner Disconnected"<<endl;
        }
};
 int main(){
    AirConditionerAdapter *airConditionerAdapter(new AirConditionerAdapter(new AirConditioner()));
    airConditionerAdapter->Connect();
    airConditionerAdapter->Disconnect();
    return 0;
 }