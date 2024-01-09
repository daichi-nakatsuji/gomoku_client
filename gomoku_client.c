//http://blog.livedoor.jp/akf0/archives/51585502.html
//-lws2_32

#include <stdio.h>
#include <winsock2.h>

#define SIZE 15
int your = 1;			//�����̎��1�ɐݒ�
int com = 2;			//����̎���Q�ɐݒ�

/*�����̕]���l�̏d�� �K�X�ǉ�*/
double W1_1=0.9; //�l�l�i���g����U�̂Ƃ��łĂ�j
double W1_2=0.8; //�O�l
double W1_3=0.7; //�S�A
double W1_4=0.5; //�O�O (���g����U�̂Ƃ��łĂ�j
double W1_5=0.4; //�O
double W1_6=0.3; //��
double W1_7=0.2; //��

/*����̕]���l�̏d�� �K�X�ǉ�*/
double W2_1=0.8; //�O�l
double W2_2=0.7; //�l�l(���肪��U�̂Ƃ��ł����)
double W2_3=0.6; //�l�A
double W2_4=0.5; //�O�X(���肪��U�̂Ƃ��ł����)
double W2_5=0.4; //�O�A
double W2_6=0.3; //2�A
double W2_7=0.2; //��A

// �Ղ̏�����(�ǉ������A�폜�s��)
void initializeBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;		//�󂢂Ă���ꏊ��0�ɐݒ�
        }
    }
}

