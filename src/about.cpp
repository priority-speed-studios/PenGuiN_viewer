#include "about.h"
#include "ui_about.h"
#include <QTextStream>
#include <QFile>
#include <QDesktopServices>
#include <iostream>

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    this->setWindowTitle("About");
}

About::~About()
{
    delete ui;
}
void About::showAboutUs()
{
    QFile file(":/aboutUs.html");
    file.open(QFile::ReadOnly | QFile::Text);
    ui->textBrowser->setHtml(file.readAll());
    show();
}
void About::showAboutProgram()
{
    QFile file(":/aboutProgram.html");
    file.open(QFile::ReadOnly | QFile::Text);
    ui->textBrowser->setHtml(file.readAll());
    show();
}

void About::openLink(QUrl url)
{
    QDesktopServices::openUrl(url);
    hide();
}
