// To create complex objects step by step we use this pattern
// Builder pattern is used to create complex objects step by step
// This is Called Chaining


#include <iostream>
#include <string>
using namespace std;

class Car{
    public:
        class CarBuilder{
            private:
        string engine;
        int wheels = 4;
        int seats = 5;
        string color = "Black";
        bool sunroof = false;
        bool airbags = false;
        friend class Car;  // Allow Car to access private members
    public:
        CarBuilder* set_engine(string engine){
            this->engine = engine;
            return this;
        }

        CarBuilder* set_wheels(int wheels){
            this->wheels = wheels;
            return this;
        }

        CarBuilder* setSeats(int seats){
            this->seats = seats;
            return this;  // Fixed: was returning seats
        }

        CarBuilder* setcolor(string color){
            this->color = color;
            return this;
        }

        CarBuilder* setsunroof(bool flag){  // Fixed: removed &
            this->sunroof = flag;
            return this;
        }

        CarBuilder* setairbags(bool flag){  // Fixed: removed &
            this->airbags = flag;
            return this;
        }

        Car* build(){
            return new Car(this);
        }
        };
    private:
        string engine;
        int wheels;
        int seats;
        string color;
        bool sunroof;
        bool airbags;
        Car(CarBuilder* builder){
            this->engine = builder->engine;
            this->wheels = builder->wheels;
            this->seats = builder->seats;
            this->color = builder->color;
            this->sunroof = builder->sunroof;
            this->airbags = builder->airbags;
        }
    public:
        string get_engine() { return engine; }
        int get_wheels() { return wheels; }
        int get_seats() { return seats; }
        string get_color() { return color; }
        bool get_sunroof() { return sunroof; }
        bool get_airbags() { return airbags; }
};



int main(){
    // Car car = new Car("V8",4,5, "Red", true,false);
    // this is not possible for creating more more parameters
    Car::CarBuilder* builder = new Car::CarBuilder();  // Fixed: proper instantiation
    Car* car = builder->set_engine("V8")->set_wheels(4)->setSeats(5)->setcolor("Red")->setsunroof(true)->setairbags(true)->build();
    cout << car->get_engine() << " " << car->get_wheels() << " " << car->get_seats() << " " 
         << car->get_color() << " " << car->get_sunroof() << " " << car->get_airbags() << endl;
    
    delete builder;
    delete car;
}

