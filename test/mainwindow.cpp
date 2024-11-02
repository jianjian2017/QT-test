#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QFont>
#include <QScreen>
#include <QGuiApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , is24HourFormat(true)  // 初始化为24小时制
    , backgroundColor(Qt::black)
    , fontColor(Qt::white)
{
    ui->setupUi(this);
    this->setWindowTitle("时钟");

    // 获取屏幕分辨率并设置窗口大小为屏幕的比例
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int width = screenGeometry.width();
    int height = screenGeometry.height();

    // 设置窗口大小为屏幕的80%
    this->resize(width * 0.8, height * 0.8);

    // 初始化时钟标签
    timeLabel = new QLabel(this);
    timeLabel->resize(width-1000, height-800);
    timeLabel->setAlignment(Qt::AlignCenter);





    timeLabel->setFont(QFont("Arial", 48, QFont::Bold));
    timeLabel->setStyleSheet("color: white; background-color: black;");

    // 初始化秒钟标签
    secondLabel = new QLabel(this);
    secondLabel->setAlignment(Qt::AlignCenter);
    secondLabel->setFont(QFont("Arial", 24));
    secondLabel->setStyleSheet("color: white; background-color: black;");

    // 初始化按钮
    formatButton = new QPushButton("24/12", this);
    formatButton->setFont(QFont("Arial", 12));
    connect(formatButton, &QPushButton::clicked, this, &MainWindow::toggleFormat);

    bgColorButton = new QPushButton("背景", this);
    bgColorButton->setFont(QFont("Arial", 12));
    connect(bgColorButton, &QPushButton::clicked, this, &MainWindow::changeBackgroundColor);

    fontColorButton = new QPushButton("字体", this);
    fontColorButton->setFont(QFont("Arial", 12));
    connect(fontColorButton, &QPushButton::clicked, this, &MainWindow::changeFontColor);

    // 圆形按钮样式
    QString buttonStyle = "QPushButton { border-radius: 20px; padding: 10px; }";
    formatButton->setStyleSheet(buttonStyle);
    bgColorButton->setStyleSheet(buttonStyle);
    fontColorButton->setStyleSheet(buttonStyle);

    // 布局按钮
    formatButton->setGeometry(20, 20, 100, 40);
    bgColorButton->setGeometry(140, 20, 100, 40);
    fontColorButton->setGeometry(260, 20, 100, 40);

    // 定时器每秒更新时间
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateClock);
    timer->start(1000);

    // 初次更新时钟和居中布局
    updateClock();
    resizeEvent(nullptr);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateClock()
{
    QTime currentTime = QTime::currentTime();
    QString timeText;

    if (is24HourFormat)
        timeText = currentTime.toString("HH:mm");
    else
        timeText = currentTime.toString("AP hh:mm ");

    timeLabel->setText(timeText);
    secondLabel->setText(currentTime.toString("ss"));
    secondLabel->adjustSize();
}

// 通过重写 resizeEvent 来调整组件大小和位置
void MainWindow::resizeEvent(QResizeEvent *event)
{
    // 获取新的窗口大小
    int width = this->width();
    int height = this->height();

    // 将 timeLabel 居中
    int timeLabelWidth = timeLabel->sizeHint().width();
    int timeLabelHeight = timeLabel->sizeHint().height();
    int timeLabelX = (width - timeLabelWidth) / 2;
    int timeLabelY = (height - timeLabelHeight) / 2;
    timeLabel->move(timeLabelX, timeLabelY);

    // 将 secondLabel 放置在右下角
    int secondLabelWidth = secondLabel->sizeHint().width();
    int secondLabelHeight = secondLabel->sizeHint().height();
    int secondLabelX = width - secondLabelWidth - 100;  // 距离右下角有20像素边距
    int secondLabelY = height - secondLabelHeight - 100;
    secondLabel->move(secondLabelX, secondLabelY);

    // 调用父类的 resizeEvent
    QMainWindow::resizeEvent(event);
}

void MainWindow::toggleFormat()
{
    is24HourFormat = !is24HourFormat;
    updateClock();
}

void MainWindow::changeBackgroundColor()
{
    QColor color = QColorDialog::getColor(backgroundColor, this, "选择背景颜色");
    if (color.isValid()) {
        backgroundColor = color;
        QString bgStyle = QString("background-color: %1;").arg(backgroundColor.name());
        this->setStyleSheet(bgStyle);
        timeLabel->setStyleSheet("color: " + fontColor.name() + "; " + bgStyle);
        secondLabel->setStyleSheet("color: " + fontColor.name() + "; " + bgStyle);
    }
}

void MainWindow::changeFontColor()
{
    QColor color = QColorDialog::getColor(fontColor, this, "选择字体颜色");
    if (color.isValid()) {
        fontColor = color;
        QString fontStyle = QString("color: %1;").arg(fontColor.name());
        timeLabel->setStyleSheet(fontStyle + " background-color: " + backgroundColor.name() + ";");
        secondLabel->setStyleSheet(fontStyle + " background-color: " + backgroundColor.name() + ";");
    }
}
