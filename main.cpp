#include "timerclass.h"

#include <QApplication>
#include <QMenu>
#include <QSystemTrayIcon>
#include <windows.h>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    HANDLE hMutex = CreateMutex(NULL, TRUE, L"4DC66B9D-1BC5-4321-8A83-429AC82F0085");     // 创建一个互斥量来保证只运行一个实例
    if(hMutex != NULL)
    {
        if(GetLastError() == ERROR_ALREADY_EXISTS)
        {
            return 1;
        }
    }

    TimerClass w;
    Timer_Config cfg;
    w.show();

    static bool isshowed = true;
    QSystemTrayIcon tray = new QSystemTrayIcon();

    QIcon icon = QIcon(":/icon/icon.png");
    tray.setIcon(icon);
    tray.setToolTip(QString::fromLocal8Bit("倒计时"));
    QMenu *menu = new QMenu();
    QAction *show = new QAction("显示/隐藏");
    QAction *exit = new QAction("退出");
    QAction *config = new QAction("配置...");
    menu->addAction(config);
    menu->addAction(show);
    menu->addAction(exit);
    tray.setContextMenu(menu);
    tray.show();
    QObject::connect(show, &QAction::triggered, [&](){
        if(isshowed)
        {
            w.hide();
        }
        else
        {
            w.show();
        }
        isshowed = !isshowed;
    });
    QObject::connect(exit,&QAction::triggered, [&](){
        QApplication::quit();
    });
    QObject::connect(config,&QAction::triggered, [&](){
        cfg.show();
    });
    tray.show();
    a.connect(&cfg, &Timer_Config::SendTransparency, &w, &TimerClass::recvTransparency);
    a.connect(&cfg, &Timer_Config::SendChangeState, &w, &TimerClass::RecvChangeState);
    a.connect(&cfg, &Timer_Config::SendbgColor, &w, &TimerClass::RecvbgColor);

    return a.exec();
}
