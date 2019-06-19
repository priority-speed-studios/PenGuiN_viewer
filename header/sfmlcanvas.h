#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "qsfmlcanvas.h"
#include "chessboard.h"

class sfCanvas : public QSFMLCanvas
{
    Q_OBJECT
private:
    void onInit();
    void onUpdate();
    int h,w;
    QMap<Chess::PieceType, sf::Texture> pieceMap;
    Chess::ChessBoard *board;

public:
    explicit sfCanvas(QWidget *parent, const QPoint& position=QPoint(0,0), const QSize& size=QSize(200,200));

public slots:
    void changeBoard(Chess::ChessBoard *board);
};

#endif // MYCANVAS_H
