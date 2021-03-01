#include <iostream>
#include <cmath>
using namespace std;

int queens_placed = 0;

bool ok(int board[8][8], int row, int col) {
	// Vertical + Horizontal Test
    for (int i = 0; i < 8; i++) {
    	if (board[row][i] == 1 || board[i][col] == 1) {
    		return false;
		}
	}
	// Left-Upper Diagonal Test
	for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
      	if (board[i][j] == 1) {
         	return false;
        }
    }
    // Left-Lower Diagonal Test
    for (int i = row, j = col; j >= 0 && i < 8; i++, j--) {
      	if (board[i][j] == 1) {
         	return false;
        }
    }
    // Right-Upper Diagonal Test
    for (int i = row, j = col; i < 8 && j < 8; i++, j++) {
    	if (board[i][j] == 1) {
    		return false;
		}
	}
	// Right-Lower Diagonal Test
	for (int i = row, j = col; j < 8 && i >= 0; i--, j++) {
		if (board[i][j] == 1) {
    		return false;
		}
	}
	return true;
}


void fancy_print(int board[][8]) {
    int i, j, k, l; //i = board row count(8), j = board collumn count(8) 
					//k = box row count(5), l = box collumn count(7)

    typedef char box[5][7];
    box bb, wb, bq, wq, *fancy_board[8][8];

    cout << "Queens Placed: " << ++queens_placed << endl;

    // Make bb a block box, wb=white box, bq=black queen and wq=white queen
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 7; j++) {
            wb[i][j] = ' ';
            bq[i][j] = ' ';
            bb[i][j] = char(219);
            wq[i][j] = char(219);
        }
    }

    for (i = 1; i <= 3; i++) {
        for (j = 1; j <= 5; j++) {
            if (i != 1 || j%2 == 1) {
                bq[i][j] = char(219);
                wq[i][j] = ' ';
            } 
        }
    }

    // Fill board with pointers to bb and wb in alternate positions
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (board[i][j] == 1) {
                if ((i + j) % 2 == 0) fancy_board[i][j] = &bq;
                else fancy_board[i][j] = &wq;
            }
            else {
                if ((i + j) % 2 == 0) fancy_board[i][j] = &wb;
                else fancy_board[i][j] = &bb;
            }
        }
    }

    // Upper border of the board
    cout << "    ";
    for (i = 0; i < 7 * 8 + 1; i++) {
		cout << '_';
	}
    cout << endl;

    // Print the board
    for (i = 0; i < 8; i++) {
        for(k = 0; k < 5; k++) {
            cout << "    " << "|"; 
            for (j = 0; j < 8; j++) {
                for (l = 0; l < 7; l++) {
                    cout << (*fancy_board[i][j])[k][l];
                }
        	}
        cout << '|' << endl; 
        }
	}
    // Lower border of the board
    cout << "    ";
    for (i = 0; i < 7 * 8 + 1; i++) {
        cout << char(196);
    }
    cout << "|" << endl;
}

int main() {
	int board[8][8] = {0};
	int row, col;
	string command;
	while (queens_placed != 8) {
		cout << "Type p to Place, d to delete, r to Reset, e to Exit: ";
		cin >> command;
		if (command == "p") {
			cout << "Input Row and Collumn (Row Col): ";
			cin >> row >> col;
			if (row < 0 || row > 7 || col < 0 || col > 7) {
				cout << "Invalid Inputs" << endl;
			} else if (ok(board, row, col)) {
				board[row][col] = 1;
				fancy_print(board);
			} else {
				cout << "Invalid Placement" << endl;
			}
		} else if (command == "r") {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					board[i][j] = 0;
				}
			}
			queens_placed = -1;
			fancy_print(board);
		} else if (command == "d") {
			cout << "Input Row and Collumn for deletion(Row Col): ";
			cin >> row >> col;
			if (row < 0 || row > 7 || col < 0 || col > 7) {
				cout << "Invalid Inputs" << endl;
			} else if (board[row][col] == 0) {
				cout << "No Queen to remove" << endl;
			} else {
				board[row][col] = 0;
				queens_placed -= 2;
				fancy_print(board);
			}
		} else if (command == "e") {
			break;
		}
	}
	
	if (queens_placed == 8) {
		cout << "8 Queens Sucessfully Placed!";
	}
	
	return 0;
}
