#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QUrl>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();

public slots:
    void showAboutUs();
    void showAboutProgram();
    void openLink(QUrl);

private:
    Ui::About *ui;
};

#endif // ABOUT_H
