#include "black_directions.hpp"
#include "piece_macros.hpp"
/*
------
0 1 2
3 x 4
5 6 7 

0 - -
- - x
1 - -
------
*/
#define BLACK_PSEUDO_CHECK(dir) ((board[pos + black_dir_to_dis[dir]] <= 0) && (board[pos + black_dir_to_dis[dir]] != DUMMY))
#define ACTIVATE_BLACK_MOVE(dir) moves[(pos + black_dir_to_dis[dir]) * 8 + dir] = pos
#define ACTIVATE_BLACK_LINEAR_MOVE(p, dir) moves[p * 8 + dir] = pos

#define BLACK_PSEUDO_KNIGHT_CHECK(dir) ((board[pos + black_knight_dir_to_dis[dir]] <= 0) && (board[pos + black_knight_dir_to_dis[dir]] != DUMMY))
#define ACTIVATE_BLACK_NIGHT_MOVE(dir) moves[(pos + black_knight_dir_to_dis[dir]) * 2 + dir] = pos

int black_direction_L(int *moves, int *board, int pos){
    if(BLACK_PSEUDO_CHECK(3)){
        ACTIVATE_BLACK_MOVE(3);
    };
    return 1;
};
int black_direction_LUD(int *moves, int *board, int pos){
    if(BLACK_PSEUDO_CHECK(0)){
        ACTIVATE_BLACK_MOVE(0);
    };
    if(BLACK_PSEUDO_CHECK(5)){
        ACTIVATE_BLACK_MOVE(5);
    };
    return 1;
};
int black_direction_UD(int *moves, int *board, int pos){
    if(BLACK_PSEUDO_CHECK(1)){
        ACTIVATE_BLACK_MOVE(1);
    };
    if(BLACK_PSEUDO_CHECK(6)){
        ACTIVATE_BLACK_MOVE(6);
    };
    return 1;
};
int black_direction_RUD(int *moves, int *board, int pos){
    if(BLACK_PSEUDO_CHECK(2)){
        ACTIVATE_BLACK_MOVE(2);
    };
    if(BLACK_PSEUDO_CHECK(7)){
        ACTIVATE_BLACK_MOVE(7);
    };
    return 1;
};
int black_direction_R(int *moves, int *board, int pos){
    if(BLACK_PSEUDO_CHECK(4)){
        ACTIVATE_BLACK_MOVE(4);
    };
    return 1;
};
int black_lance(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos - 1;p % 10 != 1;p--){
        if(board[p] > 0){
            break;
        };
        if(board[p] < 0){
            ill = -1;
        };
        ACTIVATE_BLACK_LINEAR_MOVE(p, 3) * ill;
    };
    return 1;
};
int black_knight(int *moves, int *board, int pos){
    if(BLACK_PSEUDO_KNIGHT_CHECK(0)){
        ACTIVATE_BLACK_NIGHT_MOVE(0);
    };
    if(BLACK_PSEUDO_KNIGHT_CHECK(1)){
        ACTIVATE_BLACK_NIGHT_MOVE(1);
    };
    return 1;
};

