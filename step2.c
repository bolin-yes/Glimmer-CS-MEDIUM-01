#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
    char a[130],b[130],c[130]={0};
    /*这里用130防止进行计算时造成溢出
      a，b数组为相加数，c为结果*/
      char s1[130],s2[130];
      //两个大数
      printf("请输入两个大数：");
      scanf("%s%s",s1,s2);
      int i,len1=strlen(s1),len2=strlen(s2);//len1,len2为大数位数，i控制循环
      for(i=0;i<len1;i++){
        a[len1-i-1]=s1[i]-'0';
      }//对s1进行转置
      for(i=0;i<len2;i++){
        b[len2-i-1]=s1[i]-'0';
      }//对s2进行转置
      int len=len1;
      if(len1<len2){
        len=len2;
      }//确定加法位数
      for(i=0;i<len;i++){
        c[i]=a[i]+b[i];
      }//进行每一个位数的相加
      for(i=0;i<len;i++){
        if(c[i]>=10){
            c[i+1]++;
            c[i]=c[i]%10;   
        }
      }//判断除最高位每一位是否进位
      if(c[len]!=0){
        len++;
      }//判断最高位是否
      for(i=len-1;i>-1;i--){
        printf("%d",c[i]);
      }//输出大数
    
    return 0;
}
