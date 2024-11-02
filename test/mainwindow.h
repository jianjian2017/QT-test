#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include <QColorDialog>
#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // 重写 resizeEvent，用于窗口大小变化时更新布局
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateClock();            // 更新时钟显示
    void toggleFormat();           // 切换24小时与12小时制
    void changeBackgroundColor();  // 更改背景颜色
    void changeFontColor();        // 更改字体颜色

private:
    Ui::MainWindow *ui;
    QLabel *timeLabel;             // 显示当前时间的标签
    QLabel *secondLabel;           // 显示秒数的标签
    QTimer *timer;                 // 定时器，用于每秒更新时钟
    QPushButton *formatButton;     // 切换时间格式的按钮
    QPushButton *bgColorButton;    // 更改背景颜色的按钮
    QPushButton *fontColorButton;  // 更改字体颜色的按钮

    bool is24HourFormat;           // 当前是否为24小时制
    QColor backgroundColor;        // 当前背景颜色
    QColor fontColor;              // 当前字体颜色
};

#endif // MAINWINDOW_H
