#include <bits/stdc++.h>
using namespace std;
#define int long long
class swapper{
    public:
        void swap(int a, int b){
            int temp = a;
            a = b;
            b = temp;
        }
};
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;cin>>T;
    while(T--){
        swapper s;
        s.swap(1,2);
        s.swap(3,4);
    }
}

//Can use logger class to use a single instance of log for the whole class.

// Before DRY Principle

// class SubmitButton{
//     public:
//         void Onclick(){
//             cout<<"Form Submitted"<<endl;
//         }
//         void animation(){
//             cout<<"Made Animation"<<endl;
//         }
// };

// class CancelButton{
//     public:
//         void Onclick(){
//             cout<<"Form Cancelled"<<endl;
//         }
//         void animation(){
//             cout<<"Made Animation"<<endl;
//         }
// };


//Instead of duplicating animation function we can use 

class Button{
    public:
        virtual void Onclick() = 0;
        void animation(){
            cout<<"Made Animation"<<endl;
        }
        void render(){
            cout << "Made Rendering" << endl;
        }
        virtual ~Button() {}
};

class SubmitButton: public Button{
    public:
        void Onclick() override {
            cout << "Form Submitted" << endl;
        }
};

class CancelButton: public Button{
    public:
        void Onclick() override {
            cout << "Cancelled Form" << endl;
        }
};
