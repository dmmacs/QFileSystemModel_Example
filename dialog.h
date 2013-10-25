#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDir>
#include <QtCore>
#include <QtGui>
#include <QDirModel>
#include <QStandardItem>
#include <QTreeView>
#include <QFileSystemModel>

#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
    QFileSystemModel *dirmodel;
    QFileSystemModel *filemodel;

    QDomDocument xmldoc;

    void ParseXMLFile(QString sPath, QDomDocument *xmlDoc);


};

#endif // DIALOG_H
