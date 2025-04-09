#define _CRT_SECURE_NO_WARNINGS
#define NAME_LEN 200
#define MAX_COURSES 10
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<iso646.h>
#include<ctype.h>
#include<errno.h>
typedef struct sco
{
    char *sco_name;
    float score;
    struct sco * next, * prev;
}Sco;
typedef struct student
{
    char name[NAME_LEN]; 
    long long id;
    struct sco *stu_score;
    struct student * next, * prev;
}Stu;
Stu *head = NULL;
Stu *tail = NULL;
typedef struct {
    char name[NAME_LEN];
    float total;
    int count;
} CourseStats;
void cin(char* arr,int *n)//安全输入非负整数
{
    int resulti;
    do{
    puts(arr);
    resulti = scanf("%d", n);
    while (getchar() != '\n');  
    }while (resulti != 1 or *n<0);
}
void cinl(char* arr,long long *n)//安全输入非负整数
{
    int resulti;
    do{
    puts(arr);
    resulti = scanf("%lld", n);
    while (getchar() != '\n');  
    }while (resulti != 1 or *n<0);
}
void cinf(char* arr,float *n)//安全输入非负浮点数
{
    int resultf;
    do{
    puts(arr);
    resultf = scanf("%f", n);
    while (getchar() != '\n');  
    }while (resultf != 1 or *n<0.0);
}
void cins(char* arr,char *str)//安全输入字符串
{
    int sresult = 0;
    do {
        puts(arr);
        if (fgets(str, NAME_LEN, stdin)) 
        {
            char* newline = strchr(str, '\n');
            if (newline) 
            {
                *newline = '\0';
                sresult = 1;
            } 
            else 
            {
                while (getchar() != '\n');
            }
        } 
        else 
        {
            while (getchar() != '\n'); 
        }
    } while (!sresult);
}
void Input(int num_stu,Stu *student ,int num_scores ,char subject[10][NAME_LEN]) 
{
    for (int i = 0; i < num_stu; i++) 
    {
        Stu *new_stu = (Stu *)malloc(sizeof(Stu));
        if (new_stu == NULL) 
        {
            printf("error:Memory allocation failed!\tbecause:new_stu == NULL\n");
            return;
        }
        printf("设置第%d位学生的信息----\n", i + 1);
        cins("输入姓名:",new_stu->name);
        cinl("输入学号:",&new_stu->id);
        new_stu->stu_score = NULL; 
        new_stu->next = NULL;
        new_stu->prev = NULL;
        if (head == NULL) 
        {
            head = new_stu;
            tail = new_stu;
        } 
        else 
        {
            tail->next = new_stu;
            new_stu->prev = tail;
            tail = new_stu;
        }
    for (int j = 0; j < num_scores; j++) 
    {
        Sco *new_score = (Sco *)malloc(sizeof(Sco));
        if (new_score == NULL)
         {
            printf("error:Memory allocation failed!\tbecause:new_score == NULL\n");
            return;
        }
        new_score->sco_name = (char *)malloc((strlen(subject[j]) + 1) * sizeof(char));
        strcpy(new_score->sco_name,subject[j]);
        printf("输入%s",subject[j]);
        cinf("成绩:",&new_score->score);
        new_score->next = NULL;
        new_score->prev = NULL;
        if (new_stu->stu_score == NULL) 
        {
            new_stu->stu_score = new_score;
        } 
        else 
        {
            Sco *current = new_stu->stu_score;
            while (current->next != NULL) 
            {
                current = current->next;
            }
            current->next = new_score;
            new_score->prev = current;
        }
    }
    }
}
void cout_all() 
{
    Stu *current_stu = head;
    while (current_stu != NULL) 
    {
        printf("姓名: %s\t学号: %lld\t", current_stu->name, current_stu->id);
        Sco *current_score = current_stu->stu_score;
        while (current_score != NULL) 
        {
            printf("课程: %s\t分数: %.2f\n", current_score->sco_name, current_score->score);
            current_score = current_score->next;
        }
        current_stu = current_stu->next;
    }
}
void average_stu() 
{
    Stu *current_stu = head;
    while (current_stu != NULL) 
    {
        float total = 0;
        int count = 0;
        Sco *current_score = current_stu->stu_score;
        while (current_score != NULL) 
        {
            total += current_score->score;
            count++;
            current_score = current_score->next;
        }
        float average = (count > 0) ? total / count : 0;
        printf("姓名: %s\t学号: %lld\t总成绩: %.2f\t平均分: %.2f\n", current_stu->name, current_stu->id, total, average);
        current_stu = current_stu->next;
    }
}
void average_course() 
{
    Stu *current_stu = head;
    if (head == NULL) 
    {
        printf("没有学生数据\n");
        return;
    }

    CourseStats courses[MAX_COURSES] = {0}; 
    int course_count = 0; 

    while (current_stu != NULL) 
    {
        Sco *current_score = current_stu->stu_score;
        while (current_score != NULL) 
        {
            bool found = false;
            for (int i = 0; i < course_count; i++) 
            {
                if (strcmp(courses[i].name, current_score->sco_name) == 0)
                {
                    courses[i].total += current_score->score;
                    courses[i].count++;
                    found = true;
                    break;
                }
            }
            if (!found) 
            {
                if (course_count >= MAX_COURSES) 
                {
                    printf("erroe警告:课程数量超过%d门,'%s' 未被统计\n", MAX_COURSES, current_score->sco_name);
                    break;
                }
                strncpy(courses[course_count].name, current_score->sco_name, NAME_LEN-1);
                courses[course_count].name[NAME_LEN-1] = '\0';  
                courses[course_count].total = current_score->score;
                courses[course_count].count = 1;
                course_count++;
            }
            
            current_score = current_score->next;
        }
        current_stu = current_stu->next;
    }
    printf("%-20s %-10s %-10s\n", "课程名", "总分", "平均分");
    for (int i = 0; i < course_count; i++) 
    {
        printf("%-20s %-10.2f %-10.2f\n", courses[i].name, courses[i].total, (float)(courses[i].total / courses[i].count));
    }
}
void swap_nodes(Stu *a, Stu *b) 
{
    // 交换节点数据（保留链表结构）
    char temp_name[NAME_LEN];
    long long temp_id;
    Sco *temp_scores;
            
    // 交换姓名
    strcpy(temp_name, a->name);
    strcpy(a->name, b->name);
    strcpy(b->name, temp_name);
            
    // 交换学号
    temp_id = a->id;
    a->id = b->id;
    b->id = temp_id;
            
    // 交换成绩指针
    temp_scores = a->stu_score;
    a->stu_score = b->stu_score;
    b->stu_score = temp_scores;
}      
float calculate_total(Stu *stu) 
{
    float total = 0.0f;
    Sco *current = stu->stu_score;
    while(current) 
    {
        total += current->score;
        current = current->next;
    }
    return total;
}     
void sort_students(int (*compare)(const Stu*, const Stu*), bool ascending) // 冒泡排序实现
{
    if (!head || !head->next) return;
        
    int swapped;
    Stu *ptr1;
    Stu *lptr = NULL;
        
    do {
        swapped = 0;
        ptr1 = head;
        
        while (ptr1->next != lptr) 
        {
            int compare_result = compare(ptr1, ptr1->next);
            if ((ascending && compare_result > 0) || (!ascending && compare_result < 0)) 
            {
                swap_nodes(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
int compare_total(const Stu *a, const Stu *b) // 比较函数
{
    float total_a = calculate_total((Stu*)a);
    float total_b = calculate_total((Stu*)b);
    if (total_a > total_b) return 1;
    if (total_a < total_b) return -1;
    return 0;
}      
int compare_id(const Stu *a, const Stu *b) 
{
    if (a->id > b->id) return 1;
    if (a->id < b->id) return -1;
    return 0;
} 
int compare_name(const Stu *a, const Stu *b) 
{
    return strcasecmp(a->name, b->name);
}
void statistic_analysis() // 统计分析
{
    int categories[5] = {0}; // 优秀、良好、中等、及格、不及格
    int total_scores = 0;
        
    Stu *current = head;
    while(current) 
    {
        Sco *score = current->stu_score;
        while(score) 
        {
            total_scores++;
            if (score->score >= 90)       categories[0]++;
            else if (score->score >= 80)  categories[1]++;
            else if (score->score >= 70)  categories[2]++;
            else if (score->score >= 60)  categories[3]++;
            else                          categories[4]++;
            score = score->next;
        }
        current = current->next;
    }
        
    printf("\n成绩分布统计:\n");
    const char *levels[] = {"优秀(90-100)", "良好(80-89)", "中等(70-79)", "及格(60-69)", "不及格(0-59)"};
    for (int i = 0; i < 5; i++) 
    {
        float percentage = (total_scores > 0) ? (categories[i] * 100.0f / total_scores) : 0;
        printf("%-12s: %d人(%.2f%%)\n", levels[i], categories[i], percentage);
    }
}
void write_to_file() 
{
    FILE *file = fopen("students.txt", "wb");
    if (!file) 
    {
        perror("无法打开文件");
        return;
    }
        
    Stu *current = head;
    while(current) 
    {
        // 写入学生基本信息
        fwrite(current, sizeof(Stu), 1, file);
                
        // 写入成绩数量
        int score_count = 0;
        Sco *score = current->stu_score;
        while(score) { score_count++; score = score->next; }
        fwrite(&score_count, sizeof(int), 1, file);
        
        // 写入成绩数据
        score = current->stu_score;
        while(score) 
        {
            int name_len = strlen(score->sco_name) + 1;
            fwrite(&name_len, sizeof(int), 1, file);
            fwrite(score->sco_name, sizeof(char), name_len, file);
            fwrite(&score->score, sizeof(float), 1, file);
            score = score->next;
        }
        current = current->next;
    }
    fclose(file);
    printf("数据已保存\n");
}       
void read_from_file() 
{
    FILE *file = fopen("students.txt", "rb");
    if (!file) 
    {
        perror("无法打开文件");
        return;
    }
    // 清空现有数据
    while(head) 
    {
        Stu *temp = head;
        head = head->next;
        free(temp);
    }
        
    Stu *prev = NULL;
    while(1) 
    {
        Stu stu;
        if (fread(&stu, sizeof(Stu), 1, file) != 1) 
        break;
        Stu *new_stu = (Stu*)malloc(sizeof(Stu));
        *new_stu = stu;
        new_stu->next = NULL;
        new_stu->prev = prev;
     
        // 读取成绩
        int score_count;
        fread(&score_count, sizeof(int), 1, file);
                
        Sco *prev_score = NULL;
        for (int i = 0; i < score_count; i++) 
        {
            int name_len;
            fread(&name_len, sizeof(int), 1, file);
                    
            char *name = (char*)malloc(name_len);
            fread(name, sizeof(char), name_len, file);
                    
            float score;
            fread(&score, sizeof(float), 1, file);
        
            Sco *new_score = (Sco*)malloc(sizeof(Sco));
            new_score->sco_name = name;
            new_score->score = score;
            new_score->prev = prev_score;
            new_score->next = NULL;
        
            if (prev_score) prev_score->next = new_score;
            else new_stu->stu_score = new_score;
            prev_score = new_score;
        }
        
        if (prev) prev->next = new_stu;
        else head = new_stu;
        prev = new_stu;
    }
    fclose(file);
    printf("数据已加载\n");
}
Stu* search(long long id) 
{
    Stu *current_stu = head;
    while (current_stu != NULL)
     {
        if (current_stu->id == id) 
        {
            return current_stu;
        }
        current_stu = current_stu->next;
    }
    return NULL;
}
Stu* searchname(char name[]) 
{
    Stu *current_stu = head;
    while (current_stu != NULL) 
    {
        if (strcmp(current_stu->name, name) == 0)
         {
            return current_stu;
        }
        current_stu = current_stu->next;
    }
    return NULL;
}
void deletestu(long long id) 
{
    Stu *student_d = search(id);
    if (student_d != NULL)
     {
        if (student_d->prev != NULL)
        {
            student_d->prev->next = student_d->next;
        } 
        else 
        {
            head = student_d->next;
        }
        if (student_d->next != NULL) 
        {
            student_d->next->prev = student_d->prev;
        } 
        else 
        {
            tail = student_d->prev;
        }
        Sco *Sco_goingdel = student_d->stu_score;
        while (Sco_goingdel != NULL) 
        {
            Sco *temp_score = Sco_goingdel;
            Sco_goingdel = Sco_goingdel->next;
            free(temp_score->sco_name);
            free(temp_score);
        }

        free(student_d);
        printf("成功。\n");
    } else 
    {
        printf("未查找到学生。\n");
    }
}
void modifystu(long long id) 
{
    Stu *student_m = search(id);
    if (student_m != NULL) 
    {
        cins("输入新的名字:", student_m->name);
        cinl("输入新的学号:", &student_m->id);
    } 
    else 
    {
        printf("暂无此人。\n");
    }
}
void addscore(long long id, char subject_name[], float score)
 {
    Stu *student_m = search(id);
    if (student_m != NULL) 
    {
        Sco *new_score = (Sco *)malloc(sizeof(Sco));
        if (new_score == NULL) 
        {
            printf("Error: Memory allocation failed!\n");
            return;
        }
        new_score->sco_name = (char *)malloc((strlen(subject_name) + 1) * sizeof(char));
        strcpy(new_score->sco_name, subject_name);
        new_score->score = score;
        new_score->next = NULL;
        new_score->prev = NULL;

        if (student_m->stu_score == NULL) 
        {
            student_m->stu_score = new_score;
        } 
        else 
        {
            Sco *current = student_m->stu_score;
            while (current->next != NULL) 
            {
                current = current->next;
            }
            current->next = new_score;
            new_score->prev = current;
        }

        printf("已更改。\n");
    } 
    else 
    {
        printf("查无此人。\n");
    }
}
void SXlb(Stu *student)
{
    int answer;
    cin("查看上一个学生/下一个学生/无需查看::分别输入:1/2/0或其他数字",&answer);
    switch(answer)
    {
        case 0:
        return;
        case 1:
        {
            if(student->prev == NULL)
            return;
            printf("姓名 %s, 学号: %lld\n", student->prev->name, student->prev->id);
            Sco *current_score = student->prev->stu_score;
            while (current_score != NULL) 
            {
               printf("课程: %s\t分数: %.2f\n", current_score->sco_name, current_score->score);
               current_score = current_score->next;
            }
            SXlb(student->prev);
            break;
        }
        case 2:
        {
            if(student->next == NULL)
            return;
            printf("姓名 %s, 学号: %lld\n", student->next->name, student->next->id);
            Sco *current_score = student->next->stu_score;
            while (current_score != NULL) 
            {
               printf("课程: %s\t分数: %.2f\n", current_score->sco_name, current_score->score);
               current_score = current_score->next;
            }
            SXlb(student->next);
            break;
        }
        default:
        return;
    }
}
static int Menu()
{
    int choice , result;
    char *ch = "1.输入学生信息Input record\n"
    "2.按课程计算总分、平均分Calculate total and average score of every course\n"
    "3.按学生计算总分、平均分Calculate total and average score of every student\n"
    "4.按分排序(正序)Sort in descending order by total score of every student\n"
    "5.按分排序(倒序)Sort in ascending order by total score of every student\n"
    "6.按号排序Sort in ascending order by number\n"
    "7.按名排序Sort in dictionary order by name\n"
    "8.按号查找Search by number\n"
    "9.按名查找Search by name\n"
    "10.分析成绩占比Statistic analysis\n"
    "11.列表统计List record\n"
    "12.保存到本地Write to a file\n"
    "13.读取本地记录Read from a file\n"
    "14.*修改学生信息Modify information \n"
    "15.*删除学生信息Delete student information \n"
    "16.*添加已存在学生的新科目成绩Adding new subject grades for existing students\n"
    //"17.*整理课程顺序Order class in classname\n"
    "0.退出Exit\n"
    "_____________________________________________________________________________\n";
    puts(ch);
    do{
        cin("输入选项数字-Please enter your choice number :",&choice);
    }while(choice>16);
    return choice;
}
int main()
{
    int xuanxiangka = 0;
    char subject[10][NAME_LEN];
    int num_stu, num_class;
    for(;;)
    {
        switch(xuanxiangka = Menu())
        {
            case 1://录入每个学生的学号、姓名和各科考试成绩；
            {
                cin( "请输入要输入的学生数量:", &num_stu);
                cin("请输入科目总数:", &num_class);
                for (int i = 0; i < num_class; i++)
                {
                    cins("输入课程名:", subject[i]);
                }
                Input(num_stu, head, num_class, subject);
                break;
            }
            case 2://计算每门课程的总分和平均分；
            {
                average_course();
                break;
            }
            case 3://计算每个学生的总分和平均分；
            {
                average_stu();
                break;
            }
            case 4://按每个学生的总分由高到低排出名次表；
            {
                sort_students(compare_total, false);
                cout_all();
                break;
            }
            case 5://按每个学生的总分由低到高排出名次表；
            {
                sort_students(compare_total, true);
                cout_all();
                break;
            }
            case 6://按学号由小到大排出成绩表；
            {
                sort_students(compare_id, true);
                cout_all();
                break;
            }
            case 7://按姓名的字典顺序排出成绩表；
            {
                sort_students(compare_name, true);
                cout_all();
                break;
            }
            case 8://按学号查询学生排名及其各科考试成绩；
            {
                long long id;
                    cinl("输入要查找的学号:", &id);
                    Stu *student = search(id);
                    if (student != NULL) 
                    {
                        printf("姓名 %s, 学号: %lld\n", student->name, student->id);
                        Sco *current_score = student->stu_score;
                     while (current_score != NULL) 
                     {
                        printf("课程: %s\t分数: %.2f\n", current_score->sco_name, current_score->score);
                        current_score = current_score->next;
                     }
                        SXlb(student);
                    } 
                    else 
                    {
                        printf("暂无此人。\n");
                    }

                break;
            }
            case 9://按姓名查询学生排名及其各科考试成绩；
            {
                {
                    char name[NAME_LEN];
                    cins("输入要查找的姓名:", name);
                    Stu *student = searchname(name);
                    if (student != NULL)
                    {
                        printf("姓名 %s, 学号: %lld\n", student->name, student->id);
                        Sco *current_score = student->stu_score;
                        while (current_score != NULL) 
                        {
                           printf("课程: %s\t分数: %.2f\n", current_score->sco_name, current_score->score);
                           current_score = current_score->next;
                        }
                        SXlb(student);
                    } 
                    else 
                    {
                        printf("暂无此人。\n");
                    }
                }
                break;
            }
            case 10://按优秀（90-100）、良好（80-89）、中等（70-79）、及格（60-69）、不及格(0-59）5 个类别，统计每个类别的人数以及所占的百分比；
            {
                statistic_analysis();
                break;
            }
            case 11://输出每个学生的学号、姓名、各科考试成绩、总分、平均分，以及每门课程的总分和平均分。
            {
                cout_all();
                break;
            }
            case 12://将每个学生的记录信息写入文件；
            {
                write_to_file();
                break;
            }
            case 13://从文件中读出每个学生的记录信息并显示。 
            {
                read_from_file();
                break;
            }
            case 14://修改学生信息
            {
                long long id;
                cinl("输入要查找的学号:", &id);
                modifystu(id);
                break;
            }
            case 15://删除学生信息
            {   
                long long id;
                cinl("输入要查找的学号:", &id);
                deletestu(id);
                break;
            }
            case 16://添加已存在学生的新科目成绩 
            {
                long long id;
                char subject_name[NAME_LEN];
                float score;
                cinl("输入要查找的学号:", &id);
                cins("输入学科名", subject_name);
                cinf("输入成绩:", &score);
                addscore(id, subject_name, score);
                break;
            }
            // case 17://整理课程顺序
            // {
            //     break;
            // }
            case 0://退出
            {
                return 0;
            }


        }
    }
    return 0;
}