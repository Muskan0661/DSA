#include <iostream>
using namespace std;

class Sudoku {
private:
    int board[9][9];

    bool canPlace(int row, int col, int num) {
        for (int i = 0; i < 9; i++)
           if (board[row][i] == num) return false;
           
        for (int i = 0; i < 9; i++)
            if (board[i][col] == num) return false;
            
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        
        for (int i = startRow; i < startRow + 3; i++)
            for (int j = startCol; j < startCol + 3; j++)
                if (board[i][j] == num) return false;
        return true;
    }

    bool solve() {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
              if (board[row][col] == 0) {
            for (int num = 1; num <= 9; num++) {
                if (canPlace(row, col, num)) {
                    board[row][col] = num;
                    if (solve()) return true;
                    board[row][col] = 0;
                       } }
                    return false;
                } } }
        return true;
    }

public:
    void inputBoard() {
        for (int row = 0; row < 9; row++)
            for (int col = 0; col < 9; col++)
                cin >> board[row][col];
    }

    bool solveSudoku() {
        return solve();
    }

    void display() {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++)
                cout << board[row][col] << " ";
            cout << endl;
        }
    }
};

int main() {
    Sudoku game;
    cout<<"Enter 9X9 matrix (0 for space):"<<endl;
    game.inputBoard();
    if (game.solveSudoku()) {
    	cout<<"\n\nSolution"<<endl;
        game.display();
    } else {
        cout << "No solution exists" << endl;
    }
    return 0;
}