//�l�A�𔻒�
int checkFourInRow(int board[SIZE][SIZE], int row, int col, int player) {

    // �������̔���
    int count = 1;
    for (int i = 1; i < 4; i++) {
        if (col + i < SIZE && board[row][col + i] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 4; i++) {
        if (col - i >= 0 && board[row][col - i] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 4) {
        return 1;
    }

    // �c�����̔���
    count = 1;
    for (int i = 1; i < 4; i++) {
        if (row + i < SIZE && board[row + i][col] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 4; i++) {
        if (row - i >= 0 && board[row - i][col] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 4) {
        return 1;
    }

    // �΂ߕ����i���ォ��E���j�̔���
    count = 1;
    for (int i = 1; i < 4; i++) {
        if (row + i < SIZE && col + i < SIZE && board[row + i][col + i] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 4; i++) {
        if (row - i >= 0 && col - i >= 0 && board[row - i][col - i] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 4) {
        return 1;
    }

    // �΂ߕ����i��������E��j�̔���
    count = 1;
    for (int i = 1; i < 4; i++) {
        if (row - i >= 0 && col + i < SIZE && board[row - i][col + i] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 4; i++) {
        if (row + i < SIZE && col - i >= 0 && board[row + i][col - i] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 4) {
        return 1;
    }

    return 0;
}

// ��A���������Ă��邩�𔻒肷��֐�
int checkOneInRow(int board[SIZE][SIZE], int row, int col, int player) {
    // �������̔���
    if (col + 1 < SIZE && board[row][col + 1] == player) {
        return 1;
    }
    if (col - 1 >= 0 && board[row][col - 1] == player) {
        return 1;
    }

    // �c�����̔���
    if (row + 1 < SIZE && board[row + 1][col] == player) {
        return 1;
    }
    if (row - 1 >= 0 && board[row - 1][col] == player) {
        return 1;
    }

    // �΂ߕ����i���ォ��E���j�̔���
    if (row + 1 < SIZE && col + 1 < SIZE && board[row + 1][col + 1] == player) {
        return 1;
    }
    if (row - 1 >= 0 && col - 1 >= 0 && board[row - 1][col - 1] == player) {
        return 1;
    }

    // �΂ߕ����i��������E��j�̔���
    if (row - 1 >= 0 && col + 1 < SIZE && board[row - 1][col + 1] == player) {
        return 1;
    }
    if (row + 1 < SIZE && col - 1 >= 0 && board[row + 1][col - 1] == player) {
        return 1;
    }

    return 0;
}

// 2�A���������Ă��邩�𔻒肷��֐�
int checkTwoInRow(int board[SIZE][SIZE], int row, int col, int player) {
    // �������̔���
    if ((col + 1 < SIZE && board[row][col + 1] == player) ||
        (col - 1 >= 0 && board[row][col - 1] == player)) {
        return 1;
    }

    // �c�����̔���
    if ((row + 1 < SIZE && board[row + 1][col] == player) ||
        (row - 1 >= 0 && board[row - 1][col] == player)) {
        return 1;
    }

    // �΂ߕ����i���ォ��E���j�̔���
    if ((row + 1 < SIZE && col + 1 < SIZE && board[row + 1][col + 1] == player) ||
        (row - 1 >= 0 && col - 1 >= 0 && board[row - 1][col - 1] == player)) {
        return 1;
    }

    // �΂ߕ����i��������E��j�̔���
    if ((row - 1 >= 0 && col + 1 < SIZE && board[row - 1][col + 1] == player) ||
        (row + 1 < SIZE && col - 1 >= 0 && board[row + 1][col - 1] == player)) {
        return 1;
    }

    return 0;
}

// �O�A���������Ă��邩�𔻒肷��֐�
int checkThreeInRow(int board[SIZE][SIZE], int row, int col,int player) {
    // �������̔���
    int count = 1;
    for (int i = 1; i < 3; i++) {
        if (col + i < SIZE && board[row][col + i] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 3; i++) {
        if (col - i >= 0 && board[row][col - i] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 3) {
        return 1;
    }

    // �c�����̔���
    count = 1;
    for (int i = 1; i < 3; i++) {
        if (row + i < SIZE && board[row + i][col] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 3; i++) {
        if (row - i >= 0 && board[row - i][col] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 3) {
        return 1;
    }

    // �΂ߕ����i���ォ��E���j�̔���
    count = 1;
    for (int i = 1; i < 3; i++) {
        if (row + i < SIZE && col + i < SIZE && board[row + i][col + i] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 3; i++) {
        if (row - i >= 0 && col - i >= 0 && board[row - i][col - i] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 3) {
        return 1;
    }

    // �΂ߕ����i��������E��j�̔���
    count = 1;
    for (int i = 1; i < 3; i++) {
        if (row - i >= 0 && col + i < SIZE && board[row - i][col + i] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 3; i++) {
        if (row + i < SIZE && col - i >= 0 && board[row + i][col - i] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 3) {
        return 1;
    }

    return 0;
}

//�R���є���(�ǉ������A�폜�s��)
int checkThreeBrock(int board[SIZE][SIZE], int FstPlayer, int SecPlayer, int row, int col, int gradient){
    switch(gradient){
        case 0:     //��
            if((col-4 >= 0 && col+2 < SIZE && board[row][col-4] == SecPlayer && board[row][col-3] == 0 && board[row][col-2] == FstPlayer && board[row][col-1] == FstPlayer && board[row][col+1] == 0 && board[row][col+2] == SecPlayer) ||
               (col-3 >= 0 && col+3 < SIZE && board[row][col-3] == SecPlayer && board[row][col-2] == 0 && board[row][col-1] == FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] == 0 && board[row][col+3] == SecPlayer) ||
               (col-2 >= 0 && col+4 < SIZE && board[row][col-2] == SecPlayer && board[row][col-1] == 0 && board[row][col+1] == FstPlayer && board[row][col+2] == FstPlayer && board[row][col+3] == 0 && board[row][col+4] == SecPlayer)){
                return 0;
            }
            if((col-4 >= 0 && col+1 < SIZE && board[row][col-4] == 0 && board[row][col-3] == FstPlayer && board[row][col-2] == FstPlayer && board[row][col-1] == 0 && board[row][col+1] == 0) ||
               (col-4 >= 0 && col+1 < SIZE && board[row][col-4] == 0 && board[row][col-3] == FstPlayer && board[row][col-2] == 0 && board[row][col-1] == FstPlayer && board[row][col+1] == 0) || 
               (col-4 >= 0 && col+2 < SIZE && board[row][col-4] == 0 && board[row][col-3] == 0 && board[row][col-2] == FstPlayer && board[row][col-1] == FstPlayer && board[row][col+1] == 0 && board[row][col+2] == 0) ||
               (col-3 >= 0 && col+2 < SIZE && board[row][col-3] == 0 && board[row][col-2] == FstPlayer && board[row][col-1] == 0 && board[row][col+1] == FstPlayer && board[row][col+2] == 0) ||
               (col-2 >= 0 && col+3 < SIZE && board[row][col-2] == 0 && board[row][col-1] == FstPlayer && board[row][col+1] == 0 && board[row][col+2] == FstPlayer && board[row][col+3] == 0) ||
               (col-3 >= 0 && col+3 < SIZE && board[row][col-3] == 0 && board[row][col-2] == 0 && board[row][col-1] == FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] == 0 && board[row][col+3] == 0) ||
               (col-1 >= 0 && col+4 < SIZE && board[row][col-1] == 0 && board[row][col+1] == FstPlayer && board[row][col+2] == 0 && board[row][col+3] == FstPlayer && board[row][col+4] == 0) ||
               (col-1 >= 0 && col+4 < SIZE && board[row][col-1] == 0 && board[row][col+1] == 0 && board[row][col+2] == FstPlayer && board[row][col+3] == FstPlayer && board[row][col+4] == 0) ||
               (col-2 >= 0 && col+4 < SIZE && board[row][col-2] == 0 && board[row][col-1] == 0 && board[row][col+1] == FstPlayer && board[row][col+2] == FstPlayer && board[row][col+3] == 0 && board[row][col+4] == 0)) {
                return 1;
            }
            break;
        case 1:     //�c
            if((row-4 >= 0 && row+2 < SIZE && board[row-4][col] == SecPlayer && board[row-3][col] == 0 && board[row-2][col] == FstPlayer && board[row-1][col] == FstPlayer && board[row+1][col] == 0 && board[row+2][col] == SecPlayer) ||
               (row-3 >= 0 && row+3 < SIZE && board[row-3][col] == SecPlayer && board[row-2][col] == 0 && board[row-1][col] == FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] == 0 && board[row+3][col] == SecPlayer) ||
               (row-2 >= 0 && row+4 < SIZE && board[row-2][col] == SecPlayer && board[row-1][col] == 0 && board[row+1][col] == FstPlayer && board[row+2][col] == FstPlayer && board[row+3][col] == 0 && board[row+4][col] == SecPlayer)){
                return 0;
            }
            if((row-4 >= 0 && row+1 < SIZE && board[row-4][col] == 0 && board[row-3][col] == FstPlayer && board[row-2][col] == FstPlayer && board[row-1][col] == 0 && board[row+1][col] == 0) ||
               (row-4 >= 0 && row+1 < SIZE && board[row-4][col] == 0 && board[row-3][col] == FstPlayer && board[row-2][col] == 0 && board[row-1][col] == FstPlayer && board[row+1][col] == 0) || 
               (row-4 >= 0 && row+2 < SIZE && board[row-4][col] == 0 && board[row-3][col] == 0 && board[row-2][col] == FstPlayer && board[row-1][col] == FstPlayer && board[row+1][col] == 0 && board[row+2][col] == 0) ||
               (row-3 >= 0 && row+2 < SIZE && board[row-3][col] == 0 && board[row-2][col] == FstPlayer && board[row-1][col] == 0 && board[row+1][col] == FstPlayer && board[row+2][col] == 0) ||
               (row-2 >= 0 && row+3 < SIZE && board[row-2][col] == 0 && board[row-1][col] == FstPlayer && board[row+1][col] == 0 && board[row+2][col] == FstPlayer && board[row+3][col] == 0) ||
               (row-3 >= 0 && row+3 < SIZE && board[row-3][col] == 0 && board[row-2][col] == 0 && board[row-1][col] == FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] == 0 && board[row+3][col] == 0) ||
               (row-1 >= 0 && row+4 < SIZE && board[row-1][col] == 0 && board[row+1][col] == FstPlayer && board[row+2][col] == 0 && board[row+3][col] == FstPlayer && board[row+4][col] == 0) ||
               (row-1 >= 0 && row+4 < SIZE && board[row-1][col] == 0 && board[row+1][col] == 0 && board[row+2][col] == FstPlayer && board[row+3][col] == FstPlayer && board[row+4][col] == 0) ||
               (row-2 >= 0 && row+4 < SIZE && board[row-2][col] == 0 && board[row-1][col] == 0 && board[row+1][col] == FstPlayer && board[row+2][col] == FstPlayer && board[row+3][col] == 0 && board[row+4][col] == 0)) {
                return 1;
            }
            break;
        case 2:     //���ォ��E��
            if((col-4 >= 0 && col+2 < SIZE && row-4 >= 0 && row+2 < SIZE && board[row-4][col-4] == SecPlayer && board[row-3][col-3] == 0 && board[row-2][col-2] == FstPlayer && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == 0 && board[row+2][col+2] == SecPlayer) ||
               (col-3 >= 0 && col+3 < SIZE && row-3 >= 0 && row+3 < SIZE && board[row-3][col-3] == SecPlayer && board[row-2][col-2] == 0 && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == 0 && board[row+3][col+3] == SecPlayer) ||
               (col-2 >= 0 && col+4 < SIZE && row-2 >= 0 && row+4 < SIZE && board[row-2][col-2] == SecPlayer && board[row-1][col-1] == 0 && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == 0 && board[row+4][col+4] == SecPlayer)){
                return 0;
            }
            if((col-4 >= 0 && col+1 < SIZE && row-4 >= 0 && row+1 < SIZE && board[row-4][col-4] == 0 && board[row-3][col-3] == FstPlayer && board[row-2][col-2] == FstPlayer && board[row-1][col-1] == 0 && board[row+1][col+1] == 0) ||
               (col-4 >= 0 && col+1 < SIZE && row-4 >= 0 && row+1 < SIZE && board[row-4][col-4] == 0 && board[row-3][col-3] == FstPlayer && board[row-2][col-2] == 0 && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == 0) || 
               (col-4 >= 0 && col+2 < SIZE && row-4 >= 0 && row+2 < SIZE && board[row-4][col-4] == 0 && board[row-3][col-3] == 0 && board[row-2][col-2] == FstPlayer && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == 0 && board[row+2][col+2] == 0) ||
               (col-3 >= 0 && col+2 < SIZE && row-3 >= 0 && row+2 < SIZE && board[row-3][col-3] == 0 && board[row-2][col-2] == FstPlayer && board[row-1][col-1] == 0 && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == 0) ||
               (col-2 >= 0 && col+3 < SIZE && row-2 >= 0 && row+3 < SIZE && board[row-2][col-2] == 0 && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == 0 && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == 0) ||
               (col-3 >= 0 && col+3 < SIZE && row-3 >= 0 && row+3 < SIZE && board[row-3][col-3] == 0 && board[row-2][col-2] == 0 && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == 0 && board[row+3][col+3] == 0) ||
               (col-1 >= 0 && col+4 < SIZE && row-1 >= 0 && row+4 < SIZE && board[row-1][col-1] == 0 && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == 0 && board[row+3][col+3] == FstPlayer && board[row+4][col+4] == 0) ||
               (col-1 >= 0 && col+4 < SIZE && row-1 >= 0 && row+4 < SIZE && board[row-1][col-1] == 0 && board[row+1][col+1] == 0 && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == FstPlayer && board[row+4][col+4] == 0) ||
               (col-2 >= 0 && col+4 < SIZE && row-2 >= 0 && row+4 < SIZE && board[row-2][col-2] == 0 && board[row-1][col-1] == 0 && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == 0 && board[row+4][col+4] == 0)) {
                return 1;
            }
            break;
        case 3:     //�E�ォ�獶��
            if((col-4 >= 0 && col+2 < SIZE && row+4 >= 0 && row-2 < SIZE && board[row+4][col-4] == SecPlayer && board[row+3][col-3] == 0 && board[row+2][col-2] == FstPlayer && board[row+1][col-1] == FstPlayer && board[row-1][col+1] == 0 && board[row-2][col+2] == SecPlayer) ||
               (col-3 >= 0 && col+3 < SIZE && row+3 >= 0 && row-3 < SIZE && board[row+3][col-3] == SecPlayer && board[row+2][col-2] == 0 && board[row+1][col-1] == FstPlayer && board[row-1][col+1] == FstPlayer && board[row-2][col+2] == 0 && board[row-3][col+3] == SecPlayer) ||
               (col-2 >= 0 && col+4 < SIZE && row+2 >= 0 && row-4 < SIZE && board[row+2][col-2] == SecPlayer && board[row+1][col-1] == 0 && board[row-1][col+1] == FstPlayer && board[row-2][col+2] == FstPlayer && board[row-3][col+3] == 0 && board[row-4][col+4] == SecPlayer)){
                return 0;
            }
            if((col-4 >= 0 && col+1 < SIZE && row+4 >= 0 && row-1 < SIZE && board[row+4][col-4] == 0 && board[row+3][col-3] == FstPlayer && board[row+2][col-2] == FstPlayer && board[row+1][col-1] == 0 && board[row-1][col+1] == 0) ||
               (col-4 >= 0 && col+1 < SIZE && row+4 >= 0 && row-1 < SIZE && board[row+4][col-4] == 0 && board[row+3][col-3] == FstPlayer && board[row+2][col-2] == 0 && board[row+1][col-1] == FstPlayer && board[row-1][col+1] == 0) || 
               (col-4 >= 0 && col+2 < SIZE && row+4 >= 0 && row-2 < SIZE && board[row+4][col-4] == 0 && board[row+3][col-3] == 0 && board[row+2][col-2] == FstPlayer && board[row+1][col-1] == FstPlayer && board[row-1][col+1] == 0 && board[row-2][col+2] == 0) ||
               (col-3 >= 0 && col+2 < SIZE && row+3 >= 0 && row-2 < SIZE && board[row+3][col-3] == 0 && board[row+2][col-2] == FstPlayer && board[row+1][col-1] == 0 && board[row-1][col+1] == FstPlayer && board[row-2][col+2] == 0) ||
               (col-2 >= 0 && col+3 < SIZE && row+2 >= 0 && row-3 < SIZE && board[row+2][col-2] == 0 && board[row+1][col-1] == FstPlayer && board[row-1][col+1] == 0 && board[row-2][col+2] == FstPlayer && board[row-3][col+3] == 0) ||
               (col-3 >= 0 && col+3 < SIZE && row+3 >= 0 && row-3 < SIZE && board[row+3][col-3] == 0 && board[row+2][col-2] == 0 && board[row+1][col-1] == FstPlayer && board[row-1][col+1] == FstPlayer && board[row-2][col+2] == 0 && board[row-3][col+3] == 0) ||
               (col-1 >= 0 && col+4 < SIZE && row+1 >= 0 && row-4 < SIZE && board[row+1][col-1] == 0 && board[row-1][col+1] == FstPlayer && board[row-2][col+2] == 0 && board[row-3][col+3] == FstPlayer && board[row-4][col+4] == 0) ||
               (col-1 >= 0 && col+4 < SIZE && row+1 >= 0 && row-4 < SIZE && board[row+1][col-1] == 0 && board[row-1][col+1] == 0 && board[row-2][col+2] == FstPlayer && board[row-3][col+3] == FstPlayer && board[row-4][col+4] == 0) ||
               (col-2 >= 0 && col+4 < SIZE && row+2 >= 0 && row-4 < SIZE && board[row+2][col-2] == 0 && board[row+1][col-1] == 0 && board[row-1][col+1] == FstPlayer && board[row-2][col+2] == FstPlayer && board[row-3][col+3] == 0 && board[row-4][col+4] == 0)) {
                return 1;
            }
            break;
        default:
            break;
    }

    return 0;
}

//4���є���(�ǉ������A�폜�s��)
int checkFourBrock(int board[SIZE][SIZE], int FstPlayer, int SecPlayer, int row, int col, int gradient){
    switch(gradient){
        case 0:     //��
            if((col-4 >= 0 && col+4 < SIZE && board[row][col-5] != FstPlayer && board[row][col-4] == FstPlayer && board[row][col-3] == FstPlayer && board[row][col-2] == FstPlayer && 
                    board[row][col-1] == 0 && board[row][col+1] == 0 && board[row][col+2] == FstPlayer && board[row][col+3] == FstPlayer && board[row][col+4] == FstPlayer && board[row][col+5] != FstPlayer) ||
               (col-3 >= 0 && col+3 < SIZE && board[row][col-4] != FstPlayer && board[row][col-3] == FstPlayer && board[row][col-2] == 0 && 
                    board[row][col-1] == FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] == 0 && board[row][col+3] == FstPlayer && board[row][col+4] != FstPlayer) ||
               (col-4 >= 0 && col+3 < SIZE && board[row][col-5] != FstPlayer && board[row][col-4] == FstPlayer && board[row][col-3] == FstPlayer && board[row][col-2] == 0 && 
                    board[row][col-1] == FstPlayer && board[row][col+1] == 0 && board[row][col+2] == FstPlayer && board[row][col+3] == FstPlayer && board[row][col+4] != FstPlayer) ||
               (col-3 >= 0 && col+4 < SIZE && board[row][col+5] != FstPlayer && board[row][col+4] == FstPlayer && board[row][col+3] == FstPlayer && board[row][col+2] == 0 && 
                    board[row][col+1] == FstPlayer && board[row][col-1] == 0 && board[row][col-2] == FstPlayer && board[row][col-3] == FstPlayer && board[row][col-4] != FstPlayer) ||
               (col-4 >= 0 && col+2 < SIZE && board[row][col-5] != FstPlayer && board[row][col-4] == FstPlayer && board[row][col-3] == 0 && board[row][col-2] == FstPlayer && 
                    board[row][col-1] == FstPlayer && board[row][col+1] == 0 && board[row][col+2] == FstPlayer && board[row][col+3] != FstPlayer) ||
               (col-2 >= 0 && col+4 < SIZE && board[row][col+5] != FstPlayer && board[row][col+4] == FstPlayer && board[row][col+3] == 0 && board[row][col+2] == FstPlayer && 
                    board[row][col+1] == FstPlayer && board[row][col-1] == 0 && board[row][col-2] == FstPlayer && board[row][col-3] != FstPlayer)){
                return 2; //������̎l�l��
            }

            if((col-3 >= 0 && col+1 < SIZE && board[row][col-4] != FstPlayer && board[row][col-3] == FstPlayer && board[row][col-2] == FstPlayer && board[row][col-1] == 0 && board[row][col+1] == FstPlayer && board[row][col+2] != FstPlayer) ||
               (col-3 >= 0 && col+1 < SIZE && board[row][col-4] != FstPlayer && board[row][col-3] == FstPlayer && board[row][col-2] == 0 && board[row][col-1] == FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] != FstPlayer) ||
               (col-2 >= 0 && col+1 < SIZE && board[row][col-3] != FstPlayer && board[row][col-2] == FstPlayer && board[row][col-1] == FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] != FstPlayer) || 
               (col-2 >= 0 && col+2 < SIZE && board[row][col-3] != FstPlayer && board[row][col-2] == FstPlayer && board[row][col-1] == FstPlayer && board[row][col+1] == 0 && board[row][col+2] == FstPlayer && board[row][col+3] != FstPlayer) ||
               (col-1 >= 0 && col+3 < SIZE && board[row][col-2] != FstPlayer && board[row][col-1] == FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] == 0 && board[row][col+3] == FstPlayer && board[row][col+4] != FstPlayer) ||
               (col-2 >= 0 && col+2 < SIZE && board[row][col-3] != FstPlayer && board[row][col-2] == FstPlayer && board[row][col-1] == 0 && board[row][col+1] == FstPlayer && board[row][col+2] == FstPlayer && board[row][col+3] != FstPlayer) ||
               (col-1 >= 0 && col+2 < SIZE && board[row][col-2] != FstPlayer && board[row][col-1] == FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] == FstPlayer && board[row][col+3] != FstPlayer) || 
               (col-1 >= 0 && col+3 < SIZE && board[row][col-2] != FstPlayer && board[row][col-1] == FstPlayer && board[row][col+1] == 0 && board[row][col+2] == FstPlayer && board[row][col+3] == FstPlayer && board[row][col+4] != FstPlayer) ||
               (col+3 < SIZE && board[row][col-1] != FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] == FstPlayer && board[row][col+3] == FstPlayer && board[row][col+4] != FstPlayer) ||
               (col+4 < SIZE && board[row][col-1] != FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] == 0 && board[row][col+3] == FstPlayer && board[row][col+4] == FstPlayer && board[row][col+5] != FstPlayer) ||
               (col+4 < SIZE && board[row][col-1] != FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] == FstPlayer && board[row][col+3] == 0 && board[row][col+4] == FstPlayer && board[row][col+5] != FstPlayer) ||
               (col+4 < SIZE && board[row][col-1] != FstPlayer && board[row][col+1] == 0 && board[row][col+2] == FstPlayer && board[row][col+3] == FstPlayer && board[row][col+4] == FstPlayer && board[row][col+5] != FstPlayer) ||
               (col-3 >= 0 && board[row][col+1] != FstPlayer && board[row][col-1] == FstPlayer && board[row][col-2] == FstPlayer && board[row][col-3] == FstPlayer && board[row][col-4] != FstPlayer) ||
               (col-4 >= 0 && board[row][col+1] != FstPlayer && board[row][col-1] == FstPlayer && board[row][col-2] == 0 && board[row][col-3] == FstPlayer && board[row][col-4] == FstPlayer && board[row][col-5] != FstPlayer) ||
               (col-4 >= 0 && board[row][col+1] != FstPlayer && board[row][col-1] == FstPlayer && board[row][col-2] == FstPlayer && board[row][col-3] == 0 && board[row][col-4] == FstPlayer && board[row][col-5] != FstPlayer) ||
               (col-4 >= 0 && board[row][col+1] != FstPlayer && board[row][col-1] == 0 && board[row][col-2] == FstPlayer && board[row][col-3] == FstPlayer && board[row][col-4] == FstPlayer && board[row][col-5] != FstPlayer)) {
                return 1;
            }
            break;
        case 1:     //�c
            if((row-4 >= 0 && row+4 < SIZE && board[row-5][col] != FstPlayer && board[row-4][col] == FstPlayer && board[row-3][col] == FstPlayer && board[row-2][col] == FstPlayer && 
                    board[row-1][col] == 0 && board[row+1][col] == 0 && board[row+2][col] == FstPlayer && board[row+3][col] == FstPlayer && board[row+4][col] == FstPlayer && board[row+5][col] != FstPlayer) ||
               (row-3 >= 0 && row+3 < SIZE && board[row-4][col] != FstPlayer && board[row-3][col] == FstPlayer && board[row-2][col] == 0 && 
                    board[row-1][col] == FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] == 0 && board[row+3][col] == FstPlayer && board[row+4][col] != FstPlayer) ||
               (row-4 >= 0 && row+3 < SIZE && board[row-5][col] != FstPlayer && board[row-4][col] == FstPlayer && board[row-3][col] == FstPlayer && board[row-2][col] == 0 && 
                    board[row-1][col] == FstPlayer && board[row+1][col] == 0 && board[row+2][col] == FstPlayer && board[row+3][col] == FstPlayer && board[row+4][col] != FstPlayer) ||
               (row-3 >= 0 && row+4 < SIZE && board[row+5][col] != FstPlayer && board[row+4][col] == FstPlayer && board[row+3][col] == FstPlayer && board[row+2][col] == 0 && 
                    board[row+1][col] == FstPlayer && board[row-1][col] == 0 && board[row-2][col] == FstPlayer && board[row-3][col] == FstPlayer && board[row-4][col] != FstPlayer) ||
               (row-4 >= 0 && row+2 < SIZE && board[row-5][col] != FstPlayer && board[row-4][col] == FstPlayer && board[row-3][col] == 0 && board[row-2][col] == FstPlayer && 
                    board[row-1][col] == FstPlayer && board[row+1][col] == 0 && board[row+2][col] == FstPlayer && board[row+3][col] != FstPlayer) ||
               (row-2 >= 0 && row+4 < SIZE && board[row+5][col] != FstPlayer && board[row+4][col] == FstPlayer && board[row+3][col] == 0 && board[row+2][col] == FstPlayer && 
                    board[row+1][col] == FstPlayer && board[row-1][col] == 0 && board[row-2][col] == FstPlayer && board[row-3][col] != FstPlayer)){
                return 2; //������̎l�l��
            }

            if((row-3 >= 0 && row+1 < SIZE && board[row-4][col] != FstPlayer && board[row-3][col] == FstPlayer && board[row-2][col] == FstPlayer && board[row-1][col] == 0 && board[row+1][col] == FstPlayer && board[row+2][col] != FstPlayer) ||
               (row-3 >= 0 && row+1 < SIZE && board[row-4][col] != FstPlayer && board[row-3][col] == FstPlayer && board[row-2][col] == 0 && board[row-1][col] == FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] != FstPlayer) ||
               (row-2 >= 0 && row+1 < SIZE && board[row-3][col] != FstPlayer && board[row-2][col] == FstPlayer && board[row-1][col] == FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] != FstPlayer) || 
               (row-2 >= 0 && row+2 < SIZE && board[row-3][col] != FstPlayer && board[row-2][col] == FstPlayer && board[row-1][col] == FstPlayer && board[row+1][col] == 0 && board[row+2][col] == FstPlayer && board[row+3][col] != FstPlayer) ||
               (row-1 >= 0 && row+3 < SIZE && board[row-2][col] != FstPlayer && board[row-1][col] == FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] == 0 && board[row+3][col] == FstPlayer && board[row+4][col] != FstPlayer) ||
               (row-2 >= 0 && row+2 < SIZE && board[row-3][col] != FstPlayer && board[row-2][col] == FstPlayer && board[row-1][col] == 0 && board[row+1][col] == FstPlayer && board[row+2][col] == FstPlayer && board[row+3][col] != FstPlayer) ||
               (row-1 >= 0 && row+2 < SIZE && board[row-2][col] != FstPlayer && board[row-1][col] == FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] == FstPlayer && board[row+3][col] != FstPlayer) || 
               (row-1 >= 0 && row+3 < SIZE && board[row-2][col] != FstPlayer && board[row-1][col] == FstPlayer && board[row+1][col] == 0 && board[row+2][col] == FstPlayer && board[row+3][col] == FstPlayer && board[row+4][col] != FstPlayer) ||
               (row+3 < SIZE && board[row-1][col] != FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] == FstPlayer && board[row+3][col] == FstPlayer && board[row+4][col] != FstPlayer) ||
               (row+4 < SIZE && board[row-1][col] != FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] == 0 && board[row+3][col] == FstPlayer && board[row+4][col] == FstPlayer && board[row-5][col] != FstPlayer) ||
               (row+4 < SIZE && board[row-1][col] != FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] == FstPlayer && board[row+3][col] == 0 && board[row+4][col] == FstPlayer && board[row-5][col] != FstPlayer) ||
               (row+4 < SIZE && board[row-1][col] != FstPlayer && board[row+1][col] == 0 && board[row+2][col] == FstPlayer && board[row+3][col] == FstPlayer && board[row+4][col] == FstPlayer && board[row-5][col] != FstPlayer) ||
               (row-3 >= 0 && board[row+1][col] != FstPlayer && board[row-1][col] == FstPlayer && board[row-2][col] == FstPlayer && board[row-3][col] == FstPlayer && board[row-4][col] != FstPlayer) ||
               (row-4 >= 0 && board[row+1][col] != FstPlayer && board[row-1][col] == FstPlayer && board[row-2][col] == 0 && board[row-3][col] == FstPlayer && board[row-4][col] == FstPlayer && board[row-5][col] != FstPlayer) ||
               (row-4 >= 0 && board[row+1][col] != FstPlayer && board[row-1][col] == FstPlayer && board[row-2][col] == FstPlayer && board[row-3][col] == 0 && board[row-4][col] == FstPlayer && board[row-5][col] != FstPlayer) ||
               (row-4 >= 0 && board[row+1][col] != FstPlayer && board[row-1][col] == 0 && board[row-2][col] == FstPlayer && board[row-3][col] == FstPlayer && board[row-4][col] == FstPlayer && board[row-5][col] != FstPlayer)) {
                return 1;
            }

            break;
        case 2:     //���ォ��E��
            if((row-4 >= 0 && row+4 < SIZE && col-4 >= 0 && col+4 < SIZE && board[row-5][col-5] != FstPlayer && board[row-4][col-4] == FstPlayer && board[row-3][col-3] == FstPlayer && board[row-2][col-2] == FstPlayer && 
                    board[row-1][col-1] == 0 && board[row+1][col+1] == 0 && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == FstPlayer && board[row+4][col+4] == FstPlayer && board[row+5][col+5] != FstPlayer) ||
               (row-3 >= 0 && row+3 < SIZE && col-3 >= 0 && col+3 < SIZE && board[row-4][col-4] != FstPlayer && board[row-3][col-3] == FstPlayer && board[row-2][col-2] == 0 && 
                    board[row-1][col-1] == FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == 0 && board[row+3][col+3] == FstPlayer && board[row+4][col+4] != FstPlayer) ||
               (row-4 >= 0 && row+3 < SIZE && col-4 >= 0 && col+3 < SIZE && board[row-5][col-5] != FstPlayer && board[row-4][col-4] == FstPlayer && board[row-3][col-3] == FstPlayer && board[row-2][col-2] == 0 && 
                    board[row-1][col-1] == FstPlayer && board[row+1][col+1] == 0 && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == FstPlayer && board[row+4][col+4] != FstPlayer) ||
               (row-3 >= 0 && row+4 < SIZE && col-3 >= 0 && col+4 < SIZE && board[row+5][col+5] != FstPlayer && board[row+4][col+4] == FstPlayer && board[row+3][col+3] == FstPlayer && board[row+2][col+2] == 0 && 
                    board[row+1][col+1] == FstPlayer && board[row-1][col-1] == 0 && board[row-2][col-2] == FstPlayer && board[row-3][col-3] == FstPlayer && board[row-4][col-4] != FstPlayer) ||
               (row-4 >= 0 && row+2 < SIZE && col-4 >= 0 && col+2 < SIZE && board[row-5][col-5] != FstPlayer && board[row-4][col-4] == FstPlayer && board[row-3][col-3] == 0 && board[row-2][col-2] == FstPlayer && 
                    board[row-1][col-1] == FstPlayer && board[row+1][col+1] == 0 && board[row+2][col+2] == FstPlayer && board[row+3][col+3] != FstPlayer) ||
               (row-2 >= 0 && row+4 < SIZE && col-2 >= 0 && col+4 < SIZE && board[row+5][col+5] != FstPlayer && board[row+4][col+4] == FstPlayer && board[row+3][col+3] == 0 && board[row+2][col+2] == FstPlayer && 
                    board[row+1][col+1] == FstPlayer && board[row-1][col-1] == 0 && board[row-2][col-2] == FstPlayer && board[row-3][col-3] != FstPlayer)){
                return 2; //������̎l�l��
            }

            if((row-3 >= 0 && row+1 < SIZE && col-3 >= 0 && col+1 < SIZE && board[row-4][col-4] != FstPlayer && board[row-3][col-3] == FstPlayer && board[row-2][col-2] == FstPlayer && board[row-1][col-1] == 0 && board[row+1][col+1] == FstPlayer && board[row+2][col+2] != FstPlayer) ||
               (row-3 >= 0 && row+1 < SIZE && col-3 >= 0 && col+1 < SIZE && board[row-4][col-4] != FstPlayer && board[row-3][col-3] == FstPlayer && board[row-2][col-2] == 0 && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] != FstPlayer) ||
               (row-2 >= 0 && row+1 < SIZE && col-2 >= 0 && col+1 < SIZE && board[row-3][col-3] != FstPlayer && board[row-2][col-2] == FstPlayer && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] != FstPlayer) || 
               (row-2 >= 0 && row+2 < SIZE && col-2 >= 0 && col+2 < SIZE && board[row-3][col-3] != FstPlayer && board[row-2][col-2] == FstPlayer && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == 0 && board[row+2][col+2] == FstPlayer && board[row+3][col+3] != FstPlayer) ||
               (row-1 >= 0 && row+3 < SIZE && col-1 >= 0 && col+3 < SIZE && board[row-2][col-2] != FstPlayer && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == 0 && board[row+3][col+3] == FstPlayer && board[row+4][col+4] != FstPlayer) ||
               (row-2 >= 0 && row+2 < SIZE && col-2 >= 0 && col+2 < SIZE && board[row-3][col-3] != FstPlayer && board[row-2][col-2] == FstPlayer && board[row-1][col-1] == 0 && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == FstPlayer && board[row+3][col+3] != FstPlayer) ||
               (row-1 >= 0 && row+2 < SIZE && col-1 >= 0 && col+2 < SIZE && board[row-2][col-2] != FstPlayer && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == FstPlayer && board[row+3][col+3] != FstPlayer) || 
               (row-1 >= 0 && row+3 < SIZE && col-1 >= 0 && col+3 < SIZE && board[row-2][col-2] != FstPlayer && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == 0 && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == FstPlayer && board[row+4][col+4] != FstPlayer) ||
               (row+3 < SIZE && col+3 < SIZE && board[row-1][col-1] != FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == FstPlayer && board[row+4][col+4] != FstPlayer) ||
               (row+4 < SIZE && col+4 < SIZE && board[row-1][col-1] != FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == 0 && board[row+3][col+3] == FstPlayer && board[row+4][col+4] == FstPlayer && board[row-5][col+5] != FstPlayer) ||
               (row+4 < SIZE && col+4 < SIZE && board[row-1][col-1] != FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == 0 && board[row+4][col+4] == FstPlayer && board[row-5][col+5] != FstPlayer) ||
               (row+4 < SIZE && col+4 < SIZE && board[row-1][col-1] != FstPlayer && board[row+1][col+1] == 0 && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == FstPlayer && board[row+4][col+4] == FstPlayer && board[row-5][col+5] != FstPlayer) ||
               (row-3 >= 0 && col-3 >= 0 && board[row+1][col+1] != FstPlayer && board[row-1][col-1] == FstPlayer && board[row-2][col-2] == FstPlayer && board[row-3][col-3] == FstPlayer && board[row-4][col-4] != FstPlayer) ||
               (row-4 >= 0 && col-4 >= 0 && board[row+1][col+1] != FstPlayer && board[row-1][col-1] == FstPlayer && board[row-2][col-2] == 0 && board[row-3][col-3] == FstPlayer && board[row-4][col-4] == FstPlayer && board[row-5][col-5] != FstPlayer) ||
               (row-4 >= 0 && col-4 >= 0 && board[row+1][col+1] != FstPlayer && board[row-1][col-1] == FstPlayer && board[row-2][col-2] == FstPlayer && board[row-3][col-3] == 0 && board[row-4][col-4] == FstPlayer && board[row-5][col-5] != FstPlayer) ||
               (row-4 >= 0 && col-4 >= 0 && board[row+1][col+1] != FstPlayer && board[row-1][col-1] == 0 && board[row-2][col-2] == FstPlayer && board[row-3][col-3] == FstPlayer && board[row-4][col-4] == FstPlayer && board[row-5][col-5] != FstPlayer)) {
                return 1;
            }

            break;
        case 3:     //�E�ォ�獶��
            if((row-4 >= 0 && row+4 < SIZE && col-4 >= 0 && col+4 < SIZE && board[row-5][col+5] != FstPlayer && board[row-4][col+4] == FstPlayer && board[row-3][col+3] == FstPlayer && board[row-2][col+2] == FstPlayer && 
                    board[row-1][col+1] == 0 && board[row+1][col-1] == 0 && board[row+2][col-2] == FstPlayer && board[row+3][col-3] == FstPlayer && board[row+4][col-4] == FstPlayer && board[row+5][col-5] != FstPlayer) ||
               (row-3 >= 0 && row+3 < SIZE && col-3 >= 0 && col+3 < SIZE && board[row-4][col+4] != FstPlayer && board[row-3][col+3] == FstPlayer && board[row-2][col+2] == 0 && 
                    board[row-1][col+1] == FstPlayer && board[row+1][col-1] == FstPlayer && board[row+2][col-2] == 0 && board[row+3][col-3] == FstPlayer && board[row+4][col-4] != FstPlayer) ||
               (row-4 >= 0 && row+3 < SIZE && col-3 >= 0 && col+4 < SIZE && board[row-5][col+5] != FstPlayer && board[row-4][col+4] == FstPlayer && board[row-3][col+3] == FstPlayer && board[row-2][col+2] == 0 && 
                    board[row-1][col+1] == FstPlayer && board[row+1][col-1] == 0 && board[row+2][col-2] == FstPlayer && board[row+3][col-3] == FstPlayer && board[row+4][col-4] != FstPlayer) ||
               (row-3 >= 0 && row+4 < SIZE && col-4 >= 0 && col+3 < SIZE && board[row+5][col-5] != FstPlayer && board[row+4][col-4] == FstPlayer && board[row+3][col-3] == FstPlayer && board[row+2][col-2] == 0 && 
                    board[row+1][col-1] == FstPlayer && board[row-1][col+1] == 0 && board[row-2][col+2] == FstPlayer && board[row-3][col+3] == FstPlayer && board[row-4][col+4] != FstPlayer) ||
               (row-4 >= 0 && row+2 < SIZE && col-2 >= 0 && col+4 < SIZE && board[row-5][col+5] != FstPlayer && board[row-4][col+4] == FstPlayer && board[row-3][col+3] == 0 && board[row-2][col+2] == FstPlayer && 
                    board[row-1][col+1] == FstPlayer && board[row+1][col-1] == 0 && board[row+2][col-2] == FstPlayer && board[row+3][col-3] != FstPlayer) ||
               (row-2 >= 0 && row+4 < SIZE && col-4 >= 0 && col+2 < SIZE && board[row+5][col-5] != FstPlayer && board[row+4][col-4] == FstPlayer && board[row+3][col-3] == 0 && board[row+2][col-2] == FstPlayer && 
                    board[row+1][col-1] == FstPlayer && board[row-1][col+1] == 0 && board[row-2][col+2] == FstPlayer && board[row-3][col+3] != FstPlayer)){
                return 2; //������̎l�l��
            }

            if((row-3 >= 0 && row+1 < SIZE && col-1 >= 0 && col+3 < SIZE && board[row-4][col+4] != FstPlayer && board[row-3][col+3] == FstPlayer && board[row-2][col+2] == FstPlayer && board[row-1][col+1] == 0 && board[row+1][col-1] == FstPlayer && board[row+2][col-2] != FstPlayer) ||
               (row-3 >= 0 && row+1 < SIZE && col-1 >= 0 && col+3 < SIZE && board[row-4][col+4] != FstPlayer && board[row-3][col+3] == FstPlayer && board[row-2][col+2] == 0 && board[row-1][col+1] == FstPlayer && board[row+1][col-1] == FstPlayer && board[row+2][col-2] != FstPlayer) ||
               (row-2 >= 0 && row+1 < SIZE && col-1 >= 0 && col+2 < SIZE && board[row-3][col+3] != FstPlayer && board[row-2][col+2] == FstPlayer && board[row-1][col+1] == FstPlayer && board[row+1][col-1] == FstPlayer && board[row+2][col-2] != FstPlayer) || 
               (row-2 >= 0 && row+2 < SIZE && col-2 >= 0 && col+2 < SIZE && board[row-3][col+3] != FstPlayer && board[row-2][col+2] == FstPlayer && board[row-1][col+1] == FstPlayer && board[row+1][col-1] == 0 && board[row+2][col-2] == FstPlayer && board[row+3][col-3] != FstPlayer) ||
               (row-1 >= 0 && row+3 < SIZE && col-3 >= 0 && col+1 < SIZE && board[row-2][col+2] != FstPlayer && board[row-1][col+1] == FstPlayer && board[row+1][col-1] == FstPlayer && board[row+2][col-2] == 0 && board[row+3][col-3] == FstPlayer && board[row+4][col-4] != FstPlayer) ||
               (row-2 >= 0 && row+2 < SIZE && col-2 >= 0 && col+2 < SIZE && board[row-3][col+3] != FstPlayer && board[row-2][col+2] == FstPlayer && board[row-1][col+1] == 0 && board[row+1][col-1] == FstPlayer && board[row+2][col-2] == FstPlayer && board[row+3][col-3] != FstPlayer) ||
               (row-1 >= 0 && row+2 < SIZE && col-2 >= 0 && col+1 < SIZE && board[row-2][col+2] != FstPlayer && board[row-1][col+1] == FstPlayer && board[row+1][col-1] == FstPlayer && board[row+2][col-2] == FstPlayer && board[row+3][col-3] != FstPlayer) || 
               (row-1 >= 0 && row+3 < SIZE && col-3 >= 0 && col+1 < SIZE && board[row-2][col+2] != FstPlayer && board[row-1][col+1] == FstPlayer && board[row+1][col-1] == 0 && board[row+2][col-2] == FstPlayer && board[row+3][col-3] == FstPlayer && board[row+4][col-4] != FstPlayer) ||
               (row+3 < SIZE && col-3 >= 0 && board[row-1][col+1] != FstPlayer && board[row+1][col-1] == FstPlayer && board[row+2][col-2] == FstPlayer && board[row+3][col-3] == FstPlayer && board[row+4][col-4] != FstPlayer) ||
               (row+4 < SIZE && col-4 >= 0 && board[row-1][col+1] != FstPlayer && board[row+1][col-1] == FstPlayer && board[row+2][col-2] == 0 && board[row+3][col-3] == FstPlayer && board[row+4][col-4] == FstPlayer && board[row-5][col-5] != FstPlayer) ||
               (row+4 < SIZE && col-4 >= 0 && board[row-1][col+1] != FstPlayer && board[row+1][col-1] == FstPlayer && board[row+2][col-2] == FstPlayer && board[row+3][col-3] == 0 && board[row+4][col-4] == FstPlayer && board[row-5][col-5] != FstPlayer) ||
               (row+4 < SIZE && col-4 >= 0 && board[row-1][col+1] != FstPlayer && board[row+1][col-1] == 0 && board[row+2][col-2] == FstPlayer && board[row+3][col-3] == FstPlayer && board[row+4][col-4] == FstPlayer && board[row-5][col-5] != FstPlayer) ||
               (row-3 >= 0 && col+3 < SIZE && board[row+1][col-1] != FstPlayer && board[row-1][col+1] == FstPlayer && board[row-2][col+2] == FstPlayer && board[row-3][col+3] == FstPlayer && board[row-4][col+4] != FstPlayer) ||
               (row-4 >= 0 && col+4 < SIZE && board[row+1][col-1] != FstPlayer && board[row-1][col+1] == FstPlayer && board[row-2][col+2] == 0 && board[row-3][col+3] == FstPlayer && board[row-4][col+4] == FstPlayer && board[row-5][col+5] != FstPlayer) ||
               (row-4 >= 0 && col+4 < SIZE && board[row+1][col-1] != FstPlayer && board[row-1][col+1] == FstPlayer && board[row-2][col+2] == FstPlayer && board[row-3][col+3] == 0 && board[row-4][col+4] == FstPlayer && board[row-5][col+5] != FstPlayer) ||
               (row-4 >= 0 && col+4 < SIZE && board[row+1][col-1] != FstPlayer && board[row-1][col+1] == 0 && board[row-2][col+2] == FstPlayer && board[row-3][col+3] == FstPlayer && board[row-4][col+4] == FstPlayer && board[row-5][col+5] != FstPlayer)) {
                return 1;
            }

            break;
        default:
            break;
    }

    return 0;
}

