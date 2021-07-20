#include "show_home_date.h"
#include "ui_show_home_date.h"

#include <QGraphicsDropShadowEffect>
#define main_width 400
#define main_height 450
#define w_icon 20
#define h_icon 20
#define w_close 30
#define h_close 30

Show_Home_Date::Show_Home_Date(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Show_Home_Date)
{
    ui->setupUi(this);

    init();
}

Show_Home_Date::~Show_Home_Date()
{
    delete ui;
}
void Show_Home_Date::init()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->resize(main_width, main_height);

    //设置自己的界面
    main = new QWidget(this);
    main->setObjectName("main");
    main->setGeometry(w_icon / 2, h_icon / 2, main_width - w_icon, main_height - h_icon);

    //阴影
    QGraphicsDropShadowEffect* boxShadow_login = new QGraphicsDropShadowEffect;
    boxShadow_login->setOffset(0, 0);
    boxShadow_login->setColor(QColor("gray"));
    boxShadow_login->setBlurRadius(30);
    main->setGraphicsEffect(boxShadow_login);

    //头部
    header = new QWidget(main);
    header->setObjectName("header");
    header->setFixedSize(main->width(), w_icon * 3);

    header_layout = new QGridLayout(header);

    header_title = new QLabel();
    header_title->setObjectName("header_title");
    QFont font;
    font.setBold(true);
    font.setPixelSize(20);
    header_title->setText("保险期限");
    header_title->setFont(font);
    header_title->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    header_close = new QPushButton();
    header_close->setObjectName("header_close");
    header_close->setFixedSize(w_close, h_close);
    header_close->setCursor(Qt::PointingHandCursor);

    header_hide = new QPushButton();
    header_hide->setObjectName("header_hide");
    header_hide->setFixedSize(w_close, h_close);

    header_spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    header_layout->addWidget(header_hide, 0, 0);
    header_layout->addItem(header_spacer, 1, 1);
    header_layout->addWidget(header_title, 0, 1);
    header_layout->addItem(header_spacer, 1, 2);
    header_layout->addWidget(header_close, 0, 2);
    header->setLayout(header_layout);

    //内容
    text = new QWidget(main);
    text->setObjectName("text");
    text->setGeometry(w_close / 2, header->height(), main->width() - w_close, main->height() - header->height());

    tet = new QLabel(text);
    tet->setObjectName("tet");
    tet->setText("保险期限就是没有期限");

    //qss.append("QWidget#text,QWidget#header{border:1px solid red}");

    qss.append("QWidget#main{background:white;border-radius:5px}");
    qss.append("QPushButton#header_hide{border:none;background:transparent}");
    qss.append("QWidget#header_close{border:none;image:url(:/image/close.png)}"
        "QWidget#header_close:hover{image:url(:/image/close_hover.png)}"
        "QWidget#header_close:pressed{image:url(:/image/close_pressed.png)}");

    connect(header_close, &QPushButton::clicked, [=] {
        this->close();
        });

    this->setStyleSheet(qss.join(""));

}

// 鼠标相对于窗体的位置 event->globalPos() - this->pos()
void Show_Home_Date::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}

// 若鼠标左键被按下，移动窗体位置
void Show_Home_Date::mouseMoveEvent(QMouseEvent* event)
{
    if (m_bPressed)
        move(event->globalPos() - m_point);
}

// 设置鼠标未被按下
void Show_Home_Date::mouseReleaseEvent(QMouseEvent* event)
{
    Q_UNUSED(event);

    m_bPressed = false;
}
