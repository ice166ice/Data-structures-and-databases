# Data-structures-and-databases
数据结构与数据库用C语言完成的几个实验

实验1 线性表的应用：稀疏一元多项式运算器
实验代码使用方式：
       在C++的环境下，直接编译运行该代码就会弹出程序提供的功能菜单，按照菜单指示输入相应的指令即可完成题目的要求。
数据存储格式：
       本程序建立了一个容量为10的头指针数组polyns[]，该数组存放多项式的头指针，多项式用带头结点的单链表表示。
数据输入格式：
       菜单提供的功能只允许输入数字，不同的数字代表不同的功能，如0代表退出系统。
       要输入多项式的话，输入一个数字代表一项的系数（可以是浮点数），然后enter确认，再输入一个数字，代表指数（必须是整型数），再enter确认。重复上述操作，直到输入完成所有的项，即创建多项式完成。