//�O�O��
int sansankin(int board[SIZE][SIZE], int FstPlayer, int SecPlayer, int row, int col){
    int consecutiveCount = 0;
    int checker = 0;
    for(int i = 0; i < 4; i++){
        if(checkThreeBrock(board,FstPlayer, SecPlayer, row, col, i)){
            consecutiveCount++;
        }
    }
    if(consecutiveCount >=2) return 1; //�ւ���
    return 0;
}

//�l�l��
int yonyonkin(int board[SIZE][SIZE], int FstPlayer, int SecPlayer, int row, int col){
    int consecutiveCount = 0;
    int checker = 0;
    for(int i = 0; i < 4; i++){
        checker = checkFourBrock(board,FstPlayer, SecPlayer, row, col, i);
        if(checker == 2) return 1; //�ւ���
        if(checker == 1) consecutiveCount++;
    }
    if(consecutiveCount >=2) return 1; //�ւ���
    return 0;
}

// ���A���������Ă��邩�𔻒肷��֐�
int checkLongRen(int board[SIZE][SIZE],int player, int row, int col) {
    board[row][col] = player;
    // ������
    int consecutiveCount = 0;
    for (int i = col - 5; i <= col + 5; i++) {
        if (i < 0 || i >= SIZE) continue;
        if (board[row][i] == player) {
            consecutiveCount++;
            if (consecutiveCount == 6){
                board[row][col] = 0;
                return 1; //�ւ���
            }
        } else {
            consecutiveCount = 0;
        }
    }

    // �c����
    consecutiveCount = 0;
    for (int i = row - 5; i <= row + 5; i++) {
        if (i < 0 || i >= SIZE) continue;
        if (board[i][col] == player) {
            consecutiveCount++;
            if (consecutiveCount == 6){
                board[row][col] = 0;
                return 1; //�ւ���
            }
        } else {
            consecutiveCount = 0;
        }
    }

    // �΂ߕ��� (���ォ��E��)
    consecutiveCount = 0;
    for (int i = -5; i <= 5; i++) {
        int r = row + i;
        int c = col + i;
        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) continue;
        if (board[r][c] == player) {
            consecutiveCount++;
            if (consecutiveCount == 6){
                board[row][col] = 0;
                return 1; //�ւ���
            }
        } else {
            consecutiveCount = 0;
        }
    }

    // �΂ߕ��� (�E�ォ�獶��)
    consecutiveCount = 0;
    for (int i = -5; i <= 5; i++) {
        int r = row + i;
        int c = col - i;
        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) continue;
        if (board[r][c] == player) {
            consecutiveCount++;
            if (consecutiveCount == 6){
                board[row][col] = 0;
                return 1; //�ւ���
            }
        } else {
            consecutiveCount = 0;
        }
    }

    return 0;
}

