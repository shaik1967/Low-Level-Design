// #include <iostream>
// #include <string>
// #include <vector>
// using namespace std;
// #define int long long

// class Bidder{
//     public:
//         string name;
//         int bid;
//         Bidder(string &name){
//             this->name=name;
//         }
//         void PlaceBidwithExtras(int amount,vector<Bidder*> &bidders){
//             for(auto &b:bidders){
//                 if(b!=this){
//                     b->receiveBidWithExtras(this,amount);
//                 }
//             }
//         }
//         void receiveBidWithExtras(Bidder* bidder,int amount){
//             cout<<"Bidder "<<bidder->name<<" has placed a bid of "<<amount<<endl;
//         }
// };


// int32_t main(){
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     int T;T=1;
//     while(T--){
//        Bidder bidder1("Sam");
//        Bidder bidder2("John");
//        Bidder bidder3("Alice");
//        vector<Bidder*> bidders = {&bidder1, &bidder2, &bidder3};
//        bidder1.PlaceBidwithExtras(100, bidders);
//        bidder2.PlaceBidwithExtras(200, bidders);
//        bidder3.PlaceBidwithExtras(300, bidders);
//        /*it is not scalable*/
//     }
//     return 0;
// }


#include <iostream>
using namespace std;
#define int long long

class Bidder{
    public:
        string name;
        Bidder(string name){
            this->name=name;
        }
        void receiveBid(Bidder* bidder,int amount){
            cout<<"Bidder "<<bidder->name<<" has placed a bid of "<<amount<<endl;
        }   
};

class AuctionMediator{
    public:
        vector<Bidder*> bidders;
        virtual void addBidder(Bidder* bidder)=0;
        virtual void removeBidder(Bidder* bidder)=0;
};

class AuctionImpl:public AuctionMediator{
    public:
        void addBidder(Bidder* bidder){
            bidders.push_back(bidder);
        }
        void removeBidder(Bidder* bidder){
            bidders.erase(remove(bidders.begin(), bidders.end(), bidder), bidders.end());
        }
        void placeBid(Bidder* bidder,int amount){
            for(auto b:bidders){
                if(b!=bidder){
                    b->receiveBid(bidder,amount);
                }
            }
        }
};

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;T=1;
    while(T--){
        AuctionImpl auction;
        Bidder *bidder1= new Bidder("Sam");
        Bidder *bidder2= new Bidder("John");
        Bidder *bidder3= new Bidder("Alice");
        auction.addBidder(bidder1);
        auction.addBidder(bidder2);
        auction.addBidder(bidder3);
    }
    return 0;
}