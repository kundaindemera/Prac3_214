#include "Mediator.h"
#include "Iterator.h"
#include <iostream>

int main() {
    // Create chat rooms
    CtrlCat* ctrlCat = new CtrlCat();
    Dogorithm* dogorithm = new Dogorithm();
    
    // Create users
    Name1* alice = new Name1();    // Alice
    Name2* bob = new Name2();      // Bob
    Name3* charlie = new Name3();  // Charlie
    
    std::cout << "=== Joining Chat Rooms ===" << std::endl;
    
    // Alice joins both chat rooms
    alice->joinChatRoom(ctrlCat);
    alice->joinChatRoom(dogorithm);
    
    // Bob joins CtrlCat
    bob->joinChatRoom(ctrlCat);
    
    // Charlie joins Dogorithm
    charlie->joinChatRoom(dogorithm);
    
    std::cout << "\n=== Sending Messages ===" << std::endl;
    
    // Send messages in CtrlCat
    alice->send("Hello from CtrlCat!", ctrlCat);
    bob->send("Hi Alice, how are you?", ctrlCat);
    
    // Send messages in Dogorithm
    alice->send("Anyone here in Dogorithm?", dogorithm);
    charlie->send("Yes, I'm here!", dogorithm);
    
    std::cout << "\n=== Leaving Chat Rooms ===" << std::endl;
    
    // Alice leaves CtrlCat
    alice->leaveChatRoom(ctrlCat);
    
    // Bob tries to send a message to Alice, but she already left
    bob->send("Alice, are you still there?", ctrlCat);

    std::cout << "\n=== Showing all users in CtrlCat  ===" << std::endl; 
    UserIterator* cUserIt = ChatRoomIteratorFactory::createUserIterator(ctrlCat);
    while (cUserIt->hasNext()){
        User* user = cUserIt->nextUser();
        if (user){
            std::cout << user->getName() << std::endl;
        }
    }

    delete cUserIt;


    std::cout << "\n=== Showing all messages in CtrlCat  ===" << std::endl; 
    MessageIterator* cMessageIt = ChatRoomIteratorFactory::createMessageIterator(ctrlCat);
    while (cMessageIt->hasNext()){
        std::string message = cMessageIt->nextMessage();
        std::cout << message << std::endl;
    }

    delete cMessageIt;


    std::cout << "\n=== Showing all users in Dogorithm  ===" << std::endl; 
    UserIterator* dUserIt = ChatRoomIteratorFactory::createUserIterator(dogorithm);
    while (dUserIt->hasNext()){
        User* user = dUserIt->nextUser();
        if (user){
            std::cout << user->getName() << std::endl;
        }
    }

    delete dUserIt;


    std::cout << "\n=== Showing all messages in Dogorithm  ===" << std::endl; 
    MessageIterator* dMessageIt = ChatRoomIteratorFactory::createMessageIterator(dogorithm);
    while (dMessageIt->hasNext()){
        std::string message = dMessageIt->nextMessage();
        std::cout << message << std::endl;
    }

    delete dMessageIt;
    
    
    
    // Clean up
    delete ctrlCat;
    delete dogorithm;
    delete alice;
    delete bob;
    delete charlie;
    
    
    
    return 0;
}
