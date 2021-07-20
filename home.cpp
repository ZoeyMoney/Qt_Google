#include "home.h"
#include "ui_home.h"
#include "admin_home.h"
#include "registered.h"
#include <QGraphicsDropShadowEffect>
#define x_width 230
#define y_height 34
#define w_close 30
#define h_close 30

Home::Home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);

    win_init();
}

Home::~Home()
{
    delete ui;
}

void Home::win_init()
{
    //连接数据库
    mysql = new myMysql(this);
    flag = mysql->openMysql();
    //信息
    this->setWindowTitle("Gmail");
    //隐藏头部
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->resize(500, 380);
    //继承主窗口
    main = new QWidget(this);
    main->setObjectName("main");
    main->setFixedSize(this->width() - 20, this->height() - 10);
    main->move(10, 5);

    //窗口阴影
    QGraphicsDropShadowEffect* boxThis = new QGraphicsDropShadowEffect;
    boxThis->setOffset(0);
    boxThis->setColor(QColor(Qt::gray));
    boxThis->setBlurRadius(15);
    main->setGraphicsEffect(boxThis);

    qss.append("QWidget#main{background:white;border-radius:10px}");

    //设置字体
    //this->setFont(QFont("微软雅黑"));

    //关闭按钮
    close = new QPushButton(main);
    close->setObjectName("close");
    close->setFixedSize(w_close, h_close);
    close->move(main->width() - close->width() - 10, 10);
    close->setCursor(Qt::PointingHandCursor);
    close->setToolTip("关闭");
    qss.append("QPushButton#close{border:none;image:url(:/image/close.png)}"
               "QPushButton#close:hover{image:url(:/image/close_hover.png)}"
               "QPushButton#close:pressed{image:url(:/image/close_pressed.png)}");
    connect(close, &QPushButton::clicked, this, &Home::btn_close_anmation);

    header_icon = new QWidget(this);
    header_icon->setObjectName("header_icon");
    icon = new QLabel(header_icon);
    icon->setObjectName("icon");
    icon->setPixmap(QPixmap(":/image/google.png"));
    icon->setScaledContents(true);
    header_icon->setFixedSize(70, 70);
    icon->setFixedSize(50,50);
    icon->move((header_icon->width() / 2) - (icon->width() / 2), (header_icon->height() / 2) - (icon->height() / 2));
    header_icon->move((main->width() / 2) - (header_icon->width() / 2), 40);
    //qss
    qss.append("QWidget#header_icon{background-color:white;border-radius:35px;}QLabel#icon{border-radius:25px;}QLabel#icon:focus{outline:none}");
    //阴影
    QGraphicsDropShadowEffect* boxShadow = new QGraphicsDropShadowEffect;
    boxShadow->setOffset(0,0);
    boxShadow->setColor(QColor(Qt::gray));
    boxShadow->setBlurRadius(20);
    header_icon->setGraphicsEffect(boxShadow);

    //输入框
    from = new QWidget(main);
    user = new QLineEdit(from);
    pwd = new QLineEdit(from);

    from->setObjectName("from");
    user->setObjectName("user");
    pwd->setObjectName("pwd");

    from->setFixedSize(main->width(), 100);
    from->move(0, header_icon->y() + header_icon->height() + 20);
    user->setFixedSize(x_width, y_height);
    pwd->setFixedSize(x_width, y_height);
    user->move((from->width() / 2) - (user->width() / 2), 10);
    pwd->move((from->width() / 2) - (pwd->width() / 2), user->y() + 45);
    pwd->setEchoMode(QLineEdit::Password);
    user->setPlaceholderText("Email");
    pwd->setPlaceholderText("Password");
    qss.append("QWidget#from{}QLineEdit#user,QLineEdit#pwd{font-size:13px;font-weight:700;border-radius:16px;padding-left:10px;border:1px solid gray;}"
               "QLineEdit#user:focus,QLineEdit#pwd:focus{border:1px solid #2196f3}");
    user->setContextMenuPolicy(Qt::NoContextMenu);
    pwd->setContextMenuPolicy(Qt::NoContextMenu);

    //提示语
    prompt = new QLabel(main);
    prompt->setObjectName("prompt");
    prompt->move(pwd->x()+13,from->y()+from->height());
    prompt->setFixedWidth(pwd->width());
    qss.append("QLabel#prompt{color:red;font-size:13px;}");


    //按钮
    login = new QPushButton(this);
    login->setObjectName("login");
    login->setText("Sign in");
    login->setFixedSize(x_width, y_height);
    login->move(pwd->x(), from->y()+ from->height() + y_height);
    login->setCursor(Qt::PointingHandCursor);
    login->setShortcut(Qt::Key_Return);
    //qss btn
    qss.append("QPushButton#login{border:none;font-size:15px;font-weight:700;border-radius:16px;"
               "color:white;background-color:rgba(3,169,244,0.6)}"
               "QPushButton#login:hover{background-color:rgba(3,169,244,0.46)}"
               "QPushButton#login:pressed{background-color:rgba(3,169,244,1)}"
               "QPushButton#login:focus{outline:none}");
    connect(login, &QPushButton::clicked, this, &Home::login_click);

    //阴影
    QGraphicsDropShadowEffect* boxShadow_login = new QGraphicsDropShadowEffect;
    boxShadow_login->setOffset(0, 0);
    boxShadow_login->setColor(QColor("#03a9f4"));
    boxShadow_login->setBlurRadius(30);
    login->setGraphicsEffect(boxShadow_login);

    //create
    create = new QPushButton(main);
    create->setObjectName("create");
    create->setText("Create account");
    create->move((main->width() / 2) - (create->width() / 2) , main->height() - y_height);
    create->setCursor(Qt::PointingHandCursor);
    connect(create, &QPushButton::clicked, this, &Home::btn_close_anmation);

    qss.append("QPushButton#create{border:none;font-size:13px;color:#2196f3;font-weight:700}"
               "QPushButton#create:hover{color:#8fc3ec}"
               "QPushButton#create:pressed{color:#0064b3}"
               "QPushButton#create:focus{outline:none}");

    this->setStyleSheet(qss.join(""));
}

