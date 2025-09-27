#include "Command.h"
using namespace std;

//Command

void SendMessageCommand::execute()
{
    if (room && fromUser){
        room->sendMessage(message, fromUser);
    }
}

void LogMessageCommand::execute()
{
    if (room && fromUser){
        room->saveMessage(message, fromUser);
    }
}

// void ModerateMessageCommand::execute(){
//     if (message.find("snake") != string::npos || message.find("snakes") != string::npos){
//         cout<<"Message blocked due to triggering content: " << message << endl;
//         return;
//     }
// }


void SendNotificationCommand::execute(){
    if (room && fromUser){
        string notification = fromUser->getName() + " has sent a new message in the chat.";
        room->sendMessage(notification, fromUser);
    }
}

//Users

void Users::send(const string &message, ChatRoom *room)
{
    //create command objects, add to queue and then execute command in order
    if (message.find("snake") != string::npos || message.find("snakes") != string::npos){
        cout<<"Message blocked due to triggering content: " << message << endl;
        return;
    }
    addCommand(new SendMessageCommand(room, message, this)); 
    addCommand(new SendNotificationCommand(room, message, this)); //notify other users
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

//ChatRoom

void ChatRoom::registerUser(Users *user)
{
    users.push_back(user);
    cout << user->getName() << " has entered the villa."<< endl;
}

void ChatRoom::sendMessage(const string &message, Users *fromUser)
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
    cout << user->getName() << " has been dumped from the villa."<<endl;
}
