//Decorator should implement the same interface as the base type

#include <iostream>
#include <string>
using namespace std;

class Coffee{
    public:
        virtual string getDescription() = 0;
        virtual double  getCost() = 0;
        virtual ~Coffee() = default;
};

class Espresso: public Coffee{
    public:
        string getDescription() override{
            return "Espresso";
        }
        double getCost() override {
            return 2.00;
        }
};

class Cappuccino: public Coffee{
    public:
        string getDescription() override{
            return "Cappuccino";
        }
        double getCost() override{
            return 3.00;
        }
};

class CoffeeDecorator: public Coffee{
    public:
        Coffee *coffee;
        CoffeeDecorator(Coffee *coffee): coffee(coffee){}
        ~CoffeeDecorator() {
            delete coffee;
        }
        string getDescription() override {
            return coffee->getDescription();
        }
        double getCost() override{
            return coffee->getCost();
        }
};

class MilkDecorator: public CoffeeDecorator{
    public:
        MilkDecorator(Coffee *coffee): CoffeeDecorator(coffee){}
        string getDescription() override{
            return coffee->getDescription() + ", Milk";
        }
        double getCost() override{
            return coffee->getCost() + 0.50;
        }
};

class SugarDecorator: public CoffeeDecorator{
    public:
        SugarDecorator(Coffee *coffee): CoffeeDecorator(coffee){}
        string getDescription() override{
            return coffee->getDescription() + ", Sugar";
        }
        double getCost() override{
            return coffee->getCost() + 0.25;
        }
};

class VanillaDecorator: public CoffeeDecorator{
    public:
        VanillaDecorator(Coffee *coffee): CoffeeDecorator(coffee){}
        string getDescription() override{
            return coffee->getDescription() + ", Vanilla";
        }
        double getCost() override{
            return coffee->getCost() + 0.35;
        }
};


int main(){
    Coffee *coffee = new Espresso();
    coffee = new MilkDecorator(coffee);
    coffee = new SugarDecorator(coffee);
    cout<<"Order: "<<coffee->getDescription()<<endl;
    cout<<"Cost: "<<coffee->getCost()<<endl;
    delete coffee;
    return 0;
}