#include "Command.cpp"
#include "Observer.cpp"
#include <iostream>
using namespace std;

void testObserver() {
    cout << "\n--- Testing Observer Pattern ---\n";

    // Create a chat room
    ChatRoom alpha("Alpha");
    
    Users* alice = new Users("Alice");
    Users* bob = new Users("Bob");
    Users* charlie = new Users("Charlie");

    // Register users
    alpha.registerUser(alice);
    alpha.registerUser(bob);
    alpha.registerUser(charlie);

    // Send messages
    alice->send("Hello everyone!", &alpha);
    bob->send("Hi Alice!", &alpha);
    charlie->send("Hey all!", &alpha);

    // Show chat history
    cout << "\nAlpha chat history:\n";
    vector<string> history = alpha.getChatHistory();
    for (size_t i = 0; i < history.size(); i++) {
        cout << history[i] << endl;
    }
}

void testCommand() {
    cout << "\n--- Testing Command Pattern ---\n";

    ChatRoom beta("Beta");

    Users* dave = new Users("Dave");
    Users* eve = new Users("Eve");

    beta.registerUser(dave);
    beta.registerUser(eve);

    // Command pattern: users queue commands
    dave->addCommand(new SendMessageCommand(&beta, "Hello Eve!", dave));
    dave->addCommand(new LogMessageCommand(&beta, "Hello Eve!", dave));

    eve->addCommand(new SendMessageCommand(&beta, "Hi Dave!", eve));
    eve->addCommand(new LogMessageCommand(&beta, "Hi Dave!", eve));

    // Execute commands
    dave->executeAll();
    eve->executeAll();

    // Show chat history
    cout << "\nBeta chat history:\n";
    vector<string> history = beta.getChatHistory();
    for (size_t i = 0; i < history.size(); i++) {
        cout << history[i] << endl;
    }
}

void testCombined() {
    cout << "\n--- Testing Observer + Command Combined ---\n";

    ChatRoom gamma("Gamma");

    Users* frank = new Users("Frank");
    Users* grace = new Users("Grace");

    gamma.registerUser(frank);
    gamma.registerUser(grace);

    // Combined: send() automatically uses Command internally
    frank->send("Hey Grace!", &gamma);
    grace->send("Hi Frank!", &gamma);

    // Show chat history
    cout << "\nGamma chat history:\n";
    vector<string> history = gamma.getChatHistory();
    for (size_t i = 0; i < history.size(); i++) {
        cout << history[i] << endl;
    }
}

int main() {
    testObserver();
    testCommand();
    testCombined();

    return 0;
}
