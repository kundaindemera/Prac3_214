#include "Command.cpp"
using namespace std;

int main() {
    // Create chat room
    ChatRoom villa;

    // Create users
    Users alice("Alice");
    Users bob("Bob");
    Users charlie("Charlie");

    // Register users to chat room
    villa.registerUser(&alice);
    villa.registerUser(&bob);
    villa.registerUser(&charlie);

    cout << endl;

    // Users send messages
    alice.send("Hello everyone!", &villa);
    bob.send("I think snakes should be avoided.", &villa); // should be blocked
    charlie.send("I love the villa chatroom!", &villa);

    cout << "\n--- Chat History ---\n";
    for (const auto& msg : villa.getChatHistory()) {
        cout << msg << endl;
    }

    cout << endl;

    // Remove Alice
    villa.removeUser(&alice);

    cout << endl;

    // Bob sends another message
    bob.send("Looks like Alice left.", &villa);

    cout << "\n--- Final Chat History ---\n";
    for (const auto& msg : villa.getChatHistory()) {
        cout << msg << endl;
    }

    return 0;
}
