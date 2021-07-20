#include "registered.h"
#include "ui_registered.h"
#include "Home.h"

#include <QGraphicsDropShadowEffect>
#define x_width 230
#define y_height 34
#define w_close 30
#define h_close 30

Registered::Registered(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registered)
{
    ui->setupUi(this);

    registered_init();
}

Registered::~Registered()
{
    delete ui;
}
void Registered::registered_init()
{
    //隐藏头部
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->resize(500, 550);

    main = new QWidget(this);
    main->setObjectName("main");
    main->setFixedSize(this->width() - 20, this->height() - 10);
    main->move(10, 5);

    //窗口阴影
    QGraphicsDropShadowEffect* boxThis = new QGraphicsDropShadowEffect;
    boxThis->setOffset(0,0);
    boxThis->setColor(QColor(Qt::white));
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
    connect(close, &QPushButton::clicked, this, &Registered::btn_close_anmation);

    //图标icon
    header_icon = new QWidget(this);
    header_icon->setObjectName("header_icon");
    icon = new QLabel(header_icon);
    icon->setObjectName("icon");
    icon->setPixmap(QPixmap(":/image/google.png"));
    icon->setScaledContents(true);
    header_icon->setFixedSize(70, 70);
    icon->setFixedSize(50, 50);
    icon->move((header_icon->width() / 2) - (icon->width() / 2), (header_icon->height() / 2) - (icon->height() / 2));
    header_icon->move((main->width() / 2) - (header_icon->width() / 2), 30);
    //qss
    qss.append("QWidget#header_icon{background-color:white;border-radius:35px;}QLabel#icon{border-radius:25px;}QLabel#icon:focus{outline:none}");
    //阴影
    QGraphicsDropShadowEffect* boxShadow = new QGraphicsDropShadowEffect;
    boxShadow->setOffset(0, 0);
    boxShadow->setColor(QColor(Qt::gray));
    boxShadow->setBlurRadius(20);
    header_icon->setGraphicsEffect(boxShadow);

    //输入框
    vb = new QWidget(main);
    int w_vb = main->width();
    int h_vh = (main->height() - header_icon->height()) / 2;
    vb->setFixedSize(w_vb, h_vh);
    vb->move(0, header_icon->height()+y_height);
    //vb->setStyleSheet("border:1px solid red;");

    QVBoxLayout* pLayout = new QVBoxLayout(vb);//水平布局
    email = new QLineEdit();
    userName = new QLineEdit();
    phone = new QLineEdit();
    pwd = new QLineEdit();
    configPwd = new QLineEdit();

    //设置属性
    email->setObjectName("email");
    userName->setObjectName("userName");
    phone->setObjectName("phone");
    pwd->setObjectName("pwd");
    configPwd->setObjectName("configPwd");
    email->setFixedSize(QSize(x_width, y_height));
    userName->setFixedSize(QSize(x_width, y_height));
    phone->setFixedSize(QSize(x_width, y_height));
    pwd->setFixedSize(QSize(x_width, y_height));
    configPwd->setFixedSize(QSize(x_width, y_height));

    //提示语
    email->setPlaceholderText("请输入邮箱");
    userName->setPlaceholderText("请输入用户名");
    phone->setPlaceholderText("请输入手机号");
    pwd->setPlaceholderText("请输入密码");
    configPwd->setPlaceholderText("请再次输入密码");

    //设置密码为圆点
    pwd->setEchoMode(QLineEdit::Password);
    configPwd->setEchoMode(QLineEdit::Password);

    //防止右键出现菜单
    email->setContextMenuPolicy(Qt::NoContextMenu);
    userName->setContextMenuPolicy(Qt::NoContextMenu);
    phone->setContextMenuPolicy(Qt::NoContextMenu);
    pwd->setContextMenuPolicy(Qt::NoContextMenu);
    configPwd->setContextMenuPolicy(Qt::NoContextMenu);

    //布局
    pLayout->addWidget(email, 0, Qt::AlignCenter);
    pLayout->addWidget(userName, 0, Qt::AlignCenter);
    pLayout->addWidget(phone, 0, Qt::AlignCenter);
    pLayout->addWidget(pwd, 0, Qt::AlignCenter);
    pLayout->addWidget(configPwd, 0, Qt::AlignCenter);
    vb->setLayout(pLayout);

    //验证码输入框
    code = new QLineEdit(main);
    code->setObjectName("code");
    code->setFixedSize(x_width / 2, y_height);
    code->move((vb->width() / 2) - (code->width()), h_vh + (y_height * 3));
    code->setPlaceholderText("请输入验证码");
    code->setContextMenuPolicy(Qt::NoContextMenu);
    code->installEventFilter(this);
    qss.append("QLineEdit#code{font-size:13px;font-weight:700;border:1px solid gray;border-top-left-radius:16px;border-bottom-left-radius:16px;padding-left:10px}");
    //验证码
    codeRadoum = new QPushButton(main);
    codeRadoum->setObjectName("codeRadoum");
    codeRadoum->setFixedSize(x_width /2,y_height);
    codeRadoum->move(code->width() + code->x(),code->y());
    codeRadoum->setCursor(Qt::PointingHandCursor);
    time_init();//验证码
    //更新验证码
    connect(codeRadoum, &QPushButton::clicked, this, [=]()
        {
            time_init();
        }
    );
    qss.append("QPushButton#codeRadoum{color:white;border:none;background-color:rgba(33,150,243,0.58);border-bottom-right-radius:16px;border-top-right-radius:16px}");

    qss.append("QLineEdit#email,QLineEdit#userName,QLineEdit#phone,QLineEdit#pwd,QLineEdit#configPwd{font-size:13px;font-weight:700;border-radius:16px;padding-left:10px;border:1px solid gray;}"
        "QLineEdit#email:focus,QLineEdit#userName:focus,QLineEdit#phone:focus,QLineEdit#pwd:focus,QLineEdit#configPwd:focus,QLineEdit#code:focus{border:1px solid #2196f3}");

    //注册按钮
    login = new QPushButton(this);
    login->setObjectName("create");
    login->setText("Create Account");
    login->setFixedSize(x_width, y_height);
    login->move(code->x(), code->y() + code->height() + (y_height + 15));
    login->setCursor(Qt::PointingHandCursor);
    login->setShortcut(Qt::Key_Enter);
    connect(login,&QPushButton::clicked,this,&Registered::create_user);
    //qss btn
    qss.append("QPushButton#create{border:none;font-size:15px;font-weight:700;border-radius:16px;"
        "color:white;background-color:rgba(3,169,244,0.6)}"
        "QPushButton#create:hover{background-color:rgba(3,169,244,0.46)}"
        "QPushButton#create:pressed{background-color:rgba(3,169,244,1)}"
        "QPushButton#create:focus{outline:none}");

    //阴影
    QGraphicsDropShadowEffect* boxShadow_login = new QGraphicsDropShadowEffect;
    boxShadow_login->setOffset(0, 0);
    boxShadow_login->setColor(QColor("#03a9f4"));
    boxShadow_login->setBlurRadius(30);
    login->setGraphicsEffect(boxShadow_login);

    //提示语
    prompt = new QLabel(main);
    prompt->setObjectName("prompt");
    prompt->move(code->x() + 13, code->y() + code->height() + 15);
    prompt->setFixedWidth(pwd->width());
    qss.append("QLabel#prompt{color:red;font-size:13px;}");

    //返回登录页面
    login_return = new QToolButton(main);
    login_return->setObjectName("login_return");
    login_return->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    login_return->setText("返回上一步");
    login_return->setIcon(QIcon(":/image/go-1.png"));
    login_return->setCursor(Qt::PointingHandCursor);
    login_return->move(main->width() - login_return->width(),main->height() - login_return->height());
    qss.append("QToolButton#login_return{border:none;background-color:transparent;color:#2196f3;font-size:12px}"
        "QToolButton#login_return:hover{color:#5eaeef}"
        "QToolButton#login_return:pressed{color:#0073d0}");
    connect(login_return, &QToolButton::clicked, this, &Registered::btn_close_anmation);

    this->setStyleSheet(qss.join(""));
}

