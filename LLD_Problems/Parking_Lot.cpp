#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum VehicleType{
    Bike,
    Truck,
    Car
};

enum DurationType{
    Hour,
    Day
};


class ParkingFeeStrategy{
    public:
        virtual double calculateFee(VehicleType type, int duration, DurationType durationType) = 0;
};

class BasicHourlyRateStrategy: public ParkingFeeStrategy{
    public:
        double calculateFee(VehicleType type, int duration, DurationType durationType) override{
           switch(type){
            case VehicleType::Car:
                return durationType==DurationType::Hour ? duration * 10.0 : duration * 24.0;
            case VehicleType::Truck:
                return durationType==DurationType::Hour ? duration * 20.0 : duration * 48.0;
            case VehicleType::Bike:
                return durationType==DurationType::Hour ? duration * 5.0 : duration * 12.0;
            default:
                return durationType==DurationType::Hour? duration* 8.0 : duration * 11.0;
           }
        }
};

class PremiumRatingStrategy : public ParkingFeeStrategy{
    public:
        double calculateFee(VehicleType type, int duration, DurationType durationType) override{
            switch(type){
            case VehicleType::Car:
                return durationType==DurationType::Hour ? duration * 20.0 : duration * 48.0;
            case VehicleType::Truck:
                return durationType==DurationType::Hour ? duration * 40.0 : duration * 96.0;
            case VehicleType::Bike:
                return durationType==DurationType::Hour ? duration * 10.0 : duration * 24.0;
            default:
                return durationType==DurationType::Hour? duration* 16.0 : duration * 22.0;
           }
        }
};


class Vehicle{
    public:
        string licensetype;
        VehicleType type;
        ParkingFeeStrategy* parkingFeeStrategy;
        Vehicle(string licensetype, VehicleType type, ParkingFeeStrategy* parkingFeeStrategy){
            this->licensetype = licensetype;
            this->type = type;
            this->parkingFeeStrategy = parkingFeeStrategy;
        }
        double calculateFee(int duration, DurationType durationType){
            return parkingFeeStrategy->calculateFee(type, duration, durationType);
        }
};

class CarVehicle: public Vehicle{
    public:
        CarVehicle(string licensetype, ParkingFeeStrategy* parkingFeeStrategy): Vehicle(licensetype, VehicleType::Car, parkingFeeStrategy){}
};

class BikeVehilcle: public Vehicle{
    public:
        BikeVehilcle(string licensetype, ParkingFeeStrategy* parkingFeeStrategy): Vehicle(licensetype, VehicleType::Bike, parkingFeeStrategy){}

};


class TruckVehicle: public Vehicle{
    public:
        TruckVehicle(string licensetype, ParkingFeeStrategy* parkingFeeStrategy): Vehicle(licensetype, VehicleType::Truck, parkingFeeStrategy){}

};

class VehicleFactory{
    public:
        static Vehicle* createVehicle(VehicleType type, string licensetype, ParkingFeeStrategy* parkingFeeStrategy){
            switch(type){
                case VehicleType::Car:
                    return new CarVehicle(licensetype, parkingFeeStrategy);
                case VehicleType::Truck:
                    return new TruckVehicle(licensetype, parkingFeeStrategy);
                case VehicleType::Bike:
                    return new BikeVehilcle(licensetype, parkingFeeStrategy);
                default:
                    return nullptr;
            }
        }
};



class PaymentStrategy{
    public:
        virtual bool processPayment(double amount)= 0;
};

class CashPaymentStrategy: public PaymentStrategy{
    public:
        bool processPayment(double amount){
            cout<<"Processing cash payment of amount: "<<amount<<endl;
            return true;
        }
};

class CreditCardPaymentStrategy: public PaymentStrategy{
    public:
        bool processPayment(double amount){
            cout<<"Processing credit card payment of amount: "<<amount<<endl;
            return true;
        }
};


