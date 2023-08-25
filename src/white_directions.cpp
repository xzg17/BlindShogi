#include "white_directions.hpp"
#include "piece_macros.hpp"
/*
7 6 5
4 x 3
2 1 0

- - 1
x - -
- - 0
*/
#define WHITE_PSEUDO_CHECK(dir) ((board[pos + white_dir_to_dis[dir]] <= 0) && (board[pos + white_dir_to_dis[dir]] != DUMMY))
#define ACTIVATE_WHITE_MOVE(dir) moves[(pos + white_dir_to_dis[dir]) * 8 + dir] = pos
#define ACTIVATE_WHITE_LINEAR_MOVE(p, dir) moves[p * 8 + dir] = pos

#define WHITE_PSEUDO_KNIGHT_CHECK(dir) ((board[pos + white_knight_dir_to_dis[dir]] <= 0) && (board[pos + white_knight_dir_to_dis[dir]] != DUMMY))
#define ACTIVATE_WHITE_NIGHT_MOVE(dir) moves[(pos + white_knight_dir_to_dis[dir]) * 2 + dir] = pos


int white_direction_L(int *moves, int *board, int pos){
    if(WHITE_PSEUDO_CHECK(4)){
        ACTIVATE_WHITE_MOVE(4);
    };
    return 1;
};
int white_direction_LUD(int *moves, int *board, int pos){
    if(WHITE_PSEUDO_CHECK(7)){
        ACTIVATE_WHITE_MOVE(7);
    };
    if(WHITE_PSEUDO_CHECK(2)){
        ACTIVATE_WHITE_MOVE(2);
    };
    return 1;
};
int white_direction_UD(int *moves, int *board, int pos){
    if(WHITE_PSEUDO_CHECK(6)){
        ACTIVATE_WHITE_MOVE(6);
    };
    if(WHITE_PSEUDO_CHECK(1)){
        ACTIVATE_WHITE_MOVE(1);
    };
    return 1;
};
int white_direction_RUD(int *moves, int *board, int pos){
    if(WHITE_PSEUDO_CHECK(5)){
        ACTIVATE_WHITE_MOVE(5);
    };
    if(WHITE_PSEUDO_CHECK(0)){
        ACTIVATE_WHITE_MOVE(0);
    };
    return 1;
};
int white_direction_R(int *moves, int *board, int pos){
    if(WHITE_PSEUDO_CHECK(3)){
        ACTIVATE_WHITE_MOVE(3);
    };
    return 1;
};
int white_lance(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos + 1;p % 10 != 9;p++){
        if(board[p] < 0){
            break;
        };
        if(board[p] > 0){
            ill = -1;
        };
        ACTIVATE_WHITE_LINEAR_MOVE(p, 3) * ill;
    };
    return 1;
};
int white_knight(int *moves, int *board, int pos){
    if(WHITE_PSEUDO_KNIGHT_CHECK(0)){
        ACTIVATE_WHITE_NIGHT_MOVE(0);
    };
    if(WHITE_PSEUDO_KNIGHT_CHECK(1)){
        ACTIVATE_WHITE_NIGHT_MOVE(1);
    };
    return 1;
};

int white_lattice_direction_L(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos - 1;(board[p] >= 0 || board[p] != DUMMY);p--){
        if(board[p] > 0){
            ill = -1;
        };
        ACTIVATE_WHITE_LINEAR_MOVE(p, 4) * ill;
    };
    return 1;
};
int white_lattice_direction_UD(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos - 10;(board[p] >= 0 || board[p] != DUMMY);p -= 10){
        if(board[p] > 0){
            ill = -1;
        };
        ACTIVATE_WHITE_LINEAR_MOVE(p, 6) * ill;
    };
    ill = 1;
    for(int p = pos + 10;(board[p] >= 0 || board[p] != DUMMY);p += 10){
        if(board[p] > 0){
            ill = -1;
        };
        ACTIVATE_WHITE_LINEAR_MOVE(p, 1) * ill;
    };
    return 1;
};
int white_lattice_direction_R(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos + 1;(board[p] >= 0 || board[p] != DUMMY);p++){
        if(board[p] > 0){
            ill = -1;
        };
        ACTIVATE_WHITE_LINEAR_MOVE(p, 3) * ill;
    };
    return 1;
};
int white_bishop_direction(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos - 11;(board[p] >= 0 || board[p] != DUMMY);p -= 11){
        if(board[p] > 0){
            ill = -1;
        };
        ACTIVATE_WHITE_LINEAR_MOVE(p, 7) * ill;
    };
    ill = 1;
    for(int p = pos -9;(board[p] >= 0 || board[p] != DUMMY);p -= 9){
        if(board[p] > 0){
            ill = -1;
        };
        ACTIVATE_WHITE_LINEAR_MOVE(p, 5) * ill;
    };
    ill = 1;
    for(int p = pos + 9;(board[p] >= 0 || board[p] != DUMMY);p += 9){
        if(board[p] > 0){
            ill = -1;
        };
        ACTIVATE_WHITE_LINEAR_MOVE(p, 2) * ill;
    };
    ill = 1;
    for(int p = pos + 11;(board[p] >= 0 || board[p] != DUMMY);p += 11){
        if(board[p] > 0){
            ill = -1;
        };
        ACTIVATE_WHITE_LINEAR_MOVE(p, 0) * ill;
    };
    return 1;
};

