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

		Read = new QProcess(this); ;
		connect(Read, SIGNAL(readyReadStandardOutput()), this, SLOT(on_readoutput()));
		QStringList Arg;

		Arg.clear();
		Arg.append("-s");
		Arg.append(InputFilePath);

		Read->start("./exiftool.exe", Arg);
		Read->waitForStarted();
		Read->waitForFinished(-1);
	}
}

void MediaCreateDate::on_Button_CopyTime_clicked()
{
	QDateTime dateTime = ui.dateTimeEdit_Origin->dateTime();
	ui.dateTimeEdit_Target->setDateTime(dateTime);
}


void MediaCreateDate::on_Button_Modify_clicked()
{
	QDateTime dateTime = ui.dateTimeEdit_Target->dateTime();
	if (ui.checkBox->isChecked())
	{
		dateTime = dateTime.addSecs(-28800);
	}
	QString Time = dateTime.toString("yyyy:M:d hh:mm:ss");
	QString CreateDate = "-CreateDate=";
	QString	MediaCreateDate = "-MediaCreateDate=";
	QString 	TrackCreateDate = "-TrackCreateDate=";
	CreateDate.append(Time);
	MediaCreateDate.append(Time);
	TrackCreateDate.append(Time);

	QString File = ui.lineEdit->text();

	QProcess *Convert = new QProcess(this); ;
	QStringList Arg;

	Arg.clear();
	Arg.append("-api");
	Arg.append("LargeFileSupport=1");
	Arg.append(CreateDate);
	Arg.append(File);
	Convert->start("./exiftool.exe", Arg);
	Convert->waitForStarted();
	Convert->waitForFinished(-1);

	Arg.clear();
	Arg.append("-api");
	Arg.append("LargeFileSupport=1");
	Arg.append(MediaCreateDate);
	Arg.append(File);
	Convert->start("./exiftool.exe", Arg);
	Convert->waitForStarted();
	Convert->waitForFinished(-1);

	Arg.clear();
	Arg.append("-api");
	Arg.append("LargeFileSupport=1");
	Arg.append(TrackCreateDate);
	Arg.append(File);
	Convert->start("./exiftool.exe", Arg);
	Convert->waitForStarted();
	Convert->waitForFinished(-1);

	QMessageBox::information(NULL, "提示", "完成修改！", QMessageBox::Yes, QMessageBox::Yes);

}

void MediaCreateDate::on_readoutput()
{
	QString output = Read->readAllStandardOutput().data();

	QStringList sections = output.split("\r\n");

	int length = sections.length(), i;

	for (i = 0; i < length; i++)
	{
		if (sections.at(i).contains("MediaCreateDate"))
		{
			output = sections.at(i);
		}
	}
	output.remove(" ");
	sections = output.split("e:");
	QDateTime dateTime = QDateTime::fromString(sections.at(1), "yyyy:MM:ddhh:mm:ss");
	dateTime = dateTime.addSecs(28800);
	ui.dateTimeEdit_Origin->setDateTime(dateTime);
}

