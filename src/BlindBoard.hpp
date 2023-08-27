#include "indices.hpp"
#include "piece_macros.hpp"
#include "black_directions.cpp"
#include "white_directions.cpp"

#define IS_PIECE(P) this->board[j] == P

class Board{
public:
    int board[110];
    int turn;
    int kpos[2];
    int info[4];
    int ill[2];
    int lost_pos;

    Board();
    int push(int move, int from_pos);
    int nondrop_moves(int *moves, int *knight_moves, int *PP_moves, int *toP_moves, int *fromP_moves, int *P_knight_moves);
    int drop_moves(int *drop_moves);
    int is_lose();
    int is_mate();
    int dist_check();
    int close_check();
    int check();

    int set_board(int *board);
    int set_ill(int *ill);
    int set_turn(int turn);
};

Board::Board(){
    for(int i = 0;i < 110;i++){
        this->board[i] = start_board[i];
    };
    this->turn = 1;
    this->kpos[0] = 51;
    this->kpos[1] = 59;
    this->info[0] = 0;
    this->info[1] = 0;
    this->info[2] = 0;
    this->info[3] = 0;
    this->ill[0] = 9;
    this->ill[1] = 9;
};
int Board::set_board(int *board){
    for(int i = 0;i < 110;i++){
        this->board[i] = board[i];
    };
    return 1;
};
int Board::set_ill(int *ill){
    this->ill[0] = ill[0];
    this->ill[1] = ill[1];
};
int Board::set_turn(int turn){
    this->turn = turn;
};
int Board::nondrop_moves(int *moves, int *knight_moves, int *PP_moves, int *toP_moves, int *fromP_moves, int *P_knight_moves){
    if(this->turn){
        int i, j;
        for(i = 0;i < 9;i++){
            j = this->board[non_dumyy_indices[i]];
            if(0 < j){
                if(j == BLACK_SILVER){
                    black_direction_RUD(moves, this->board, j);
                }else if(j == BLACK_BISHOP){
                    black_bishop_direction(moves, this->board, j);
                    black_fromP_bishop_direction(fromP_moves, this->board, j);
                    black_PP_bishop_direction(PP_moves, this->board, j);
                }else{
                    //この時点で金以上の動きが保証されている。成れるのは飛車のみ。
                    black_direction_R(moves, this->board, j);
                    black_direction_UD(moves, this->board, j);
                    if(j == BLACK_KING or j == BLACK_PROMOTED_ROOK){
                        black_direction_RUD(moves, this->board, j);
                    }else if(j == BLACK_ROOK){
                        black_fromP_lattice_direction_R(fromP_moves, this->board, j);
                        black_PP_lattice_direction_UD(PP_moves, this->board, j);
                        black_PP_lattice_direction_R(PP_moves, this->board, j);
                    }else if(j == BLACK_PROMOTED_BISHOP){
                        black_bishop_direction(moves, this->board, j);
                    };
                };
            };
        };
        for(;i < 18;i++){
            j = this->board[non_dumyy_indices[i]];
            if(0 < j){
                if(j == BLACK_BISHOP){
                    black_bishop_direction(moves, this->board, j);
                    black_fromP_bishop_direction(fromP_moves, this->board, j);
                    black_PP_bishop_direction(PP_moves, this->board, j);
                }else{
                    //この時点で歩以上の動きが保証されている。歩香は成のみ。
                    black_PP_direction_L(PP_moves, this->board, j);
                    if(j == BLACK_SILVER){
                        black_direction_L(moves, this->board, j);
                        black_direction_LUD(moves, this->board, j);
                        black_direction_RUD(moves, this->board, j);
                        black_PP_direction_LUD(PP_moves, this->board, j);
                        black_PP_direction_RUD(PP_moves, this->board, j);
                    }else if(5 <= j){
                        //この時点で金以上の動きが保証されている。成れるのは飛車のみ。
                        black_direction_R(moves, this->board, j);
                        black_direction_UD(moves, this->board, j);
                        black_direction_L(moves, this->board, j);
                        black_direction_LUD(moves, this->board, j);
                        if(j == BLACK_KING or j == BLACK_PROMOTED_ROOK){
                            black_direction_RUD(moves, this->board, j);
                        }else if(j == BLACK_ROOK){
                            black_fromP_lattice_direction_R(fromP_moves, this->board, j);
                            black_PP_lattice_direction_UD(PP_moves, this->board, j);
                            black_PP_direction_R(PP_moves, this->board, j);
                            //PPのLは歩の効きでもう生成したはず。
                        }else if(j == BLACK_PROMOTED_BISHOP){
                            black_bishop_direction(moves, this->board, j);
                        };
                    };
                };
            };        
        };
        for(;i < 27; i++){
            j = this->board[non_dumyy_indices[i]];
            if(0 < j){
                if(j == BLACK_KNIGHT){
                    black_P_knight(P_knight_moves, this->board, j);
                }else if(j == BLACK_BISHOP){
                    black_bishop_direction(moves, this->board, j);
                    black_fromP_bishop_direction(fromP_moves, this->board, j);
                    black_PP_bishop_direction(PP_moves, this->board, j);
                }else{
                    //この時点で歩以上の動きが保証されている。
                    black_PP_direction_L(PP_moves, this->board, j);
                    black_direction_L(moves, this->board, j);
                    if(j == BLACK_LANCE){
                        //生では一マスしか進めないので、成のみ考える。
                        black_PP_lattice_direction_L(PP_moves, this->board, j);
                    }else{
                        //この時点で斜め前が保証される。
                        black_direction_LUD(moves, this->board, j);
                        black_PP_direction_LUD(PP_moves, this->board, j);
                        if(j == BLACK_SILVER){
                            black_direction_RUD(moves, this->board, j);
                            black_fromP_direction_RUD(fromP_moves, this->board, j);
                        }else if(5 <= j){
                            //この時点で金以上の動きが保証されている。成れるのは飛車のみ。
                            black_direction_R(moves, this->board, j);
                            black_direction_UD(moves, this->board, j);
                            if(j == BLACK_KING or j == BLACK_PROMOTED_ROOK){
                                black_direction_RUD(moves, this->board, j);
                            }else if(j == BLACK_ROOK){
                                black_fromP_lattice_direction_R(fromP_moves, this->board, j);
                                black_PP_lattice_direction_UD(PP_moves, this->board, j);
                                black_PP_lattice_direction_L(PP_moves, this->board, j);
                            }else if(j == BLACK_PROMOTED_BISHOP){
                                black_bishop_direction(moves, this->board, j);
                            };
                        };
                    };
                };
            };
        };
        for(;i < 36; i++){
            j = this->board[non_dumyy_indices[i]];
            if(0 < j){
                if(j == BLACK_KNIGHT){
                    black_P_knight(P_knight_moves, this->board, j);
                }else if(j == BLACK_BISHOP){
                    black_bishop_direction(moves, this->board, j);
                    black_toP_bishop_direction(fromP_moves, this->board, j);
                }else{
                    //この時点で歩以上の動きが保証されている。
                    black_toP_direction_L(toP_moves, this->board, j);
                    black_direction_L(moves, this->board, j);
                    if(j == BLACK_LANCE){
                        black_toP_lattice_direction_L(PP_moves, this->board, j);
                        black_lance(moves, this->board, j);
                    }else{
                        //この時点で斜め前が保証される。
                        black_direction_LUD(moves, this->board, j);
                        black_toP_direction_LUD(toP_moves, this->board, j);
                        if(j == BLACK_SILVER){
                            black_direction_RUD(moves, this->board, j);
                        }else if(5 <= j){
                            //この時点で金以上の動きが保証されている。成れるのは飛車のみ。
                            black_direction_R(moves, this->board, j);
                            black_direction_UD(moves, this->board, j);
                            if(j == BLACK_KING or j == BLACK_PROMOTED_ROOK){
                                black_direction_RUD(moves, this->board, j);
                            }else if(j == BLACK_ROOK){
                                black_lattice_direction_R(moves, this->board, j);
                                black_lattice_direction_UD(moves, this->board, j);
                                black_toP_lattice_direction_L(toP_moves, this->board, j);
                            }else if(j == BLACK_PROMOTED_BISHOP){
                                black_bishop_direction(moves, this->board, j);
                            };
                        };
                    };
                };
            };
        };
        for(;i < 45; i++){
            j = this->board[non_dumyy_indices[i]];
            if(0 < j){
                if(j == BLACK_KNIGHT){
                    black_P_knight(P_knight_moves, this->board, j);
                    black_knight(knight_moves, this->board, j);
                }else if(j == BLACK_BISHOP){
                    black_bishop_direction(moves, this->board, j);
                    black_toP_bishop_direction(fromP_moves, this->board, j);
                }else{
                    //この時点で歩以上の動きが保証されている。
                    black_direction_L(moves, this->board, j);
                    if(j == BLACK_LANCE){
                        black_toP_lattice_direction_L(PP_moves, this->board, j);
                        black_lance(moves, this->board, j);
                    }else{
                        //この時点で斜め前が保証される。
                        black_direction_LUD(moves, this->board, j);
                        if(j == BLACK_SILVER){
                            black_direction_RUD(moves, this->board, j);
                        }else if(5 <= j){
                            //この時点で金以上の動きが保証されている。成れるのは飛車のみ。
                            black_direction_R(moves, this->board, j);
                            black_direction_UD(moves, this->board, j);
                            if(j == BLACK_KING or j == BLACK_PROMOTED_ROOK){
                                black_direction_RUD(moves, this->board, j);
                            }else if(j == BLACK_ROOK){
                                black_lattice_direction_R(moves, this->board, j);
                                black_lattice_direction_UD(moves, this->board, j);
                                black_toP_lattice_direction_L(toP_moves, this->board, j);
                            }else if(j == BLACK_PROMOTED_BISHOP){
                                black_bishop_direction(moves, this->board, j);
                            };
                        };
                    };
                };
            };
        };
        for(;i < 81; i++){
            j = this->board[non_dumyy_indices[i]];
            if(0 < j){
                if(j == BLACK_KNIGHT){
                    black_knight(knight_moves, this->board, j);
                }else if(j == BLACK_BISHOP){
                    black_bishop_direction(moves, this->board, j);
                    black_toP_bishop_direction(fromP_moves, this->board, j);
                }else{
                    //この時点で歩以上の動きが保証されている。
                    black_direction_L(moves, this->board, j);
                    if(j == BLACK_LANCE){
                        black_toP_lattice_direction_L(PP_moves, this->board, j);
                        black_lance(moves, this->board, j);
                    }else{
                        //この時点で斜め前が保証される。
                        black_direction_LUD(moves, this->board, j);
                        if(j == BLACK_SILVER){
                            black_direction_RUD(moves, this->board, j);
                        }else if(5 <= j){
                            //この時点で金以上の動きが保証されている。成れるのは飛車のみ。
                            black_direction_R(moves, this->board, j);
                            black_direction_UD(moves, this->board, j);
                            if(j == BLACK_KING or j == BLACK_PROMOTED_ROOK){
                                black_direction_RUD(moves, this->board, j);
                            }else if(j == BLACK_ROOK){
                                black_lattice_direction_R(moves, this->board, j);
                                black_lattice_direction_UD(moves, this->board, j);
                                black_toP_lattice_direction_L(toP_moves, this->board, j);
                            }else if(j == BLACK_PROMOTED_BISHOP){
                                black_bishop_direction(moves, this->board, j);
                            };
                        };
                    };
                };
            };
        };
        return 1;
    }else{
        int i, j;
        for(i = 0;i < 9;i++){
            j = 110 - this->board[non_dumyy_indices[i]];
            if(0 < j){
                if(j == WHITE_SILVER){
                    white_direction_LUD(moves, this->board, j);
                }else if(j == WHITE_BISHOP){
                    white_bishop_direction(moves, this->board, j);
                    white_fromP_bishop_direction(fromP_moves, this->board, j);
                    white_PP_bishop_direction(PP_moves, this->board, j);
                }else{
                    //この時点で金以上の動きが保証されている。成れるのは飛車のみ。
                    white_direction_L(moves, this->board, j);
                    white_direction_UD(moves, this->board, j);
                    if(j == WHITE_KING or j == WHITE_PROMOTED_ROOK){
                        white_direction_LUD(moves, this->board, j);
                    }else if(j == WHITE_ROOK){
                        white_fromP_lattice_direction_L(fromP_moves, this->board, j);
                        white_PP_lattice_direction_UD(PP_moves, this->board, j);
                        white_PP_lattice_direction_L(PP_moves, this->board, j);
                    }else if(j == WHITE_PROMOTED_BISHOP){
                        white_bishop_direction(moves, this->board, j);
                    };
                };
            };
        };
        for(;i < 18;i++){
            j = 110 - this->board[non_dumyy_indices[i]];
            if(0 < j){
                if(j == WHITE_BISHOP){
                    white_bishop_direction(moves, this->board, j);
                    white_fromP_bishop_direction(fromP_moves, this->board, j);
                    white_PP_bishop_direction(PP_moves, this->board, j);
                }else{
                    //この時点で歩以上の動きが保証されている。歩香は成のみ。
                    white_PP_direction_R(PP_moves, this->board, j);
                    if(j == WHITE_SILVER){
                        white_direction_R(moves, this->board, j);
                        white_direction_RUD(moves, this->board, j);
                        white_direction_LUD(moves, this->board, j);
                        white_PP_direction_RUD(PP_moves, this->board, j);
                        white_PP_direction_LUD(PP_moves, this->board, j);
                    }else if(5 <= j){
                        //この時点で金以上の動きが保証されている。成れるのは飛車のみ。
                        white_direction_L(moves, this->board, j);
                        white_direction_UD(moves, this->board, j);
                        white_direction_R(moves, this->board, j);
                        white_direction_RUD(moves, this->board, j);
                        if(j == WHITE_KING or j == WHITE_PROMOTED_ROOK){
                            white_direction_LUD(moves, this->board, j);
                        }else if(j == WHITE_ROOK){
                            white_fromP_lattice_direction_L(fromP_moves, this->board, j);
                            white_PP_lattice_direction_UD(PP_moves, this->board, j);
                            white_PP_direction_L(PP_moves, this->board, j);
                            //PPのRは歩の効きでもう生成したはず。
                        }else if(j == WHITE_PROMOTED_BISHOP){
                            white_bishop_direction(moves, this->board, j);
                        };
                    };
                };
            };        
        };
        for(;i < 27; i++){
            j = 110 - this->board[non_dumyy_indices[i]];
            if(0 < j){
                if(j == WHITE_KNIGHT){
                    white_P_knight(P_knight_moves, this->board, j);
                }else if(j == WHITE_BISHOP){
                    white_bishop_direction(moves, this->board, j);
                    white_fromP_bishop_direction(fromP_moves, this->board, j);
                    white_PP_bishop_direction(PP_moves, this->board, j);
                }else{
                    //この時点で歩以上の動きが保証されている。
                    white_PP_direction_R(PP_moves, this->board, j);
                    white_direction_R(moves, this->board, j);
                    if(j == WHITE_LANCE){
                        //生では一マスしか進めないので、成のみ考える。
                        white_PP_lattice_direction_R(PP_moves, this->board, j);
                    }else{
                        //この時点で斜め前が保証される。
                        white_direction_RUD(moves, this->board, j);
                        white_PP_direction_RUD(PP_moves, this->board, j);
                        if(j == WHITE_SILVER){
                            white_direction_LUD(moves, this->board, j);
                            white_fromP_direction_LUD(fromP_moves, this->board, j);
                        }else if(5 <= j){
                            //この時点で金以上の動きが保証されている。成れるのは飛車のみ。
                            white_direction_L(moves, this->board, j);
                            white_direction_UD(moves, this->board, j);
                            if(j == WHITE_KING or j == WHITE_PROMOTED_ROOK){
                                white_direction_LUD(moves, this->board, j);
                            }else if(j == WHITE_ROOK){
                                white_fromP_lattice_direction_L(fromP_moves, this->board, j);
                                white_PP_lattice_direction_UD(PP_moves, this->board, j);
                                white_PP_lattice_direction_R(PP_moves, this->board, j);
                            }else if(j == WHITE_PROMOTED_BISHOP){
                                white_bishop_direction(moves, this->board, j);
                            };
                        };
                    };
                };
            };
        };
        for(;i < 36; i++){
            j = 110 - this->board[non_dumyy_indices[i]];
            if(0 < j){
                if(j == WHITE_KNIGHT){
                    white_P_knight(P_knight_moves, this->board, j);
                }else if(j == WHITE_BISHOP){
                    white_bishop_direction(moves, this->board, j);
                    white_toP_bishop_direction(fromP_moves, this->board, j);
                }else{
                    //この時点で歩以上の動きが保証されている。
                    white_toP_direction_R(toP_moves, this->board, j);
                    white_direction_R(moves, this->board, j);
                    if(j == WHITE_LANCE){
                        white_toP_lattice_direction_R(PP_moves, this->board, j);
                        white_lance(moves, this->board, j);
                    }else{
                        //この時点で斜め前が保証される。
                        white_direction_RUD(moves, this->board, j);
                        white_toP_direction_RUD(toP_moves, this->board, j);
                        if(j == WHITE_SILVER){
                            white_direction_LUD(moves, this->board, j);
                        }else if(5 <= j){
                            //この時点で金以上の動きが保証されている。成れるのは飛車のみ。
                            white_direction_L(moves, this->board, j);
                            white_direction_UD(moves, this->board, j);
                            if(j == WHITE_KING or j == WHITE_PROMOTED_ROOK){
                                white_direction_LUD(moves, this->board, j);
                            }else if(j == WHITE_ROOK){
                                white_lattice_direction_L(moves, this->board, j);
                                white_lattice_direction_UD(moves, this->board, j);
                                white_toP_lattice_direction_R(toP_moves, this->board, j);
                            }else if(j == WHITE_PROMOTED_BISHOP){
                                white_bishop_direction(moves, this->board, j);
                            };
                        };
                    };
                };
            };
        };
        for(;i < 45; i++){
            j = 110 - this->board[non_dumyy_indices[i]];
            if(0 < j){
                if(j == WHITE_KNIGHT){
                    white_P_knight(P_knight_moves, this->board, j);
                    white_knight(knight_moves, this->board, j);
                }else if(j == WHITE_BISHOP){
                    white_bishop_direction(moves, this->board, j);
                    white_toP_bishop_direction(fromP_moves, this->board, j);
                }else{
                    //この時点で歩以上の動きが保証されている。
                    white_direction_R(moves, this->board, j);
                    if(j == WHITE_LANCE){
                        white_toP_lattice_direction_R(PP_moves, this->board, j);
                        white_lance(moves, this->board, j);
                    }else{
                        //この時点で斜め前が保証される。
                        white_direction_RUD(moves, this->board, j);
                        if(j == WHITE_SILVER){
                            white_direction_LUD(moves, this->board, j);
                        }else if(5 <= j){
                            //この時点で金以上の動きが保証されている。成れるのは飛車のみ。
                            white_direction_L(moves, this->board, j);
                            white_direction_UD(moves, this->board, j);
                            if(j == WHITE_KING or j == WHITE_PROMOTED_ROOK){
                                white_direction_LUD(moves, this->board, j);
                            }else if(j == WHITE_ROOK){
                                white_lattice_direction_L(moves, this->board, j);
                                white_lattice_direction_UD(moves, this->board, j);
                                white_toP_lattice_direction_R(toP_moves, this->board, j);
                            }else if(j == WHITE_PROMOTED_BISHOP){
                                white_bishop_direction(moves, this->board, j);
                            };
                        };
                    };
                };
            };
        };
        for(;i < 81; i++){
            j = 110 - this->board[non_dumyy_indices[i]];
            if(0 < j){
                if(j == WHITE_KNIGHT){
                    white_knight(knight_moves, this->board, j);
                }else if(j == WHITE_BISHOP){
                    white_bishop_direction(moves, this->board, j);
                    white_toP_bishop_direction(fromP_moves, this->board, j);
                }else{
                    //この時点で歩以上の動きが保証されている。
                    white_direction_R(moves, this->board, j);
                    if(j == WHITE_LANCE){
                        white_toP_lattice_direction_R(PP_moves, this->board, j);
                        white_lance(moves, this->board, j);
                    }else{
                        //この時点で斜め前が保証される。
                        white_direction_RUD(moves, this->board, j);
                        if(j == WHITE_SILVER){
                            white_direction_LUD(moves, this->board, j);
                        }else if(5 <= j){
                            //この時点で金以上の動きが保証されている。成れるのは飛車のみ。
                            white_direction_L(moves, this->board, j);
                            white_direction_UD(moves, this->board, j);
                            if(j == WHITE_KING or j == WHITE_PROMOTED_ROOK){
                                white_direction_LUD(moves, this->board, j);
                            }else if(j == WHITE_ROOK){
                                white_lattice_direction_L(moves, this->board, j);
                                white_lattice_direction_UD(moves, this->board, j);
                                white_toP_lattice_direction_R(toP_moves, this->board, j);
                            }else if(j == WHITE_PROMOTED_BISHOP){
                                white_bishop_direction(moves, this->board, j);
                            };
                        };
                    };
                };
            };
        };
        return 1;
    };
};