//�ւ��蔻��(�ǉ������A�폜�s��)
int checkForbiddenMoves(int board[SIZE][SIZE], int FstPlayer, int SecPlayer, int row, int col){
	int consecutiveCount = 0;
    int checker = 0;
	//�O�O��
    consecutiveCount = sansankin(board, FstPlayer, SecPlayer, row, col);
    if(consecutiveCount == 1) return 1;

	//�l�l��
    consecutiveCount = yonyonkin(board, FstPlayer, SecPlayer, row, col);
    if(consecutiveCount == 1) return 1;
    
	//���A
	consecutiveCount = checkLongRen(board, FstPlayer, row, col);
    if(consecutiveCount == 1) return 1;

	return 0;	//�ւ���Ȃ�
}

// �����ɎO�A�Ǝl�A���ł��邩�𔻒肷��֐�
int checkThreeAndFourInRow(int board[SIZE][SIZE], int row, int col, int player) {
    // �^����ꂽ���W�ɉ��̎��ł�
    board[row][col] = player;

    // �O�A���������Ă��邩����
    int threeInRow = checkThreeInRow(board, row, col, player);

    // �l�A���������Ă��邩����
    int fourInRow = checkFourInRow(board, row, col, player);

    // �^�������W�ɑł���������ɖ߂�
    board[row][col] = 0;

    // �����ɎO�A�Ǝl�A���ł���ꍇ��1��Ԃ�
    return threeInRow && fourInRow;
}

