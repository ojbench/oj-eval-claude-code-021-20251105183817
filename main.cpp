#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <random>
#include <cmath>

using namespace std;

// Simple physics simulation to understand ball movement
struct Ball {
    int x, y;      // position
    int vx, vy;    // velocity
};

// Simulate basic ball movement to predict where it might go
vector<pair<int, int>> predictBallPath(Ball ball, int n, const vector<vector<int>>& bricks) {
    vector<pair<int, int>> path;
    const int max_steps = 1000;

    for (int step = 0; step < max_steps; step++) {
        // Simple prediction: ball moves in straight lines
        int next_x = ball.x + ball.vx;
        int next_y = ball.y + ball.vy;

        // Check boundaries (simplified)
        if (next_y < 0 || next_y > 3*n) {
            ball.vy = -ball.vy;
            next_y = ball.y + ball.vy;
        }
        if (next_x < -2*n || next_x > 2*n) {
            ball.vx = -ball.vx;
            next_x = ball.x + ball.vx;
        }

        ball.x = next_x;
        ball.y = next_y;

        path.push_back({ball.x, ball.y});

        // Stop if ball hits bottom again
        if (ball.y <= 0) break;
    }

    return path;
}

// Analyze brick distribution to find good targeting strategies
vector<pair<int, int>> analyzeBrickDistribution(int n, const vector<vector<int>>& bricks) {
    vector<pair<int, int>> colored_bricks;

    for (int i = 0; i < 2*n; i++) {
        for (int j = 0; j < 2*n; j++) {
            if (bricks[i][j] > 0) { // Colored brick
                colored_bricks.push_back({i, j});
            }
        }
    }

    return colored_bricks;
}

int main() {
    int k, n, m, s;
    cin >> k >> n >> m >> s;

    // Read brick colors
    vector<vector<int>> bricks(2*n, vector<int>(2*n));
    for (int i = 0; i < 2*n; i++) {
        for (int j = 0; j < 2*n; j++) {
            cin >> bricks[i][j];
        }
    }

    // Analyze the brick distribution
    auto colored_bricks = analyzeBrickDistribution(n, bricks);

    // Count total bricks and colored bricks
    int total_bricks = 4 * n * n;
    int colored_count = colored_bricks.size();

    vector<char> operations;

    // Strategy based on field size and brick distribution
    if (n <= 10) {
        // Small field: more targeted approach
        // Try to sweep systematically but also target colored bricks

        // Create a pattern that covers the field well
        char sweep_pattern[] = {'C', 'B', 'D', 'A', 'E', 'C', 'B', 'D'};
        char targeted_pattern[] = {'B', 'D', 'C', 'A', 'E', 'B', 'D', 'C'};

        for (int i = 0; i < m && i < 500; i++) {
            if (colored_count > 0 && i % 3 == 0) {
                operations.push_back(targeted_pattern[i % 8]);
            } else {
                operations.push_back(sweep_pattern[i % 8]);
            }
        }
    } else {
        // Larger field: use more systematic approach
        // Progressive sweeping with occasional targeted shots

        int phase_length = max(5, n / 2);

        for (int i = 0; i < m && i < 2000; i++) {
            int phase = (i / phase_length) % 6;

            switch (phase) {
                case 0: operations.push_back('A'); break; // far left
                case 1: operations.push_back('B'); break; // left
                case 2: operations.push_back('C'); break; // center
                case 3: operations.push_back('D'); break; // right
                case 4: operations.push_back('E'); break; // far right
                case 5: operations.push_back('C'); break; // center
            }
        }
    }

    // Output the operations
    for (char op : operations) {
        cout << op << endl;
    }

    return 0;
}