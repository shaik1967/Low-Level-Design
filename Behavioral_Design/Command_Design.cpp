// #include <iostream>
// using namespace std;
// #define int long long
// class TV{
//     public:
//         void TurnOn(){
//             cout<<"Turn on TV"<<endl;
//         }
//         void TurnOff(){
//             cout<<"Turn Off TV"<<endl;
//         }
//         void AdjustVolume(){
//             cout<<"Adjusted Volume to "<<endl;
//         }
//         void TurnOnandAdjustVolume(){
//             TurnOn();
//             AdjustVolume();
//         }
//         TurningOn and AdjustVolume
// };  
// int32_t main(){
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     int T;T=1;
//     while(T--){
//         TV tv;
//         tv.TurnOnandAdjustVolume();
//     }
//     return 0;
// }


#include <iostream>
#include <string>
using namespace std;
#define int long long

class TV{
    public:
        void TurnOn(){
            cout<<"Turn on TV"<<endl;
        }
        void TurnOff(){
            cout<<"Turn Off TV"<<endl;
        }
        void AdjustVolume(int volume){
            cout<<"Adjusted Volume to "<<volume<<endl;
        }
};

class Command{
    public:
        virtual void execute()=0;
};

class TurnOnCommand : public Command{
    private:
        TV* tv;
    public:
        TurnOnCommand(TV* tv){
            this->tv = tv;
        }
        void execute(){
            tv->TurnOn();
        }
};

class TurnOffCommand : public Command{
    private:
        TV* tv;
    public:
        TurnOffCommand(TV* tv){
            this->tv = tv;
        }
        void execute(){
            tv->TurnOff();
        }
};

class AdjustVolumeCommand : public Command{
    private:
        TV* tv;
        int volume;
    public:
        AdjustVolumeCommand(TV* tv, int volume){
            this->tv = tv;
            this->volume = volume;
        }
        void execute(){
            tv->AdjustVolume(volume);
        }
};

class RemoteControl{
    private:
        Command* turnOnCommand;
        Command* turnOffCommand;
        Command* adjustVolumeCommand;
    public:
        RemoteControl(Command* turnOn, Command* turnOff, Command* adjustVolume){
            this->turnOnCommand = turnOn;
            this->turnOffCommand = turnOff;
            this->adjustVolumeCommand = adjustVolume;
        }
        void pressTurnOnButton(){
            turnOnCommand->execute();
        }   
        void pressTurnOffButton(){
            turnOffCommand->execute();
        }
        void pressAdjustVolumeButton(){
            adjustVolumeCommand->execute();
        }
};

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;T=1;
    while(T--){
        TV *tv = new TV();
        Command *turnOn = new TurnOnCommand(tv);
        Command *turnOff = new TurnOffCommand(tv);
        Command *adjustVolume = new AdjustVolumeCommand(tv, 5);
        RemoteControl *remote = new RemoteControl(turnOn,turnOff,adjustVolume);
        remote->pressTurnOnButton();
        remote->pressAdjustVolumeButton();
        remote->pressTurnOffButton();

    }
    return 0;
}