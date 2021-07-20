#include "show_home_add.h"
#include "ui_show_home_add.h"

#include "Show_Home.h"

#include <QGraphicsDropShadowEffect>
#define main_width 400
#define main_height 450
#define title_height 80
#define w_close 30
#define h_close 30
#define x_width 230
#define y_height 34

Show_Home_Add::Show_Home_Add(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Show_Home_Add)
{
    ui->setupUi(this);

    init();
}

Show_Home_Add::~Show_Home_Add()
{
    delete ui;
}
void Show_Home_Add::init()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->resize(main_width, main_height);

    //主界面
    main = new QWidget(this);
    main->setObjectName("main");
    main->setFixedSize(main_width - 10, main_height - 10);
    main->move(5,5);
    qss.append("QWidget#main{background:white}");

    //阴影
    QGraphicsDropShadowEffect* boxShadow_login = new QGraphicsDropShadowEffect;
    boxShadow_login->setOffset(0, 0);
    boxShadow_login->setColor(QColor("gray"));
    boxShadow_login->setBlurRadius(30);
    main->setGraphicsEffect(boxShadow_login);

    //头部
    title = new QWidget(main);
    title->setObjectName("title");
    title->setFixedSize(main->width() - 40, title_height);
    title->move(main->width() - title->width(), 0);
    //布局
    title_layout = new QGridLayout(title);
    title_text = new QLabel();
    title_close = new QPushButton();
    space = new QSpacerItem(20,40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    title_layout->setObjectName("title_layout");
    title_text->setObjectName("title_text");
    title_close->setObjectName("title_close");

    title_text->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    title_close->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QFont title_text_font;
    title_text_font.setPixelSize(20);
    title_text_font.setBold(true);
    title_text->setFont(title_text_font);

    title_text->setText("投保录入");
    title_close->setCursor(Qt::PointingHandCursor);
    title_close->setFixedSize(w_close, h_close);

    title_layout->addWidget(title_text, 0, 0, 2, 1);
    title_layout->addItem(space, 1, 1, 1, 1);
    title_layout->addWidget(title_close, 0, 1, 1, 1);
    title->setLayout(title_layout);

    qss.append("QPushButton#title_close{border:none;image:url(:/image/close.png)}"
        "QPushButton#title_close:hover{image:url(:/image/close_hover.png)}"
        "QPushButton#title_close:pressed{image:url(:/image/close_pressed.png)}");

    connect(title_close, &QPushButton::clicked, this, [&]() {
        this->close();
        });

    //输入框
    from = new QWidget(main);
    from->setObjectName("from");
    from->setFixedSize(main->width(), main->height() - (title->height() * 2));
    from->move(0,title->height());

    //输入框、布局
    from_layout = new QVBoxLayout(from);
    name = new QLineEdit();
    identity_number = new QLineEdit();
    data_of_birth = new QDateEdit();
    phone = new QLineEdit();
    post = new QComboBox();
    add_book = new QLineEdit();
    //岗位
    QList<QString>PostText;
    QStringList strList;
    PostText << "技术员" << "销售员" << "管理员" << "执行员";
    strList.append(PostText);

    name->setObjectName("name");
    identity_number->setObjectName("identity_number");
    data_of_birth->setObjectName("data_of_birth");
    phone->setObjectName("phone");
    post->setObjectName("post");
    add_book->setObjectName("add_book");

    //过滤器
    data_of_birth->installEventFilter(this);

    name->setFixedSize(QSize(x_width, y_height));
    identity_number->setFixedSize(QSize(x_width, y_height));
    data_of_birth->setFixedSize(QSize(x_width, y_height));
    phone->setFixedSize(QSize(x_width, y_height));
    post->setFixedSize(QSize(x_width, y_height));
    add_book->setFixedSize(QSize(x_width, y_height));

    name->setContextMenuPolicy(Qt::NoContextMenu);
    identity_number->setContextMenuPolicy(Qt::NoContextMenu);
    data_of_birth->setContextMenuPolicy(Qt::NoContextMenu);
    phone->setContextMenuPolicy(Qt::NoContextMenu);
    post->setContextMenuPolicy(Qt::NoContextMenu);
    add_book->setContextMenuPolicy(Qt::NoContextMenu);

    name->setPlaceholderText("请输入姓名");
    identity_number->setPlaceholderText("请输入身份证号");
    phone->setPlaceholderText("请输入联系电话");
    post->addItem("请选择技术岗位");
    post->addItems(strList);
    add_book->setPlaceholderText("请输入通讯地址");

    //name->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //identity_number->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //data_of_birth->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //phone->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //post->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //add_book->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    from_layout->setMargin(0);
    from_layout->addWidget(name,0,Qt::AlignCenter);
    from_layout->addWidget(identity_number, 0, Qt::AlignCenter);
    from_layout->addWidget(data_of_birth, 0, Qt::AlignCenter);
    from_layout->addWidget(phone, 0, Qt::AlignCenter);
    from_layout->addWidget(post, 0, Qt::AlignCenter);
    from_layout->addWidget(add_book, 0, Qt::AlignCenter);
    from->setLayout(from_layout);

    qss.append("QLineEdit#name,QLineEdit#identity_number,QLineEdit#data_of_birth,QLineEdit#phone,QComboBox#post,QLineEdit#add_book{"
    "border-radius:16px;border:1px solid gray;font-size:13px;font-weight:700;padding-left:10px}");
    qss.append("QComboBox::drop-down{border:none}");
    //qss.append("QWidget#from{border:1px solid red}");

    //底部按钮
    footer = new QWidget(main);
    promat = new QLabel(footer);
    add_btn = new QPushButton(footer);

    footer->setObjectName("footer");
    add_btn->setObjectName("add_btn");
    promat->setObjectName("promat");

    footer->setFixedSize(main->width(), main->height() - title->height() - from->height());
    footer->move(0,title->height() + from->height());

    add_btn->setText("添加投保人员");
    add_btn->setFixedSize(name->width(), y_height);
    add_btn->move((footer->width() / 2) - (add_btn->width() / 2),(footer->height() / 2) - (add_btn->height() / 2));
    add_btn->setCursor(Qt::PointingHandCursor);

    promat->setFixedWidth(main->width());
    promat->move((main->width() / 2) - (x_width / 2), 0);

    qss.append("QWidget#add_btn{border-radius:17px;border:none;background:#7969e6;color:white;font-size:13px;outline:none}"
        "QLabel#promat{color:red;font-size:13px;font-weight:700}"
        "QWidget#add_btn:hover{background:#9b8fec}"
        "QWidget#add_btn:pressed{background:#7969e6}");
    qss.append("QWidget#main{border-radius:7px}");
    //qss.append("QWidget#footer{border:1px solid red}");
    //下拉框
    connect(add_btn, &QPushButton::clicked, this, &Show_Home_Add::btn_submit);

    this->setStyleSheet(qss.join(""));

}

