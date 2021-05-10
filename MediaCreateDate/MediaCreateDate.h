#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QDialog>
#include <QDateTime>
#include <QProcess>
#include <QMimeData>
#include <QDropEvent>
#include <QMessageBox>
#include "ui_MediaCreateDate.h"

class MediaCreateDate : public QDialog
{
    Q_OBJECT

public:
    MediaCreateDate(QWidget *parent = Q_NULLPTR);

private:
    Ui::MediaCreateDateClass ui;

private slots:
	void dropEvent(QDropEvent *event);          //֧��ͨ����ק��ʽ�����ļ�
	void dragEnterEvent(QDragEnterEvent *event);
	void on_pushButton_clicked();
};
