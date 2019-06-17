#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "qsfmlcanvas.h"


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

class sfCanvas : public QSFMLCanvas
{
    Q_OBJECT
private:
    void onInit();
    void onUpdate();
    int h,w;
    sf::Texture king,queen,knight,bishop,rook,pawn;

public:
    explicit sfCanvas(QWidget *parent, const QPoint& position=QPoint(0,0), const QSize& size=QSize(200,200));

signals:

public slots:
};

#endif // MYCANVAS_H
