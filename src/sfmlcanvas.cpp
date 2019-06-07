#include "header/sfmlcanvas.h"

sfCanvas::sfCanvas(QWidget *parent, const QPoint& position, const QSize& size) :
    QSFMLCanvas(parent, position, size)
{
}

void sfCanvas::onInit()
{

}

void sfCanvas::onUpdate()
{
    // render cycle updates here!!
    sf::RenderWindow::clear(sf::Color::Blue);
}
