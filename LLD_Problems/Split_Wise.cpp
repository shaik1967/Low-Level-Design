#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;

enum SplitType{
    EQUAL,
    PERCENTAGE
};

class User{
    public:
        string name,id;
};

class Split{
    public:
        User* user;
        double amount;
};

class Expense{
    public:
        string description;
        string name;
        double amount;
        User* paidBy;
        vector<User*>participants;
        SplitType splitType;
        vector<Split*>splits;
        Expense(string description,string name,double amount,User* paidBy,vector<User*>participants,SplitType splitType,vector<Split*>splits){
            this->description = description;
            this->name = name;
            this->amount = amount;
            this->paidBy = paidBy;
            this->participants = participants;
            this->splitType = splitType;
            this->splits = splits;
        }
};  

class BalanceSheet{
    public:
        double TotalPaid;
        double TotalExpense;
        map<User*,double> owes;
};

class Group{
    public:
        string id;
        string name;
        set<User*> participants;
        set<Expense*>expenses;
        map<User*,BalanceSheet> balanceSheet;
        void addParticipant(User* user){
            participants.insert(user);
        }
        void addExpense(Expense* expense){
            expenses.insert(expense);
        }
};

class GroupRepository{
    public:
        map<string, Group*> groups;
        virtual void save(Group* group) = 0;
        virtual Group* findbyid(string id) = 0;
};

class InMemoryGroupRepository: public GroupRepository{
    public:
        void save(Group* group){
            groups[group->id] = group;
        }
        Group* findbyid(string id){
            return groups[id];
        }
};


class SplitTypeStrategy{
    public:
        virtual vector<Split*> get_splits(double amount, map<User*, double> metadata) = 0;
};

class EqualSplitStrategy: public SplitTypeStrategy{
    public:
        vector<Split*> get_splits(double amount, map<User*, double> metadata){
            int count = metadata.size();
            double splitAmount = amount / count;
            vector<Split*> result;
            for(auto& pair : metadata){
                Split* split = new Split();
                split->user = pair.first;
                split->amount = splitAmount;
                result.push_back(split);
            }
            return result;
        }
};

class PercentageSplitStrategy: public SplitTypeStrategy{
    public:
        vector<Split*> get_splits(double amount, map<User*, double> metadata){
            vector<Split*> result;
            for(auto& pair : metadata){
                Split* split = new Split();
                split->user = pair.first;
                split->amount = amount * pair.second / 100;
                result.push_back(split);
            }
            return result;
        }
};

class SplitTypeFactory{
    public:
        SplitTypeStrategy* getSplitTypeStrategy(SplitType splitType){
            switch(splitType){
                case EQUAL:
                    return new EqualSplitStrategy();
                case PERCENTAGE:
                    return new PercentageSplitStrategy();
                default:
                    return nullptr;
            }
        }
};


class BalanceSheetService{
    public:
        void updateBalance(double amount, User* paidBy, vector<Split*> splits,Group *group){
            group->balanceSheet[paidBy].TotalPaid += amount;
            for(auto& split : splits){
                group->balanceSheet[split->user].TotalExpense += split->amount;
                if(paidBy != split->user){
                    group->balanceSheet[split->user].owes[paidBy] += split->amount;
                }
            }
        }
};

class ExpenseService{
    BalanceSheetService* balanceSheetService;
    public:
        ExpenseService(){
            this->balanceSheetService=new BalanceSheetService();
        }
        void addExpense(string description, double amount, User* paidBy, SplitType splitType, map<User*, double> metadata, Group* group){
            SplitTypeFactory* factory=new SplitTypeFactory();
            SplitTypeStrategy* strategy=factory->getSplitTypeStrategy(splitType);
            vector<Split*> splits=strategy->get_splits(amount, metadata);
            Expense* expense=new Expense(description, "", amount, paidBy, {}, splitType, splits);
            group->addExpense(expense);
            balanceSheetService->updateBalance(amount, paidBy, splits, group);
        }
};

