#include "Command.h"
using namespace std;

//Command

/**
 * @class SendMessageCommand
 * @brief Concrete Command to send a message in a chat room and notify observers.
 *
 * This command sends a message from a user to all other users in the chat room
 * and notifies observers about the new message.
 */

 /**
  * @brief Executes the command to send a message and notify observers.
*/
void SendMessageCommand::execute()
{
    if (room && fromUser){
        room->sendMessage(message, fromUser);
        room->notifyObservers(message, fromUser);
    }
}

/**
 * @class LogMessageCommand
 * @brief Concrete Command to log a message in the chat room's history.
 *
 * This command saves a message sent by a user into the chat room's history for future retrieval.
 *
 */

/**
* @brief Executes the command to log a message in the chat room's history.
*/
void LogMessageCommand::execute()
{
    if (room && fromUser){
        room->saveMessage(message, fromUser);
    }
}

//Users

/**
 * @class Users
 * @brief Concrete Observer representing a user in the chat system.
 *
 * This class allows users to join and leave chat rooms, send and receive messages,
 * and manage a queue of commands to be executed. It implements the Observer interface to receive
 * notifications about new messages in chat rooms.
 */

 /**
  * @brief User joins a chat room and registers as an observer.
  * @param room Pointer to the ChatRoom to join.
  */
void Users::joinRoom(ChatRoom* room){
    chatRooms.push_back(room);
    room->registerUser(this);
}

/**
 * @brief User leaves a chat room and unregisters as an observer.
 * @param room Pointer to the ChatRoom to leave.
*/
void Users::leaveRoom(ChatRoom* room){
    vector<ChatRoom*> newRooms;
    for (size_t i=0; i < chatRooms.size(); i++){
        if (chatRooms[i] != room){
            newRooms.push_back(chatRooms[i]);
        }
    }
    chatRooms = newRooms;
    room->removeUser(this);
}

/**
 * @brief User sends a message to a chat room by creating and executing commands.
 * @param message The message to send.
 * @param room Pointer to the ChatRoom to send the message to.
*/
void Users::send(const string &message, ChatRoom *room)
{   
    if (!room) return;
    //create command objects, add to queue and then execute command in order
    if (message.find("snake") != string::npos || message.find("snakes") != string::npos){
        cout<<"Message blocked due to triggering content: " << message << endl;
        return;
    }
    addCommand(new SendMessageCommand(room, message, this)); 
    addCommand(new LogMessageCommand(room, message, this)); //save message command
    executeAll();
}

/**
 * @brief User receives a message from another user in a chat room.
 * @param message The message received.
 * @param fromUser Pointer to the Users who sent the message.
 * @param room Pointer to the ChatRoom where the message was sent.
*/
void Users::receive(const string &message, Users *fromUser, ChatRoom *room)
{
    cout << fromUser->getName() << " to " << name << ": "<< message<<endl;
}

/**
 * @brief Adds a command to the user's command queue.
 * @param command Pointer to the Command to add.
*/
void Users::addCommand(Command *command)
{
    commandQueue.push_back(command);
}

/**
 * @brief Executes all commands in the user's command queue in sequence.
*/
void Users::executeAll()
{
    for (Command* c : commandQueue){
        c->execute();
        delete c;
    }
    commandQueue.clear(); //clear queue after executing all commands
}

/**
 * @brief Updates the user with a new message notification from a chat room.
 * @param message The message received.
 * @param sender The name of the user who sent the message.
 * @param room Pointer to the ChatRoom where the message was sent.
*/
void Users::update(const string& message, const string& sender, ChatRoom* room){
    if (sender != name){
        cout << "[Notification] " << sender << " sent a message in " << room->getName() << " : " << message << endl;
    }
}

//ChatRoom

/**
 * @class ChatRoom
 * @brief Concrete Subject representing a chat room in the chat system.
 *
 * This class manages users, message history, and observers. It allows users to register/join,
 * send messages, save message history, and notify observers about new messages.
 */

 /**
  * @brief Registers a user to the chat room and adds them as an observer.
  * @param user Pointer to the Users to register.
*/
void ChatRoom::registerUser(Users *user)
{   
    bool exists = false;
    for (size_t i=0; i < users.size(); i++){
        if (users[i] == user){
            exists = true;
            break;
        }
    }
    if (!exists){
        users.push_back(user);
        observers.push_back(user);
        cout << user->getName() << " has joined the room " << name << "." << endl;
    }
}

/**
 * @brief Sends a message from a user to all other users in the chat room and notifies observers.
 * @param message The message to send.
 * @param fromUser Pointer to the Users who is sending the message.
*/
void ChatRoom::sendMessage(const string &message, Users *fromUser) //send to users then notify observers
{
    saveMessage(message, fromUser);
    for (Users* user: users){
        if (user != fromUser){
            user->receive(message,fromUser,this);
        }
    }
}

/**
 * @brief Saves a message sent by a user into the chat room's history.
 * @param message The message to save.
 * @param fromUser Pointer to the Users who sent the message.
*/
void ChatRoom::saveMessage(const string &message, Users *fromUser)
{
    chatHistory.push_back(fromUser->getName() + ": " + message);
}

/**
 * @brief Removes a user from the chat room and unregisters them as an observer.
 * @param user Pointer to the Users to remove.
*/
void ChatRoom::removeUser(Users *user)
{
    vector<Users*> newUsers;
    for (size_t i=0; i < users.size(); i++){
        if (users[i] != user){
            newUsers.push_back(users[i]);
        }
    }
    users = newUsers;

    vector<Users*> newObservers;
    for (size_t i=0; i < observers.size(); i++){
        if (observers[i] != user){
            newObservers.push_back(observers[i]);
        }
    }
    observers = newObservers;
    cout << user->getName() << " has left the room."<<endl;
}

/**
 * @brief Notifies all observers (users) in the chat room about a new message.
 * @param message The message to notify about.
 * @param fromUser Pointer to the Users who sent the message.
*/
void ChatRoom::notifyObservers(const string& message, Users* fromUser){
    for (Users* o:observers){
        if (o != fromUser){
            o->update(message, fromUser->getName(), this);
        }
    }
}