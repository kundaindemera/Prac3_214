/**
 * @file Observer.h
 * @brief Includes Observer class definition
 *
 * This file defines the Observer pattern implementation for a chat room system,
 * including the Observer interface that users can implement to receive updates
 * when new messages are sent in a chat room.
 *
 * @date 2025-09-30
 * @author Mosa Leiee and Kundai Ndemera
 */

#ifndef OBSERVER_H
#define OBSERVER_H
#include "iostream"
#include "vector"
#include "map"
#include "list"
#include <string>
using namespace std;

class ChatRoom;
class Observer{ 
    public:
        virtual void update(const string& message, const string& sender, ChatRoom* room) = 0;
        virtual ~Observer(){}
};

#endif