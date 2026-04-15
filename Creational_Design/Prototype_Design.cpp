#include <iostream>
#include <string>
using namespace std;

class Bullet{
    public:
        virtual ~Bullet() {}
        virtual Bullet* clone() const = 0;
};

class SimpleBullet: public Bullet{  
    public:
        class SimpleBulletbuilder;
    private:
        string bulletName;
        long long bulletDamagePower;
        long long bulletSpeed;
        long long bulletfirepower;
        SimpleBullet(SimpleBulletbuilder *builder);
    public:
        string get_bulletName(){ return bulletName; }
        long long get_bulletDamagePower(){ return bulletDamagePower; }
        long long get_bulletSpeed(){ return bulletSpeed; }
        long long get_bulletfirepower(){ return bulletfirepower; }

        class SimpleBulletbuilder{
            private:
                string bulletName;
                long long bulletDamagePower = 0;
                long long bulletSpeed = 0;
                long long bulletfirepower = 0;
                friend class SimpleBullet;
            public:
                SimpleBulletbuilder *set_bulletName(string name){
                    this->bulletName = name;
                    return this;
                }
                SimpleBulletbuilder *set_bulletDamagePower(long long val){
                    this->bulletDamagePower = val;
                    return this;
                }
                SimpleBulletbuilder *set_bulletSpeed(long long val){
                    this->bulletSpeed = val;
                    return this;
                }
                SimpleBulletbuilder *set_bulletfirepower(long long val){
                    this->bulletfirepower = val;
                    return this;
                }
                SimpleBullet *build(){
                    return new SimpleBullet(this);
                }
        };
        SimpleBullet* clone() const override{
            return new SimpleBullet(*this);
        }
};

SimpleBullet::SimpleBullet(SimpleBulletbuilder *builder){
    this->bulletName = builder->bulletName;
    this->bulletDamagePower = builder->bulletDamagePower;
    this->bulletSpeed = builder->bulletSpeed;
    this->bulletfirepower = builder->bulletfirepower;
}


class GoodBullet: public Bullet{  
    public:
        class GoodBulletbuilder;
    private:
        string bulletName;
        long long bulletDamagePower;
        long long bulletSpeed;
        long long bulletfirepower;
        GoodBullet(GoodBulletbuilder *builder);
    public:
        string get_bulletName(){ return bulletName; }

        class GoodBulletbuilder{
            private:
                string bulletName;
                long long bulletDamagePower = 0;
                long long bulletSpeed = 0;
                long long bulletfirepower = 0;
                friend class GoodBullet;
            public:
                GoodBulletbuilder *set_bulletName(string name){
                    this->bulletName = name;
                    return this;
                }
                GoodBulletbuilder *set_bulletDamagePower(long long val){
                    this->bulletDamagePower = val;
                    return this;
                }
                GoodBulletbuilder *set_bulletSpeed(long long val){
                    this->bulletSpeed = val;
                    return this;
                }
                GoodBulletbuilder *set_bulletfirepower(long long val){
                    this->bulletfirepower = val;
                    return this;
                }
                GoodBullet *build(){
                    return new GoodBullet(this);
                }
        };
        GoodBullet* clone() const override{
            return new GoodBullet(*this);
        }
};

GoodBullet::GoodBullet(GoodBulletbuilder *builder){
    this->bulletName = builder->bulletName;
    this->bulletDamagePower = builder->bulletDamagePower;
    this->bulletSpeed = builder->bulletSpeed;
    this->bulletfirepower = builder->bulletfirepower;
}

int main(){
    SimpleBullet::SimpleBulletbuilder *simplebulletbuilder = new SimpleBullet::SimpleBulletbuilder();
    SimpleBullet *simplebullet = simplebulletbuilder->set_bulletName("SimpleBullet")->set_bulletDamagePower(10)->set_bulletSpeed(10)->set_bulletfirepower(10)->build();
    SimpleBullet *simplebullet2 = simplebullet->clone();
    cout << simplebullet2->get_bulletName() << endl;
    cout << simplebullet2->get_bulletDamagePower() << endl;
    
    delete simplebulletbuilder;
    delete simplebullet;
    delete simplebullet2;
    return 0;
}