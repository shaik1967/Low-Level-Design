// Observer Design Pattern
//one object contain a list of dependent classes and notify them of any state changes

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Subscriber{
    public:
        virtual void update(string &video)=0;
};

class YoutubeSubcriber: public Subscriber{
    public:
        void update(string &video){
            cout << "Youtube Subcriber: " << video << endl;
        }
};

class EmailSubscriber: public Subscriber{
    public:
        void update(string &video){
            cout << "Email Subcriber: " << video << endl;
        }
};

class YoutubeChannel{
    public:
        string video;
        vector<Subscriber*>subscribers;
        void subscribe(Subscriber *s){
            subscribers.push_back(s);
        }
        void uploadVideo(string v){
            video = v;
            notifysubscribers();
        }
        void notifysubscribers(){
            for(auto &s:subscribers){
                s->update(video);
            }
        }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    YoutubeSubcriber *y= new YoutubeSubcriber();
    EmailSubscriber *e= new EmailSubscriber();
    YoutubeChannel c;
    c.subscribe(y);
    c.subscribe(e);
    c.uploadVideo("Observer Design Pattern Tutorial");

    return 0;
}