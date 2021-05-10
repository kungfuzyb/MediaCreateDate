#pragma once

#include <QtWidgets/QDialog>
#include "ui_MediaCreateDate.h"

class MediaCreateDate : public QDialog
{
    Q_OBJECT

public:
    MediaCreateDate(QWidget *parent = Q_NULLPTR);

private:
    Ui::MediaCreateDateClass ui;
};
