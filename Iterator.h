#ifndef ITERATOR_H
#define ITERATOR_H

#include <vector>
#include <string>

// Forward declarations
class User;
class ChatRoom;

// Iterator interface
class Iterator {
public:
    virtual ~Iterator() {}
    virtual bool hasNext() const = 0;
    virtual void* next() = 0;
};

// Concrete Iterator for users
class UserIterator : public Iterator {
private:
    const std::vector<User*>& users;
    size_t position;

public:
    UserIterator(const std::vector<User*>& users);
    bool hasNext() const override;
    void* next() override;
    User* nextUser();  // Helper method that casts the result
};

// Concrete Iterator for messages
class MessageIterator : public Iterator {
private:
    const std::vector<std::string>& messages;
    size_t position;

public:
    MessageIterator(const std::vector<std::string>& messages);
    bool hasNext() const override;
    void* next() override;
    std::string nextMessage();  // Helper method that returns the message
};

// Factory for creating iterators
class ChatRoomIteratorFactory {
public:
    static UserIterator* createUserIterator(const ChatRoom* chatRoom);
    static MessageIterator* createMessageIterator(const ChatRoom* chatRoom);
};

#endif // ITERATOR_H
