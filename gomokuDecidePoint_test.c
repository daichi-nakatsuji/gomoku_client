#include <stdio.h>
#include <stdbool.h>

#define SIZE 15 // 適切なサイズに変更する

/*自分の評価値の重み 適宜追加*/
int W1_1=0.9; //純４連
int W1_2=0.8; //四四（自身が後攻のとき打てる）
/*相手の評価値の重み 適宜追加*/
int W2_1=0.7; //純四連
int W2_2=0.6; //三四
int W2_3=0.5; //四四(相手が後攻のとき打たれる)

int your = 1;			//自分の手を1に設定
int com = 2;			//相手の手を２に設定

//純４
junyon(int Advance, int board[SIZE][SIZE], int row, int col, int player){
    board[row][col] = player;
    return 1;
}
//四四
yonyon(int Advance, int board[SIZE][SIZE], int row, int col, int player){
    board[row][col] = player;
    if(Advance == 2 && player == 1){//自分が後攻であるときの自分の手を評価するという場合
        return 1;
    }else if(Advance == 1 && player ==2){//相手が後攻であるときの相手の手を評価するという場合
        return 1;
    }else{
        return 0;
    }
}
//三四
sanyon(int Advance, int board[SIZE][SIZE], int row, int col, int player){
    board[row][col] = player;
    return 1;
}

//評価値を計算
CheckScore(int Advance, int board, int row, int col){
    int score1 = 0; //自分の評価値
    int score2 = 0; //相手の評価値

    //自分に対する各メソッドの評価値
    int s1_1 = junyon(Advance, board, row , col, 1) * W1_1;
    int s1_2 = yonyon(Advance, board, row , col, 1) * W1_2;
    //相手に対する各メソッドの評価値
    int s2_1 = junyon(Advance, board, row , col, 2) * W2_1;
    int s2_2 = sanyon(Advance, board, row , col, 2) * W2_2;
    int s2_3 = yonyon(Advance, board, row , col, 2) * W2_3;

    //各scoreでの総計
    score1 = s1_1 + s1_2;
    score2 = s2_1 + s2_2 + s2_3;

    //総scoreの集計
    int score = score1 + score2;
    return score;
}

Forbidden();
// MaxIndex 関数の実装
int MaxIndex(int Advance, int board[SIZE][SIZE]){
    int board[SIZE][SIZE] = board;
    int maxIndexRow = 0; //評価値が最大の手の行番号
    int maxIndexCol = 0; //評価値が最大の手の列番号
    int maxScore = 0; //最大評価値
    int result[2] = {0,0}; //最大の評価値を取る配列の行列番号(index)を格納





    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(Forbidden() == 1){ //反則手である場合
                continue;
            }else if(board[i][j] == 0){//盤面が空の場合
                int row = i;
                int col = j;
                int score = CheckScore(Advance, board, row, col); //評価値の計算
                if (score > maxScore) {
                    maxIndexRow = i;
                    maxIndexCol = j;
                    maxScore = score;
                }
                result[0] = maxIndexRow;
                result[1] = maxIndexCol;
            }continue; //盤面が1or2の場合
        }
    }
    return result;

}

int main(){
    // 盤面の初期化（' 'は空マスを表す）
    char board[SIZE][SIZE] = {
    {'0', '1', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'}
    };

    bool advance = true; // 先行後攻を示す変数（例として true に設定）
    int player = 1;      // プレイヤーを示す変数（例として 1 に設定）

    // MaxIndex 関数を呼び出して最大の要素のインデックスを取得
    int *result = MaxIndex(advance, board, player);

    printf("行:",result[0]);
    printf("列:",result[1]);

}