int white_P_knight(int *moves, int *board, int pos){
    if(WHITE_PSEUDO_KNIGHT_CHECK(0)){
        ACTIVATE_WHITE_NIGHT_MOVE(0);
    };
    if(WHITE_PSEUDO_KNIGHT_CHECK(1)){
        ACTIVATE_WHITE_NIGHT_MOVE(1);
    };
    return 1;
};

int white_PP_direction_L(int *moves, int *board, int pos){
    if(WHITE_PSEUDO_CHECK(4)){
        ACTIVATE_WHITE_MOVE(4);
    };
    return 1;
};
int white_PP_direction_LUD(int *moves, int *board, int pos){
    if(WHITE_PSEUDO_CHECK(7)){
        ACTIVATE_WHITE_MOVE(7);
    };
    if(WHITE_PSEUDO_CHECK(2)){
        ACTIVATE_WHITE_MOVE(2);
    };
    return 1;
};
int white_PP_direction_UD(int *moves, int *board, int pos){
    if(WHITE_PSEUDO_CHECK(6)){
        ACTIVATE_WHITE_MOVE(6);
    };
    if(WHITE_PSEUDO_CHECK(1)){
        ACTIVATE_WHITE_MOVE(1);
    };
    return 1;
};
int white_PP_direction_RUD(int *moves, int *board, int pos){
    if(WHITE_PSEUDO_CHECK(5)){
        ACTIVATE_WHITE_MOVE(5);
    };
    if(WHITE_PSEUDO_CHECK(0)){
        ACTIVATE_WHITE_MOVE(0);
    };
    return 1;
};
int white_PP_direction_R(int *moves, int *board, int pos){
    if(WHITE_PSEUDO_CHECK(3)){
        ACTIVATE_WHITE_MOVE(3);
    };
    return 1;
};

//この辺りどうするか迷い中
int white_PP_lattice_direction_L(int *moves, int *board, int pos){
    //九段目にしか使わない。
    if(board[pos - 1] <= 0){
        ACTIVATE_WHITE_LINEAR_MOVE(pos - 1, 4);
        if(board[pos - 1] == 0){
            ACTIVATE_WHITE_LINEAR_MOVE(pos - 2, 4);
        }else{
            ACTIVATE_WHITE_LINEAR_MOVE(pos - 2, 4) * -1;
        };
        
    };
    return 1;
};
int white_PP_lattice_direction_UD(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos - 10;(board[p] >= 0 || board[p] != DUMMY);p -= 10){
        if(board[p] > 0){
            ill = -1;
        };
        ACTIVATE_WHITE_LINEAR_MOVE(p, 6) * ill;
    };
    ill = 1;
    for(int p = pos + 10;(board[p] >= 0 || board[p] != DUMMY);p += 10){
        if(board[p] > 0){
            ill = -1;
        };
        ACTIVATE_WHITE_LINEAR_MOVE(p, 1) * ill;
    };
    return 1;
};
int white_PP_lattice_direction_R(int *moves, int *board, int pos){
    //七段目にしか使わない。
    if(board[pos + 1] <= 0){
        ACTIVATE_WHITE_LINEAR_MOVE(pos + 1, 3);
        if(board[pos + 1] == 0){
            ACTIVATE_WHITE_LINEAR_MOVE(pos + 2, 3);
        }else{
            ACTIVATE_WHITE_LINEAR_MOVE(pos + 2, 3) * -1;
        };
        
    };
    return 1;
};
int white_PP_bishop_direction(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos - 11;(board[p] >= 0 || 7 <= p % 10);p -= 11){
        if(board[p] > 0){
            ill = -1;
        };
        ACTIVATE_WHITE_LINEAR_MOVE(p, 7) * ill;
    };
    ill = 1;
    for(int p = pos -9;(board[p] >= 0 || board[p] != DUMMY);p -= 9){
        if(board[p] > 0){
            ill = -1;
        };
        ACTIVATE_WHITE_LINEAR_MOVE(p, 5) * ill;
    };
    ill = 1;
    for(int p = pos + 9;(board[p] >= 0 || 7 <= p % 10);p += 9){
        if(board[p] > 0){
            ill = -1;
        };
        ACTIVATE_WHITE_LINEAR_MOVE(p, 2) * ill;
    };
    ill = 1;
    for(int p = pos + 11;(board[p] >= 0 || board[p] != DUMMY);p += 11){
        if(board[p] > 0){
            ill = -1;
        };
        ACTIVATE_WHITE_LINEAR_MOVE(p, 0) * ill;
    };
    return 1;
};

