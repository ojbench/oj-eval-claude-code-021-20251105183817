#include <iostream>
#include "game.h"

using namespace std;

int main() {
    try {
        Game game(cin);

        cout << "Game initialized successfully!" << endl;
        cout << "Total bricks: " << game.bricksTotal() << endl;
        cout << "Remaining bricks: " << game.bricksRemaining() << endl;

        // Test one move
        char test_op = 'C';
        int reward = game.play(test_op);
        cout << "Test move " << test_op << " reward: " << reward << endl;
        cout << "Remaining after move: " << game.bricksRemaining() << endl;

    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
        return 1;
    } catch (const string& s) {
        cout << "String exception: " << s << endl;
        return 1;
    }

    return 0;
}