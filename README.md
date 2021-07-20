# Goolge

## 简介：在设计网随便找个登录效果图、就尝试着做了下来，登录过后就又随意找个看着非常舒服的管理界面尝试做了下来。

#### 1.登录：<Home.cpp、Home.h、Home.ui>  
![](https://github.com/ZoeyMoney/Qt_Google_Admin/blob/main/effect/Home.png)

#### 2.注册：<registered.cpp、registered.h、registered.ui>  
![](https://github.com/ZoeyMoney/Qt_Google_Admin/blob/main/effect/registered.png)

#### 3.管理界面：<AdminHome.cpp、AdminHome.h、AdminHome.ui>
![](https://github.com/ZoeyMoney/Qt_Google_Admin/blob/main/effect/AdminHome.png)


### 里面有个主页内容 main_show的类名，用来装嵌套的窗口、导航栏发来什么信号用来显示什么窗口，默认显示第一个窗口为Show_Home(我要投保)，  QListWidget与QStackedWidget的结合用来切换窗口   

#### 4.默认显示第一个窗口（我要投保）：<Show_Home.cpp、Show_Home.h、Show_Home.ui>  
![](https://github.com/ZoeyMoney/Qt_Google_Admin/blob/main/effect/AdminHome.png)


#### 4.1 我要投保窗口:<Show_Home_add.cpp、Show_Home_add.h、Show_Home_add.ui>  
![](https://github.com/ZoeyMoney/Qt_Google_Admin/blob/main/effect/ShowHomeadd.png)

#### 4.2 保险方案窗口：<Show_Home_Insurance.cpp、Show_Home_Insurance.h、Show_Home_Insurance.ui>  
![](https://github.com/ZoeyMoney/Qt_Google_Admin/blob/main/effect/ShowHomeInsurance.png)

#### 4.3 使用期限窗口：<Show_Home_date.cpp、Show_Home_date.h、Show_Home.dae.ui>  
![](https://github.com/ZoeyMoney/Qt_Google_Admin/blob/main/effect/ShowHomedate.png)

#### 5.我要查询：<Show_Search.cpp、Show_Search.h、Show_Search.ui>  
![](https://github.com/ZoeyMoney/Qt_Google_Admin/blob/main/effect/ShowSearch.png)

# 缺点 
#### 1. 管理界面<adminHome.cpp>：  
	- 菜单栏延迟卡顿、houver 鼠标触发背景变色 延迟显示  
	- button按钮无图片是个遗憾、添加图片后无法居中(文字在左、图片在右)居中效果 
![](https://github.com/ZoeyMoney/Qt_Google_Admin/blob/main/effect/btnIcon.png)
