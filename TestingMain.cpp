#include <iostream>
#include <string>
#include <vector>
#include "Command.h"
#include "Mediator.h"
#include "Observer.h"
#include "Iterator.h"

using namespace std;

// ------------------ Helper Functions ------------------
void printChatHistory(ChatRoom* room) {
    cout << "\n" << room->getName() << " chat history:" << endl;
    MessageIterator* mit = ChatRoomIteratorFactory::createMessageIterator(room);
    while (mit->hasNext()) {
        cout << "  " << mit->nextMessage() << endl;
    }
    delete mit;
}

void printUsers(ChatRoom* room) {
    cout << "\nUsers in " << room->getName() << ":" << endl;
    UserIterator* uit = ChatRoomIteratorFactory::createUserIterator(room);
    while (uit->hasNext()) {
        cout << "  - " << uit->nextUser()->getName() << endl;
    }
    delete uit;
}

// ------------------ Observer Test ------------------
void testObserver() {
    cout << "\n=== Testing Observer Pattern ===\n";

    ChatRoom* alpha = new CtrlCat();

    Users* alice = new Users("Alice");
    Users* bob   = new Users("Bob");
    Users* charlie = new Users("Charlie");

    cout << "\n--- Users joining room ---" << endl;
    alice->joinRoom(alpha);
    bob->joinRoom(alpha);
    charlie->joinRoom(alpha);

    cout << "\n--- Sending messages (Observer notifications) ---" << endl;
    alice->send("Hello everyone!", alpha);
    bob->send("Hi Alice!", alpha);
    charlie->send("Hey all!", alpha);

    printUsers(alpha);
    printChatHistory(alpha);

    delete alice;
    delete bob;
    delete charlie;
    delete alpha;
}

// ------------------ Command Test ------------------
void testCommand() {
    cout << "\n=== Testing Command Pattern ===\n";

    ChatRoom* beta = new Dogorithm();

    Users* dave = new Users("Dave");
    Users* eve  = new Users("Eve");

    cout << "\n--- Users joining room ---" << endl;
    dave->joinRoom(beta);
    eve->joinRoom(beta);

    cout << "\n--- Adding commands to queue ---" << endl;
    dave->addCommand(new SendMessageCommand(beta, "Hello Eve!", dave));
    eve->addCommand(new SendMessageCommand(beta, "Hi Dave!", eve));

    cout << "\n--- Executing all commands ---" << endl;
    dave->executeAll();
    eve->executeAll();

    printUsers(beta);
    printChatHistory(beta);

    delete dave;
    delete eve;
    delete beta;
}

// ------------------ Mediator + Iterator Test ------------------
void testMediatorIterator() {
    cout << "\n=== Testing Mediator + Iterator ===\n";

    CtrlCat* gamma = new CtrlCat(); // Mediator
    Users* frank = new Users("Frank");
    Users* grace = new Users("Grace");

    cout << "\n--- Registering users through mediator ---" << endl;
    gamma->registerUsers(frank);
    gamma->registerUsers(grace);

    cout << "\n--- Sending messages through mediator ---" << endl;
    frank->send("Hey Grace!", gamma);
    grace->send("Hi Frank!", gamma);

    printUsers(gamma);
    printChatHistory(gamma);

    delete frank;
    delete grace;
    delete gamma;
}

// ------------------ Combined Test ------------------
void testCombined() {
    cout << "\n=== Testing All Patterns Combined ===\n";

    Dogorithm* delta = new Dogorithm(); // Mediator + ChatRoom
    Users* hannah = new Users("Hannah");
    Users* ian    = new Users("Ian");

    cout << "\n--- Registering users ---" << endl;
    delta->registerUsers(hannah);
    delta->registerUsers(ian);

    cout << "\n--- Adding and executing commands ---" << endl;
    hannah->addCommand(new SendMessageCommand(delta, "Hello Ian!", hannah));
    ian->addCommand(new SendMessageCommand(delta, "Hi Hannah!", ian));

    hannah->executeAll();
    ian->executeAll();

    cout << "\n--- Testing content filtering ---" << endl;
    hannah->send("I love snakes!", delta); // Should be blocked

    printUsers(delta);
    printChatHistory(delta);

    delete hannah;
    delete ian;
    delete delta;
}

// ------------------ Additional Pattern Tests ------------------
void testConcreteUsers() {
    cout << "\n=== Testing Concrete User Classes ===\n";

    CtrlCat* room = new CtrlCat();
    
    Name1* alice = new Name1(); // Alice
    Name2* bob = new Name2();   // Bob
    Name3* charlie = new Name3(); // Charlie

    cout << "\n--- Concrete users joining ---" << endl;
    alice->joinRoom(room);
    bob->joinRoom(room);
    charlie->joinRoom(room);

    cout << "\n--- Concrete users chatting ---" << endl;
    alice->send("Hello from concrete Alice!", room);
    bob->send("Bob here!", room);
    charlie->send("Charlie joining the conversation!", room);

    printUsers(room);
    printChatHistory(room);

    delete alice;
    delete bob;
    delete charlie;
    delete room;
}

int main() {
    cout << "========================================\n";
    cout << "   COMPREHENSIVE PATTERN TESTING       \n";
    cout << "========================================\n";

    try {
        testObserver();
        testCommand();
        testMediatorIterator();
        testCombined();
        testConcreteUsers();

        cout << "\n========================================\n";
        cout << "       ALL TESTS COMPLETED             \n";
        cout << "========================================\n";
    }
    catch (const exception& e) {
        cout << "Error during testing: " << e.what() << endl;
    }

    return 0;
}
