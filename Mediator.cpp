#include "Mediator.h"
#include "Command.h"
#include <iostream>

// CtrlCat implementation
void CtrlCat::registerUsers(Users* user) {
    registerUser(user);
}

void CtrlCat::removeUsers(Users* user) {
    removeUser(user);
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

// Concrete Users
Name1::Name1() : Users("Alice") {}
Name2::Name2() : Users("Bob") {}
Name3::Name3() : Users("Charlie") {}
