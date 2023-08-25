#ifndef _WHITE_DIRECTIONS_HPP_
#define _WHITE_DIRECTIONS_HPP_
/*
7 6 5
4 x 3
2 1 0

- - 1
x - -
- - 0
*/
int white_dir_to_dis[10] = {11, 10, 9, 1, -1, -9, -10, -11}; 
int white_knight_dir_to_dis[2] = {12, -8};

int white_direction_L(int *moves, int *board, int pos);
int white_direction_LUD(int *moves, int *board, int pos);
int white_direction_UD(int *moves, int *board, int pos);
int white_direction_RUD(int *moves, int *board, int pos);
int white_direction_R(int *moves, int *board, int pos);
int white_pawn(int *moves, int *board, int pos);
int white_lance(int *moves, int *board, int pos);
int white_knight(int *moves, int *board, int pos);

int white_lattice_direction_L(int *moves, int *board, int pos);
int white_lattice_direction_UD(int *moves, int *board, int pos);
int white_lattice_direction_R(int *moves, int *board, int pos);
int white_bishop_direction(int *moves, int *board, int pos);

int white_P_knight(int *moves, int *board, int pos);

int white_PP_direction_L(int *moves, int *board, int pos);
int white_PP_direction_LUD(int *moves, int *board, int pos);
int white_PP_direction_UD(int *moves, int *board, int pos);
int white_PP_direction_RUD(int *moves, int *board, int pos);
int white_PP_direction_R(int *moves, int *board, int pos);

//この辺りどうするか迷い中
int white_PP_lattice_direction_L(int *moves, int *board, int pos);
int white_PP_lattice_direction_UD(int *moves, int *board, int pos);
int white_PP_lattice_direction_R(int *moves, int *board, int pos);
int white_PP_bishop_direction(int *moves, int *board, int pos);

int white_toP_direction_R(int *moves, int *board, int pos);
int white_toP_direction_RUD(int *moves, int *board, int pos);
int white_fromP_direction_LUD(int *moves, int *board, int pos);
int white_fromP_direction_L(int *moves, int *board, int pos);

//この辺りどうするか迷い中
int white_toP_lattice_direction_R(int *moves, int *board, int pos);
int white_fromP_lattice_direction_L(int *moves, int *board, int pos);
int white_toP_bishop_direction(int *moves, int *board, int pos);
int white_fromP_bishop_direction(int *moves, int *board, int pos);
#endif