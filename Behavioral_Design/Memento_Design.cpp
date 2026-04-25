// #include <iostream>
// #include <string>
// using namespace std;

// class TextEditorTradaitional{
//     public:
//         string text;
//         TextEditorTradaitional(string text){
//             this->text=text;
//         }
//         void setText(string text){
//             this->text=text;
//         }
//         void Undo(string previousState){
//             this->text=previousState;
//         }
//         void showText(){
//             cout<<text<<endl;
//         }
// };

// int main(){
//     TextEditorTradaitional *editor =new TextEditorTradaitional("Hello");
//     editor->showText();
//     //Doing it manually
//     string backup= "Hello";
//     editor->setText("Hello World");
//     editor->showText();
//     editor->Undo(backup);
//     editor->showText();

//     //Doing it manually
//     return 0;
// }

//Undo and Redo using like getting back and front in the states

#include <iostream>
#include <string>

using namespace std;


class Memento{
    public:
        string text;
        Memento(string text){
            this->text=text;
        }
};

class TextEditor{
    public:
        string text;
        TextEditor(string text){
            this->text=text;
        }
        void setText(string text){
            this->text=text;
        }
        Memento *save(){
            return new Memento(text);
        }
        void restore(Memento *memento){
            this->text=memento->text;
        }
};

class History{
    public:
        stack<Memento*> undoHistory,redoHistory;
        void push(Memento *memento){
            undoHistory.push(memento);
        }
        Memento* undo(){
            Memento* memento = undoHistory.top();
            redoHistory.push(memento);
            undoHistory.pop();
            return undoHistory.top();
        }
        Memento *redo(){
            Memento* memento = redoHistory.top();
            undoHistory.push(memento);
            redoHistory.pop();
            return memento;
        }
};
int main(){
    TextEditor* editor =new TextEditor("Hello");
    History* history =new History();
    history->push(editor->save());
    cout<<editor->text<<endl;
    editor->setText("Hello World");
    history->push(editor->save());
    cout<<editor->text<<endl;
    editor->setText("Hello World Again");
    history->push(editor->save());
    cout<<editor->text<<endl;
    editor->setText("Hello World Again and Again");
    history->push(editor->save());
    cout<<editor->text<<endl;
    editor->setText("Hello World Again and Again and Again");
    history->push(editor->save());
    cout<<editor->text<<endl;
    editor->restore(history->undo());
    cout<<editor->text<<endl;
    editor->restore(history->redo());
    cout<<editor->text<<endl;
    editor->restore(history->undo());
    cout<<editor->text<<endl;
    editor->restore(history->undo());
    cout<<editor->text<<endl;
    editor->restore(history->undo());
    cout<<editor->text<<endl;
    return 0;
}