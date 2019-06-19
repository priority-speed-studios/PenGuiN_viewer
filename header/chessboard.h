#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QPair>
#include <QList>

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
    Piece(PieceType type=PieceType::Empty, QPair<int,int> position={0,0}, bool polarity=false)
    {
        this->type = type; this->position = position; this->polarity = polarity;
    }
#endif
};

class ChessBoard
{
    QVector<Piece> pieces;
public:
    ChessBoard();
    QVector<Piece> getState();
};
}

#endif // CHESSBOARD_H
