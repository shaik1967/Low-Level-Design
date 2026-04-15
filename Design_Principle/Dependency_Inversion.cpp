// without Dependency Inversion Principle (Tightly Coupled)
// #include <bits/stdc++.h>
// using namespace std;
// 
// class EmailService{
//     public:
//         void sendEmail(string message){
//             cout << message << endl;
//         }
// };  
// 
// class OrderService{
//     private:
//         EmailService emailService;  // Direct dependency - tightly coupled
//     public:
//         OrderService(){
//             // Creating concrete class inside - hard to test/swap
//         }
//         void placeOrder(string orderId){
//             emailService.sendEmail("Order Placed: " + orderId);
//             // Can't easily switch to SMS or other notification service
//         }
// };

#include <bits/stdc++.h>
using namespace std;
#define int long long 
class NotifactionService{
    public:
        virtual void sendNotification(string message) = 0;
        virtual ~NotifactionService() {}
}

class EmailNotificationService: public NotifactionService{
    public:
        void sendNotification(string message) override{
            cout<<"Email Notification "<<message<<endl;
        }
};

class YahooNotificationService: public NotifactionService{
    public:
        void sendNotification(string message) override{
            cout<<"Yahoo Notification "<<message<<endl;
        }
};


class OrderService{
    NotifactionService *notificationservice;
    public:
        OrderService(NotifactionService *notificationservice){
            this->notificationservice = notificationservice;
        }
        void placeOrder(string orderId){
            //Loosely Coupled to Send Notification Testability Increases
            notificationservice->sendNotification("Order Placed: " + orderId);
        }
};
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;cin>>T;
    while(T--){
        OrderService O1= new OrderService(new EmailNotificationService());
        O1.placeOrder("123");

        OrderService O2= new OrderService(new YahooNotificationService());
        O2.placeOrder("123")

    }
}
