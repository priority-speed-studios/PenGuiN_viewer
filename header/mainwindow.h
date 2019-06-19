#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QListWidgetItem>
#include "chessboard.h"
#include "about.h"

namespace Ui {
class MainWindow;
}

struct PGN {
    QString white="",black="",comment="";
    unsigned move=0;
    PGN(QString w,QString b,QString com,unsigned m)
    {
        white = w; black = b; comment = com; move = m;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void exit();
    void loadfile();
    void changeHighLight(QListWidgetItem*);

signals:
    void boardStateChanged(Chess::ChessBoard* next);

private:
    Ui::MainWindow *ui;
    QString loadedText;
    QList<PGN> list;
    About *about;
    QVector<Chess::ChessBoard> boards;
};

#endif // MAINWINDOW_H
