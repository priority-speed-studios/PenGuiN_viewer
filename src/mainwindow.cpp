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

    //reg = QRegularExpression("([KQRBN]?[a-h]?x?[a-h][1-8]=?[KQRBN]?[\\+#]?|O-O|O-O-O)");
    reg = QRegularExpression("((?<num>\\d+). ([KQRBN]?[a-h]?x?[a-h][\\\\+#]?[1-8]=?[KQRBN]?|O-O|O-O-O)(\\+?)( |\n)"
                             "([KQRBN]?[a-h]?x?[a-h][\\\\+#]?[1-8]=?[KQRBN]?|O-O|O-O-O)(\\+?))"
                             "( |\n)(\\{.+?\\})?|\\d+. ([KQRBN]?[a-h]?x?[a-h][\\\\+#]?[1-8]=?"
                             "[KQRBN]?|O-O|O-O-O)(\\+?)(( |\n)(\\{.+?\\}))?");
    reg = QRegularExpression(
                "((?<num>(\\d+)). (?<white>([KQRBN]?[a-h]?x?[a-h][\\\\+#]?[1-8]=?[KQRBN]?|O-O|O-O-O)(\\+?))( |\n)(?<black>([KQRBN]?[a-h]?x?[a-h][\\\\+#]?[1-8]=?[KQRBN]?|O-O|O-O-O)(\\+?))( |\n)(?<comment>\\{.+?\\})?)|((?<numi>\\d+).( |\n)(?<whitei>([KQRBN]?[a-h]?x?[a-h][\\\\+#]?[1-8]=?[KQRBN]?|O-O|O-O-O))(\\+?)(( |\n)((?<commenti>\\{.+?\\})?)))");

    regexMatchIterator = reg.globalMatch(loadedText);
    while(regexMatchIterator.hasNext())
    {
        QRegularExpressionMatch match = regexMatchIterator.next();
        int num = (match.captured("num").trimmed()=="" ?
                       match.captured("numi").trimmed():match.captured("num").trimmed()).toInt();
        list.push_back(PGN(match.captured("white").trimmed()=="" ?
                               match.captured("whitei").trimmed():match.captured("white").trimmed(),
                           match.captured("black").trimmed()=="" ?
                               match.captured("blacki").trimmed():match.captured("black").trimmed(),
                           match.captured("comment").trimmed()=="" ?
                               match.captured("commenti").trimmed():match.captured("comment").trimmed(),num));
    }
    // data in list
}
