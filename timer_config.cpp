#include "timer_config.h"
#include "ui_timer_config.h"
#include <QCheckBox>
#include <QDebug>
#include <QSettings>
#include <QTableWidgetItem>
#include <QModelIndex>
#include <QDebug>
#include <QProcess>
#include <QColorDialog>

extern int ex_value = 90;
extern int ex_position = 65;
extern QString CurrentbgColor;

Timer_Config::Timer_Config(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Timer_Config)
{
    ui->setupUi(this);

    //----------------读取cfg--------------------------------
    QString filename;
    filename = QCoreApplication::applicationDirPath();
    filename += "/config/cfg.ini";
    QSettings set(filename, QSettings::IniFormat);
    set.beginGroup("cfg");
    ui->horizontalSlider->setValue(set.value("Transparency_position").toInt());
    if(set.value("enableTopMost").toString()=="1")
        ui->checkBox->setCheckState(Qt::Checked);
    else if(set.value("enableTopMost").toString()=="0")
        ui->checkBox->setCheckState(Qt::Unchecked);
    CurrentbgColor = set.value("bgColor").toString();
    ui->textEdit->setText(set.value("Text").toString());
    ui->dateEdit->setDate(set.value("Time").toDate());
    set.endGroup();

    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground,true);

}

void Timer_Config::emitTransparency(int position)//position（1~100）
{

    emit SendTransparency(position);
}

Timer_Config::~Timer_Config()
{
    delete ui;
}

void Timer_Config::on_pushButton_clicked()
{
    WriteCfgFile();
    this->hide();
    //qApp->quit();
    //QProcess::startDetached(qApp->applicationFilePath(), QStringList());
}

void Timer_Config::on_pushButton_2_clicked()
{
    this->hide();
}


void Timer_Config::on_horizontalSlider_sliderMoved(int position)
{

    int i = 255 - static_cast<int>((position / 100.0) * 255);
    ui->transpearnt_pctg->setText(QString::number(position));
    ex_value = i;
    ex_position = position;
    emitTransparency(i);
}


void Timer_Config::WriteCfgFile()
{
    QString filename;
    filename = QCoreApplication::applicationDirPath();
    filename += "/config/cfg.ini";
    QSettings set(filename, QSettings::IniFormat);
    set.beginGroup("cfg");
    set.setValue("Transparency",QString::number(ex_value));
    set.setValue("Transparency_position",QString::number(ex_position));
    if(ui->checkBox->isChecked())
        set.setValue("enableTopMost","1");
    else if(ui->checkBox->isChecked()==false)
        set.setValue("enableTopMost","0");
    set.setValue("bgColor",CurrentbgColor);
    set.setValue("Text",ui->textEdit->toPlainText());
    set.setValue("Time",ui->dateEdit->date());
    set.endGroup();
}

void Timer_Config::ChangeTopMost(Qt::CheckState state)
{
    emit SendChangeState(state);
}



void Timer_Config::on_horizontalSlider_valueChanged(int value)
{
    int i = 255 - static_cast<int>((value / 100.0) * 255);
    ui->transpearnt_pctg->setText(QString::number(value));
    ex_value = i;
    ex_position = value;
    emitTransparency(i);
}


void Timer_Config::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->checkState()==Qt::Checked)
        ChangeTopMost(Qt::Checked);
    else if(ui->checkBox->checkState()==Qt::Unchecked)
        ChangeTopMost(Qt::Unchecked);
}


void Timer_Config::on_pushButton_3_clicked()
{
    QColor deflt = QColor::fromString(CurrentbgColor);
    QColor color = QColorDialog::getColor(deflt, this, "选择背景颜色");
    //qDebug() << "颜色选择" << color << color.name();
    if(!color.isValid())
    {
        return;
    }
    else
    {
        //qDebug()<<color.name();
        CurrentbgColor = color.name();
        emit SendbgColor(color);
    }
}


void Timer_Config::on_label_4_linkActivated(const QString &link)
{
    //qDebug()<<"clicked!";
}

