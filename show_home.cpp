#include "show_home.h"
#include "ui_show_home.h"

#include <QGraphicsDropShadowEffect>
#include "Show_Home_Insurance.h"
#include "show_home_date.h"
#define header_height 100
#define	header_btn_width 150
#define header_btn_height 32
#define icon_width 20
#define icon_height 20

Show_Home::Show_Home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Show_Home)
{
    ui->setupUi(this);

    showHomeInit();
}

Show_Home::~Show_Home()
{
    delete ui;
}
void Show_Home::showHomeInit()
{
    //初始化背景
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    main = new QWidget(this);
    main->setObjectName("main");
    main->setStyleSheet("QWidget#main{background:white}");
    //按钮盒子
    widget_header = new QWidget(main);
    widget_header->setObjectName("widget_header");
    headerLyout = new QGridLayout(widget_header);
    //实例化按钮
    addBtn = new QToolButton();
    bxBtn = new QToolButton();
    qxBtn = new QToolButton();
    startBtn = new QPushButton();
    orderBtn = new QPushButton();
    //给按钮设置对象名称
    addBtn->setObjectName("addBtn");
    bxBtn->setObjectName("bxBtn");
    qxBtn->setObjectName("qxBtn");
    startBtn->setObjectName("startBtn");
    orderBtn->setObjectName("orderBtn");
    //按钮大小
    addBtn->setFixedSize(header_btn_width, header_btn_height);
    bxBtn->setFixedSize(header_btn_width, header_btn_height);
    qxBtn->setFixedSize(header_btn_width, header_btn_height);
    //鼠标样式
    addBtn->setCursor(Qt::PointingHandCursor);
    bxBtn->setCursor(Qt::PointingHandCursor);
    qxBtn->setCursor(Qt::PointingHandCursor);
    orderBtn->setCursor(Qt::PointingHandCursor);
    //按钮内容
    addBtn->setText("添加投保人员");
    bxBtn->setText("保险方案");
    qxBtn->setText("保险期限");
    startBtn->setText(QString("起止时间\n2021-4-19 : %1").arg(dataTime()));

    //按钮图标、设置图片居右文字在左
    //addBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //bxBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //qxBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //addBtn->setLayoutDirection(Qt::RightToLeft);
    //bxBtn->setLayoutDirection(Qt::RightToLeft);
    //qxBtn->setLayoutDirection(Qt::RightToLeft);
    //addBtn->setIcon(QIcon(":/image/add.png"));
    //bxBtn->setIcon(QIcon("image/select.png"));
    //qxBtn->setIcon(QIcon("image/select.png"));
    //addBtn->setIconSize(QSize(icon_width, icon_height));
    //bxBtn->setIconSize(QSize(icon_width, icon_height));
    //qxBtn->setIconSize(QSize(icon_width, icon_height));
    //弹簧
    horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Maximum);
    addBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    bxBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    qxBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    startBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    orderBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //栅格化添加内容
    headerLyout->addWidget(addBtn, 0,0,1,1);
    headerLyout->addWidget(bxBtn, 0,1,1,1);
    headerLyout->addWidget(qxBtn, 0,2,1,1);
    headerLyout->addItem(horizontalSpacer,0,3,1,1);
    headerLyout->addWidget(startBtn, 0,4,1,1);
    headerLyout->addWidget(orderBtn, 0,5,1,1);
    widget_header->setLayout(headerLyout);

    QGraphicsDropShadowEffect* boxShadow_login = new QGraphicsDropShadowEffect;
    boxShadow_login->setOffset(0, 0);
    boxShadow_login->setColor(QColor("gray"));
    boxShadow_login->setBlurRadius(30);
    startBtn->setGraphicsEffect(boxShadow_login);


    //按钮样式
    qss.append("QToolButton#addBtn,QToolButton#bxBtn,QToolButton#qxBtn{background:#7969e6;color:white;border-radius:16px;font-size:14px;}"
        "QToolButton#addBtn:hover,QToolButton#bxBtn:hover,QToolButton#qxBtn:hover{background:#9b8fec;}"
        "QToolButton#addBtn:pressed,QToolButton#bxBtn:pressed,QToolButton#qxBtn:pressed{background:#7968e8}");
    qss.append("QPushButton#startBtn{background:white;color:gray;padding-left:3px;text-align:left;padding-left:10px;border-radius:10px}"
        "QPushButton#orderBtn{background:#7969e6;color:white;font-size:16px;font-weight:700;border-radius:10px}"
        "QPushButton#orderBtn:hover{background:#9487ec}"
        "QPushButton#orderBtn:pressed{background:#7969e6}");



    //表格初始化
    table_widget = new QWidget(main);
    table_widget->setObjectName("table_widget");
    table_view = new QTableView(table_widget);
    model = new QStandardItemModel();
    query_model = new QSqlQueryModel;
    QStringList listText;
    listText << "选择" << "姓名" << "身份证号" << "出生日期" << "联系电话" << "岗位职责" << "通讯地址";
    //设置头部、列数
    model->setColumnCount(listText.count());
    table_view->setModel(model);
    //设置表格属性
    table_view->verticalHeader()->setHidden(true);		//去掉边侧id
    model->setHorizontalHeaderLabels(listText);
    table_view->setSelectionBehavior(QAbstractItemView::SelectRows);		//选中整行
    table_view->setEditTriggers(QAbstractItemView::NoEditTriggers);		//禁止修改
    table_view->setFocusPolicy(Qt::NoFocus);
    table_view->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    table_view->setShowGrid(false);		//不显示格子线
    table_view->horizontalHeader()->setHighlightSections(false);	//表头不能点击
    table_view->setAlternatingRowColors(true);

    table_view_class();
    table_view_query_exec();


    //向表中插入300条数据
