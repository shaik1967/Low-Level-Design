// separating the abraction from it's implementation
//something very specific to the class variables 
//In adapter no change in class

#include <iostream>
#include <string>
using namespace std;



class color{
    public:
        virtual void color_Car()=0;
        virtual void color_Bike()=0;
};

class red: public color{
    public:
        void color_Car() override{
            cout<<"Applying red color"<<endl;
        }
        void color_Bike() override{
            cout<<"Applying red color"<<endl;
        }
};

class blue: public color{
    public:
        void color_Car() override{
            cout<<"Applying blue color"<<endl;
        }
        void color_Bike() override{
            cout<<"Applying blue color"<<endl;
        }
};

class Vehicle{
    public:
        color *col;
        Vehicle(color *col){
            this->col = col;
        }
        virtual void color_impl()=0;
};

class Car: public Vehicle{
    public:
        Car(color *col):Vehicle(col){
            cout<<"Car is Created"<<endl;
        }
        void color_impl() override{
            col->color_Car();
        }
};

class Bike: public Vehicle{
    public:
        Bike(color *col):Vehicle(col){
            cout<<"Bike is Created"<<endl;
        }
        void color_impl() override{
            col->color_Bike();
        }
};


int main(){
    color *redColor = new red();
    color *blueColor = new blue();
    Vehicle *car = new Car(redColor);
    Vehicle *bike = new Bike(blueColor);
    car->color_impl();
    bike->color_impl();
    return 0;
}