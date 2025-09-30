#include "Iterator.h"
#include "Command.h" 

/**
 * @class UserIterator
 * @brief Concrete Iterator for iterating over Users in a ChatRoom.
 *
 * This iterator provides methods to traverse the list of users in a chat room.
 * It implements the Iterator interface.
 */

 /**
  * @brief Constructor for UserIterator.
  * @param users Reference to the vector of Users in the ChatRoom.
*/
UserIterator::UserIterator(const std::vector<Users*>& users)
    : users(users), position(0) {}

/**
 * @brief Checks if there are more users to iterate over.
 * @return true if there are more users, false otherwise.
*/
bool UserIterator::hasNext() const {
    return position < users.size();
}
/**
 * @brief Returns the next user in the iteration.
 * @return Pointer to the next user, or nullptr if no more users.
*/
void* UserIterator::next() {
    return hasNext() ? (void*)users[position++] : nullptr;
}

/**
 * @brief Helper method to get the next user as a Users* type.
 * @return Pointer to the next Users object, or nullptr if no more users.
*/
Users* UserIterator::nextUser() {
    return static_cast<Users*>(next());
}

/**
 * @class MessageIterator
 * @brief Concrete Iterator for iterating over messages in a ChatRoom.
 *
 * This iterator provides methods to traverse the chat history of a chat room.
 * It implements the Iterator interface.
 */

 /**
  * @brief Constructor for MessageIterator.
  * @param messages Reference to the vector of messages in the ChatRoom.
*/
MessageIterator::MessageIterator(const std::vector<std::string>& messages)
    : messages(messages), position(0) {}

/**
 * @brief Checks if there are more messages to iterate over.
 * @return true if there are more messages, false otherwise.
*/
bool MessageIterator::hasNext() const {
    return position < messages.size();
}

/**
 * @brief Returns the next message in the iteration.
 * @return Pointer to the next message, or nullptr if no more messages.
*/
void* MessageIterator::next() {
    return hasNext() ? (void*)&messages[position++] : nullptr;
}

/**
 * @brief Helper method to get the next message as a std::string type.
 * @return The next message string, or an empty string if no more messages.
*/
std::string MessageIterator::nextMessage() {
    std::string* messagePtr = static_cast<std::string*>(next());
    return messagePtr ? *messagePtr : "";
}


/**
 * @class ChatRoomIteratorFactory
 * @brief Factory class to create iterators for ChatRoom.
 *
 * This factory provides static methods to create UserIterator and MessageIterator
 * for a given ChatRoom instance.
 */

 /**
  * @brief Creates a UserIterator for the given ChatRoom.
  * @param chatRoom Pointer to the ChatRoom instance.
  * @return Pointer to a new UserIterator instance.
*/
UserIterator* ChatRoomIteratorFactory::createUserIterator(const ChatRoom* chatRoom) {
    return new UserIterator(chatRoom->getUsers());
}
/**
 * @brief Creates a MessageIterator for the given ChatRoom.
 * @param chatRoom Pointer to the ChatRoom instance.
 * @return Pointer to a new MessageIterator instance.
*/
MessageIterator* ChatRoomIteratorFactory::createMessageIterator(const ChatRoom* chatRoom) {
    return new MessageIterator(chatRoom->getChatHistory());
}
