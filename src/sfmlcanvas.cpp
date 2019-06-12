#include "header/sfmlcanvas.h"
#include <QResource>

sfCanvas::sfCanvas(QWidget *parent, const QPoint& position, const QSize& size) :
    QSFMLCanvas(parent, position, size)
{
    QResource n(":/knight");
    mTexture.loadFromMemory(n.data(),std::size_t(n.size()));
    mSprite.setTexture(mTexture);
    mSprite.setColor(sf::Color(51,51,51));
}

void sfCanvas::onInit()
{

}

void sfCanvas::onUpdate()
{
    sf::RenderWindow::clear(sf::Color::Yellow);
    int h = height()/8, w = width()/8;

    sf::RectangleShape rect(sf::Vector2f(w,h));
    rect.setOutlineColor(sf::Color::Green);
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            rect.setFillColor((i+j)%2?sf::Color::White:sf::Color::Black);
            rect.setPosition(i*w,j*h);
            sf::RenderWindow::draw(rect);
            if(i==1 && j==0)
            {
                rect.setTexture(&mTexture,true);
                rect.setFillColor(sf::Color::White);
                sf::RenderWindow::draw(rect);
                rect.setTexture(nullptr,true);
            }
        }
}
