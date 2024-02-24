#ifndef TIMER_CONFIG_H
#define TIMER_CONFIG_H

#include <QWidget>

namespace Ui {
class Timer_Config;
}

class Timer_Config : public QWidget
{
    Q_OBJECT


public:
    explicit Timer_Config(QWidget *parent = nullptr);
    void emitTransparency(int position);//使用ui-slider的position值调用函数，发送信号
    ~Timer_Config();

    void WriteCfgFile();
    void ChangeTopMost(Qt::CheckState state);

signals:
    void SendTransparency(int value);
    void SendChangeState(Qt::CheckState state);
    void SendbgColor(QColor color);
    //void SendDate(QDate date);
    //void SendText(QString text);

private slots:
    void on_pushButton_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_pushButton_2_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_3_clicked();

    void on_label_4_linkActivated(const QString &link);

private:
    Ui::Timer_Config *ui;
};

#endif // TIMER_CONFIG_H
