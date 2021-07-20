#include "show_search.h"
#include "ui_show_search.h"
#define	header_btn_width 150
#define header_btn_height 32

Show_Search::Show_Search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Show_Search)
{
    ui->setupUi(this);
}

Show_Search::~Show_Search()
{
    delete ui;
}
void Show_Search::getResize(int w, int h)
{
    width = w;
    height = h;

    search_init();
}

//初始化内容
void Show_Search::search_init()
{
    main = new QWidget(this);
    main->setObjectName("main");
    main->setFixedSize(width, height);

    //查询部分
    header = new QWidget(main);
    header->setObjectName("header");
    header->setFixedSize(width, 100);

    header_layout = new QGridLayout(header);

    space = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);

    combobox = new QComboBox();
    combobox->setObjectName("combobox");
    combobox->addItem("请选择");
    combobox->setFixedSize(header_btn_width,header_btn_height);

    search = new QLineEdit();
    search->setObjectName("search");
    search->setPlaceholderText("请输入姓名进行查询");
    search->setFixedHeight(header_btn_height);

    submit = new QPushButton();
    submit->setObjectName("submit");
    submit->setText("搜索");
    submit->setCursor(Qt::PointingHandCursor);
    submit->setFixedSize(header_btn_width, header_btn_height);

    header_layout->setHorizontalSpacing(0);
    header_layout->addItem(space, 0, 0);
    header_layout->addWidget(combobox, 0, 1);
    header_layout->addWidget(search, 0, 2);
    header_layout->addWidget(submit, 0, 3);
    header_layout->addItem(space, 0, 4);
    header->setLayout(header_layout);

    connect(submit, &QPushButton::clicked, this, &Show_Search::search_click);

    //表格
    table = new QTableView(main);
    table->setObjectName("table");
    itemModel = new QStandardItemModel();
    tablemodel = new QSqlTableModel;
    QStringList listText;
    listText << "姓名" << "身份证号" << "出生日期" << "联系电话" << "岗位职责" << "通讯地址";
    //设置头部、列数
    itemModel->setColumnCount(listText.count());
    table->setModel(itemModel);
    //设置属性
    table->verticalHeader()->setHidden(true);		//去掉边侧id
//    itemModel->setHorizontalHeaderLabels(listText);
    for(int i=0;i<listText.count();i++)
    {
        itemModel->setHeaderData(i,Qt::Horizontal,listText.at(i));
    }
    table->setModel(itemModel);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);		//选中整行
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);		//禁止修改
    table->setFocusPolicy(Qt::NoFocus);
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    table->setShowGrid(false);		//不显示格子线
    table->horizontalHeader()->setHighlightSections(false);	//表头不能点击
    table->setAlternatingRowColors(true);


    table->setGeometry(header->x(), header->height(), header->width(), main->height() - header->height());
    table_data_init();
    table_title_init();


    qss.append("QTableView{border:none;color:gray;padding-left:5px}"
        "QTableView QHeaderView::section{background:white;border:none;color:black;border-bottom:1px solid gray;min-height:50px;}"
        "QTableView::item{border-bottom:1px solid #EEF1F7;}"
        "QTableView::item::selected{background:#f1f1fd;color:black;border-bottom:1px solid #717171;height:50px}");
    qss.append("QScrollBar{background-color:#d1cdef;border:none;border-radius:3px;width:7px}"
        "QScrollBar::handle{background:#7969e6;border:2px solid transparent;border-radius:3px}"
        "QScrollBar::sub-line{background:transparent}"
        "QScrollBar::add-line{background:transparent}");
    qss.append("#submit{outline:none;background:#7969e6;color:white;font-size:14px;border-top-right-radius:16px;border-bottom-right-radius:16px;}");
    qss.append("#search{border:1px solid black}#search:focus{border:1px solid #0043ff}");
    qss.append("#combobox{}"
        "#combobox::down-arrow{}"
        "#combobox::drop-down{}");
    qss.append("#main{background:white;}");
    this->setStyleSheet(qss.join(""));
    this->setMouseTracking(true);
}

//表格模型
void Show_Search::table_title_init()
{
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);		//列行充满屏幕
//    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);		//列行充满屏幕
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Interactive);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Interactive);
    table->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Interactive);
}

