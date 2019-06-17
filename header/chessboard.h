#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QPair>
namespace Chess
{
enum class PieceType
{
    Empty, Pawn, Bishop, Knight, Rook, Queen, King
};

struct Piece
{
    PieceType type;
    QPair<int,int> position;
    bool polarity;
#if __linux__
    char unused[3]; // just for providing the padding, faster memory access
#endif
};

class ChessBoard
{
    Piece pieces[32];
public:
    ChessBoard();
};
}

#endif // CHESSBOARD_H