//    for(int i=0;i<300;i++)
//    {
//        QString num = QString::fromUtf8("小明_%1").arg(i);
//        QString idents = QString("123456789987654%1").arg(QString::number(i));
//        QString inseti = QString("insert into show_admin(user,ident,birth_date,phone,gwze,site) values ('%1','%2','%3','%4','%5','%6')").arg(num)
//                .arg(idents).arg("2020-10-27").arg("12345678999").arg("技术部").arg("山东菏泽曹县牛逼6666");
//        if(query.exec(inseti))
//        {
//            qDebug()<<"123";
//        }else
//        {
//            qDebug()<<"456";
//        }
//    }

    //确认选择、取消选择
    footer_btn = new QWidget(main);
    footer_layout = new QGridLayout(footer_btn);
    footer_spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    footer_btn->setObjectName("footer_btn");

    confirm = new QPushButton(footer_btn);
    cancel = new QPushButton(footer_btn);
    del = new QPushButton(footer_btn);

    confirm->setObjectName("confirm");
    cancel->setObjectName("cancel");
    del->setObjectName("del");

    confirm->setText("全部选择");
    cancel->setText("取消选择");
    del->setText("删除选中项");

    confirm->setFixedSize(header_btn_width, header_btn_height);
    cancel->setFixedSize(header_btn_width, header_btn_height);
    del->setFixedSize(header_btn_width, header_btn_height);

    confirm->setCursor(Qt::PointingHandCursor);
    cancel->setCursor(Qt::PointingHandCursor);
    del->setCursor(Qt::PointingHandCursor);

    footer_layout->addWidget(confirm, 0, 0, 1, 1);
    footer_layout->addWidget(cancel, 0, 1, 1, 1);
    footer_layout->addWidget(del, 0, 2, 1, 1);
    footer_layout->addItem(footer_spacer, 0, 2, 1, 1);
    footer_btn->setLayout(footer_layout);

    //全部选择
    connect(confirm, &QPushButton::clicked, this, &Show_Home::confirm_click);
    //取消选择
    connect(cancel, &QPushButton::clicked, this, &Show_Home::cancel_click);
    //删除选中项
    connect(del, &QPushButton::clicked, this, &Show_Home::del_click);

    qss.append("QTableView{border:none;color:gray;padding-left:5px}"
        "QTableView QHeaderView::section{background:white;border:none;color:black;border-bottom:1px solid gray;min-height:50px;}"
        "QTableView::item{border-bottom:1px solid #EEF1F7;}"
        "QTableView::item::selected{background:#f1f1fd;color:black;border-bottom:1px solid #717171;height:50px}");
    qss.append("QPushButton#confirm,QPushButton#del{outline:none;background:#7969e6;color:white;border-radius:16px;font-size:14px;}"
        "QPushButton#cancel{outline:none;background:gray;color:white;border-radius:16px;font-size:14px;}"
        "QPushButton#confirm:hover,QPushButton#del:hover{background:#9b8fec;}"
        "QPushButton#confirm:pressed,QPushButton#del:pressed{background:#7968e8}"
        "QPushButton#cancel:hover{background:#c7c7c7;color:black;}"
        "QPushButton#cancel:pressed{background:gray}");
    qss.append("#check::indicator{width:20px;height:20px;padding-left:35px}"
        "#check::indicator:unchecked{image:url(':/image/check_un.png')}"
        "#check::indicator:checked{image:url(':/image/check_check.png')}");
    qss.append("QScrollBar{background-color:#d1cdef;border:none;border-radius:3px;width:7px}"
        "QScrollBar::handle{background:#7969e6;border:2px solid transparent;border-radius:3px}"
        "QScrollBar::sub-line{background:transparent}"
        "QScrollBar::add-line{background:transparent}");
    //槽
    connect(addBtn,&QPushButton::clicked,this,&Show_Home::add);
    //保险方案
    connect(bxBtn, &QPushButton::clicked, this, [=]() {
        Show_Home_Insurance* insu = new Show_Home_Insurance();
        insu->setWindowModality(Qt::ApplicationModal);
        insu->show();
        });
    //添加投保人员窗口
    show_home_add = new Show_Home_Add();
    connect(show_home_add, SIGNAL(sendDataList(QString)), this, SLOT(sendData(QString)));
    //保险期限
    connect(qxBtn, &QPushButton::clicked, [=]() {
        Show_Home_Date* date = new Show_Home_Date();
        date->setWindowModality(Qt::ApplicationModal);
        date->show();
        });


    orderBtn->setText(QString("订单人数%1人").arg(QString::number(ddrs)));
    this->setStyleSheet(qss.join(""));
}

