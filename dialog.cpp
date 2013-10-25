#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);

    dirmodel = new QFileSystemModel(this);
    filemodel = new QFileSystemModel(this);

    QString sPath = "C:/Users/dmmacs/Documents/Qt Projects/tmp_root";

    dirmodel->setRootPath(sPath);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel->setReadOnly(true);


    ui->treeView->setModel(dirmodel);
    ui->treeView->expandAll();
    ui->treeView->resizeColumnToContents(0);
    //ui->treeView->columnWidth(0)
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);

    ui->m_dirPath->setText(sPath);


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_treeView_clicked(const QModelIndex &index)
{
    QString sPath;// = dirmodel->fileInfo(index).absoluteFilePath();

    sPath = ui->textEdit->toPlainText();
    sPath += "/n";
    sPath += dirmodel->fileInfo(index).absoluteFilePath();

    ui->textEdit->setText(sPath);


}

void Dialog::on_pushButton_clicked()
{
    ParseXMLFile("C:/Users/dmmacs/Documents/Qt Projects/QFileSystemModel/tmp.xml", &xmldoc);
}


void Dialog::ParseXMLFile(QString sPath, QDomDocument *xmlDoc)
{
    QFile file(sPath);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file";
        ui->textEdit->setText("Failed to open file");
    }
    else
    {
        if(!xmlDoc->setContent(&file))
        {
            qDebug() << "Failed to load document";
            ui->textEdit->setText("Failed to load document");
        }
        file.close();
    }


    //get the root element
    QDomElement root = xmlDoc->firstChildElement();
    QDomNodeList items = root.elementsByTagName("dir");

     qDebug() << "Total items = " << items.count();
     QString tmp_str;
     tmp_str = "Total items  = ";
     QLocale tmpLoc;
     tmp_str += tmpLoc.toString(items.count());
//     tmp_str += QLocale::toString(i);


     ui->textEdit->setText(tmp_str);

     for(int i = 0; i < items.count(); i++)
     {
        QDomNode itemnode = items.at(i);

        //convert to element
        if(itemnode.isElement())
        {
            QDomElement itemele = itemnode.toElement();
            qDebug() << itemele.attribute("name");
            tmp_str = ui->textEdit->toPlainText();
            tmp_str += "\n";
            tmp_str += itemele.attribute("name");
            ui->textEdit->setText(tmp_str);
        }
     }
}
