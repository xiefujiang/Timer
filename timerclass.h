#ifndef TIMERCLASS_H
#define TIMERCLASS_H

#include <QWidget>
#include "timer_config.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TimerClass; }
QT_END_NAMESPACE

class TimerClass : public QWidget
{
    Q_OBJECT

public:
    TimerClass(QWidget *parent = nullptr);
    ~TimerClass();
    Timer_Config *TimerConfig_ptr;
    void OnSliderMoved(int position);

public slots:
    void recvTransparency(int value_a);
    void RecvChangeState(Qt::CheckState state);
    void RecvbgColor(QColor color);
    //void RecvDate(QDate date);
    //void RecvText(QString text);

private:
    Ui::TimerClass *ui;
};
#endif // TIMERCLASS_H
