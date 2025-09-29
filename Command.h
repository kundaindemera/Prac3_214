#ifndef COMMAND_H
#define COMMAND_H
#include "iostream"
#include "vector"
#include "map"
#include "list"
#include <string>
#include "Observer.h"
using namespace std;

//class ChatRoom;
class Users;

class Command{
    protected:
        ChatRoom* room;
        string message;
        Users* fromUser;
    public:
        Command(ChatRoom* r, string msg, Users* u): room(r), message(msg), fromUser(u) {}
        virtual void execute() = 0;
        virtual ~Command(){}
};

class SendMessageCommand : public Command{
    public:
        SendMessageCommand(ChatRoom* r, string msg, Users* u): Command(r, msg, u) {}
        void execute() override;
};

class LogMessageCommand : public Command{
    public:
        LogMessageCommand(ChatRoom* r, string msg, Users* u): Command(r, msg, u) {}
        void execute() override;
};

class Users : public Observer{
    protected:
        vector <ChatRoom*> chatRooms;
        string name;
        vector <Command*> commandQueue; //list of all the commands
    public:
        Users(string n): name(n) {}
        string getName() { return name; }
        void joinRoom(ChatRoom* room);
        void leaveRoom(ChatRoom* room);
        void send(const string& message, ChatRoom* room);
        void receive(const string& message, Users* fromUser, ChatRoom* room);
        void addCommand(Command* command); //adds command to the queue
        void executeAll(); //executes all queued command in sequence

        void update(const string& message, const string& sender, ChatRoom* room);
};

class ChatRoom{
    private:
        vector <Users*> users; //keeps track of all users in this chat room
        vector <string> chatHistory; //stores all messages sent in chat room
        vector<Users*> observers;
        string name;
    public:
        ChatRoom(string n): name(n) {}
        void registerUser(Users* user);
        void sendMessage(const string& message, Users* fromUser); //to all users in the room
        void saveMessage(const string& message, Users* fromUser); //appends the message to the chat history for later retrieval
        void removeUser(Users* user);
        void notifyObservers(const string& message, Users* fromUser);
        vector<string> getChatHistory() const {return chatHistory;}
        string getName() const {return name;}
        vector<Users*> getUsers() const {return users;}
};

#endif