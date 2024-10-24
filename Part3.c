#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
//函数声明
void extract (char *expression,char*FirBig,char *SecBig,char *operator);//提取操作数和符

//函数定义
void extract (char *expression,char*FirBig,char *SecBig,char *operator){
     char flag1='\0',flag2='\0';
     int len=strlen(expression),i=0,j=0,mark;//len表示长度，i控制读取字符次数,j控制读取第一个操作数
     while(!isdigit(expression[i])){
      if (expression[i]=='-')
        {
            flag1='-';
            i++;
            continue;
        }
        i++;
     }//判断第一个数是否为负数
        
     for(;i<len;i++){
        if (!isdigit(expression[i]))
        {
            mark=i;
            break;
        }
     }//找到第一个操作数结束的位置
    for (i=0;i<mark;i++){
        FirBig[j]=expression[i];
        j++;
       }
       i=mark;//用mark1将i还原
      for(;i<len;i++){
        if (!isspace(expression[i]))
        {
            *operator=expression[i];
            break;
        }
      }
    while(!isdigit(expression[i])){
      if (expression[i]=='-')
        {
            flag2='-';
            i++;
            continue;
        }
        i++;
     }//找到第二个大数
    j = 0;
    for (; i < len; i++) {
        if (!isdigit(expression[i])) {
            break;
        }
        SecBig[j] = expression[i];
        j++;
    }//将第二个大数赋值

       printf("第一个操作数：%c%s\n",flag1,FirBig);
       
       printf("第二个操作数：%c%s\n",flag2,SecBig);
       
       printf("操作符：%c\n",*operator);

}

//主程序
int main(){
    char expression[260]={0},Big1[130],Big2[130],operator;
    printf("请输入表达式:");
    scanf("%s",expression);
    extract(expression,Big1,Big2,&operator);
    return 0;
}