double CheckScore(int Advance, int board[SIZE][SIZE], int row, int col){
    double score1 = 0.0; //�����̕]���l
    double score2 = 0.0; //����̕]���l
    //�����ɑ΂���e���\�b�h�̕]���l
    double s1_1=0.0;//�l�l��
    double s1_4=0.0;//�O�O��
    if(Advance == 2){ //��������U�̏ꍇ
        s1_1 = yonyonkin(board, com , your, row, col) * W1_1; //�l�l
        s1_4 = sansankin(board, com, your, row, col) * W1_4; //�O�O
    }
    double s1_2 = checkThreeAndFourInRow(board, row , col, your) * W1_2; //�O�l
    double s1_3 = checkFourInRow(board, row , col, your) * W1_3; //�l�A
    double s1_5 = checkThreeInRow(board, row, col, your) * W1_5;//�O�A
    double s1_6 = checkTwoInRow(board, row, col, your) * W1_6; //��A
    double s1_7 = checkOneInRow(board, row, col, your) * W1_7; //��A

    //����ɑ΂���e���\�b�h�̕]���l
    double s2_2=0.0;//�l�l��
    double s2_4=0.0;//�O�O��
    if(Advance == 1){ //���肪��U�̏ꍇ
        s2_2 = yonyonkin(board, com , your, row, col) * W2_2; //�l�l
        s2_4 = sansankin(board, com, your, row, col) * W2_4; //�O�O
    }
    double s2_1 = checkThreeAndFourInRow(board, row, col, com) * W2_1;//�O�l
    double s2_3 = checkFourInRow(board, row , col, com) * W2_3;//�l�A
    double s2_5 = checkThreeInRow(board, row, col, com) * W2_5;//�O�A
    double s2_6 = checkTwoInRow(board, row, col, com) * W2_6; //��A
    double s2_7 = checkOneInRow(board, row, col, com) * W2_7; //��A

    //�escore�ł̑��v
    score1 = s1_1 + s1_2 + s1_3 + s1_4 + s1_5 + s1_6 + s1_7;
    score2 = s2_1 + s2_2 + s2_3 + s2_4 + s2_5 + s2_6 + s2_7;

    //��score�̏W�v
    double score = score1 + score2;
    return score;
}

