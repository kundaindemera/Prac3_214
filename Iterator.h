/**
 * @file Iterator.h
 * @brief Includes Iterator, concrete iterator and ChatRoomIteratorFactory class definitions
 *
 * This file defines the Iterator pattern implementation for iterating over users and messages
 * in a chat room. It includes concrete iterators for users and messages, as well as
 * a factory class for creating these iterators.
 *
 * @date 2025-09-30
 * @author Mosa Leiee and Kundai Ndemera
 */

#ifndef ITERATOR_H
#define ITERATOR_H

#include <vector>
#include <string>

// Forward-declare types defined in Command.h
class Users;
class ChatRoom;

// Iterator interface
class Iterator {
public:
    virtual ~Iterator() {}
    virtual bool hasNext() const = 0;
    virtual void* next() = 0;
};

// Concrete Iterator for users (iterates Users*)
class UserIterator : public Iterator {
private:
    const std::vector<Users*>& users;
    size_t position;

public:
    UserIterator(const std::vector<Users*>& users);
    bool hasNext() const override;
    void* next() override;
    Users* nextUser();  // Helper method that casts the result
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
