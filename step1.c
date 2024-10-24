#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
      char a[130]={0},s1[130];
      //一个大数
      printf("请输入一个大数：");
      scanf("%s",s1);
      int i,len1=strlen(s1);//len为大数位数，i控制循环
      for(i=0;i<len1;i++){
        a[len1-i-1]=s1[i]-'0';
      }//对s1进行转置,虽然在这里好像有点多余了
      for(i=len1-1;i>-1;i--){
        printf("%d",a[i]);
}
return 0;
}