// ������������(�ǉ������A�폜�s��)
int checkDraw(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return 0; // �{�[�h���܂����܂��Ă��Ȃ�
            }
        }
    }
    return 1; // �{�[�h�����܂��Ă���
}

//��������(�ǉ������A�폜�s��)
int checkWin(int board[SIZE][SIZE], int player, int row, int col) {
    int consecutiveCount = 0;

    // ������
    for (int i = col - 4; i <= col + 4; i++) {
        if (i < 0 || i >= SIZE) continue;
        if (board[row][i] == player) {
            consecutiveCount++;
            if (consecutiveCount == 5) return 1; // ����
        } else {
            consecutiveCount = 0;
        }
    }

    // �c����
    consecutiveCount = 0;
    for (int i = row - 4; i <= row + 4; i++) {
        if (i < 0 || i >= SIZE) continue;
        if (board[i][col] == player) {
            consecutiveCount++;
            if (consecutiveCount == 5) return 1; // ����
        } else {
            consecutiveCount = 0;
        }
    }

    // �΂ߕ��� (���ォ��E��)
    consecutiveCount = 0;
    for (int i = -4; i <= 4; i++) {
        int r = row + i;
        int c = col + i;
        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) continue;
        if (board[r][c] == player) {
            consecutiveCount++;
            if (consecutiveCount == 5) return 1; // ����
        } else {
            consecutiveCount = 0;
        }
    }

    // �΂ߕ��� (�E�ォ�獶��)
    consecutiveCount = 0;
    for (int i = -4; i <= 4; i++) {
        int r = row + i;
        int c = col - i;
        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) continue;
        if (board[r][c] == player) {
            consecutiveCount++;
            if (consecutiveCount == 5) return 1; // ����
        } else {
            consecutiveCount = 0;
        }
    }

    return 0; // �����Ȃ�
}

