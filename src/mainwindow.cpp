#include "header/mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QRegularExpression>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadedText = "";
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
    while(regexMatchIterator.hasNext())
    {
        QRegularExpressionMatch match = regexMatchIterator.next();
        list.push_back(PGN(match.captured("white").trimmed(),
                           match.captured("black").trimmed(),
                           match.captured("comment").trimmed(),
                           match.captured("num").trimmed().toInt()));

        ui->listWidget->addItem(QString::number(list.last().move) + ". " +
                                list.last().white + " " +
                                list.last().black);
        /*QTextStream(stdout) << match.captured("white").trimmed()<< " "<<
                match.captured("black").trimmed()<< " "<<
                match.captured("comment").trimmed()<< " "<<
                num<<"\n";*/
    }
    ui->listWidget->item(0)->setTextColor(QColor(100,255,100));
    ui->listWidget->sortItems();
}

void MainWindow::changeHighLight(QListWidgetItem */*item*/)
{
// handle hightlight change here
}
