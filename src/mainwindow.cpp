#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QRegularExpression>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include "about.h"
#include <QTextStream>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadedText = "";
    about = new About(this);
    this->setWindowTitle("PenGuiN Viewer");
    for(QAction* action : ui->menuFile->actions())
    {
        if(action->text().contains("PGN"))
            connect(action,&QAction::triggered,this,&MainWindow::loadfile);
        else if(action->text().contains("Exit"))
            connect(action,&QAction::triggered,this,&MainWindow::exit);
    }
    for(QAction* action  : ui->menuAbout->actions())
    {
        if(action->text().contains("Us"))
            connect(action,&QAction::triggered,about,&About::showAboutUs);
        else if(action->text().contains("Program"))
            connect(action,&QAction::triggered,about,&About::showAboutProgram);
    }

    connect(this,&MainWindow::boardStateChanged,ui->widget,&sfCanvas::changeBoard);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::exit()
{
    QApplication::exit(0);
}

void MainWindow::loadfile()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open PGN"), "",
                                                    tr("PGN Files (*.pgn)"));
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        return;

    loadedText = file.readAll();
    QString writerBuffer;
    QXmlStreamWriter writer(&writerBuffer);
    writer.writeStartDocument();
    writer.writeStartElement("table");
    writer.writeStartElement("tr");
    writer.writeTextElement("th","ID");
    writer.writeTextElement("th","Detail");
    writer.writeEndElement();

    QRegularExpression reg("\\[(?<id>(.*?)) \"(?<detail>(.*?))\"\\]",
                           QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator regexMatchIterator = reg.globalMatch(loadedText);
    while (regexMatchIterator.hasNext())
    {
        QRegularExpressionMatch match = regexMatchIterator.next();
        writer.writeStartElement("tr");
        writer.writeTextElement("td",match.captured("id"));
        writer.writeTextElement("td",match.captured("detail"));
        writer.writeEndElement();
    }
    writer.writeEndDocument();
    ui->textBrowser->setHtml(writerBuffer);
    reg = QRegularExpression(
                "((?<num>\\d+)\\.) (?<white>([KQRBN]?[a-h]?x?[a-h][1-8]=?[KQRBN]?[\\+#]?|O-O|O-O-O)"
                "( |\n))(?<black>([KQRBN]?[a-h]?x?[a-h][1-8]=?[KQRBN]?[\\+#]?|O-O|O-O-O))?"
                "((( |\n)\\{(?<comment>(.*?))\\})?)");
    regexMatchIterator = reg.globalMatch(loadedText);
    ui->listWidget->clear();
    ui->listWidget->addItem("0. Begin");
    unsigned i=0;
    while(regexMatchIterator.hasNext())
    {
        i++;
        QRegularExpressionMatch match = regexMatchIterator.next();
        list.push_back(PGN(match.captured("white").trimmed(),
                           match.captured("black").trimmed(),
                           match.captured("comment").trimmed(),
                           unsigned(match.captured("num").trimmed().toInt())));

        ui->listWidget->addItem(QString::number(list.last().move) + ".1. " +
                                list.last().white);
        if(list.last().black != "")
            ui->listWidget->addItem(QString::number(list.last().move) + ".2. " +
                                    list.last().black);
        if(i!=list.last().move)
            QMessageBox::information(this,"Corrupt?","The game data maybe corrupt! Call the cops");
    }
    ui->listWidget->setCurrentRow(0);
    boards.resize(list.length());
    emit this->boardStateChanged(&boards[0]);
}

void MainWindow::changeHighLight(QListWidgetItem *item)
{
    ui->statusBar->showMessage(list[(item->text().split(".")[0]).toInt()].comment);
    emit this->boardStateChanged(&boards[(item->text().split(".")[0]).toInt()]);
}
