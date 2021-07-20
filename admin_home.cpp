#include "admin_home.h"
#include "ui_admin_home.h"

#include <QGraphicsDropShadowEffect>
#define admin_width 1440
#define admin_height 900
#define admin_logo_width 60
#define admin_logo_height 60

Admin_Home::Admin_Home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin_Home)
{
    ui->setupUi(this);

    AdminHomeInit();
}

Admin_Home::~Admin_Home()
{
    delete ui;
}

//初始化
void Admin_Home::AdminHomeInit()
{
    //去掉默认边框
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->resize(admin_width, admin_height);

    //背景盒子
    main = new QWidget(this);
    main->setObjectName("main");
    main->setFixedSize(admin_width - 10, admin_height - 10);
    main->move(5,5);
    qss.append("QWidget#main{background:#dadada;border-radius:10px}");

    //窗口阴影
    QGraphicsDropShadowEffect* boxThis = new QGraphicsDropShadowEffect;
    boxThis->setOffset(0, 0);
    boxThis->setColor(QColor(Qt::black));
    boxThis->setBlurRadius(15);
    main->setGraphicsEffect(boxThis);

    //导航栏盒子
    left_list_box = new QWidget(main);
    left_list_box->setObjectName("left_list_box");
    left_list_box->setFixedSize(admin_width / 7, main->height());

    //导航栏数据
    list_widget = new QListWidget(left_list_box);
    list_widget->setIconSize(QSize(25,25));
    list_widget->setFixedSize(left_list_box->width(),left_list_box->height());
    list_widget->setObjectName("list_widget");
    QList<QString>list;
    QList<QString>list_image;
    list << "我要投保" << "我要查询" << "我要报案" << "企业管理" << "个人中心" << "下载中心";
    list_image << ":/image/input_click.png" << ":/image/search_click.png" << ":/image/ba_click.png" << ":/image/qy_click.png"
        << ":/image/user_click.png" << ":/image/dow_click.png";
    for (int i = 0; i < list.count(); i++)
    {
        item = new QListWidgetItem;
        item->setText(list.at(i));
        item->setSizeHint(QSize(list_widget->width(),50));
        item->setIcon(QIcon(list_image.at(i)));
        list_widget->addItem(item);
    }
    list_widget->setCurrentRow(0);	//默认选中第一条数据(导航栏第一个数据)
    connect(list_widget,&QListWidget::itemClicked,this,&Admin_Home::list_item_click);

    //顶部盒子
    top_list_box = new QWidget(main);
    top_list_box->setObjectName("top_list_box");
    top_list_box->setFixedSize(main->width() - left_list_box->width(), left_list_box->width() / 2);
    top_list_box->move(left_list_box->width(),0);
    qss.append("QWidget#left_list_box{background:#101b31;border-top-left-radius:5px;border-bottom-left-radius:5px;color:white}"
        "QWidget#top_list_box{background:#283349;border-top-right-radius:5px;color:white}");

    //logo
    icon = new QWidget(left_list_box);
    icon->setObjectName("icon");
    icon->setFixedSize(left_list_box->width(), top_list_box->height());
    logo = new QLabel(icon);
    logo->setObjectName("logo");
    logo->setPixmap(QPixmap(":/image/logo-ionic.png"));
    logo->setScaledContents(true);
    logo->setFixedSize(admin_logo_width, admin_logo_height);
    logo->move((icon->width() / 2) - (logo->width() / 2),(icon->height() / 2) - (logo->height() / 2));

    list_widget->move(0,icon->height());
    qss.append("QListWidget#list_widget{background: transparent;border:none;color:white;font-size:15px;font-weight:700;outline:0px;}"
        "QListWidget::item{padding-left:10px;color:white;}"
        "QListWidget::item:hover{background-color:rgba(105,93,205,0.74);color:white;}"
        "QListWidget::item:selected{border:none;background-color:rgba(105,93,205,0.74);color:white;}");

    //个人头像、名称 盒子
    logo_user = new QWidget(top_list_box);
    logo_user->setObjectName("logo_user");
    logo_user->setFixedSize(admin_logo_width * 4 ,top_list_box->height() - 20);
    logo_user->move(top_list_box->width() - logo_user->width() - 10,10);
    //头像
    logo_pix = new QLabel();
    logo_pix->setObjectName("logo_pix");
    logo_pix->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    logo_pix->setPixmap(QPixmap(":/image/google.png"));
    logo_pix->setFixedSize(40, 40);
    logo_pix->setScaledContents(true);
    qss.append("QLabel#logo_pix{background-color:black;border-radius:20px}");
    //欢迎
    hy = new QLabel();
    hy->setObjectName("hy");
    hy->setText("您好");
    //用户名
    userName = new QLabel();
    userName->setObjectName("userName");
    //退出按钮
    exit_user = new QPushButton();
    exit_user->setObjectName("exit_user");
    exit_user->setText("退出");
    exit_user->setFixedSize(60, 30);
    exit_user->setCursor(Qt::PointingHandCursor);
    connect(exit_user, &QPushButton::clicked, this, &Admin_Home::exit_click);

    logo_layout = new QGridLayout(logo_user);
    logo_layout->addWidget(logo_pix,0,0,2,1);
    logo_layout->addWidget(hy,0,1,1,1,Qt::AlignBottom);
    logo_layout->addWidget(userName, 1,1,1,1,Qt::AlignTop);
    logo_layout->addWidget(exit_user, 0, 2,2,1);
    logo_layout->setVerticalSpacing(0);
    logo_user->setLayout(logo_layout);

    //主页内容
    main_show = new QWidget(main);
    main_show->setObjectName("main_click");
    main_show->setFixedSize(main->width() - left_list_box->width() - 20,main->height() - top_list_box->height() - 20);
    main_show->move(left_list_box->width() + 10 , top_list_box->height() + 10);
    //窗口切换
    stack_main = new QStackedWidget(main_show);
    stack_main->setObjectName("stack_main");
    stack_main->setFixedSize(main_show->width(), main_show->height());

    //初始化内容、大小
    int getSize_w = main_show->width();
    int getSize_h = main_show->height();
    showHome = new Show_Home(main_show);
    showHome->getSize(getSize_w, getSize_h);
    search = new Show_Search(main_show);
    search->getResize(getSize_w, getSize_h);

    stack_main->addWidget(showHome);
    stack_main->addWidget(search);

    stack_main->setCurrentWidget(showHome);	//默认显示的窗口

    qss.append("QWidget#main_click{border-radius:5px;}"
        "QWidget#hy,QWidget#userName,QPushButton#exit_user{color:#ababab;font-size:13px}"
        "QPushButton#exit_user{background-color:rgba(12,23,43,1);border-radius:15px}"
        "QPushButton#exit_user:hover{background-color:rgba(12,23,43,0.72);}");

    //调用显示的函数界面
    init_home_main();


    qss.append("QWidget#icon{border-bottom:1px solid gray}");


    this->setStyleSheet(qss.join(""));
    this->setMouseTracking(true);
}


