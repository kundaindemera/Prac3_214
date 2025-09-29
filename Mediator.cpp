#include "Mediator.h"
#include "Command.h"
#include <iostream>

// Users implementation
Users::Users(const std::string& name) : name(name) {}

Users::~Users() {}

void Users::send(const std::string& message, ChatRoom* room) {
    room->sendMessage(message, this);
}

void Users::receive(const std::string& message, Users* fromUsers, ChatRoom* room) {
    std::cout << name << " received in " 
              << (dynamic_cast<CtrlCat*>(room) ? "CtrlCat" : "Dogorithm")
              << ": " << message << " from " << fromUsers->getName() << std::endl;
}

std::string Users::getName() const {
    return name;
}

void Users::joinChatRoom(ChatRoom* room) {
    chatRooms.push_back(room);
    room->registerUsers(this);
}

void Users::leaveChatRoom(ChatRoom* room) {
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
        room->removeUsers(this);
    }
}

// CtrlCat implementation
void CtrlCat::registerUsers(Users* user) {
    users.push_back(user);
    std::string message = user->getName() + " joined CtrlCat";
    chatHistory.push_back(message);
    std::cout << message << std::endl;
}

void CtrlCat::removeUsers(Users* user) {
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

void CtrlCat::sendMessage(const std::string& message, Users* fromUsers) {
    std::string formattedMessage = fromUsers->getName() + ": " + message;
    chatHistory.push_back(formattedMessage);
    receiveMessage(message, fromUsers);
}

void CtrlCat::receiveMessage(const std::string& message, Users* fromUsers) {
    for (Users* user : users) {
        if (user != fromUsers) {
            user->receive(message, fromUsers, this);
        }
    }
}

// Dogorithm implementation
void Dogorithm::registerUsers(Users* user) {
    users.push_back(user);
    std::string message = user->getName() + " joined Dogorithm";
    chatHistory.push_back(message);
    std::cout << message << std::endl;
}

void Dogorithm::removeUsers(Users* user) {
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

void Dogorithm::sendMessage(const std::string& message, Users* fromUsers) {
    std::string formattedMessage = fromUsers->getName() + ": " + message;
    chatHistory.push_back(formattedMessage);
    receiveMessage(message, fromUsers);
}

void Dogorithm::receiveMessage(const std::string& message, Users* fromUsers) {
    for (Users* user : users) {
        if (user != fromUsers) {
            user->receive(message, fromUsers, this);
        }
    }
}

// Concrete Userss
Name1::Name1() : Users("Alice") {}
Name2::Name2() : Users("Bob") {}
Name3::Name3() : Users("Charlie") {}
