// // with_out Open/Closed Principle
// #inlcude <bits/stdc++.h>
// using namespace std;
// #define int long long 
// class Shape{
//     private:
//         String type;
//     public:
//         double CalculateArea(){
//             if(type=="circle"){
//                 //TODO circle Area Calculation    
//             }
//             else if(type=="rectangle"){
//                 //TODO rectangle area calculation
//             }
//              else{
//                // TODO ADD new Shape Tightly Coupled    
//              }
//         }   
// };

// int32_t main(){
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     int T;cin>>T;
//     while(T--){

//     }
// }


#include <bits/stdc++.h>
using namespace std;
#define int long long 

class Shape{
    public:
    virtual void CalculateArea() = 0; 
    virtual ~Shape() {}
};

class Circle : public Shape{
    private:
        int radius;
    public:
        Circle(int r) : radius(r) {}
        void CalculateArea() override{
            cout << 3.14159 * radius * radius << endl;        
        }
};

class Rectangle : public Shape{
    private:
        int length, breadth;
    public:
        Rectangle(int l, int b) : length(l), breadth(b) {}
        void CalculateArea() override{
            cout << length * breadth << endl;
        }
};


class Triangle: public Shape{
    private:
        int base,height;
    public:
    Triangle(int b,int h): base(b),height(h){}
    void CalculateArea() override{
        cout<<0.5*base*height<<endl;
    }
};
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    while(T--){
        int l, b;
        cin >> l >> b;
        Shape *s1 = new Rectangle(l, b);
        s1->CalculateArea();
        delete s;

        int r;
        cin>>r;
        Shape *s2 = new Circle(r);
        s2->CalculateArea();
        delete s2;
        

        int b,h;
        cin>>b>>h;
        Shape *s3 = new Triangle(b,h);
        s3->CalculateArea();
        delete s3;
    }
    return 0;
}