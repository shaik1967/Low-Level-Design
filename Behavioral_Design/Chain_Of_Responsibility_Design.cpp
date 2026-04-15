#include <bits/stdc++.h>
using namespace std;
#define int long long

class Approver{
    protected: 
        Approver *next;
    public:
        void setnextApprover(Approver *next){
            this->next=next;
        }
        virtual void procesleaverequest(int leavedays)=0;
        bool check(Approver *approver){
            return approver != NULL;
        }
};

class supervisor: public Approver{
    public:
        void procesleaverequest(int leavedays) override{
            if(leavedays <= 3){
                cout << "Supervisor approved the leave...." << endl;
            }
            else if(check(next)){
                next->procesleaverequest(leavedays);
            }
        }
};

class Manager: public Approver{
    public:
        void procesleaverequest(int leavedays) override{
            if(leavedays<=7){
                cout<<"Manager approved the leave...."<<endl;
            }
            else if(check(next)){
                next->procesleaverequest(leavedays);
            }
        }
};

class Director: public Approver{
    public:
        void procesleaverequest(int leavedays) override{
            if(leavedays<=14){
                cout<<"Director approved the leave...."<<endl;
            }
            else if(check(next)){
                next->procesleaverequest(leavedays);
            }
            else{
                cout<<"Leave request cannot be processed...."<<endl;
            }
        }

};

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;T=1;
    while(T--){
        supervisor *sup = new supervisor();
        Manager *man = new Manager();
        Director *dir = new Director();
        sup->setnextApprover(man);
        man->setnextApprover(dir);
        sup->procesleaverequest(5);
    }
    return 0;
}