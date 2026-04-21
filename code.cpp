#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

bool check_win(const vector<string>& board, char c) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == c && board[i][1] == c && board[i][2] == c) return true;
        if (board[0][i] == c && board[1][i] == c && board[2][i] == c) return true;
    }
    if (board[0][0] == c && board[1][1] == c && board[2][2] == c) return true;
    if (board[0][2] == c && board[1][1] == c && board[2][0] == c) return true;
    return false;
}

set<vector<string>> reachable;

void generate(vector<string> board, bool xTurn) {
    reachable.insert(board);
    if (check_win(board, 'x') || check_win(board, 'o')) return;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == '-') {
                board[i][j] = xTurn ? 'x' : 'o';
                generate(board, !xTurn);
                board[i][j] = '-';
            }
        }
    }
}

int main() {
    vector<string> board(3);
    int nx = 0, no = 0, empty = 0;
    bool has_input = false;
    for (int i = 0; i < 3; ++i) {
        if (!(cin >> board[i])) break;
        has_input = true;
        for (char c : board[i]) {
            if (c == 'x') nx++;
            else if (c == 'o') no++;
            else empty++;
        }
    }
    if (!has_input) return 0;

    vector<string> start(3, "---");
    generate(start, true);

    if (reachable.find(board) == reachable.end()) {
        cout << "invalid" << endl;
    } else {
        bool winX = check_win(board, 'x');
        bool winO = check_win(board, 'o');

        if (winX) cout << "win" << endl;
        else if (winO) cout << "lose" << endl;
        else if (empty == 0) cout << "tie" << endl;
        else cout << "ongoing" << endl;
    }

    return 0;
}