//初始化表格模型
void Show_Home::table_view_class()
{
    table_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);		//列行充满屏幕
//    table_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);		//列行充满屏幕
    table_view->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
    table_view->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Interactive);
    table_view->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Interactive);
    table_view->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Interactive);
}

//表格初始化
void Show_Home::table_view_query_exec()
{

    //渲染数据
    query_model->setQuery("select user,ident,birth_date,phone,gwze,site from show_admin order by id desc");


    for(int i=0;i<query_model->rowCount();i++)
    {
        for(int j=0;j<query_model->columnCount();j++)
        {
            QCheckBox *check = new QCheckBox();
            check->setObjectName("check");
            table_view->setIndexWidget(model->index(i,0),check);

            QModelIndex index = query_model->index(i,j);
            QStandardItem *item = new QStandardItem(query_model->data(index).toString());
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            table_view->setRowHeight(i,50); //设置每行的高度
            model->setItem(i,j+1,item);

            QModelIndex modelIndex = query_model->index(i,1);
            map.insert(modelIndex.data().toString(),check);
            connect(check,&QCheckBox::stateChanged,this,&Show_Home::change_check);
        }
        ddrs++;
    }
    table_view->show();
}

//全选
void Show_Home::confirm_click()
{
    QList<QCheckBox *> check = table_view->findChildren<QCheckBox *>();
    foreach(QCheckBox *c,check)
    {
        c->setChecked(true);
    }
}

//取消选择
void Show_Home::cancel_click()
{
    QList<QCheckBox *> check = table_view->findChildren<QCheckBox *>();
    foreach(QCheckBox *c,check)
    {
        c->setChecked(false);
    }
}

//筛选数据
void Show_Home::change_check()
{
    QCheckBox* check = qobject_cast<QCheckBox*>(sender());
    for(auto it = map.begin();it!=map.end();it++)
    {
        if(check == it.value())
        {
            if(it.value()->isChecked() == true)
            {
                list_data << it.key();
            }else
            {
                list_data.removeAll(it.key());
            }
        }
    }
    qDebug() << list_data << "12223";
}

//删除选中项
void Show_Home::del_click()
{
    if(list_data.isEmpty())
    {
        QMessageBox::information(NULL,"删除失败！","您未选择数据、请选择数据在进行删除",QMessageBox::Yes);
    }else
    {
        bool delete_find;
        for(int i=0;i<list_data.size();i++)
        {
            QString val = list_data.at(i);
            QString sqlFind = QString("delete from show_admin where ident='%1'").arg(val);
            delete_find = query.exec(sqlFind);
        }
        if(delete_find)
        {
            QMessageBox::information(NULL,"操作成功","删除成功",QMessageBox::Yes);
            ddrs = 0;
            list_data.clear();
            table_view_query_exec();
            table_view_class();
            orderBtn->setText(QString("订单人数%1人").arg(QString::number(ddrs)));
        }
    }
}

//我要投保、传值
void Show_Home::sendData(QString val)
{
    if(val == "成功")
    {
        ddrs = 0;
        table_view_query_exec();
        table_view_class();
        orderBtn->setText(QString("订单人数%1人").arg(QString::number(ddrs)));
    }
}

void Show_Home::getSize(int w, int h)
{
    width = w;
    height = h;
    main->setFixedSize(w, h);
    widget_header->setFixedSize(w - header_height, header_height);
    widget_header->move((width /2) - (widget_header->width() /2) ,10);

    table_widget->setFixedSize(main->width(), main->height() - widget_header->height() - header_height);
    table_widget->move(0, widget_header->height() + icon_height);
//    table->setFixedSize(table_widget->width(), table_widget->height());
    table_view->setFixedSize(table_widget->width(), table_widget->height());

    footer_btn->setFixedSize(w, h - widget_header->height() - table_widget->height() - icon_height);
    footer_btn->move(0, h - footer_btn->height());
}

//封装时间
QString Show_Home::dataTime()
{
    QDateTime data = QDateTime::currentDateTime();
    QString dataText = data.toString("yyyy/MM/dd");
    return dataText;
}

//添加投保
void Show_Home::add()
{
    show_home_add->setWindowModality(Qt::ApplicationModal);
    show_home_add->show();
}
