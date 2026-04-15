// create only one instance of class
// #include <bits/stdc++.h>
// using namespace std;
// #define int long long
// class Logger{
//     public:
//         void log(string message){
//           cout<<"Log "<<message<<endl;   
//         }
// }

// class Application1{
//     public:
//         void run1(){
//             Logger *logger =new Logger(); // New instance created every time
//             logger->log("Application is running");
//         }
// }

// class Application2{
//     public:
//         void run2(){
//             Logger *logger =new Logger(); // New instance created every time
//             logger->log("Application is running");
//         }
// }


// int32_t main(){
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     int T;cin>>T;
//     while(T--){
//         Application1 app1;
//         Application2 app2;
//         app1.run1();
//         app2.run2();    
//         // there are multiple instances of logger
//     }
// }


// only one instance for database querying
#include <iostream>
#include <string>
#include <mutex>
using namespace std;

class Logger{
    private:
        static Logger *logger;
        static std::mutex mutex;
        Logger() {}  // Private constructor
    public:
        static Logger* getLogger(){
            if(logger == NULL){
                std::lock_guard<std::mutex> lock(mutex);
                if(logger == NULL){
                    logger = new Logger();// only one thread can enter this block
                }
            }
            // thread can come here and return instead of waiting for lock to be released
            return logger;
        }
        void log(string message){
            cout << "Log: " << message << endl;
        }
};

Logger* Logger::logger = NULL;
std::mutex Logger::mutex;
class Application1{
    public:
        void run1(){
            Logger *logger = Logger::getLogger();  // Uses singleton
            cout<<logger<<endl;
            logger->log("Application1 is running");
        }
};

class Application2{
    public:
        void run2(){
            Logger *logger = Logger::getLogger();  // Same instance
            cout<<logger<<endl;
            logger->log("Application2 is running");
        }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;cin>>T;
    while(T--){
        Application1 app1;
        Application2 app2;
        app1.run1();
        app2.run2();    
    }
}