int black_lattice_direction_L(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos - 1;(board[p] <= 0 || board[p] != DUMMY);p--){
        if(board[p] < 0){
            ill = -1;
        };
        ACTIVATE_BLACK_LINEAR_MOVE(p, 3) * ill;
    };
    return 1;
};
int black_lattice_direction_UD(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos - 10;(board[p] <= 0 || board[p] != DUMMY);p -= 10){
        if(board[p] < 0){
            ill = -1;
        };
        ACTIVATE_BLACK_LINEAR_MOVE(p, 1) * ill;
    };
    ill = 1;
    for(int p = pos + 10;(board[p] <= 0 || board[p] != DUMMY);p += 10){
        if(board[p] < 0){
            ill = -1;
        };
        ACTIVATE_BLACK_LINEAR_MOVE(p, 6) * ill;
    };
    return 1;
};
int black_lattice_direction_R(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos + 1;(board[p] <= 0 || board[p] != DUMMY);p++){
        if(board[p] < 0){
            ill = -1;
        };
        ACTIVATE_BLACK_LINEAR_MOVE(p, 4) * ill;
    };
    return 1;
};
int black_bishop_direction(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos - 11;(board[p] <= 0 || board[p] != DUMMY);p -= 11){
        if(board[p] < 0){
            ill = -1;
        };
        ACTIVATE_BLACK_LINEAR_MOVE(p, 0) * ill;
    };
    ill = 1;
    for(int p = pos -9;(board[p] <= 0 || board[p] != DUMMY);p -= 9){
        if(board[p] < 0){
            ill = -1;
        };
        ACTIVATE_BLACK_LINEAR_MOVE(p, 2) * ill;
    };
    ill = 1;
    for(int p = pos + 9;(board[p] <= 0 || board[p] != DUMMY);p += 9){
        if(board[p] < 0){
            ill = -1;
        };
        ACTIVATE_BLACK_LINEAR_MOVE(p, 5) * ill;
    };
    ill = 1;
    for(int p = pos + 11;(board[p] <= 0 || board[p] != DUMMY);p += 11){
        if(board[p] < 0){
            ill = -1;
        };
        ACTIVATE_BLACK_LINEAR_MOVE(p, 7) * ill;
    };
    return 1;
};
//成作りきる前に一度落ち着け
int black_P_knight(int *moves, int *board, int pos){//black_knightと変わらんなぁ
    if(BLACK_PSEUDO_KNIGHT_CHECK(0)){
        ACTIVATE_BLACK_NIGHT_MOVE(0);
    };
    if(BLACK_PSEUDO_KNIGHT_CHECK(1)){
        ACTIVATE_BLACK_NIGHT_MOVE(1);
    };
    return 1;
};

int black_PP_direction_L(int *moves, int *board, int pos){
    if(BLACK_PSEUDO_CHECK(3)){
        ACTIVATE_BLACK_MOVE(3);
    };
    return 1;
};
int black_PP_direction_LUD(int *moves, int *board, int pos){
    if(BLACK_PSEUDO_CHECK(0)){
        ACTIVATE_BLACK_MOVE(0);
    };
    if(BLACK_PSEUDO_CHECK(5)){
        ACTIVATE_BLACK_MOVE(5);
    };
    return 1;
};
int black_PP_direction_UD(int *moves, int *board, int pos){
    if(BLACK_PSEUDO_CHECK(1)){
        ACTIVATE_BLACK_MOVE(1);
    };
    if(BLACK_PSEUDO_CHECK(6)){
        ACTIVATE_BLACK_MOVE(6);
    };
    return 1;
};
int black_PP_direction_RUD(int *moves, int *board, int pos){
    if(BLACK_PSEUDO_CHECK(2)){
        ACTIVATE_BLACK_MOVE(2);
    };
    if(BLACK_PSEUDO_CHECK(7)){
        ACTIVATE_BLACK_MOVE(7);
    };
    return 1;
};
int black_PP_direction_R(int *moves, int *board, int pos){
    if(BLACK_PSEUDO_CHECK(4)){
        ACTIVATE_BLACK_MOVE(4);
    };
    return 1;
};

//この辺りどうするか迷い中
int black_PP_lattice_direction_L(int *moves, int *board, int pos){
    //三段目にしか使わない。
    if(board[pos - 1] <= 0){
        ACTIVATE_BLACK_LINEAR_MOVE(pos - 1, 3);
        if(board[pos - 1] == 0){
            ACTIVATE_BLACK_LINEAR_MOVE(pos - 2, 3);
        }else{
            ACTIVATE_BLACK_LINEAR_MOVE(pos - 2, 3) * -1;
        };
        
    };
    return 1;
};
int black_PP_lattice_direction_UD(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos - 10;(board[p] <= 0 || board[p] != DUMMY);p -= 10){
        if(board[p] < 0){
            ill = -1;
        };
        ACTIVATE_BLACK_LINEAR_MOVE(p, 1) * ill;
    };
    ill = 1;
    for(int p = pos + 10;(board[p] <= 0 || board[p] != DUMMY);p += 10){
        if(board[p] < 0){
            ill = -1;
        };
        ACTIVATE_BLACK_LINEAR_MOVE(p, 6) * ill;
    };
    return 1;
};
int black_PP_lattice_direction_R(int *moves, int *board, int pos){
    //一段目にしか使わない。
    if(board[pos + 1] <= 0){
        ACTIVATE_BLACK_LINEAR_MOVE(pos + 1, 4);
        if(board[pos + 1] == 0){
            ACTIVATE_BLACK_LINEAR_MOVE(pos + 2, 4);
        }else{
            ACTIVATE_BLACK_LINEAR_MOVE(pos + 2, 4) * -1;
        };
        
    };
    return 1;
};
int black_PP_bishop_direction(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos - 11;(board[p] <= 0 || board[p] != DUMMY);p -= 11){
        if(board[p] < 0){
            ill = -1;
        };
        ACTIVATE_BLACK_LINEAR_MOVE(p, 0) * ill;
    };
    ill = 1;
    for(int p = pos -9;(board[p] <= 0 || p % 10 < 4);p -= 9){
        if(board[p] < 0){
            ill = -1;
        };
        ACTIVATE_BLACK_LINEAR_MOVE(p, 2) * ill;
    };
    ill = 1;
    for(int p = pos + 9;(board[p] <= 0 || board[p] != DUMMY);p += 9){
        if(board[p] < 0){
            ill = -1;
        };
        ACTIVATE_BLACK_LINEAR_MOVE(p, 5) * ill;
    };
    ill = 1;
    for(int p = pos + 11;(board[p] <= 0 || p % 10 < 4);p += 11){
        if(board[p] < 0){
            ill = -1;
        };
        ACTIVATE_BLACK_LINEAR_MOVE(p, 7) * ill;
    };
    return 1;
};

