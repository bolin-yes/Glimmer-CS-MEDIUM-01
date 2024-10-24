//由于这是本人第一次写如此长的程序，有些命名可能不太规范，请见谅
/*我先介绍一下我的思路
总体思路是在运算时都先将大数转化为正数，然后再进行计算，然后分情况确定最后的符号
加法：分四种情况，不过这个比较简单不过多说明
减法：例如a-b可以看作a+（-b）转化为加法来做
乘法：这个就稍显复杂了但是通过小学学过的竖式计算可以发现从c[i+j]=a[i]*b[j]
除法：这个我的思路源于减法，第一个大数能减第二个大数多少次就是这个除法的结果

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define debug 0//进入debug模式，但是程序调试好了之后防止看着太乱就把#if #endif全部删了
#define max 130
#include <ctype.h>

//函数声明
void extract (char *expression,char*FirBig,char *SecBig,char *operator);//提取操作数和符
void transpose1(char d[130],char s[130]);//对输入的正大数进行转置
void transpose2(char d[130],char s[130]);//对输入的负大数进行转置
char add(char *FirBig, char *SecBig,char*result);//加法
char minus(char*FirBig,char*SecBig,char*result);//减法
void mutiply(char*FirBig,char*SecBig,char*result);//乘法
void divide(char*FirBig,char*SecBig,char*result);//除法
int lenth1(char arr[]);//测量数组内存大小为260的大数长度
int lenth2(char arr[]);//测量数组内存大小为130的大数长度
int compare( char* FirBig,  char* SecBig);//比较大数大小
void jian(char*a, char*b,char*c);//一个类似于减法的专用于除法的函数

//主程序
int main(){
    char expression[260]={0},FirBig[130]={0},SecBig[130]={0},operator,result[260]={0};
    printf("请输入表达式:");
   scanf("%[^\n]", expression);
    extract(expression,FirBig,SecBig,&operator);
   switch (operator)
   {
   case '+':
            printf("result:%c",add(FirBig,SecBig,result));
            for(int i=lenth1(result)-1;i>-1;i--){
              printf("%d",result[i]);
            }
            break;
   case'-':
            printf("result:%c",minus(FirBig,SecBig,result));
            for(int i=lenth1(result)-1;i>-1;i--){
              printf("%d",result[i]);
            }
            break;
   case'*':
            mutiply(FirBig,SecBig,result);
            break;
   case'/':
            divide(FirBig,SecBig,result);
            break;
   default:
           printf("error");
            break;
   }
    return 0;
}


//函数定义
void transpose1(char d[130],char s[130]){
    int i,len=strlen(s);//len为大数位数，i控制循环
    for(i=0;i<len;i++){
        d[len-i-1]=s[i]-'0';
        
      }
}
void transpose2(char d[130],char s[130]){
    int i,len=strlen(s);//len为大数位数，i控制循环
    for(i=0;i<len-1;i++){
        d[len-i-2]=s[i+1]-'0';
      }
}
//提取操作数和操作符
void extract (char *expression,char*FirBig,char *SecBig,char *operator){
     char flag1='\0',flag2='\0';
     int len=strlen(expression),i=0,j=0,mark;//len表示长度，i控制读取字符次数,j控制读取第一个操作数
     while(!isdigit(expression[i])){
      if (expression[i]=='-'){
            flag1='-';
            i++;
            continue;
        }
        i++;
     }//判断第一个数是否为负数
        
     for(;;i++){
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
       i=mark;//用mark将i还原
       while(isspace(expression[i])||expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/'||expression[i]=='\0'){
        if (!isspace(expression[i])) {
            *operator = expression[i];
        }
        i++;
      }

       //跳过空格并将将操作符赋给operator
    while (isspace(expression[i])) {
        i++;
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
       if(flag1=='-'){
         int i,len=strlen(FirBig);
        for(i=len-1;i>-1;i--){
            FirBig[i+1]=FirBig[i];
        }
          FirBig[0]=flag1;
    }
       if(flag2=='-'){
        int i;len=strlen(SecBig);
        for(i=len-1;i>-1;i--){
             SecBig[i+1]=SecBig[i];
        }
        SecBig[0]=flag2;
    }
}

//加法
char add(char *FirBig, char *SecBig,char*result){
    char s1[130]={0},s2[130]={0};
    strcpy(s1, FirBig);
    strcpy(s2, SecBig);
    char a[130],b[130],c[130]={0};
    /*这里用130防止进行计算时造成溢出
      a，b数组为相加数，c为结果*/
      char flag='\0';
      int len1=lenth2(s1),len2=lenth2(s2);
      if (s1[0]=='-')
      {   
        len1=len1-1;
      }
      if (s2[0]=='-')
      {
        len2=len2-1;
      }
      int i,n,len=len1;
      if(len1<len2){
        len=len2;
      }//确定加法位数

      //第一种情况：第一个为负数
      if (s1[0] == '-' && s2[0]!= '-'){
        transpose2(a, s1);
        transpose1(b, s2);
        if (len1 > len2 || (len1 == len2 && (s1[1]) > (s2[0]))) {
            flag = '-';
            int lend = 0;//借位
        for (int i = 0; i < len; i++) {
            int temp = a[i] - b[i] - lend;
            if (temp < 0) {
                temp += 10;
               lend = 1;
            } 
            else {
               lend = 0;
            }
            c[i] = temp;
            }
            flag='-';
        }
        else{
        int lend = 0;//借位
        for (int i = 0; i < len; i++) {
            int temp = b[i] - a[i] - lend;
            if (temp < 0) {
                temp += 10;
               lend = 1;
            } 
            else {
               lend = 0;
            }
            c[i] = temp;
            }
        }
        
        for (i = len-1; i >= 0; i--) {
            if (c[i] != 0 || i == 0) break;
            }//去除首位0
       
    }

        //第二种情况：第二个为负数
       else if(s1[0]!='-'&&s2[0]=='-'){
       transpose1( a,s1);
       transpose2( b,s2);
       if(len1<len2||len1==len2&&(s1[0])<(s2[1])){
        flag='-';
       int lend = 0;//借位
        for (int i = 0; i < len; i++) {
            int temp = b[i] - a[i] - lend;
            if (temp < 0) {
                temp += 10;
               lend = 1;
            } 
            else {
               lend = 0;
            }
            c[i] = temp;
        }
          flag='-';
       }
       else{
        int lend = 0;//借位
        for (int i = 0; i < len; i++) {
            int temp = a[i] - b[i] - lend;
            if (temp < 0) {
                temp += 10;
               lend = 1;
            } 
            else {
               lend = 0;
            }
            c[i] = temp;
            }
       }
       //进行每一个位数的相减
       
       for (i = len; i >= 0; i--){
            if (c[i] != 0 || i == 0) break;
            }//去除首位0
      }
      
      //第三种情况：两个负数
      else if(s1[0]=='-'&&s2[0]=='-'){
       transpose2( a,s1);
       transpose2( b,s2);
       flag='-';
       for(i=0;i<len;i++){
        c[i]=a[i]+b[i];
      }//进行每一个位数的相加
      for(i=0;i<len;i++){
        if(c[i]>=10){
            c[i+1]++;
            c[i]=c[i]%10;   
        }//进位
      }
       
        for (i = max-1; i >= 0; i--) {
            if (c[i] != 0 || i == 0) break;
            }//首位进位
    }
    //第四种情况：两个正数
     else if(s1[0]!='-'&&s2[0]!='-'){
       transpose1( a,s1);
       transpose1( b,s2);
       for(i=0;i<len;i++){
        c[i]=a[i]+b[i];
       }//进行每一个位数的相加
       for(i=0;i<len;i++){
        if(c[i]>=10){
            c[i+1]++;
            c[i]=c[i]%10;   
        }//进位
       }
        for (i = max-1; i >= 0; i--) {
            if (c[i] != 0 || i == 0) break;
            }//首位进位，以去掉所有前导0的方式
    }
      int j=0;
        for (; i >= 0; i--){
          result[i]=c[i];
        }
        return flag;
}
//减法
char minus(char*FirBig,char*SecBig,char*result){
      char flag='\0';
      char s1[130]={0},s2[130]={0};
      strcpy(s1, FirBig);
      strcpy(s2, SecBig);
      //判断结果符号
      if (s1[0] == '-' && s2[0]!= '-'){
        flag='-';
        }
        else if(s1[0]!='-'&&s2[0]=='-'){
       }
       else if(s1[0]=='-'&&s2[0]=='-'){
       if(compare(s1,s2)==1){
        flag='-';
       }
       }
       else {
       if(compare(s1,s2)==-1){
         flag='-';
       }
       }
    if(SecBig[0]=='-'){
        int i=0,len=strlen(SecBig);
        for(;i<len-1;i++){
            SecBig[i]=SecBig[i+1];
        }
        SecBig[len-1]='\0';
        add(FirBig,SecBig,result);

    }
    else{
        int i,len=strlen(SecBig);
        for(i=len-1;i>=0;i--){
            SecBig[i+1]=SecBig[i];
        }
        SecBig[0]='-';
        add(FirBig,SecBig,result);
    }
    return flag;
}
//乘法
void mutiply(char*FirBig,char*SecBig,char*result){
     char s1[130],s2[130];
    strcpy(s1, FirBig);
    strcpy(s2, SecBig);
    char a[130],b[130],c[130]={0};
      char flag='\0';
      int len1=strlen(s1),len2=strlen(s2);
      if (s1[0]=='-'){
        len1=len1-1;  
      }
      if (s2[0]=='-'){
        len2=len2-1;
      }
      //第一种情况：第一个为负数
      if (s1[0] == '-' && s2[0]!= '-'){
        transpose2(a, s1);
        transpose1(b, s2);
        printf("result:-");
        
        }
     //第二种情况：第二个为负数
       else if(s1[0]!='-'&&s2[0]=='-'){
       transpose1( a,s1);
       transpose2( b,s2);
       printf("result:-");
       }
     //第三种情况：两个负数
      else if(s1[0]=='-'&&s2[0]=='-'){
       transpose2(a,s1);
       transpose2(b,s2);
       printf("result:");
       }
       //第四种情况：两个正数
      else{
       transpose1(a,s1);
       transpose1(b,s2);
       printf("result:");
       }
       for(int i=0;i<len1;i++){
        for(int j=0;j<len2;j++){
         c[i+j]=c[i+j]+a[i]*b[j];
         if(c[i+j]>=10){
            c[i+j+1]=c[i+j+1]+c[i+j]/10;
            c[i+j]=c[i+j]%10;
         }
         }//处理进位
       }
       //处理最大位是否进位
       int len=len1+len2+1;
       if(c[len]>0){
        len++;
        }
        while (c[len-1]==0&&len>1)
        {
          len--;
        }//删除前导0
        
       printf("result:\n");
       for(int i=len-1;i>=0;i--){
         printf("%d",c[i]);
       }
}
void divide(char*FirBig,char*SecBig,char*result){
     char s1[130],s2[130];
    strcpy(s1, FirBig);
    strcpy(s2, SecBig);
    char a[130]={0},b[130]={0},c[130]={0};
      char flag='\0';//结果的符号
      int len1=strlen(s1),len2=strlen(s2);
      //第一种情况：第一个为负数
      if (s1[0] == '-' && s2[0]!= '-'){
        transpose2(a, s1);
        transpose1(b, s2);
        flag='-';
        }
     //第二种情况：第二个为负数
       else if(s1[0]!='-'&&s2[0]=='-'){
       transpose1( a,s1);
       transpose2( b,s2);
       flag='-';
       }
     //第三种情况：两个负数
      else if(s1[0]=='-'&&s2[0]=='-'){
       transpose2(a,s1);
       transpose2(b,s2);
       }
       //第四种情况：两个正数
      else{
       transpose1(a,s1);
       transpose1(b,s2);
       }
       len1=lenth2(a);len2=lenth2(b);
     char quotient[130]={0};
      while((len1>len2)||(len1==len2&&(compare(a,b)==1||compare(a,b)==0))){
        jian(a,b,c);
        for(int i=0;i<max;i++){
          a[i]=c[i];
        }
        len1=lenth2(a);
        quotient[0]++;
        for (int i = 0; i <max; i++)
        {
          if(quotient[i]>=10){
            quotient[i+1]++;
            quotient[i]=quotient[i]%10;
          }
        }
      }
      printf("result:%c",flag);
      for(int i=lenth2(quotient)-1;i>-1;i--){
          printf("%d",quotient[i]);
      }
}
//测量如result内存总长度为260的大数位数
int lenth1(char arr[]){
    int i = 260;
    while (arr[i-1] == 0) {
        i--;
    }
    return i;
}
//测量内存为130的数组中大数位数例如FirBig等
int lenth2(char arr[]){
    int i = 130;
    while (arr[i-1] == 0) {
        i--;
    }
    return i;
}
//用于比较大数大小的函数1
int compare( char* FirBig,  char* SecBig) {
       int len1 = lenth2(FirBig);
       int len2 = lenth2(SecBig);
       if (len1 > len2) {
           return 1;
       } else if (len1 < len2) {
           return -1;
       } else {
           // 长度相等，逐位比较
           for (int i = len1-1; i >-1; i++) {
               if (FirBig[i] > SecBig[i]) {
                   return 1;
               } else if (FirBig[i] < SecBig[i]) {
                   return -1;
               }
               else{
                return 0;
               }
           }
          
       }
   }
   //用于大数除法的类似于减法逻辑的函数
   void jian(char*a, char*b,char*c){
       int lend = 0;//借位
       int len=lenth2(a);
        for (int i = 0; i < len; i++) {
            int temp = a[i] - b[i] - lend;
            if (temp < 0) {
                temp += 10;
               lend = 1;
            } 
            else {
               lend = 0;
            }
            c[i] = temp;
        
       }
      }