// This is the Class Diagram Link:-https://excalidraw.com/#json=4M2uFIa1Xvf-c53y7Y_Vb,MM238yjLU5dxiMkvuMWI5Q
#include <thread>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum SeatCategory{
    SILVER,
    GOLD,
    PLATINUM
};

enum BookingStatus{
    CREATED,
    CONFIRMED,
    EXPIRED,
};

class Movie(){
    private:
        int movieId;
        string movieName;
        int movieDurationInSeconds;
    public:
        Movie(int movieId, string movieName, int movieDurationInSeconds):movieId(movieId), movieName(movieName), movieDurationInSeconds(movieDurationInSeconds){}
        int getMovieId(){return movieId;}
        string getMovieName(){return movieName;}
        int getMovieDurationInSeconds(){return movieDurationInSeconds;}

};

class Seat(){
    private:
        int seatId;
        int row;
        SeatCategory seatCategory;
    public:
        Seat(int seatId, int row, SeatCategory seatCategory):seatId(seatId), row(row), seatCategory(seatCategory){}
        int getSeatId(){return seatId;}
        int getRow(){return row;}
        SeatCategory getSeatCategory(){return seatCategory;}

};

class screen(){
    private:
        int screenId;
        string screenName;
        string theatreName;
        vector<Seat*> seats;
    public:
        Screen(int screenId, string screenName,string theatreName, vector<Seat> seats):screenId(screenId), screenName(screenName), TheatreName(TheatreName), seats(seats){}
        int getScreenId(){return screenId;}
        string getScreenName(){return screenName;}
        string TheatreName(){return TheatreName;}
        vector<Seat*> getSeats(){return seats;}
        void addSeat(Seat* seat){
            seats.push_back(seat);
        }
};

class Show(){
    private:
        int showId;
        Screen* screen;
        Movie* movie;
        DateTime startTime;
        DateTime endTime;
    public:
        Show(int showId,screen* screen, Movie* movie, DateTime startTime, DateTime endTime){
            this->showId = showId;
            this->screen = screen;
            this->movie = movie;
            this->startTime = startTime;
            this->endTime = MovieDurationInSeconds+startTime;
        }
};


class Theatre(){
    private:
        int theatreId;
        string theatreName;
        vector<Screen*>screens;
    public:
        Theatre(int theatreId, string theatreName, vector<Screen*> screens):theatreId(theatreId), theatreName(theatreName), screens(screens){}
        void addScreen(Screen* screen){
            screens.push_back(screen);
        }
        vector<Screen*> getScreens(){return screens;}
};

class User(){
    private:
        string userId;
        string email;
    public:
        User(string userId, string email):userId(userId), email(email){}
};

class Booking(){
    private:
        int bookingId;
        User* user;
        Show* show;
        vector<Seat*>seats;
        BookingStatus bookingStatus;
    public:
        Booking(int BookingId, User* user, Show* show, vector<Seat*>seats){
            this->bookingId = bookingId;
            this->user = user;
            this->show = show;
            this->seats = seats;
            this->bookingStatus = CREATED;
        }
        bool isBookingConfirmed(){return bookingStatus == CONFIRMED;}
};

class SeatLock(){
    private:
        Seat* seat;
        Show* show;
        User* lockedBy;
        DateTime locktime;
        int timeoutInSeconds;
    public:
        SeatLock(Seat* seat, Show* show, User* lockedBy, DateTime locktime, int timeoutInSeconds):seat(seat), show(show), lockedBy(lockedBy), locktime(locktime), timeoutInSeconds(timeoutInSeconds){}
        isLockExpired(){return DateTime.now() - locktime > timeoutInSeconds;}
        User* isLockedByUser{
            return lockedBy;
        }
};

class SeatLockManager(){
    private:
        map<Show*,map<Seat*,SeatLock*>>locks;
        std::mutex mtx;
        condition_variable seatLockCV;
    public:
        SeatLock* lockSeats(Show* show, vector<Seat*>seats, User* user) throws Exception{
            std::lock_guard<std::mutex> lock(mtx);
            for(Seat* seat : seats){
                if(locks[show][seat] != nullptr && !locks[show][seat]->isLockExpired()){
                    throw new Exception("Seat already locked");
                }
            }
            for(Seat* seat : seats){
                locks[show][seat] = new SeatLock(seat, show, user, DateTime.now(), 10);
            }
            return locks[show][seat];
        }
        void unlockSeats(Show* show, vector<Seat*>seats){
            std::lock_guard<std::mutex> lock(mtx);
            for(Seat* seat : seats){
                if(locks[show][seat] != nullptr){
                    locks[show][seat] = nullptr;
                }
            }
        }
        vector<Seat*>getLockedSeats (Show* show) throws Exception{
            std::lock_guard<std::mutex> lock(mtx);
            vector<Seat*>lockedSeats;
            for(auto& [seat, lock] : locks[show]){
                if(lock == nullptr || lock->isLockExpired()){
                    throw new Exception("Seat not locked");
                }
            }
            return lockedSeats;
        }
};

int main(){
    return 0;
}