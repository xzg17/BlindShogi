#ifndef _ACTIVATE_DROP_MACROS_HPP_
#define _ACTIVATE_DROP_MACROS_HPP_

#include "indices.hpp"

#define ACTIVATE_DROPS(piece) drops[i * 4 + normal_drop_pieces[piece]] = 1
#define ACTIVATE_PAWN_LANCE_DROPS(piece) pawn_lance_drops[i * 2 + piece - 3] = 1
#define ACTIVATE_KNIGHT_DROPS knight_drops[i] = 1

#endif