// �őP��𒲍����o�͂���֐�
void getNextIndex(int Advance, int board[SIZE][SIZE], int *Rrow, int *Rcol){
    double maxScore = 0.0; //�ő�]���l
    double score;
    *Rrow = 7;
    *Rcol = 7;

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(board[i][j] == 0){//�Ֆʂ���̏ꍇ
                int row = i;
                int col = j;
                // �ւ���̔��f(�ǉ������A�폜�s��)
                if(Advance == your && checkForbiddenMoves(board, your, com, row, col) == 1){
                    continue;
                }

                //�őP�蒲��
                //�����̏������f
                if(checkWin(board, your, row, col)){
                    *Rrow = row;
                    *Rcol = col;
                    break;
                }
                //����̏������f
                if(checkWin(board, com, row, col)){
                    *Rrow = row;
                    *Rcol = col;
                    break;
                }
                if(Advance = 1 && checkLongRen(board, com, row, col) == 1){///���肪��U�ŁA���A������ꍇ
                    *Rrow = row;
                    *Rcol = col;
                    break;
                }
                //�ݐϕ]���l�̎Z�o
                score = CheckScore(Advance, board, row, col); //�]���l�̌v�Z
                if (score > maxScore) {
                    *Rrow = row;
                    *Rcol = col;
                    maxScore = score;
                }

                board[row][col] = 0;
            }continue; //�Ֆʂ�1or2�̏ꍇ
        }
    }
}

