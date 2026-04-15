// with_out Liskov_Substitution
// #include <bits/stdc++.h>
// using namespace std;
// #define int long long

// class Vehile{
//     public:
//         virtual void StartEngine()=0;
// };  

// class Car: public Vehicle{
//     public:
//         void StartEngine() override{
//             cout<<"Car Engine Started"<<endl;
//         }
// };


// //Bicycle doesnot have class StartEngine as it doesnot have engine...
// class Bicycle: public Vehicle{
//     public:
//         void StartEngine() override{
//             Throw an exception with an issue.
//             cout<<"Bicycle Engine Started"<<endl;
//         }
// };


#include <bits/stdc++.h>
using namespace std;

class Vehicle{
    public: 
        virtual void move() = 0;
        virtual ~Vehicle() {}
};

class EngineVehicle: public Vehicle{
    public:
        virtual void StartEngine() = 0;
        virtual ~EngineVehicle() {}
};

class NonEngineVehicle: public Vehicle{
};

class Car: public EngineVehicle{
    public:
        void move() override {
            cout << "Car Moved" << endl;
        }
        void StartEngine() override {
            cout << "Car Engine Started" << endl;
        }
};

class Bicycle: public NonEngineVehicle{
    public:
        void move() override {
            cout << "Bicycle Moved" << endl;
        }
};

int main(){
    Vehicle* car = new Car();
    Vehicle* bicycle = new Bicycle();
    
    car->move();
    bicycle->move();
    
    // Both can substitute Vehicle seamlessly - LSP satisfied
    // No try catch error is required
    // Child is now really the parent without an exceptions
    
    delete car;
    delete bicycle;
    return 0;
}
