#include "Mediator.h"
#include <iostream>

// User implementation
User::User(const std::string& name) : name(name) {}

User::~User() {}

void User::send(const std::string& message, ChatRoom* room) {
    room->sendMessage(message, this);
}

void User::receive(const std::string& message, User* fromUser, ChatRoom* room) {
    std::cout << name << " received in " 
              << (dynamic_cast<CtrlCat*>(room) ? "CtrlCat" : "Dogorithm")
              << ": " << message << " from " << fromUser->getName() << std::endl;
}

std::string User::getName() const {
    return name;
}

void User::joinChatRoom(ChatRoom* room) {
    chatRooms.push_back(room);
    room->registerUser(this);
}

void User::leaveChatRoom(ChatRoom* room) {
    // Manual search instead of using std::find
    size_t i = 0;
    bool found = false;
    for(; i < chatRooms.size(); i++) {
        if(chatRooms[i] == room) {
            found = true;
            break;
        }
    }
    
    if(found) {
        chatRooms.erase(chatRooms.begin() + i);
        room->removeUser(this);
    }
}

// CtrlCat implementation
void CtrlCat::registerUser(User* user) {
    users.push_back(user);
    std::string message = user->getName() + " joined CtrlCat";
    chatHistory.push_back(message);
    std::cout << message << std::endl;
}

void CtrlCat::removeUser(User* user) {
    // Manual search instead of using std::find
    size_t i = 0; 
    bool found = false;
    for(; i < users.size(); i++) {
        if(users[i] == user) {
            found = true;
            break;
        }
    }
    
    if(found) {
        users.erase(users.begin() + i);
        std::string message = user->getName() + " left CtrlCat";
        chatHistory.push_back(message);
        std::cout << message << std::endl;
    }
}

void CtrlCat::sendMessage(const std::string& message, User* fromUser) {
    std::string formattedMessage = fromUser->getName() + ": " + message;
    chatHistory.push_back(formattedMessage);
    receiveMessage(message, fromUser);
}

void CtrlCat::receiveMessage(const std::string& message, User* fromUser) {
    for (User* user : users) {
        if (user != fromUser) {
            user->receive(message, fromUser, this);
        }
    }
}

// Dogorithm implementation
void Dogorithm::registerUser(User* user) {
    users.push_back(user);
    std::string message = user->getName() + " joined Dogorithm";
    chatHistory.push_back(message);
    std::cout << message << std::endl;
}

void Dogorithm::removeUser(User* user) {
    // Manual search instead of using std::find
    size_t i = 0;
    bool found = false;
    for(; i < users.size(); i++) {
        if(users[i] == user) {
            found = true;
            break;
        }
    }
    
    if(found) {
        users.erase(users.begin() + i);
        std::string message = user->getName() + " left Dogorithm";
        chatHistory.push_back(message);
        std::cout << message << std::endl;
    }
}

void Dogorithm::sendMessage(const std::string& message, User* fromUser) {
    std::string formattedMessage = fromUser->getName() + ": " + message;
    chatHistory.push_back(formattedMessage);
    receiveMessage(message, fromUser);
}

void Dogorithm::receiveMessage(const std::string& message, User* fromUser) {
    for (User* user : users) {
        if (user != fromUser) {
            user->receive(message, fromUser, this);
        }
    }
}

// Concrete Users
Name1::Name1() : User("Alice") {}
Name2::Name2() : User("Bob") {}
Name3::Name3() : User("Charlie") {}
