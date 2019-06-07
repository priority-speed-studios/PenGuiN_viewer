#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

#include <SFML/Graphics.hpp>
#include <QWidget>
#include <QTimer>

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
    Q_OBJECT
private:
    virtual void onInit() = 0;
    virtual void onUpdate() = 0;

    virtual QPaintEngine* paintEngine() const override;

    virtual void showEvent(QShowEvent* e) override;

    virtual void paintEvent(QPaintEvent* e) override;

    QTimer mTimer;
    bool mInitialized;

public:
    explicit QSFMLCanvas(QWidget *parent, const QPoint& position, const QSize& size, int frametime = 0);

    virtual ~QSFMLCanvas() override;

signals:

public slots:

};

#endif // QSFMLCANVAS_H
