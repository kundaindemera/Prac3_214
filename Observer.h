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