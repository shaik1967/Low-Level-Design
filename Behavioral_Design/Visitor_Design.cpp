// #include <bits/stdc++.h>
// using namespace std;
// #define int long long

// class ChildPatient{
//     public:
//         void diagnosis(){
//             cout<<"Diagnosing a child patient"<<endl;
//         }
//         void billing(){
//             cout<<"Calculating billing for a child patient"<<endl;
//         }
// };

// class AdultPatient{
//     public:
//         void diagnosis(){
//             cout<<"Diagnosing a Adult patient"<<endl;
//         }
//         void billing(){
//             cout<<"Calculating billing for a Adult patient"<<endl;
//         }
//         //surgery
//         //massage
// };

// class SeniorPatient{
//     public:
//         void diagnosis(){
//             cout<<"Diagnosing a Senior patient"<<endl;
//         }
//         void billing(){
//             cout<<"Calculating billing for a Senior patient"<<endl;
//         }
// };


//     }   
//     return 0;
// }

//accept a vistor and he performs the action by himself
// each service is revolving across the patient


#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Forward declarations
class ChildPatient;
class AdultPatient;
class SeniorPatient;

class Visitor{
    public:
        virtual void visit(ChildPatient *patient) = 0;
        virtual void visit(AdultPatient *patient) = 0;
        virtual void visit(SeniorPatient *patient) = 0;
};

class Patient{
    public:
        virtual void accept(Visitor *vis) = 0;
};

class ChildPatient: public Patient{
    public:
        void accept(Visitor *vis) override {
           vis->visit(this);
        }
};

class AdultPatient: public Patient{
    public:
        void accept(Visitor *vis) override {
           vis->visit(this);
        }
};

class SeniorPatient: public Patient{
    public:
        void accept(Visitor *vis) override {
           vis->visit(this);
        }
};

class DiagnosingVisitor: public Visitor{
    public:
        void visit(ChildPatient* p) override {
            cout<<"Diagnosing a Child Patient"<<endl;
        }
        void visit(AdultPatient* p) override {
            cout<<"Diagnosing an Adult Patient"<<endl;
        }
        void visit(SeniorPatient* p) override {
            cout<<"Diagnosing a Senior Patient"<<endl;
        }
};

class BillingVisitor: public Visitor{
    public:
        void visit(ChildPatient* p) override {
            cout<<"Billing a Child Patient"<<endl;
        }
        void visit(AdultPatient* p) override {
            cout<<"Billing an Adult Patient"<<endl;
        }
        void visit(SeniorPatient* p) override {
            cout<<"Billing a Senior Patient"<<endl;
        }
};

int main(){
    ChildPatient* child = new ChildPatient();
    AdultPatient* adult = new AdultPatient();
    SeniorPatient* senior = new SeniorPatient();
    
    DiagnosingVisitor* diagnosingVisitor = new DiagnosingVisitor();
    BillingVisitor* billingVisitor = new BillingVisitor();
    
    child->accept(diagnosingVisitor);
    adult->accept(diagnosingVisitor);
    senior->accept(diagnosingVisitor);
    
    child->accept(billingVisitor);
    adult->accept(billingVisitor);
    senior->accept(billingVisitor);
    
    delete diagnosingVisitor;
    delete billingVisitor;
    
    return 0;
}