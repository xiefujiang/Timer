#include "timerclass.h"
#include "ui_timerclass.h"
#include <QScreen>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include <QSettings>

extern Qt::WindowFlags m_flags = Qt::FramelessWindowHint|Qt::WindowTransparentForInput|Qt::ToolTip;
extern QString CurrentTransparency = "65";
extern QString CurrentbgColor = "#000000";


//
TimerClass::TimerClass(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TimerClass)
{

    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/icon/icon.png"));
    //this->setWindowFlag(Qt::FramelessWindowHint);
    //this->setWindowFlag(Qt::WindowStaysOnTopHint);
    //this->setWindowFlag(Qt::WindowTransparentForInput);
    //this->setWindowFlag(Qt::ToolTip);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    //-----------------读取cfg------------------
    QString filename;
    filename = QCoreApplication::applicationDirPath();
    filename += "/config/cfg.ini";
    QSettings set(filename, QSettings::IniFormat);
    set.beginGroup("cfg");
    //QString stysht = "border-bottom-left-radius: 10%;border-bottom-right-radius: 10%;background-color: rgba(255,255,255,";
    QString stysht = "border-bottom-left-radius: 10%;border-bottom-right-radius: 10%;background-color: rgba(";
    QString bgcolor_str = set.value("bgColor").toString();
    CurrentbgColor = bgcolor_str;
    QColor color = QColor::fromString(bgcolor_str);
    stysht += QString::number(color.red());
    stysht += ",";
    stysht += QString::number(color.green());
    stysht += ",";
    stysht += QString::number(color.blue());
    stysht += ",";
    stysht += set.value("Transparency").toString();
    stysht += ");";

    CurrentTransparency = set.value("Transparency").toString();
    //-----------------设置stylesheet
    ui->layer1->setStyleSheet(stysht);
    if(set.value("enableTopMost").toString()=="1")
    this->setWindowFlags(m_flags|Qt::WindowStaysOnTopHint);
    else if(set.value("enableTopMost").toString()=="0")
    this->setWindowFlags(m_flags);
    QDateTime time_cfg = set.value("Time").toDateTime();
    QString str1 = set.value("Text").toString();

    set.endGroup();
    //-------------------------------------------结束cfg
    ui->layer1->setAttribute(Qt::WA_TranslucentBackground,true);
    QFontDatabase::addApplicationFont(":/fonts/cute_font.ttf");
    //根据分辨率置顶
    QScreen *screen=QGuiApplication::primaryScreen ();
    QRect mm=screen->availableGeometry() ;
    int screen_width = mm.width();
    int screen_height = mm.height();
    int size=(int)(screen_height*0.060)-10;
    QFont font;
    font.setFamily("MaoKenTangYuan (beta)");
    font.setPointSize(size);//size=(int)(screen_height*0.065)-10
    QFontMetrics fm(font);
    int textw = fm.boundingRect("距2024年高考还有：000天00小时00分00秒").width();
    int texth = fm.boundingRect("距2024年高考还有：000天00小时00分00秒").height();
    QString str="font-family:'MaoKenTangYuan (beta)';font-size:";
    str += QString::number(size);
    str += "px;border-bottom-left-radius:10%;border-bottom-right-radius:10%;";
    ui->text->setStyleSheet(str);
    ui->text->setWordWrap(false);
    ui->text->setGeometry(0,0,textw,texth);
    ui->layer1->setGeometry(10,0,(int)(size*12.3),texth);
    ui->text->setText("距2024年高考还有：000天");
    this->setGeometry((int)(screen_width-(ui->layer1->width())-10),0,ui->layer1->width()+20,ui->layer1->height()+10);
    this->repaint();
    QTimer timer;
    //QDateTime time1 = QDateTime::fromString("2024-06-07 09:00:00", "yyyy-MM-dd hh:mm:ss");

    QDateTime time2 = QDateTime::currentDateTime();
    int spareday = time2.daysTo(time_cfg);

    //QString str1="距2024年高考还有：";
    str1 += "还有：";
    str1 += QString::number(spareday);
    str1 += "天";
    ui->text->setText(str1);

}



TimerClass::~TimerClass()
{
    delete ui;
}


void TimerClass::recvTransparency(int value_a)
{
    QString str = "background-color: rgba(";
    QString alpha = QString::number(value_a);
    CurrentTransparency = alpha;
    QColor color = QColor::fromString(CurrentbgColor);
    str += QString::number(color.red());
    str += ",";
    str += QString::number(color.green());
    str += ",";
    str += QString::number(color.blue());
    str += ",";
    str += alpha;
    str += ");";
    //qDebug()<<Qt::endl<<str;
    ui->layer1->setStyleSheet(str);
    return;
}

void TimerClass::RecvChangeState(Qt::CheckState state)
{
    if(state==Qt::Checked)
    {
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint);
    this->show();
    }
    else if(state==Qt::Unchecked)
    {
    this->setWindowFlags(Qt::Widget);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->setWindowFlag(Qt::WindowTransparentForInput);
    this->setWindowFlag(Qt::ToolTip);

    this->show();
    }
    return;
}

void TimerClass::RecvbgColor(QColor color)
{
    //qDebug()<<"Recved!"<<color;
    QString str = "background-color: rgba(";
    str += QString::number(color.red());
    str += ",";
    str += QString::number(color.green());
    str += ",";
    str += QString::number(color.blue());
    str += ",";
    str += CurrentTransparency;
    str += ");";
    //qDebug()<<Qt::endl<<str;
    ui->layer1->setStyleSheet(str);
    return;
}