int main(void) {	

	//�ڑ�����T�[�o�̏��̍\���̂�p��

	struct sockaddr_in dest;

	memset(&dest, 0, sizeof(dest));

	//�T�[�o�̏������

	char destination[100];  //�A�h���X
	int port;		//�|�[�g�ԍ�

	printf("�A�h���X����͂��Ă�������");
	scanf("%s", destination);
	printf("�|�[�g�ԍ�����͂��Ă�������");
	scanf("%d", &port);
	dest.sin_port = htons(port);
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(destination);



	//�\�P�b�g�ʐM�̏����E����
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	//�T�[�o�ւ̐ڑ�
	if (connect(s, (struct sockaddr *) &dest, sizeof(dest))) {
		printf("%s�ɐڑ��ł��܂���ł���\n", destination);
		return -1;

	}

	printf("%s�ɐڑ����܂���\n", destination);
	
	char msg[1024];
	char buffer[1024];
	int board[SIZE][SIZE];	//�Ղ̍쐬
	initializeBoard(board);	//�Ղ̏�����

	boolean isFirst = TRUE;	//���O���͂��ǂ����̔���
	int Advance;		//��U���ǂ���
	int row, col;			//�ł�����̈ʒu

	//��U����U��(�ǉ������A�폜�s��)
	if(port == 12345){
		Advance = your;		//���g����U
	}else{
		Advance = com;	//���g����U
	}

	//�T�[�o����f�[�^����M
	recv(s, buffer, 1024, 0);
	printf("�� %s\n\n", buffer);

	while(1){
		char buffer2[1024];
		
		if(isFirst){
			//���O�̓���
			printf("���M���b�Z�[�W�����(q�ŏI��)");
			scanf("%s", msg);
			if(msg[0] == 'q' || msg[0] == 'Q'){
				break;
			}
            isFirst = FALSE;
		}else if(strcmp(buffer2, "end!") == 0){
            printf("gmae end");
            break;
        }else{
			// ����̎����(�ǉ������A�폜�s��)
			if(strcmp(buffer2, "start") != 0){
                sscanf(buffer2, "%d,%d", &row, &col);
				row--;
				col--;
				board[row][col] = com;
			}
			
			// �ւ���̔��f(�ǉ������A�폜�s��)
			if(Advance == com && checkForbiddenMoves(board, com, your, row, col) == 1){
				const char Forbidden[1024] = "Yuor hands is Forbidden";
				send(s, Forbidden, strlen(Forbidden), 0);
				break;
			}

			// �����������f(�ǉ������A�폜�s��)
			if (checkDraw(board)) {
				const char drow[1024] = "The game is a draw!";
				send(s, drow, strlen(drow), 0);
				break;
			}

			//�����̎������(����ύX)
			getNextIndex(Advance, board, &row, &col);
            board[row][col] = your;
            //�������f(����ǉ�)
			if(checkWin(board, your, row, col)){
                sprintf(msg, "%d,%d,win", row+1, col+1);
            }else{
                sprintf(msg, "%d,%d", row+1, col+1);
            }

            printf("���g�̎�:%s\n\n", msg);

		}
		//�T�[�o�Ƀf�[�^�𑗐M
		send(s, msg, strlen(msg), 0);

		//�T�[�o����f�[�^����M
        memset(buffer2, 0, sizeof(buffer2));
		recv(s, buffer2, 1024, 0);
		printf("�� %s\n\n", buffer2);
	}

	// Windows �ł̃\�P�b�g�̏I��
	closesocket(s);
	WSACleanup();
	return 0;

}