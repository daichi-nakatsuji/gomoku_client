#include <stdio.h>

#define SIZE 15

void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '-';
        }
    }
}

void printBoard(char board[SIZE][SIZE]) {
    printf("   ");
    for (int i = 1; i <= SIZE; i++) {
        printf("%2d ", i);
    }
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf("%2c ", board[i][j]);
        }
        printf("\n");
    }
}

int checkWin(char board[SIZE][SIZE], char player, int row, int col) {
    int consecutiveCount = 0;

    // 横方向
    for (int i = col - 4; i <= col; i++) {
        if (i < 0 || i >= SIZE) continue;
        if (board[row][i] == player) {
            consecutiveCount++;
            if (consecutiveCount == 5) return 1; // 勝利
        } else {
            consecutiveCount = 0;
        }
    }

    // 縦方向
    consecutiveCount = 0;
    for (int i = row - 4; i <= row; i++) {
        if (i < 0 || i >= SIZE) continue;
        if (board[i][col] == player) {
            consecutiveCount++;
            if (consecutiveCount == 5) return 1; // 勝利
        } else {
            consecutiveCount = 0;
        }
    }

    // 斜め方向 (左上から右下)
    consecutiveCount = 0;
    for (int i = -4; i <= 0; i++) {
        int r = row + i;
        int c = col + i;
        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) continue;
        if (board[r][c] == player) {
            consecutiveCount++;
            if (consecutiveCount == 5) return 1; // 勝利
        } else {
            consecutiveCount = 0;
        }
    }

    // 斜め方向 (右上から左下)
    consecutiveCount = 0;
    for (int i = -4; i <= 0; i++) {
        int r = row + i;
        int c = col - i;
        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) continue;
        if (board[r][c] == player) {
            consecutiveCount++;
            if (consecutiveCount == 5) return 1; // 勝利
        } else {
            consecutiveCount = 0;
        }
    }

    return 0; // 勝利なし
}

// 禁じ手のチェック
int checkForbiddenMoves(char board[SIZE][SIZE], int row, int col, char player) {
    // 三々の禁じ手
    if ((row >= 1 && row <= SIZE - 2 && col >= 1 && col <= SIZE - 2) &&
        ((board[row - 1][col - 1] == player && board[row + 1][col + 1] == player && board[row - 2][col - 2] == player) ||
         (board[row - 1][col + 1] == player && board[row + 1][col - 1] == player && board[row - 2][col + 2] == player))) {
        return 1;
    }

    // 四々の禁じ手
    if ((row >= 1 && row <= SIZE - 2 && col >= 1 && col <= SIZE - 2) &&
        ((board[row - 1][col] == player && board[row + 1][col] == player && board[row - 2][col] == player) ||
         (board[row][col - 1] == player && board[row][col + 1] == player && board[row][col - 2] == player))) {
        return 1;
    }

    // 長連の禁じ手
    int consecutiveCount = 1;
    // 横方向
    for (int i = col - 1; i >= 0 && board[row][i] == player; i--) {
        consecutiveCount++;
    }
    for (int i = col + 1; i < SIZE && board[row][i] == player; i++) {
        consecutiveCount++;
    }
    if (consecutiveCount >= 5) {
        return 1;
    }

    consecutiveCount = 1;
    // 縦方向
    for (int i = row - 1; i >= 0 && board[i][col] == player; i--) {
        consecutiveCount++;
    }
    for (int i = row + 1; i < SIZE && board[i][col] == player; i++) {
        consecutiveCount++;
    }
    if (consecutiveCount >= 5) {
        return 1;
    }

    return 0; // 禁じ手なし
}

// 引き分け判定
int checkDraw(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == '-') {
                return 0; // ボードがまだ埋まっていない
            }
        }
    }
    return 1; // ボードが埋まっている
}

int main() {
    char board[SIZE][SIZE];
    int row, col;
    char currentPlayer = 'B'; // 黒石が先手

    initializeBoard(board);
    
    do {
        printBoard(board);

        // プレイヤーに次の手を入力させる
        printf("Player %c, enter your move (row [1-%d] and column [1-%d]): ", currentPlayer, SIZE, SIZE);
        scanf("%d,%d", &row, &col);
        row--; // 入力を0-indexに変換
        col--;

        // 有効な手かどうかを確認
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != '-' || checkForbiddenMoves(board, row, col, currentPlayer)) {
            printf("Invalid move. Try again.\n");
            continue;
        }

        // 石を置く
        board[row][col] = currentPlayer;

        // 引き分け判定
        if (checkDraw(board)) {
            printBoard(board);
            printf("The game is a draw!\n");
            break;
        }

        // 勝利判定
        if (checkWin(board, currentPlayer, row, col)) {
            printBoard(board);
            printf("Player %c wins!\n", currentPlayer);
            break;
        }

        // プレイヤーを切り替える
        currentPlayer = (currentPlayer == 'B') ? 'W' : 'B';

    } while (1);

    return 0;
}
