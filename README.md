# TGU
基于双向链表的学生管理系统
一、设计要求
某班有最多不超过 30 人（具体人数由键盘输入）参加期末考试，考试科目 
最多不超过 6 门（具体门数有键盘输入），学生成绩管理系统是一个非常实用的 
程序，如果能够把用户输入的数据存盘，下次运行时读出，就更有用了。增加文 
件读写的功能，编程实现如下学生成绩管理： 
（1） 录入每个学生的学号、姓名和各科考试成绩； 
（2） 计算每门课程的总分和平均分； 
（3） 计算每个学生的总分和平均分； 
（4） 按每个学生的总分由高到低排出名次表； 
（5） 按每个学生的总分由低到高排出名次表； 
（6） 按学号由小到大排出成绩表； 
（7） 按姓名的字典顺序排出成绩表； 
（8） 按学号查询学生排名及其各科考试成绩； 
（9） 按姓名查询学生排名及其各科考试成绩； 
（10）按优秀（90-100）、良好（80-89）、中等（70-79）、及格（60-69）、不及格 
（0-59）5 个类别，统计每个类别的人数以及所占的百分比； 
（11）输出每个学生的学号、姓名、各科考试成绩、总分、平均分，以及每门课 
程的总分和平均分。 
（12）将每个学生的记录信息写入文件； 
（13）从文件中读出每个学生的记录信息并显示；
***（14）.修改学生信息；
***（15）.删除学生信息；
***（16）.添加已存在学生的新科目成绩。
二、程序运行结果
各模块调用数字目录：
1.输入学生信息Input record
2.按课程计算总分、平均分Calculate total and average score of every course
3.按学生计算总分、平均分Calculate total and average score of every student
4.按分排序(正序)Sort in descending order by total score of every student
5.按分排序(倒序)Sort in ascending order by total score of every student
6.按号排序Sort in ascending order by number
7.按名排序Sort in dictionary order by name
8.按号查找Search by number
9.按名查找Search by name
10.分析成绩占比Statistic analysis
11.列表统计List record
12.保存到本地Write to a file
13.读取本地记录Read from a file
14.*修改学生信息Modify information 
15.*删除学生信息Delete student information 
16.*添加已存在学生的新科目成绩Adding new subject grades for existing students
0.退出Exit





使用双向链表进行设计，目的是实现便于在查找到已知项之后可以再次自由查找上一个，下一个的信息的功能。
在代码中对于输入通过封装近似于重载的函数实现安全输入。
增加了功能如删除、更改学生信息的功能。
