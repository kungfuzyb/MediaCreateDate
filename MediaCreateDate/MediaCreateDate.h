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
	QProcess *Read;

private slots:
	void dropEvent(QDropEvent *event);          //支持通过拖拽方式读入文件
	void dragEnterEvent(QDragEnterEvent *event);

	void on_readoutput();

	void on_Button_CopyTime_clicked();
	void on_Button_Modify_clicked();
};
