#include "show_home_insurance.h"
#include "ui_show_home_insurance.h"

#include <QGraphicsDropShadowEffect>
#define main_width 800
#define main_height 450
#define w_icon 20
#define h_icon 20
#define w_close 30
#define h_close 30

Show_Home_Insurance::Show_Home_Insurance(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Show_Home_Insurance)
{
    ui->setupUi(this);


    this->setAttribute(Qt::WA_DeleteOnClose);

    insurance_init();
}

Show_Home_Insurance::~Show_Home_Insurance()
{
    delete ui;
}
void Show_Home_Insurance::insurance_init()
{
    //隐藏菜单栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->resize(main_width, main_height);

    main = new QWidget(this);
    main->setObjectName("main");
    main->setFixedSize(main_width - w_icon , main_height - h_icon);
    main->move(10,10);

    //阴影
    QGraphicsDropShadowEffect* boxShadow_login = new QGraphicsDropShadowEffect;
    boxShadow_login->setOffset(0, 0);
    boxShadow_login->setColor(QColor("gray"));
    boxShadow_login->setBlurRadius(30);
    main->setGraphicsEffect(boxShadow_login);

    //头部
    header = new QWidget(main);
    header->setObjectName("header");
    header->setFixedSize(main->width(), h_icon*(2+2));

    header_layout = new QGridLayout(header);
    header_title = new QLabel();
    header_close = new QPushButton();
    header_spacer = new QSpacerItem(40, 80, QSizePolicy::Minimum, QSizePolicy::Expanding);


    header_title->setObjectName("header_title");
    header_close->setObjectName("header_close");

    QFont title_text_font;
    title_text_font.setPixelSize(20);
    title_text_font.setBold(true);
    header_title->setFont(title_text_font);

    header_title->setText("保险方案");
    header_title->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    //header_close->setText("12444");
    header_close->setCursor(Qt::PointingHandCursor);
    header_close->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    header_close->setFixedSize(w_close, h_close);

    header_layout->addWidget(header_title, 0, 0, 2, 1);
    header_layout->addItem(header_spacer, 1, 1, 1, 1);
    header_layout->addWidget(header_close, 0, 1, 1, 1);
    header->setLayout(header_layout);

    connect(header_close, &QPushButton::clicked, this, [=]() {
        this->close();
        });

    //内容
    text = new QWidget(main);
    text->setObjectName("text");
    text->setGeometry((w_close * 2) / 2, header->height(), main->width() - (w_close * 2), main->height() - header->height());

    text_label = new QLabel(text);
    text_label->setObjectName("text_label");
    text_label->setFixedSize(text->width(), text->height());

    QString str;
    str += "一、山有木兮木有枝，心悦君兮君不知。\n";
    str += "二、望一眼，千山万水。忘一眼，人事全非。\n";
    str += "三、玲珑骰子安红豆，相思红豆，入骨相思君知否。——《华胥引》\n";
    str += "四、细看来，不是杨花，点点是离人泪。断送一生憔悴，只消几个黄昏。——赵令峙《清平乐》\n";
    str += "五、你不过惊艳了我的半载浮生，便自此以后让我求生不得，求死不能。\n";
    str += "六、既不回头，何必不忘。既然无缘，何须誓言。今日种种，似水无痕。明夕何夕，君已陌路。\n";
    str += "七、世间安得双全法，不负如来不负卿。\n";
    str += "八、终于为那一身江南烟雨覆了天下，容华谢后，不过一场，山河永寂。——寒呵《南唐旧梦：山河永寂》\n";
    str += "九、尘缘从来都如水，罕须泪，何尽一生情？莫多情，情伤己。\n";
    str += "十、十年情思百年渡，不斩相思不忍顾。——萧鼎《诛仙》\n";
    str += "十一、若君为我赠玉簪，我便为君绾长发。洗尽铅华，从此以后，日暮天涯。\n";
    str += "十二、他们之间的相遇终究不过是笑话一场，其中最可笑的，莫过于你以为我刀枪不入，我以为你百毒不侵。\n";
    str += "十三、奈何桥上又奈何？三生石涯待几生？为君痴心情深陷，来世再续桃花缘。\n";
    str += "十四、怎知红丝错千重，路同归不同，踏雪寻梅方始休，回首天尽头。\n";

    text_label->setText(str);



    qss.append("QPushButton#header_close{border:none;image:url(:/image/close.png)}"
        "QPushButton#header_close:hover{image:url(:/image/close_hover.png)}"
        "QPushButton#header_close:pressed{image:url(:/image/close_pressed.png)}");
    qss.append("QWidget#text{border-top:1px solid gray}");
    qss.append("QWidget#main{background:white;border-radius:5px}");
    this->setStyleSheet(qss.join(""));

}

// 鼠标相对于窗体的位置 event->globalPos() - this->pos()
void Show_Home_Insurance::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}

// 若鼠标左键被按下，移动窗体位置
void Show_Home_Insurance::mouseMoveEvent(QMouseEvent* event)
{
    if (m_bPressed)
        move(event->globalPos() - m_point);
}

// 设置鼠标未被按下
void Show_Home_Insurance::mouseReleaseEvent(QMouseEvent* event)
{
    Q_UNUSED(event);

    m_bPressed = false;
}
