#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

namespace Ui {
class MainWindow;
}

struct PGN {
    QString white="",black="",comment="";
    int move=0;
    PGN(QString w,QString b,QString com,int m)
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

private:
    Ui::MainWindow *ui;
    QString loadedText;
    QList<PGN> list;
};

#endif // MAINWINDOW_H