int black_toP_direction_L(int *moves, int *board, int pos){
    if(BLACK_PSEUDO_CHECK(3)){
        ACTIVATE_BLACK_MOVE(3);
    };
    return 1;
};

int black_toP_direction_LUD(int *moves, int *board, int pos){
    if(BLACK_PSEUDO_CHECK(0)){
        ACTIVATE_BLACK_MOVE(0);
    };
    if(BLACK_PSEUDO_CHECK(5)){
        ACTIVATE_BLACK_MOVE(5);
    };
    return 1;
};
int black_fromP_direction_RUD(int *moves, int *board, int pos){
    if(BLACK_PSEUDO_CHECK(2)){
        ACTIVATE_BLACK_MOVE(2);
    };
    if(BLACK_PSEUDO_CHECK(7)){
        ACTIVATE_BLACK_MOVE(7);
    };
    return 1;
};
int black_fromP_direction_R(int *moves, int *board, int pos){
    if(BLACK_PSEUDO_CHECK(4)){
        ACTIVATE_BLACK_MOVE(4);
    };
    return 1;
};
//この辺りどうするか迷い中
int black_toP_lattice_direction_L(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos - 1;(board[p] <= 0 || board[p] != DUMMY);p--){
        if(board[p] < 0){
            ill = -1;
        };
        if(p % 10 < 4){
            ACTIVATE_BLACK_LINEAR_MOVE(p, 3) * ill;
        };
    };
    return 1;
};
int black_fromP_lattice_direction_R(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos + 1;(board[p] <= 0 || board[p] != DUMMY);p++){
        if(board[p] < 0){
            ill = -1;
        };
        ACTIVATE_BLACK_LINEAR_MOVE(p, 4) * ill;    
    };
    return 1;
};
int black_toP_bishop_direction(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos - 11;(board[p] <= 0 || board[p] != DUMMY);p -= 11){
        if(board[p] < 0){
            ill = -1;
        };
        if(p % 10 < 4){
            ACTIVATE_BLACK_LINEAR_MOVE(p, 0) * ill;
        };
    };
    ill = 1;
    for(int p = pos + 9;(board[p] <= 0 || board[p] != DUMMY);p += 9){
        if(board[p] < 0){
            ill = -1;
        };
        if(p % 10 < 4){
            ACTIVATE_BLACK_LINEAR_MOVE(p, 5) * ill;
        };
    };
    return 1;
};
int black_fromP_bishop_direction(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos -9;(board[p] <= 0 || board[p] != DUMMY);p -= 9){
        if(board[p] < 0){
            ill = -1;
        };
        ACTIVATE_BLACK_LINEAR_MOVE(p, 2) * ill;
    };
    ill = 1;
    for(int p = pos + 11;(board[p] <= 0 || board[p] != DUMMY);p += 11){
        if(board[p] < 0){
            ill = -1;
        };
        ACTIVATE_BLACK_LINEAR_MOVE(p, 7) * ill;
    };
    return 1;
};