//关闭
bool Registered::btn_close_anmation()
{
    QString btn_name = "";

    QPushButton* btn = (QPushButton*)sender();
    //QString text = btn->objectName();

    QToolButton* qtoolBtn = (QToolButton*)sender();

    if (btn->objectName() != "")
    {
        btn_name = btn->objectName();
    }
    else if (qtoolBtn->objectName() != "")
    {
        btn_name = btn->objectName();
    }

    QPropertyAnimation* animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(300);   //过渡效果为3毫秒
    animation->setStartValue(1);    //实体为一
    animation->setEndValue(0);      //隐藏为零
    animation->start();

    //判断点击的那个按钮  进行相对应的触发事件
    if (btn_name == "close")
    {
        connect(animation, &QPropertyAnimation::finished, this, &Registered::btn_close);
    }
    else if (btn_name == "login_return")
    {
        login_return->setEnabled(false);
        connect(animation, &QPropertyAnimation::finished, this, &Registered::login_ites);
    }
    return true;
}

//注册
void Registered::create_user()
{
    static QString prompt_s = "提示：";
    QString name = email->text();	//邮箱
    QString user = userName->text();	//用户名
    QString phone_p = phone->text();	//手机号
    QString password = pwd->text();		//密码
    QString config_password = configPwd->text();	//确认密码
    int code_c = code->text().toInt();		//验证码

    QRegExp exp("[a-zA-Z0-9-_]+@[a-zA-Z0-9-_]+\\.[a-zA-Z]+");//正则表达式
    QRegExpValidator* emailExp = new QRegExpValidator(exp, this);
    email->setValidator(emailExp);
//    phone->setValidator(phoneExp);
//    if (!exp.exactMatch(name))
//    {
//        prompt->setText(QString(prompt_s + "%1").arg("邮箱格式有误！"));
//        return;
//    }
//    if (user == "")
//    {
//        prompt->setText(QString(prompt_s + "%1").arg("用户名不能为空"));
//        return;
//    }
//    if (phone_p == "")
//    {
//        prompt->setText(QString(prompt_s + "%1").arg("手机号不能为空"));
//        return;
//    }
//    if (password == "")
//    {
//        prompt->setText(QString(prompt_s + "%1").arg("密码不能为空"));
//        return;
//    }
//    if (config_password == "")
//    {
//        prompt->setText(QString(prompt_s + "%1").arg("二次密码不能为空"));
//        return;
//    }
//    if (password != config_password)
//    {
//        prompt->setText(QString(prompt_s + "%1").arg("密码不一致,请重新输入"));
//        return;
//    }
//    if (code_c == NULL)
//    {
//        prompt->setText(QString(prompt_s + "%1").arg("验证码不能为空"));
//        return;
//    }
//    if (code_c != IntCode)
//    {
//        prompt->setText(QString(prompt_s + "%1").arg("验证码错误！"));
//        time_init();
//        return;
//    }
    QList<QString>promat_null;
    promat_null << "邮箱不能为空！" << "用户名不能为空" << "手机号不能为空" << "密码不能为空" << "二次密码不能为空"
                << "验证码不能为空";
    QList<QLineEdit*> line = findChildren<QLineEdit *>();
    for(int i =0;i<line.size();i++)
    {
        //获取到注册窗口下面的输入框是否为空、是否密码相同、是否邮箱格式正确、是否验证码正确
        if(line.at(i)->text() == "")
        {
            prompt->setText(QString(prompt_s + "%1").arg(promat_null.at(i)));
            return;
        }
    }
    if (!exp.exactMatch(name))
    {
        prompt->setText(QString(prompt_s + "%1").arg("邮箱格式有误！"));
        return;
    }
    if(phone_p.length() != 11)
    {
        prompt->setText(QString(prompt_s + "%1").arg("手机格式有误"));
        return;
    }
    if(password != config_password)
    {
        prompt->setText(QString(prompt_s + "%1").arg("密码不一致,请重新输入"));
        return;
    }
    if(code_c != IntCode)
    {
        prompt->setText(QString(prompt_s + "%1").arg("验证码错误！"));
        time_init();
        return;
    }
    QSqlQuery query;
    if(query.exec(QString("insert into user_pwd(user,pwd,email,phone) values ('%1','%2','%3','%4')")
                  .arg(user).arg(password).arg(name).arg(phone_p)))
    {
        QMessageBox::information(NULL,"成功！","注册成功，快去登录把",QMessageBox::Yes);
        login_ites();
    }
    else
    {
        prompt->setText(QString(prompt_s+ "%1").arg("数据库出错或字段出错"));
        return;
    }


    prompt->setText("");

}

//随机数
void Registered::time_init()
{
    QTime time;
    time = QTime::currentTime();
    qsrand(time.msec() + time.second() * 1000);
    QString codes = "";
    for (int i = 0; i < 4; i++)
    {
        int rando = qrand() % 10;
        codes += QString("%1").arg(rando, 1, 10);
    }
    codeRadoum->setText(codes);
    IntCode = codes.toInt();
}

//关闭
void Registered::btn_close()
{
    QApplication::quit();
}

//切换注册界面
void Registered::login_ites()
{
    Home* home = new Home();
    home->show();
    this->hide();

}

// 鼠标相对于窗体的位置 event->globalPos() - this->pos()
void Registered::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}

// 若鼠标左键被按下，移动窗体位置
void Registered::mouseMoveEvent(QMouseEvent* event)
{
    if (m_bPressed)
        move(event->globalPos() - m_point);
}

// 设置鼠标未被按下
void Registered::mouseReleaseEvent(QMouseEvent* event)
{
    Q_UNUSED(event);

    m_bPressed = false;
}
