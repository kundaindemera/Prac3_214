#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <string>
#include <vector>

// Forward declaration
class User;

// Mediator interface
class ChatRoom {
protected:
    std::vector<User*> users;
    std::vector<std::string> chatHistory;

public:
    virtual ~ChatRoom() {}
    virtual void registerUser(User* user) = 0;
    virtual void removeUser(User* user) = 0;
    virtual void sendMessage(const std::string& message, User* fromUser) = 0;
    virtual void receiveMessage(const std::string& message, User* fromUser) = 0;
    
    // For iterators
    const std::vector<User*>& getUsers() const { return users; }
    const std::vector<std::string>& getChatHistory() const { return chatHistory; }
};

// User class
class User {
protected:
    std::string name;
    std::vector<ChatRoom*> chatRooms;

public:
    User(const std::string& name);
    virtual ~User();
    
    void send(const std::string& message, ChatRoom* room);
    void receive(const std::string& message, User* fromUser, ChatRoom* room);
    std::string getName() const;
    void joinChatRoom(ChatRoom* room);
    void leaveChatRoom(ChatRoom* room);
};

// Concrete ChatRoom implementations
class CtrlCat : public ChatRoom {
public:
    void registerUser(User* user) override;
    void removeUser(User* user) override;
    void sendMessage(const std::string& message, User* fromUser) override;
    void receiveMessage(const std::string& message, User* fromUser) override;
};

class Dogorithm : public ChatRoom {
public:
    void registerUser(User* user) override;
    void removeUser(User* user) override;
    void sendMessage(const std::string& message, User* fromUser) override;
    void receiveMessage(const std::string& message, User* fromUser) override;
};

// Concrete Users
class Name1 : public User {
public:
    Name1();
};

class Name2 : public User {
public:
    Name2();
};

class Name3 : public User {
public:
    Name3();
};

#endif // MEDIATOR_H
