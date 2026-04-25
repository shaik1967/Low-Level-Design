// Controlling access
// It acts as a gate keeper and handles the main load 

// Video service will only handle the video streaming and not the authentication and ratelimiting etc;

#include <iostream>
#include <string>
#include <map>
using namespace std;

enum UserType{
    BASIC,
    FREE,
    PREMIUM
};

class User{
    public:
        UserType usertype;
        string userId;
        User(UserType usertype, string userId){
            this->usertype = usertype;
            this->userId = userId;
        }
};
class VideoServiceInterface{
    public:
        void playVideo(string videoId){
            cout<<"Video service is playing video"<<endl;
        }
        virtual ~VideoServiceInterface()=default;
};

class RealVideoService: public VideoServiceInterface{
    public:
        void playVideo(string videoId) {
            cout<<"Real video service is playing video"<<endl;
        }
};

class ProxyVideoService: public VideoServiceInterface{
    RealVideoService *realVideoService;
    // can also handle cached videos;
    map<string,string> cachedVideos;
    map<string,int>requestCount;
    public:
        ProxyVideoService(){
            realVideoService = new RealVideoService();
        }
        ~ProxyVideoService(){
            delete realVideoService;
        }
        void playVideo(string videoId,User* user) {
            if(cachedVideos.find(videoId) != cachedVideos.end()){
                cout<<"Playing cached video"<<endl;
            }
            else if(user->usertype == BASIC|| user->usertype == FREE){
                cout<<"Basic or Free user cannot play video"<<endl;
            }
            else if(requestCount[user->userId] >2){
                cout<<"User request limit exceeded"<<endl;
            }
            else{
                requestCount[user->userId]++;
                realVideoService->playVideo(videoId);
            }
        } 
};

int main(){
    User* user1 = new User(UserType::BASIC,"123");
    ProxyVideoService* proxyVideoService = new ProxyVideoService();
    proxyVideoService->playVideo("123",user1);
    delete user1;

    User* user2 = new User(UserType::FREE,"456");
    proxyVideoService->playVideo("456",user2);
    delete user2;

    User* user3 = new User(UserType::PREMIUM,"789");
    proxyVideoService->playVideo("789",user3);
    delete user3;
    delete proxyVideoService;
    return 0;
}


 