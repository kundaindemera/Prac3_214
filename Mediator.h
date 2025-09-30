/**
 * @file Mediator.h
 * @brief Includes concrete chat room class definitions
 *
 * This file defines concrete chat room classes that inherit from the ChatRoom class
 * defined in Command.h. These classes represent specific chat rooms with predefined names.
 * 
 *
 * @date 2025-09-30
 * @author Mosa Leiee and Kundai Ndemera
 */

#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <string>
#include "Command.h" // Use your canonical Users and ChatRoom

// Concrete chat rooms that reuse ChatRoom implementation from Command.h.
// They simply call the ChatRoom(string name) constructor.
class CtrlCat : public ChatRoom {
public:
    CtrlCat() : ChatRoom("CtrlCat") {}
    void registerUsers(Users* user) override;
    void removeUsers(Users* user) override;
    void sendMessage(const std::string& message, Users* fromUsers) override;
    void receiveMessage(const std::string& message, Users* fromUsers) override;
};

class Dogorithm : public ChatRoom {
public:
    Dogorithm() : ChatRoom("Dogorithm") {}
    void registerUsers(Users* user) override;
    void removeUsers(Users* user) override;
    void sendMessage(const std::string& message, Users* fromUsers) override;
    void receiveMessage(const std::string& message, Users* fromUsers) override;
};

// Concrete Userss
class Name1 : public Users {
public:
    Name1();
};

class Name2 : public Users {
public:
    Name2();
};

class Name3 : public Users {
public:
    Name3();
};

#endif // MEDIATOR_H
