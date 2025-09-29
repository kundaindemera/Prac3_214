#include "Iterator.h"
#include "Mediator.h"

// UserIterator implementation
UserIterator::UserIterator(const std::vector<User*>& users)
    : users(users), position(0) {}

bool UserIterator::hasNext() const {
    return position < users.size();
}

void* UserIterator::next() {
    return hasNext() ? (void*)users[position++] : nullptr;
}

User* UserIterator::nextUser() {
    return static_cast<User*>(next());
}

// MessageIterator implementation
MessageIterator::MessageIterator(const std::vector<std::string>& messages)
    : messages(messages), position(0) {}

bool MessageIterator::hasNext() const {
    return position < messages.size();
}

void* MessageIterator::next() {
    return hasNext() ? (void*)&messages[position++] : nullptr;
}

std::string MessageIterator::nextMessage() {
    std::string* messagePtr = static_cast<std::string*>(next());
    return messagePtr ? *messagePtr : "";
}

// Factory implementation
UserIterator* ChatRoomIteratorFactory::createUserIterator(const ChatRoom* chatRoom) {
    return new UserIterator(chatRoom->getUsers());
}

MessageIterator* ChatRoomIteratorFactory::createMessageIterator(const ChatRoom* chatRoom) {
    return new MessageIterator(chatRoom->getChatHistory());
}
