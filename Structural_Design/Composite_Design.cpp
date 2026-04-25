//How we handle for loop component
//specially for tree structures home->floor->room->(different types of appliants)

#include <iostream>
#include <set>
#include <string>
using namespace std;

class SmartComponent{  //common interface for all the components
    public:
        virtual void turnOn()=0;
        virtual void turnOff()=0;
};

class AirConditioner: public SmartComponent{
    public:
        void turnOn() override{
            cout<<"Air Conditioner is Turned On"<<endl;
        }

        void turnOff() override{
            cout<<"Air Conditioner is Turned off"<<endl;
        }
};

class CompositeSmartComponents: public SmartComponent{
    set<SmartComponent*>components;
    public:
        void addComponent(SmartComponent* component){
            components.insert(component);
        }
        void removeComponent(SmartComponent* component){
            components.erase(component);
        }
        void turnOn() override{
            for(auto component:components){
                component->turnOn();
            }
        }
        void turnOff() override{
            for(auto component:components){
                component->turnOff();
            }
        }
};



int main(){
    SmartComponent *ac = new AirConditioner();
    CompositeSmartComponents *room = new CompositeSmartComponents();
    CompositeSmartComponents *floor = new CompositeSmartComponents();
    CompositeSmartComponents *home = new CompositeSmartComponents();
    room->addComponent(ac);
    floor->addComponent(room);
    home->addComponent(floor);
    home->turnOn();
    home->turnOff();
    return 0;
}