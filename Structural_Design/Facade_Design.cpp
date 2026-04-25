//the facade class that provides simple interface to the consumers
// the consumer will not be knowing the underlying implementation

#include <iostream>
#include <string>
using namespace std;

enum Player{
    Music,
    Video
};

class MusicPlayer{
    public:
        void initializeAudioDrivers(){
            cout<<"Audio drivers initialized"<<endl;
        }
        void decodeAudio(){
            cout<<"Audio Decoded"<<endl;
        }
        void startPlayback(){
            cout<<"Music playback started"<<endl;
        }
};

class VideoPlayer{
    public:
        void setupRenderingEngine(){
            cout<<"Rendering engine setup"<<endl;
        }
        void loadVideFile(){
            cout<<"Video File Loaded"<<endl;
        }
        void playVideo(){
            cout<<"Video playback started"<<endl;
        }
};



class MediaPlayerFacade{
    private:
    MusicPlayer* musicPlayer;
    VideoPlayer* videoPlayer;
    public:
        MediaPlayerFacade(){
            this->musicPlayer = new MusicPlayer();
            this->videoPlayer = new VideoPlayer();
        }
        ~MediaPlayerFacade(){
            delete musicPlayer;
            delete videoPlayer;
        }
        void performAction(Player player){
            switch(player){
                case Player::Music :
                    musicPlayer->initializeAudioDrivers();
                    musicPlayer->decodeAudio();
                    musicPlayer->startPlayback();
                    break;
                case Player::Video :
                    videoPlayer->setupRenderingEngine();
                    videoPlayer->loadVideFile();
                    videoPlayer->playVideo();
                    break;
                default:
                    cout<<"Invalid player"<<endl;
                    break;
            }
        }
};

int main(){
    MediaPlayerFacade *facade = new MediaPlayerFacade();
    facade->performAction(Player::Music);
    facade->performAction(Player::Video);
    delete facade;
    return 0;
}