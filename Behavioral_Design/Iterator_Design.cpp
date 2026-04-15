// Playlist Iterator to shuffle the songs so to be my favorite collection
//More modular following open closed principle

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class PlayListIterator{
    public:
        virtual Playlist* next()=0;
        virtual bool hasNext()=0;
        int index;
};

class Playlist{
    public:
        vector<string>songs;
        void addsong(string &name){
            songs.push_back(name);
        }
        PlayListIterator* createIterator(string type){
            switch(type):
                case "Simple":
                    return new SimplePlaylistIterator(this);
                case "Shuffle":
                    return new ShufflePlaylistIterator(this);
                case "Favorite":
                    return new ShufflePlaylistIterator(this);
                default:
                    return NULL;
        }

};

class SimplePlaylistIterator: public PlayListIterator{
    Playlist* playlist;
    public:
        SimplePlaylistIterator(Playlist* playlist){
            this->playlist=playlist;
            index=0;
        }
        bool hasNext() override{
            if(index<playlist->size()){
                return true;
            }
            return false;
        }
        Playlist* next() override{
            return playlist->songs[index++];
        }
};  

class ShufflePlaylistIterator: public PlayListIterator{
    Playlist *playlist:
    public:
        ShufflePlaylistIterator(Playlist* playlist){
            this->playlist=shuffle(playlist);
            index=0;
        }
        bool hasNext() override{
            if(index<playlist->size()){
                return true;
            }
            return false;
        }
        Playlist* next() override{
            return playlist->songs[index++];
        }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Playlist p;
    p.addsong("priyatama");
    p.addsong("kurchi");
    PlayListIterator *it=p.createIterator("Shuffle");
    while(it->hasNext()){
        cout<<it->next()<<endl;
    }
    return 0;
}