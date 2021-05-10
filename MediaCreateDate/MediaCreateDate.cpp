#include "MediaCreateDate.h"

MediaCreateDate::MediaCreateDate(QWidget *parent)
    : QDialog(parent)
{
	Qt::WindowFlags flags = Qt::Dialog; flags |= Qt::WindowCloseButtonHint; setWindowFlags(flags);
    ui.setupUi(this);
	this->setAcceptDrops(true);
}

void MediaCreateDate::dragEnterEvent(QDragEnterEvent *event)                //拖拽文件进窗口
{
	if (event->mimeData()->hasUrls())
		event->acceptProposedAction();
	else
		event->ignore();
}


void MediaCreateDate::dropEvent(QDropEvent *event)                 //拖拽文件进窗口
{
	const QMimeData *mimeData = event->mimeData();      // 获取MIME数据
	QString InputFilePath;
	if (mimeData->hasUrls())
	{                            // 如果数据中包含URL
		QList<QUrl> urlList = mimeData->urls();         // 获取URL列表
		InputFilePath = urlList.at(0).toLocalFile();  // 将其中第一个URL表示为本地文件路径

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

	QMessageBox::information(NULL, "提示", "完成修改！", QMessageBox::Yes, QMessageBox::Yes);

}



