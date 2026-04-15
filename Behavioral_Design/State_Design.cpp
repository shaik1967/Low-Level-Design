// #include <iostream>
// #include <string>
// #include <vector>
// using namespace std;
// #define int long long


// class TrafficLight{
//     private:
//         string color;
//     public:
//         TrafficLight(string color){
//             this->color=color;
//         }
//         void next(){
//             if(color=="RED"){
//                 color="Green";
//                 cout<<"Green"<<endl;
//             }
//             else if(color=="GREEN"){
//                 color="Yellow";
//                 cout<<"Yellow"<<endl;
//             }
//             else if (color=="YELLOW"){
//                 color="RED";
//                 cout<<"Red"<<endl;
//             }
//             //  it becomes bloated as it become higher and higher.
//         }
// };

// int32_t main(){
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     int T;T=1;
//     while(T--){
//         TrafficLight *trafficlight= new TrafficLight("RED");
//         trafficlight->next();
//         trafficlight->next();
//         trafficlight->next();
//     }
//     return 0;
// }


// #include <iostream>
// #include <string>
// using namespace std;
// #define int long long

// class TrafficLightContext;
// class TrafficLightState{
//     private:
//         string color;
//     public:
//         virtual void next(TrafficLightContext *context) = 0;
//         void setcolor(string color){
//             this->color=color;
//         }
//         string getColor(){
//             return this->color;
//         }
// };
// class GreenState;
// class RedState;
// class YellowState;

// class TrafficLightContext{
//     private:
//         TrafficLightState *tls;
//     public:
//         TrafficLightContext();
//         void SetState(TrafficLightState *tls){
//             this->tls= tls;
//         }
//         void next(){
//             tls->next(this);
//         }
// };

// class RedState: public TrafficLightState{
//     public:
//         RedState(){
//             cout<<"Now it is RedColor"<<endl;
//             this->setcolor("Red");
//         }
//         void next(TrafficLightContext *context) override;
// };

// class GreenState: public TrafficLightState{
//     public:
//         GreenState(){
//             cout<<"Now it is GreenColor"<<endl;
//             this->setcolor("Green");
//         }
//         void next(TrafficLightContext *context) override;
// };

// class YellowState: public TrafficLightState{
//     public:
//         YellowState(){
//             cout<<"Now it is YellowColor"<<endl;
//             this->setcolor("Yellow");
//         }
//         void next(TrafficLightContext *context) override;
// };

// void RedState::next(TrafficLightContext *context){
//     context->SetState(new GreenState());
// }

// void GreenState::next(TrafficLightContext *context){
//     context->SetState(new YellowState());
// }

// void YellowState::next(TrafficLightContext *context){
//     // here we can add the logic so that something like blinking which makes our code more modular
//     context->SetState(new RedState());
// }

// TrafficLightContext::TrafficLightContext(){
//     this->tls = new RedState();
// }

// int32_t main(){
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     int T;T=1;
//     while(T--){
//         TrafficLightContext *tlc= new TrafficLightContext();
//         tlc->next();
//         tlc->next();
//         tlc->next();
//         tlc->next();
//     }
//     return 0;
// }

// Both State and Prototype Design Patterns/
#include <bits/stdc++.h>
using namespace std;
#define int long long

enum TrafficLightStateType {
    RED,
    GREEN,
    YELLOW
};

class TrafficLightContext;

class TrafficLightState{
    public:
        virtual void next(TrafficLightContext* tlc)=0;
        virtual TrafficLightState* clone()=0;
};

map<TrafficLightStateType, TrafficLightState*> stateMap;
class RedLight: public TrafficLightState{
    public:
        RedLight(){
        }
        RedLight(const RedLight& other){
            cout<<"It is Red Color"<<endl;
        }
        void next(TrafficLightContext* tlc) override;
        TrafficLightState* clone() override{
            return new RedLight(*this);//copy constructor//
        }
};
class GreenLight: public TrafficLightState{
    public:
        GreenLight(){
        }
        GreenLight(const GreenLight& other){
            cout<<"It is Green Color"<<endl;
        }
        void next(TrafficLightContext* tlc) override;
        TrafficLightState* clone() override{
            return new GreenLight(*this);//copy constructor//
        }
};

class YellowLight: public TrafficLightState{
    public:
        YellowLight(){
        }
        YellowLight(const YellowLight& other){
            cout<<"It is Yellow Color"<<endl;
        }
       void next(TrafficLightContext* tlc) override;
       TrafficLightState* clone() override{
            return new YellowLight(*this);//copy constructor//
        }
}; 

class TrafficLightContext{
    TrafficLightState* current;
    public:
        TrafficLightContext(){
            current = stateMap[RED]->clone();
        }
        void next(){
            current->next(this);
        }
        void SetNext(TrafficLightState* state){
            current = state;
        }
};


void RedLight::next(TrafficLightContext* tlc){
    tlc->SetNext(stateMap[GREEN]->clone());
}

void GreenLight::next(TrafficLightContext* tlc){
    tlc->SetNext(stateMap[YELLOW]->clone());
}

void YellowLight::next(TrafficLightContext* tlc){
    tlc->SetNext(stateMap[RED]->clone());
}


int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;T=1;
    while(T--){
        // TrafficLightContext *tlc= new TrafficLightContext();
        // tlc->next();
        // tlc->next();
        // tlc->next();
        // tlc->next();
        //can use prototype design pattern also//
        stateMap[RED] =  new RedLight();
        stateMap[GREEN] =  new GreenLight();
        stateMap[YELLOW] = new YellowLight();
        TrafficLightContext *tlc = new TrafficLightContext();
        tlc->next();
        tlc->next();
        tlc->next();
        tlc->next();
    }
    return 0;
}