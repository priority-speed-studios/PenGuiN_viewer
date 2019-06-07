#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "qsfmlcanvas.h"

class sfCanvas : public QSFMLCanvas
{
    Q_OBJECT
private:
    void onInit();
    void onUpdate();

    sf::Texture mTexture;
    sf::Sprite mSprite;
    sf::Image mImage;

public:
    explicit sfCanvas(QWidget *parent, const QPoint& position=QPoint(0,0), const QSize& size=QSize(200,200));

signals:

public slots:
};

#endif // MYCANVAS_H