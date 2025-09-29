#include "Command.h"
using namespace std;

//Command

void SendMessageCommand::execute()
{
    if (room && fromUser){
        room->sendMessage(message, fromUser);
        room->notifyObservers(message, fromUser);
    }
}

void LogMessageCommand::execute()
{
    if (room && fromUser){
        room->saveMessage(message, fromUser);
    }
}

//Users

void Users::joinRoom(ChatRoom* room){
    chatRooms.push_back(room);
    room->registerUser(this);
}
void Users::leaveRoom(ChatRoom* room){
    vector<ChatRoom*> newRooms;
    for (size_t i=0; i < chatRooms.size(); i++){
        if (chatRooms[i] != room){
            newRooms.push_back(chatRooms[i]);
        }
    }
    chatRooms = newRooms;
    room->removeUser(this);
}

void Users::send(const string &message, ChatRoom *room)
{   
    if (!room) return;
    //create command objects, add to queue and then execute command in order
    if (message.find("snake") != string::npos || message.find("snakes") != string::npos){
        cout<<"Message blocked due to triggering content: " << message << endl;
        return;
    }
    addCommand(new SendMessageCommand(room, message, this)); 
    addCommand(new LogMessageCommand(room, message, this)); //save message command
    executeAll();
}

void Users::receive(const string &message, Users *fromUser, ChatRoom *room)
{
    cout << fromUser->getName() << " to " << name << ": "<< message<<endl;
}
void Users::addCommand(Command *command)
{
    commandQueue.push_back(command);
}
void Users::executeAll()
{
    for (Command* c : commandQueue){
        c->execute();
        delete c;
    }
    commandQueue.clear(); //clear queue after executing all commands
}

void Users::update(const string& message, const string& sender, ChatRoom* room){
    if (sender != name){
        cout << "[Notification] " << sender << " sent a message in " << room->getName() << " : " << message << endl;
    }
}

//ChatRoom

void ChatRoom::registerUser(Users *user)
{   
    bool exists = false;
    for (size_t i=0; i < users.size(); i++){
        if (users[i] == user){
            exists = true;
            break;
        }
    }
    if (!exists){
        users.push_back(user);
        observers.push_back(user);
        cout << user->getName() << " has joined the room " << name << "." << endl;
    }
}

void ChatRoom::sendMessage(const string &message, Users *fromUser) //send to users then notify observers
{
    for (Users* user: users){
        if (user != fromUser){
            user->receive(message,fromUser,this);
        }
    }
}

void ChatRoom::saveMessage(const string &message, Users *fromUser)
{
    chatHistory.push_back(fromUser->getName() + ": " + message);
}

void ChatRoom::removeUser(Users *user)
{
    vector<Users*> newUsers;
    for (size_t i=0; i < users.size(); i++){
        if (users[i] != user){
            newUsers.push_back(users[i]);
        }
    }
    users = newUsers;

    vector<Users*> newObservers;
    for (size_t i=0; i < observers.size(); i++){
        if (observers[i] != user){
            newObservers.push_back(observers[i]);
        }
    }
    observers = newObservers;
    cout << user->getName() << " has left the room."<<endl;
}

void ChatRoom::notifyObservers(const string& message, Users* fromUser){
    for (Users* o:observers){
        if (o != fromUser){
            o->update(message, fromUser->getName(), this);
        }
    }
}