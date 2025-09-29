#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <string>
#include <vector>

// Forward declaration
class Users;

// Mediator interface
class ChatRoom {
protected:
    std::vector<Users*> users;
    std::vector<std::string> chatHistory;

public:
    virtual ~ChatRoom() {}
    virtual void registerUsers(Users* user) = 0;
    virtual void removeUsers(Users* user) = 0;
    virtual void sendMessage(const std::string& message, Users* fromUsers) = 0;
    virtual void receiveMessage(const std::string& message, Users* fromUsers) = 0;
    
    // For iterators
    const std::vector<Users*>& getUserss() const { return users; }
    const std::vector<std::string>& getChatHistory() const { return chatHistory; }
};

// Users class
class Users {
protected:
    std::string name;
    std::vector<ChatRoom*> chatRooms;

public:
    Users(const std::string& name);
    virtual ~Users();
    
    void send(const std::string& message, ChatRoom* room);
    void receive(const std::string& message, Users* fromUsers, ChatRoom* room);
    std::string getName() const;
    void joinChatRoom(ChatRoom* room);
    void leaveChatRoom(ChatRoom* room);
};

// Concrete ChatRoom implementations
class CtrlCat : public ChatRoom {
public:
    void registerUsers(Users* user) override;
    void removeUsers(Users* user) override;
    void sendMessage(const std::string& message, Users* fromUsers) override;
    void receiveMessage(const std::string& message, Users* fromUsers) override;
};

class Dogorithm : public ChatRoom {
public:
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
