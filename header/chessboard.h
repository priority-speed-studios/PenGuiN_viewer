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
    bool polarity;
    QPair<int,int> position;
};

class ChessBoard
{
public:
    ChessBoard();
};
}

#endif // CHESSBOARD_H
