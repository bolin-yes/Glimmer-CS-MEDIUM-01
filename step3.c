#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define debug 0//用于调试
#define max 130

//函数声明
void transpose1(char d[130],char s[130]);//对输入的正大数进行转置

void transpose2(char d[130],char s[130]);//对输入的负大数进行转置



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
//主程序
int main(){
    char a[130],b[130],c[130]={0};
    /*这里用130防止进行计算时造成溢出
      a，b数组为相加数，c为结果*/
      char s1[130],s2[130];
      //两个大数
      printf("请输入两个大数：\n");
      scanf("%s%s",s1,s2);
      char flag='+';
      int len1=strlen(s1),len2=strlen(s2);
      if (s1[0]=='-')
      {
        #if debug
      printf("%d\t%d\t",len1,len2);
      #endif
        len1=len1-1;
        #if debug
      printf("%d\t%d\t",len1,len2);
      #endif
      }
      if (s2[0]=='-')
      {
        len2=len2-1;
      }

      #if debug
      printf("%d\t%d\t",len1,len2);
      #endif

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
        printf("%c",flag);
        for (i = len-1; i >= 0; i--) {
            if (c[i] != 0 || i == 0) break;
            }//去除首位0
        for (; i >= 0; i--){
            printf("%d", c[i]);
        }
    }


        //第二种情况：第二个为负数
       if(s1[0]!='-'&&s2[0]=='-'){
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
       printf("%c",flag);
       for (i = len; i >= 0; i--) {
            if (c[i] != 0 || i == 0) break;
            }//去除首位0
        for(;i>-1;i--){ 
            printf("%d",c[i]);
       }//输出大数
      }
      


      //第三种情况：两个负数
      if(s1[0]=='-'&&s2[0]=='-'){
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
        printf("%c",flag);
        for (i = max-1; i >= 0; i--) {
            if (c[i] != 0 || i == 0) break;
            }//首位进位
        for(;i>-1;i--){
        printf("%d",c[i]);
       }//输出大数
        
    }



    //第四种情况：两个正数
    if(s1[0]!='-'&&s2[0]!='-'){
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
            }//首位进位
        for(;i>-1;i--){
        printf("%d",c[i]);
       }//输出大数
        
    }
    return 0;
}