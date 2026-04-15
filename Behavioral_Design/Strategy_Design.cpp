//instead of if-else statement we can use this strategy.

#include <iostream>
#include <string>
using namespace std;
class PaymentStrategy{
    public:
        virtual void process_payment()=0;
};

class CreditCardPayment: public PaymentStrategy{
    public:
        void process_payment() override{
            cout << "Processing Credit Card Payment" << endl;
        }
};

class PaypalPayment: public PaymentStrategy{
    public:
        void process_payment() override{
            cout << "Processing PayPal Payment" << endl;
        }
};

class CryptoPayment: public PaymentStrategy{
    public:
        void process_payment() override{
            cout << "Processing Crypto Payment" << endl;
        }
};

class PaymentProcessor{
    private:
        PaymentStrategy *paymentstrategy;
    public:
        PaymentProcessor(PaymentStrategy *paymentstrategy){
            this->paymentstrategy = paymentstrategy;
        }
        ~PaymentProcessor(){
        }
        void SetPaymentStrategy(PaymentStrategy* paymentstrategy){
            this->paymentstrategy = paymentstrategy;
        }
        void process_payment(){
            paymentstrategy->process_payment();
        }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    PaymentStrategy* creditcardpayment = new CreditCardPayment();
    PaymentStrategy* paypalpayment = new PaypalPayment();
    PaymentStrategy* cryptopayment= new CryptoPayment();

    PaymentProcessor *p = new PaymentProcessor(creditcardpayment);
    p->process_payment();

    p->SetPaymentStrategy(paypalpayment);
    p->process_payment();

    p->SetPaymentStrategy(cryptopayment);
    p->process_payment();

    delete p;
    return 0;
}