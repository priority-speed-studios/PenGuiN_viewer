#include "chessboard.h"

Chess::ChessBoard::ChessBoard()
{
    pieces = {
        {Chess::PieceType::King, {4,1}, true},
        {Chess::PieceType::King, {5,8}, true},
        {Chess::PieceType::Queen, {5,1}, true},
        {Chess::PieceType::Queen, {4,8}, true},
        {Chess::PieceType::Bishop, {3,1}, true},
        {Chess::PieceType::Bishop, {3,8}, true},
        {Chess::PieceType::Bishop, {6,1}, true},
        {Chess::PieceType::Bishop, {6,8}, true},
        {Chess::PieceType::Knight, {2,1}, true},
        {Chess::PieceType::Knight, {2,8}, true},
        {Chess::PieceType::Knight, {7,1}, true},
        {Chess::PieceType::Knight, {7,8}, true},
        {Chess::PieceType::Rook, {1,1}, true},
        {Chess::PieceType::Rook, {1,8}, true},
        {Chess::PieceType::Rook, {8,1}, true},
        {Chess::PieceType::Rook, {8,8}, true},
        {Chess::PieceType::Pawn, {1,7}, true},
        {Chess::PieceType::Pawn, {2,7}, true},
        {Chess::PieceType::Pawn, {3,7}, true},
        {Chess::PieceType::Pawn, {4,7}, true},
        {Chess::PieceType::Pawn, {5,7}, true},
        {Chess::PieceType::Pawn, {6,7}, true},
        {Chess::PieceType::Pawn, {7,7}, true},
        {Chess::PieceType::Pawn, {8,7}, true},
        {Chess::PieceType::Pawn, {1,2}, true},
        {Chess::PieceType::Pawn, {2,2}, true},
        {Chess::PieceType::Pawn, {3,2}, true},
        {Chess::PieceType::Pawn, {4,2}, true},
        {Chess::PieceType::Pawn, {5,2}, true},
        {Chess::PieceType::Pawn, {6,2}, true},
        {Chess::PieceType::Pawn, {7,2}, true},
        {Chess::PieceType::Pawn, {8,2}, true}
    };
}

QVector<Chess::Piece> Chess::ChessBoard::getState()
{
    return this->pieces;
}
