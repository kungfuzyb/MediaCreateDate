#include "MediaCreateDate.h"

MediaCreateDate::MediaCreateDate(QWidget *parent)
    : QDialog(parent)
{
	Qt::WindowFlags flags = Qt::Dialog; flags |= Qt::WindowCloseButtonHint; setWindowFlags(flags);
    ui.setupUi(this);
	this->setAcceptDrops(true);
}

void MediaCreateDate::dragEnterEvent(QDragEnterEvent *event)                //��ק�ļ�������
{
	if (event->mimeData()->hasUrls())
		event->acceptProposedAction();
	else
		event->ignore();
}


void MediaCreateDate::dropEvent(QDropEvent *event)                 //��ק�ļ�������
{
	const QMimeData *mimeData = event->mimeData();      // ��ȡMIME����
	QString InputFilePath;
	if (mimeData->hasUrls())
	{                            // ��������а���URL
		QList<QUrl> urlList = mimeData->urls();         // ��ȡURL�б�
		InputFilePath = urlList.at(0).toLocalFile();  // �����е�һ��URL��ʾΪ�����ļ�·��

		ui.lineEdit->setText(InputFilePath);
	}
}

void MediaCreateDate::on_pushButton_clicked()
{
	QDateTime dateTime = ui.dateTimeEdit->dateTime();
	QString Time = dateTime.toString("yyyy:M:d hh:mm:ss");
	QString CreateDate = "-CreateDate=";
	QString	MediaCreateDate = "-MediaCreateDate=";
	QString 	TrackCreateDate = "-TrackCreateDate=";
	CreateDate.append(Time);
	CreateDate.append("+08:00");
	MediaCreateDate.append(Time);
	MediaCreateDate.append("+08:00");
	TrackCreateDate.append(Time);
	TrackCreateDate.append("+08:00");
	QString File = ui.lineEdit->text();

	QProcess *Convert = new QProcess(this); ;
	QStringList Arg;

	Arg.clear();
	Arg.append("-api");
	Arg.append("QuickTimeUTC");
	Arg.append(CreateDate);
	Arg.append(File);
	Convert->start("./exiftool.exe", Arg);

	Arg.clear();
	Arg.append("-api");
	Arg.append("QuickTimeUTC");
	Arg.append(MediaCreateDate);
	Arg.append(File);
	Convert->start("./exiftool.exe", Arg);

	Arg.clear();
	Arg.append("-api");
	Arg.append("QuickTimeUTC");
	Arg.append(TrackCreateDate);
	Arg.append(File);
	Convert->start("./exiftool.exe", Arg);

	QMessageBox::information(NULL, "��ʾ", "����޸ģ�", QMessageBox::Yes, QMessageBox::Yes);

}



