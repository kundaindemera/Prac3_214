/**
 * @file Command.h
 * @brief Includes Command, Users, and ChatRoom class definitions.
 *
 * This file defines the Command pattern implementation for a chat room system,
 * including command classes for sending and logging messages, as well as
 * user and chat room management. It also incorporates the Observer pattern for
 * user notifications.
 *
 * @date 2025-09-30
 * @author Mosa Leiee and Kundai Ndemera
 */

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
    protected:
        vector <Users*> users; //keeps track of all users in this chat room
        vector <string> chatHistory; //stores all messages sent in chat room
        vector<Users*> observers;
        string name;
    public:
        ChatRoom(string n): name(n) {}
        virtual ~ChatRoom() {}
        virtual void registerUsers(Users* user) { registerUser(user); }
        virtual void removeUsers(Users* user) { removeUser(user); }
        virtual void sendMessage(const std::string& message, Users* fromUsers);
        virtual void receiveMessage(const std::string& message, Users* fromUsers) {}
        void registerUser(Users* user);
        void removeUser(Users* user);
        void saveMessage(const string& message, Users* fromUser);
        void notifyObservers(const string& message, Users* fromUser);
        const vector<string>& getChatHistory() const {return chatHistory;}
        string getName() const {return name;}
        const vector<Users*>& getUsers() const {return users;}
};

#endif