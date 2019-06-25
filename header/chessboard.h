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

struct move // parse moves to form this struct (@2bit-hack 's implementation)
{
    bool polarity; // black or white
    PieceType type; // piecetype
    uint8_t origin; // piece origin of format base10(file)*10 + base10(rank)
    uint8_t dest; // piece destination of format base10(file)*10 + base10(rank)
    PieceType promo; // promoted to
    enum class Castle{None, Short, Long} castle; // typeof castle
    enum class CheckMate{None, Check, Mate} isCheckMate; // typeof check/mate
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
