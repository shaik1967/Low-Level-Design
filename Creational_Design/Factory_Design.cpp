//Factory Design Pattern nothing but centralizes object creation
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
#define int long long

class Vehicle{
    public:
        virtual ~Vehicle() {}  // Virtual destructor for safe polymorphic deletion
        virtual void start() = 0;
        virtual void stop() = 0;
};


class Car:public Vehicle{
    public:
        void start() override{
            cout<<"Car is starting"<<endl;
        }
        void stop() override{
            cout<<"Car is stoping"<<endl;
        }
};

class Truck:public Vehicle{
    public:
        void start() override{
            cout<<"Truck is starting"<<endl;
        }
        void stop() override{
            cout<<"Truck is stoping"<<endl;
        }
};

class Bike: public Vehicle{
    public:
        ~Bike(){};
        void start() override{
            cout<<"Bike is starting"<<endl;
        }
        void stop() override{
            cout<<"Bike is stoping"<<endl;
        }
};

class VehicleFactory{
    public:
        Vehicle *createVehicle(string p){
            // I will know which vehicle to create based on the input
            // I donot want to know inner implementation of how the object is made nothing but encapsulation
            if(p=="Car"){
                return new Car();
            }
            else if(p=="Truck"){
                return new Truck();
            }
            else if(p=="Bike"){
                return new Bike();
            }
            else{
                throw runtime_error("No Vehicle found with this specifications");
            }
        }
};
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;cin>>T;
    while(T--){
        VehicleFactory v;
        Vehicle *car = v.createVehicle("Car");
        car->start();
        car->stop();

        Vehicle *Truck =v.createVehicle("Truck");
        Truck->start();
        Truck->stop();

        Vehicle *Bike =v.createVehicle("Bike");
        Bike->start();
        Bike->stop();
        try{
            Vehicle *Bus =v.createVehicle("Bus");
        }
        catch(exception &e){
            cout<<e.what()<<endl;
        }
        delete car;
        delete Truck;
        delete Bike;
    }
}