//获取导航栏发送的信号
void Admin_Home::list_item_click(QListWidgetItem* item)
{
    QString text = item->text();
    qDebug() << text;
    if (text == "我要投保")
    {
        //showHome->setAttribute(Qt::WA_DeleteOnClose);
        //showHome->show();
        stack_main->setCurrentWidget(showHome);
    }
    else if (text == "我要查询")
    {
        //search->setAttribute(Qt::WA_DeleteOnClose);
        //search->show();
        stack_main->setCurrentWidget(search);

    }
}

//初始化内容
void Admin_Home::init_home_main()
{

    //showHome->show();
    //默认显示
    /*if (list_name_click == "我要投保")
    {
        Show_Home* showHome = new Show_Home(main_show);
        showHome->get_resize(main_show->width(), main_show->height());
        showHome->setAttribute(Qt::WA_DeleteOnClose);
        showHome->show();
    }
    else if (list_name_click == "我要查询")
    {
        qDebug() << "123";
    }*/
}

//获取当前用户名
void Admin_Home::GetName(const QString name)
{
    value = name;
    userName->setText(value);
}

//退出
void Admin_Home::exit_click()
{
    qApp->exit(0);
}

// 鼠标相对于窗体的位置 event->globalPos() - this->pos()
void Admin_Home::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}

// 若鼠标左键被按下，移动窗体位置
void Admin_Home::mouseMoveEvent(QMouseEvent* event)
{
    if (m_bPressed)
        move(event->globalPos() - m_point);
}

// 设置鼠标未被按下
void Admin_Home::mouseReleaseEvent(QMouseEvent* event)
{
    Q_UNUSED(event);

    m_bPressed = false;
}