int white_toP_direction_R(int *moves, int *board, int pos){
    if(WHITE_PSEUDO_CHECK(3)){
        ACTIVATE_WHITE_MOVE(3);
    };
    return 1;
};
int white_toP_direction_RUD(int *moves, int *board, int pos){
    if(WHITE_PSEUDO_CHECK(5)){
        ACTIVATE_WHITE_MOVE(5);
    };
    if(WHITE_PSEUDO_CHECK(0)){
        ACTIVATE_WHITE_MOVE(0);
    };
    return 1;
};
int white_fromP_direction_LUD(int *moves, int *board, int pos){
    if(WHITE_PSEUDO_CHECK(2)){
        ACTIVATE_WHITE_MOVE(2);
    };
    if(WHITE_PSEUDO_CHECK(7)){
        ACTIVATE_WHITE_MOVE(7);
    };
    return 1;
};
int white_fromP_direction_L(int *moves, int *board, int pos){
    if(WHITE_PSEUDO_CHECK(4)){
        ACTIVATE_WHITE_MOVE(4);
    };
    return 1;
};

//この辺りどうするか迷い中
int white_toP_lattice_direction_R(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos + 1;(board[p] >= 0 || board[p] != DUMMY);p++){
        if(board[p] > 0){
            ill = -1;
        };
        if(7 <= p % 10){
            ACTIVATE_WHITE_LINEAR_MOVE(p, 3) * ill;
        };
    };
    return 1;
};
int white_fromP_lattice_direction_L(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos - 1;(board[p] >= 0 || board[p] != DUMMY);p--){
        if(board[p] > 0){
            ill = -1;
        };
        ACTIVATE_WHITE_LINEAR_MOVE(p, 4) * ill;
    };
    return 1;
};
int white_toP_bishop_direction(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos + 11;(board[p] >= 0 || board[p] != DUMMY);p += 11){
        if(board[p] > 0){
            ill = -1;
        };
        if(7 <= p % 10){
            ACTIVATE_WHITE_LINEAR_MOVE(p, 5) * ill;
        };
    };
    ill = 1;
    for(int p = pos - 9;(board[p] >= 0 || board[p] != DUMMY);p -= 9){
        if(board[p] > 0){
            ill = -1;
        };
        if(7 <= p % 10){
            ACTIVATE_WHITE_LINEAR_MOVE(p, 0) * ill;
        };
    };
    return 1;
};
int white_fromP_bishop_direction(int *moves, int *board, int pos){
    int ill = 1;
    for(int p = pos - 11;(board[p] >= 0 || board[p] != DUMMY);p -= 11){
        if(board[p] > 0){
            ill = -1;
        };
        ACTIVATE_WHITE_LINEAR_MOVE(p, 7) * ill;
    };
    ill = 1;
    for(int p = pos + 9;(board[p] >= 0 || board[p] != DUMMY);p += 9){
        if(board[p] > 0){
            ill = -1;
        };
        ACTIVATE_WHITE_LINEAR_MOVE(p, 2) * ill;
    };
    return 1;
};