// 鼠标相对于窗体的位置 event->globalPos() - this->pos()
void Home::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}

//登录
void Home::login_click()
{
    //登录
    QString name = user->text();
    QString pwds = pwd->text();
    QString prompt_s = "提示：";
    QRegExp exp("[a-zA-Z0-9-_]+@[a-zA-Z0-9-_]+\\.[a-zA-Z]+");//正则表达式
    QRegExpValidator* email = new QRegExpValidator(exp, this);
    user->setValidator(email);

    if (!exp.exactMatch(name))
    {
        prompt->setText(QString(prompt_s + "%1").arg("邮箱格式有误！"));
        return;
    }

    QSqlQuery query;
    query.exec( QString("select * from user_pwd where email='%1' and pwd='%2'").arg(name).arg(pwds));
    if(query.next()){
        prompt->setText("登录成功");
        login->setEnabled(false);
        //实例化管理员界面
        Admin_Home* admin = new Admin_Home();
        admin->GetName(name);
        admin->show();
        this->hide();
    }
    else
    {
        prompt->setText(QString(prompt_s + "邮箱或密码错误"));
        return;
    }

}

//关闭
bool Home::btn_close_anmation()
{

    QPushButton* btn = (QPushButton*)sender();
    QString text = btn->objectName();

    QPropertyAnimation* animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(300);   //过渡效果为3毫秒
    animation->setStartValue(1);    //实体为一
    animation->setEndValue(0);      //隐藏为零
    animation->start();


    //判断点击的那个按钮  进行相对应的触发事件
    if (text == "close")
    {
        connect(animation, &QPropertyAnimation::finished, this, &Home::btn_close);
    }
    else if (text == "create")
    {
        create->setEnabled(false);
        connect(animation, &QPropertyAnimation::finished, this, &Home::create_ites);
    }
    return true;
}

//关闭
void Home::btn_close()
{
    QApplication::quit();
}

//切换注册界面
void Home::create_ites()
{
    Registered* reg = new Registered();
    reg->show();
    this->hide();
}


// 若鼠标左键被按下，移动窗体位置
void Home::mouseMoveEvent(QMouseEvent* event)
{
    if (m_bPressed)
        move(event->globalPos() - m_point);
}

// 设置鼠标未被按下
void Home::mouseReleaseEvent(QMouseEvent* event)
{
    Q_UNUSED(event);

    m_bPressed = false;
}
