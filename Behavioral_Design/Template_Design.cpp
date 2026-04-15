// #include <bits/stdc++.h>
// using namespace std;
// #define int long long
// class Coffee{
//     public void prepare(){
//         boilingwaiter();
//         brew();
//         pourInCup();
//     }
//     void boilingwaiter(){
//         cout<<"Boiling water"<<endl;
//     }
//     void brew(){
//         cout<<"Brewing coffee"<<endl;
//     }
//     void pourInCup(){
//         cout<<"Pouring coffee in cup"<<endl;
//     }
// };

// class Tea{
//     public void prepare(){
//         boilingwaiter();
//         brew();
//         pourInCup();
//     }
//     void boilingwaiter(){
//         cout<<"Boiling Water"<<endl;
//     }
//     void brew(){
//         cout<<"Stepping tea bag"<<endl;
//     }
//     void pourInCup(){
//         cout<<"Adding lemon"<<endl;
//     }
// };
// int32_t main(){
//     int T;T=1;
//     while(T--){
//         cout<<-1<<endl;
//     }
//     return 0;
// }

// // void boilingwaiter(){
// //         cout<<"Boiling Water"<<endl;
// // }

// // void pourInCup(){
// //     cout<<"Adding lemon"<<endl;
// // }
// // these steps are being repeated 

#include <bits/stdc++.h>
using namespace std;
#define int long long

class beverage{
    public:
        void boilingwater(){
            cout<<"Boiling water"<<endl;
        }
        virtual void brew()=0;
        void pourInCup(){
            cout<<"Pouring in cup"<<endl;
        }
        virtual void addIngredients()=0;
        void recipe(){
            boilingwater();
            brew();
            pourInCup();
            addIngredients();
        }
};

class tea: public beverage{
    public:
        void brew() override{
            cout<<"Steeping tea bag"<<endl;
        }
        void addIngredients() override{
            cout<<"Adding lemon"<<endl;
        }
};

class coffee: public beverage{
    public:
        void brew() override{
            cout<<"Brewing coffee"<<endl;
        }
        void addIngredients() override{
            cout<<"Adding sugar and milk"<<endl;
        }
};
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;T=1;
    while(T--){
        beverage* t= new tea();
        t->recipe();
        cout<<endl;
        beverage* c = new coffee();
        c->recipe();
    }
    return 0;
}