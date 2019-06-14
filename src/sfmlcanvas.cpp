#include "sfmlcanvas.h"
#include <QResource>

sfCanvas::sfCanvas(QWidget *parent, const QPoint& position, const QSize& size) :
    QSFMLCanvas(parent, position, size)
{
    QResource n(":/king");
    king.loadFromMemory(n.data(),std::size_t(n.size()));
    n.setFileName(":/queen");
    queen.loadFromMemory(n.data(),std::size_t(n.size()));
    n.setFileName(":/bishop");
    bishop.loadFromMemory(n.data(),std::size_t(n.size()));
    n.setFileName(":/knight");
    knight.loadFromMemory(n.data(),std::size_t(n.size()));
    n.setFileName(":/rook");
    rook.loadFromMemory(n.data(),std::size_t(n.size()));
    n.setFileName(":/pawn");
    pawn.loadFromMemory(n.data(),std::size_t(n.size()));
}

void sfCanvas::onInit()
{
    h=height(); w=width();
}

void sfCanvas::onUpdate()
{
    sf::RenderWindow::clear(sf::Color::Transparent);
    if(h!=height() || w!=width())
    {
        h=height(); w=width();
        sf::RenderWindow::create(winId());
    }
    int h = height()/8, w = width()/8;

    sf::RectangleShape rect(sf::Vector2f(w,h));

    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            rect.setFillColor((i+j)%2?sf::Color(179,179,179):sf::Color(77,77,77));
            rect.setPosition(i*w,j*h);
            sf::RenderWindow::draw(rect);
            if(j==6 || j==1)
            {
                rect.setTexture(&pawn);
                rect.setFillColor(j==6?sf::Color::Black:sf::Color::White);
                sf::RenderWindow::draw(rect);
                rect.setTexture(nullptr,true);
            }
            else if((j==0) || (j==7))
            {
                if((i==0) || (i==7))
                    rect.setTexture(&rook);
                else if((i==1) || (i==6))
                    rect.setTexture(&knight);
                else if((i==2) || (i==5))
                    rect.setTexture(&bishop);
                else if(((j==0) && (i==3)) || ((j==7) && (i==4)))
                    rect.setTexture(&queen);
                else
                    rect.setTexture(&king);
                rect.setFillColor(j==7?sf::Color::Black:sf::Color::White);
                sf::RenderWindow::draw(rect);
                rect.setTexture(nullptr,true);
            }
        }
}