class ParkingSpot{
    public:
        int spotNumber;
        VehicleType spotType;
        bool is_Occupied;
        Vehicle* vehicle;
        ParkingSpot(int spotNumber, VehicleType spotType):spotNumber(spotNumber), spotType(spotType), is_Occupied(false){}
        virtual bool canParkVehicle(Vehicle *vehicle) = 0;
        bool parkVehicle(Vehicle *vehicle){
            if(is_Occupied){
                throw runtime_error("Cannot Park Vehicle");
            }
            if(!canParkVehicle(vehicle)){
                throw runtime_error("This vechicle cannot be parked here");
            }
            this->vehicle=vehicle;
            this->is_Occupied=true;
            return true;
        }
        bool vacate(){
            if(!is_Occupied){
                throw runtime_error("This Spot is already Vacant");
            }
            is_Occupied = false;
            vehicle = nullptr;
            return true;
        }
};

class CarParkingSpot: public ParkingSpot{
    public:
        CarParkingSpot(int spotNumber):ParkingSpot(spotNumber, VehicleType::Car){}
        bool canParkVehicle(Vehicle *vehicle){
            return vehicle->type == VehicleType::Car;
        }

};

class BikeParkingSpot: public ParkingSpot{
    public:
        BikeParkingSpot(int spotNumber):ParkingSpot(spotNumber, VehicleType::Bike){}
        bool canParkVehicle(Vehicle *vehicle){
            return vehicle->type == VehicleType::Bike;
        }

};

class TruckParkingSpot: public ParkingSpot{
    public:
        TruckParkingSpot(int spotNumber):ParkingSpot(spotNumber, VehicleType::Truck){}
        bool canParkVehicle(Vehicle *vehicle){
            return vehicle->type == VehicleType::Truck;
        }
};

class ParkingLot{
    public:
        vector<ParkingSpot*>parkingSpots;
        ParkingLot(vector<ParkingSpot*> spots):parkingSpots(spots){}
        ParkingSpot* findAvailableSpot(Vehicle *vehicle){
            for(auto &spot:parkingSpots){
                if(!spot->is_Occupied && spot->canParkVehicle(vehicle)){
                    return spot;
                }
            }
            return nullptr;
        }

        ParkingSpot* parkVehicle(Vehicle *vehicle){
            ParkingSpot* spot = findAvailableSpot(vehicle);
            if(spot == nullptr){
                cout<<"No available spot to park the vehicle"<<endl;
                return NULL;
            }
            spot->parkVehicle(vehicle);
            return spot;
        }
        void vacateSpot(ParkingSpot* spot){
            if(!spot->is_Occupied){
                cout<<"This Spot is already Vacant"<<endl;
                return;
            }
            spot->vacate();
        }
};

int main(){
    vector<ParkingSpot*>parkingSpots;
    parkingSpots.push_back(new CarParkingSpot(1));
    parkingSpots.push_back(new BikeParkingSpot(2));
    parkingSpots.push_back(new TruckParkingSpot(3));
 
    ParkingLot *sameer = new ParkingLot(parkingSpots);
    BasicHourlyRateStrategy* p1= new BasicHourlyRateStrategy();
    PremiumRatingStrategy* p2= new PremiumRatingStrategy();
    VehicleFactory vehilceFactory;
    Vehicle *v[4];
    v[0]  = vehilceFactory.createVehicle(VehicleType::Car,"ABC123",p1);
    v[1]  = vehilceFactory.createVehicle(VehicleType::Bike,"DEF456",p2);
    v[2]  = vehilceFactory.createVehicle(VehicleType::Truck,"GHI789",p1);
    v[3] = vehilceFactory.createVehicle(VehicleType::Car,"JKL012",p2);
    PaymentStrategy *cashPaymentStrategy =new CashPaymentStrategy();
    PaymentStrategy *creditCardPaymentStrategy =new CreditCardPaymentStrategy();
    vector<ParkingSpot*>filled_parkedSpots;
    for(int i=0;i<4;i++){
        ParkingSpot* p=sameer->parkVehicle(v[i]);
        if(p==NULL){
            cout<<"No Parking Spot"<<endl;
            continue;
        }
        double amount=v[i]->calculateFee(2, DurationType::Hour);
        cout<<"Amount to be paid: "<<amount<<endl;
        if(i%2)cashPaymentStrategy->processPayment(amount);
        else creditCardPaymentStrategy->processPayment(amount);
        // sameer->vacateSpot(p);
        filled_parkedSpots.push_back(p);
    }
    for(auto &p:filled_parkedSpots){
        sameer->vacateSpot(p);
    }
}