class MinimumTransactionService{
    public:
        int get_minimum_transactions(Group* group){
            vector<int>values;
            for(auto& entry : group->balanceSheet){
                User* user=entry.first;
                values.push_back(entry.second.TotalExpense - entry.second.TotalPaid);
            }
            int len=values.size();
            vector<int>dp(1<<len,-1e9);
            for(int i=1;i<(1<<len);i++){
                int sum=0;
                for(int j=0;j<len;j++){
                    if(i & (1 << j)){
                        sum+=values[j];
                    }
                }
                if(sum==0){
                    dp[i]=1;
                }
                for(int s=i;s;s=(s-1)&i){
                    dp[i]=max(dp[i], dp[s]+dp[i^s]);
                }
            }
            return len-dp[(1<<len)-1];
        }
};

class GroupService{
    GroupRepository* repo;
    ExpenseService* expenseService;
    MinimumTransactionService* minimumTransactionService;
    public:
        GroupService(GroupRepository* repo){
            this->repo=repo;
            expenseService=new ExpenseService();
            minimumTransactionService=new MinimumTransactionService();
        }
        string creatGroup(string name){
            string id=to_string(repo->groups.size()+1);
            Group* group=new Group();
            group->id=id;
            group->name=name;
            repo->save(group);
            return id;
        }
        void addExpense(string description, double amount, User* paidBy, SplitType splitType, map<User*, double> metadata, string groupId){
            Group * group =repo->findbyid(groupId);
            expenseService->addExpense(description, amount, paidBy, splitType, metadata, group);
        }
        int get_minimum_transactions(string groupId){
            Group * group =repo->findbyid(groupId);
            return minimumTransactionService->get_minimum_transactions(group);
        }
};



int main(){
     InMemoryGroupRepository* repo = new InMemoryGroupRepository();
    GroupService* groupService = new GroupService(repo);
    
    // Create a group
    string groupId = groupService->creatGroup("Trip to Goa");
    cout << "Group ID: " << groupId << endl;
    
    // Create users
    User* sam = new User();
    sam->id = "1";
    sam->name = "Sam";
    
    User* john = new User();
    john->id = "2";
    john->name = "John";
    
    User* alice = new User();
    alice->id = "3";
    alice->name = "Alice";
    
    // Add participants to group (need to add this method to GroupService)
    Group* group = repo->findbyid(groupId);
    group->addParticipant(sam);
    group->addParticipant(john);
    group->addParticipant(alice);
    
    // Create metadata for equal split
    map<User*, double> equalMetadata;
    equalMetadata[sam] = 0;    // Value ignored for equal split
    equalMetadata[john] = 0;
    equalMetadata[alice] = 0;
    
    // Add expense 1: Sam paid 300 for dinner, split equally
    groupService->addExpense("Dinner", 300.0, sam, SplitType::EQUAL, equalMetadata, groupId);
    cout << "Added expense: Dinner (300) paid by Sam, split equally" << endl;
    
    // Create metadata for percentage split
    map<User*, double> percentMetadata;
    percentMetadata[sam] = 50.0;    // 50%
    percentMetadata[john] = 30.0;   // 30%
    percentMetadata[alice] = 20.0;  // 20%
    
    // Add expense 2: John paid 500 for hotel, split by percentage
    groupService->addExpense("Hotel", 500.0, john, SplitType::PERCENTAGE, percentMetadata, groupId);
    cout << "Added expense: Hotel (500) paid by John, split by percentage" << endl;
    
    // Get minimum transactions to settle
    int minTransactions = groupService->get_minimum_transactions(groupId);
    cout << "Minimum transactions to settle: " << minTransactions << endl;
    
    // Print balance sheet
    cout << "\n--- Balance Sheet ---" << endl;
    for(auto& entry : group->balanceSheet){
        User* user = entry.first;
        BalanceSheet& bs = entry.second;
        cout << user->name << ": Paid=" << bs.TotalPaid << ", Owes=" << bs.TotalExpense << endl;
        for(auto& owe : bs.owes){
            cout << "  -> Owes " << owe.first->name << ": " << owe.second << endl;
        }
    }
    
    // Cleanup
    delete sam;
    delete john;
    delete alice;
    delete repo;
    delete groupService;
    
    return 0;
}