//表格数据初始化
void Show_Search::table_data_init()
{

//    int index=0;
//    if(query.exec("select user,ident,birth_date,phone,gwze,site from show_admin order by id desc"))
//    {
//        while (query.next()) {
//            for(int col=0;col<6;col++)
//            {
//                table->setRowCount(index+1);    //设置表格行数
//                table->setItem(index,col,new QTableWidgetItem(query.value(col).toString()));
//                table->item(index,col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

//            }
//            table->setRowHeight(index,50);
//        index++;
//        }
//    }
    tablemodel->setTable("show_admin");
    tablemodel->select();
    table->setModel(tablemodel);
}

//清空表
void Show_Search::table_remove()
{
    //删除所有行
//    for(int i=table->rowCount() - 1;i>=0;i--)
//    {
//        table->removeRow(i);
//    }
}

//搜索事件
void Show_Search::search_click()
{
    QString name = search->text();
//    QString str = QString("select user,ident,birth_date,phone,gwze,site from show_admin where user='%1' or ident = '%2' or birth_date='%3'"
//                          "or phone='%4' or gwze='%5' or site='%6'").arg(name).arg(name).arg(name).arg(name).arg(name).arg(name);
    QString linkSearch = QString("select user,ident,birth_date,phone,gwze,site from show_admin where user like '%1' order by id desc").arg(name);
    qDebug() << linkSearch;
    //行
    int index=0;
    //判断是否为空、如果为空则重新调用数据
    if(name.isEmpty())
    {
        qDebug()<<"44444444444444";
        table_remove();
        table_data_init();
    }

    if(query.exec(linkSearch))
    {
        if(!query.next())
        {
            QMessageBox::information(NULL,"查询失败","未查询到数据",QMessageBox::Yes);
            return;
        }

        QString names = QString("user = '%1'").arg(name);

//        rec = query.record();



//            qDebug() << query.size();
//            qDebug() << rec.count();
//            for(int i=0;i<query.size();i++)
//            {
//                for(int j=0;j<rec.count();j++)
//                {
//                    qDebug() << i << j;

//                    table->setRowCount(i+1);    //设置表格行数
//                    table->setItem(i,j,new QTableWidgetItem(query.value(j).toString()));
//                    table->item(i,j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

//                    table->setRowHeight(i,50);
//                }
//            }

    }

//        qDebug() << query.size();
//        while (query.next()) {
//            qDebug() << linkSearch + ":::11111";
//            for(int col=0;col<6;col++)
//            {
//                table->setRowCount(index+1);    //设置表格行数
//                table->setItem(index,col,new QTableWidgetItem(query.value(col).toString()));
//                table->item(index,col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);



//                qDebug() << query.value("user").toString()
//                         << query.value("ident").toString()
//                         << query.value("birth_date").toString()
//                         << query.value("phone").toString()
//                         << query.value("gwze").toString()
//                         << query.value("site").toString();
//            }
//            table->setRowHeight(index,50);
//            index++;
//        }
//    }
//    for(int i=table->rowCount() - 1;i>=0;i--)
//    {
//        table->removeRow(i);
//    }
//    int index=0;
//    if(query.exec(str))
//    {
//        while (query.next()) {
//            for(int col=0;col<6;col++)
//            {
//                table->setRowCount(index+1);    //设置表格行数
//                table->setItem(index,col,new QTableWidgetItem(query.value(col).toString()));
//                table->item(index,col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

//            }
//            table->setRowHeight(index,50);
//            qDebug() << query.value("user").toString()
//                     << query.value("ident").toString()
//                     << query.value("birth_date").toString()
//                     << query.value("phone").toString()
//                     << query.value("gwze").toString()
//            << query.value("site").toString();
//            index++;
//        }
//    }
}

// 鼠标相对于窗体的位置 event->globalPos() - this->pos()
void Show_Search::mousePressEvent(QMouseEvent* event)
{

}

// 若鼠标左键被按下，移动窗体位置
void Show_Search::mouseMoveEvent(QMouseEvent* event)
{

}

// 设置鼠标未被按下
void Show_Search::mouseReleaseEvent(QMouseEvent* event)
{

}
