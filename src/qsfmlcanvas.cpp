#include "qsfmlcanvas.h"

QSFMLCanvas::QSFMLCanvas(QWidget *parent, const QPoint &position, const QSize &size, int frameTime) :
    QWidget(parent), mInitialized(false)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    setFocusPolicy(Qt::StrongFocus);

    move(position);
    resize(size);

    mTimer.setInterval(frameTime);
}

#ifdef Q_WS_X11
#include <qt/qx11info_x11.h>
#include <x11/xlib.h>
#endif
void QSFMLCanvas::showEvent(QShowEvent* e)
{
    (void)e;
    if(!mInitialized)
    {
#ifdef Q_WS_X11
        XFlush(QX11Info::display());
#endif

        sf::RenderWindow::create(winId());
        onInit();

        connect(&mTimer, &QTimer::timeout, this, static_cast<void(QSFMLCanvas::*)(void)>(&QSFMLCanvas::repaint));
        mTimer.start();
        mInitialized = true;
    }
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
    return nullptr;
}


void QSFMLCanvas::paintEvent(QPaintEvent* e)
{
    (void)e;
    onUpdate();
    sf::RenderWindow::display();
}

QSFMLCanvas::~QSFMLCanvas()
{
}
