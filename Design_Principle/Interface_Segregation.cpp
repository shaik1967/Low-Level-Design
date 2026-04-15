// without Interface Segregation Principle
// #include <bits/stdc++.h>
// using namespace std;
// class Machine{
//     public:
//         virtual void scanner()=0;
//         virtual void printer()=0;
//         virtual void FaxMachine()=0;
// };
// class All_in_One_Printer: public Machine{
//     public:
//         void scanner(){
//             cout<<"Scan"<<endl;
//         }
//         void printer(){
//             cout<<"Print"<<endl;
//         }
//         void FaxMachine(){
//             cout<<"Fax"<<endl;
//         }
// };

// class Basic_Printer: public Machine{
//     public:
//         void scanner(){
//             // Not feasible - forced to implement unwanted method
//             throw runtime_error("No Scanning Available");
//         }
//         void printer(){
//             cout<<"Print"<<endl;
//         }
//         void FaxMachine(){
//             // Not feasible - forced to implement unwanted method
//             throw runtime_error("No Fax Available");
//         }
// };


// With Interface Segregation Principle
// Better with less forced implementation with each class
#include <bits/stdc++.h>
using namespace std;

// Separate interfaces for each functionality
class IPrinter {
    public:
        virtual void print() = 0;
        virtual ~IPrinter() {}
};

class IScanner {
    public:
        virtual void scan() = 0;
        virtual ~IScanner() {}
};

class IFax {
    public:
        virtual void fax() = 0;
        virtual ~IFax() {}
};

// All-in-one implements all interfaces
class AllInOnePrinter : public IPrinter, public IScanner, public IFax {
    public:
        void print() override {
            cout << "Print" << endl;
        }
        void scan() override {
            cout << "Scan" << endl;
        }
        void fax() override {
            cout << "Fax" << endl;
        }
};

// Basic printer only implements what it needs
class BasicPrinter : public IPrinter {
    public:
        void print() override {
            cout << "Print" << endl;
        }
};

int main() {
    AllInOnePrinter allInOne;
    allInOne.print();
    allInOne.scan();
    allInOne.fax();

    BasicPrinter basic;
    basic.print();
    // basic.scan(); // Not available - no forced implementation!

    return 0;
}+