//过滤器
bool Show_Home_Add::eventFilter(QObject* w, QEvent* e)
{
    //时间选择器
    if (w == data_of_birth)
    {
        if (e->type() == QEvent::FocusIn)
        {

        }
        else if(e->type() == QEvent::FocusOut)
        {
            qDebug() << "555";
        }
    }

    return QWidget::eventFilter(w, e);
}

//提交
void Show_Home_Add::btn_submit()
{
    QString promat_text = "提示：";
    //获取所有输入框
    QList<QLineEdit*>list_input = from->findChildren<QLineEdit*>();
    for (int i = 0; i < list_input.count(); i++)
    {
        QLineEdit* itemInput = list_input.at(i);
        if (itemInput->text() == "")
        {
            promat->setText(promat_text + "输入框不能为空");
            return;
        }
        else
        {
            promat->setText("");
        }
    }
    if (post->currentText() == "请选择技术岗位")
    {
        promat->setText("技术岗位不能为空");
        return;
    }
    //提交至数据库
    QString insert = QString("insert into show_admin(user,ident,birth_date,phone,gwze,site) values ('%1','%2','%3','%4','%5','%6')").arg(name->text())
                    .arg(identity_number->text()).arg(data_of_birth->text()).arg(phone->text()).arg(post->currentText()).arg(add_book->text());
//    qDebug() << insert;
    if(query.exec(insert))
    {
        QMessageBox::information(NULL,"成功","添加成功",QMessageBox::Yes);
        emit sendDataList("成功");
    }else
    {
        QMessageBox::information(NULL,"失败","添加失败",QMessageBox::Yes);
        return;
    }

    //提交上方数据  将清空内容
    for (int i = 0; i < list_input.count(); i++)
    {
        QLineEdit* itemText = list_input.at(i);
        itemText->clear();
    }
    post->setCurrentIndex(0);
    this->close();
}

// 鼠标相对于窗体的位置 event->globalPos() - this->pos()
void Show_Home_Add::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}

// 若鼠标左键被按下，移动窗体位置
void Show_Home_Add::mouseMoveEvent(QMouseEvent* event)
{
    if (m_bPressed)
        move(event->globalPos() - m_point);
}

// 设置鼠标未被按下
void Show_Home_Add::mouseReleaseEvent(QMouseEvent* event)
{
    Q_UNUSED(event);

    m_bPressed = false;
}
