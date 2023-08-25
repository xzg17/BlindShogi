#ifndef _BLACK_DIRECTIONS_HPP_
#define _BLACK_DIRECTIONS_HPP_
/*
0 1 2
3 x 4
5 6 7 

0 - -
- - x
1 - -
*/
int black_dir_to_dis[10] = {-11, -10, -9, -1, 1, 9, 10, 11}; 
int black_knight_dir_to_dis[2] = {-12, 8}; 

int black_direction_L(int *moves, int *board, int pos);
int black_direction_LUD(int *moves, int *board, int pos);
int black_direction_UD(int *moves, int *board, int pos);
int black_direction_RUD(int *moves, int *board, int pos);
int black_direction_R(int *moves, int *board, int pos);
int black_pawn(int *moves, int *board, int pos);
int black_lance(int *moves, int *board, int pos);
int black_knight(int *moves, int *board, int pos);

int black_lattice_direction_L(int *moves, int *board, int pos);
int black_lattice_direction_UD(int *moves, int *board, int pos);
int black_lattice_direction_R(int *moves, int *board, int pos);
int black_bishop_direction(int *moves, int *board, int pos);

int black_P_knight(int *moves, int *board, int pos);

int black_PP_direction_L(int *moves, int *board, int pos);
int black_PP_direction_LUD(int *moves, int *board, int pos);
int black_PP_direction_UD(int *moves, int *board, int pos);
int black_PP_direction_RUD(int *moves, int *board, int pos);
int black_PP_direction_R(int *moves, int *board, int pos);

//この辺りどうするか迷い中
int black_PP_lattice_direction_L(int *moves, int *board, int pos);
int black_PP_lattice_direction_UD(int *moves, int *board, int pos);
int black_PP_lattice_direction_R(int *moves, int *board, int pos);
int black_PP_bishop_direction(int *moves, int *board, int pos);

int black_toP_direction_L(int *moves, int *board, int pos);
int black_toP_direction_LUD(int *moves, int *board, int pos);
int black_fromP_direction_RUD(int *moves, int *board, int pos);
int black_fromP_direction_R(int *moves, int *board, int pos);

//この辺りどうするか迷い中
int black_toP_lattice_direction_L(int *moves, int *board, int pos);
int black_fromP_lattice_direction_R(int *moves, int *board, int pos);
int black_toP_bishop_direction(int *moves, int *board, int pos);
int black_fromP_bishop_direction(int *moves, int *board, int pos);
#endif