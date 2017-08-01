#include<math.h>
#include<stdio.h>  
#include<string.h>
#include<stdlib.h>
#include<string.h>
#include<utility>
#include<map>
#include<iostream>
using namespace std;
map <string,int> variables;
char stack[65536][256];
char nextword[256];
char filepath[201];
int counter=-1;
int varcounter=-1;
FILE *file;

int init(int x,char *y[]){
  if(x==1){
    printf("ERROR : NO nextword FILE.\n");
    exit(0);
  }
  if(x>2){
    printf("NOTE : EFORTH TAKES ONLY ONE nextword FILE.\nEFORTH WILL ONLY eval %s.\n",y[1]);
  }
  file=fopen(y[1],"r");
  if(file==NULL){
    printf("ERROR : %s DOES NOT EXIST OR EFORTH DOES NOT HAVE PERMISSION TO READ IT.\n",y[1]);
    exit(0);
  }
}

int eval(){
    fscanf(file,"%256s",nextword);
    if(feof(file)){
      exit(0);
    }
     for(int i=0;i<=sizeof(nextword);i++){
            if(nextword[0]=='#'){
                strcpy(nextword,"<COMMENT>");
            } 
            if(nextword[0]=='*'){
                strcpy(nextword,"<COMMENT>");
            } 
 
     }
    if(counter>65535)
        printf("STACK OVERFLOW ERROR");
     else if(strcmp(nextword,"LOOP")==0){
           
     } else if(strcmp(nextword,"PI")==0){
        counter++;
        strcpy(stack[counter],"3.141592653589793");
    } else if(strcmp(nextword,">")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        if(isgreater(y,x)){
            counter=counter-1;
            strcpy(stack[counter],"TRUE");
            eval();
        }else{
            counter=counter-1;
            strcpy(stack[counter],"FALSE");
            eval();
        }
    } else if(strcmp(nextword,"<")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        if(isless(y,x)){
            counter=counter-1;
            strcpy(stack[counter],"TRUE");
            eval();
        }else{
            counter=counter-1; 
            strcpy(stack[counter],"FALSE");  
            eval();
        }
    } else if(strcmp(nextword,"==")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        if(y==x){
            counter=counter-1;
            strcpy(stack[counter],"TRUE");
            eval();
        }else{
            counter=counter-1; 
            strcpy(stack[counter],"FALSE");  
            eval();
        }
    } else if(strcmp(nextword,"!=")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        if(y!=x){
            counter=counter-1;
            strcpy(stack[counter],"TRUE");
            eval();
        }else{
            counter=counter-1; 
            strcpy(stack[counter],"FALSE");  
            eval();
        }
    } else if(strcmp(nextword,"<=")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        if(islessequal(y,x)){
            counter=counter-1;
            strcpy(stack[counter],"TRUE");


        }else{
            counter=counter-1; 
            strcpy(stack[counter],"FALSE");  
            eval();
        }
    } else if(strcmp(nextword,">=")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        if(isgreaterequal(y,x)){
            counter=counter-1;
            strcpy(stack[counter],"TRUE");
            eval();
        }else{
            counter=counter-1; 
            strcpy(stack[counter],"FALSE");  
            eval();
        }
    } else if(strcmp(nextword,"IF")==0){ 
        if(strcmp(stack[counter],"TRUE")==0){
            counter=counter-1;
            eval();
        }else if(strcmp(stack[counter],"FALSE")==0){
            fscanf(file,"%256s",nextword);
            strcpy(stack[counter],"FALSE");
        }else{
            printf("ERROR : %s DOES NOT EVAL TO TRUE OR FALSE.",stack[counter]);
            exit(0);
        }
    } else if(strcmp(nextword,"ELSE")==0){
         if(strcmp(stack[counter],"FALSE")==0){
            eval();
         }else{
            fscanf(file,"%256s",nextword);
            strcpy(stack[counter],"FALSE");
         }
    } else if(strcmp(nextword,"VARIABLE")==0){
        char name[256];
        char data[256];
        counter++;
        varcounter=counter;
        strcpy(name,stack[counter-1]);
        strcpy(data,stack[counter]);
        strcpy(stack[counter],data);
        variables[name]=varcounter;
    } else if(strcmp(nextword,"SWAP")==0){
        char x[256];
        char y[256];
        strcpy( x,stack[counter]);
        strcpy (y,stack[counter-1]);
        strcpy(stack[counter-1],x);
        strcpy(stack[counter],y);
    } else if(strcmp(nextword,"PEEK")==0){
        char x[256];
        strcpy(x,stack[counter]);
        if(nextword[0]=='<'){
            ;
        }else{
        printf("%s\n",x);
        }
    } else if(strcmp(nextword,"POP")==0){
        char x[256];
        strcpy(x,stack[counter]);	
        counter=counter-1;
        if(nextword[0]=='<'){
            ;
        }else{
        printf("%s\n",x);
        }
    } else if(strcmp(nextword,"POPS")==0){
        counter=counter-1;
    } else if(strcmp(nextword,"CLEAR")==0){
        counter=-1;
    } else if(strcmp(nextword,"LIST")==0){
        printf("{ ");
        for(int i=0;i<=counter;i++){  
            if(stack[i][0]=='<'){
                ;
            }else{
              printf("`%s' ",stack[i]);
            }
        }
        printf("}\n");
    } else if(strcmp(nextword,"BYE")==0){
        exit(0);
    } else if(strcmp(nextword,"STRCMP")==0){
        char first[256];
        char second[256];
        strcpy(first,stack[counter-1]);
        strcpy(second,stack[counter]);
        if(strcmp(first,second)==0){
            counter=counter-1;
            strcpy(stack[counter],"TRUE");
        }else{
            counter=counter-1;
            strcpy(stack[counter],"FALSE");
        }
        
    } else if(strcmp(nextword,"GETWORD")==0){
        char thing[2048];
        scanf("%2048s",thing);
        counter++;
        strcpy(stack[counter],thing);
    } else if(strcmp(nextword,"+")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=x+y;
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"-")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=y-x;
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"*")==0){       
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=x*y;
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"/")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=y/x;
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"^")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=pow(y,x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"TAN")==0){
        double x=atof(stack[counter]);
        double z=tan(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"SIN")==0){
        double x=atof(stack[counter]);
        double z=sin(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"COS")==0){
        double x=atof(stack[counter]);
        double z=cos(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"TRUNC")==0){
        double x=atof(stack[counter]);
        double z=trunc(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"HYPOT")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=hypot(x,y);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"ROUNDU")==0){
        double x=atof(stack[counter]);
        double z=ceil(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"ROUND")==0){
        double x=atof(stack[counter]);
        double z=rint(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"ABS")==0){
        double x=atof(stack[counter]);
        double z=abs(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"SQRT")==0){
        double x=atof(stack[counter]);
        double z=sqrt(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"CBRT")==0){
        double x=atof(stack[counter]);
        double z=cbrt(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"ARCSIN")==0){
        double x=atof(stack[counter]);
        double z=asin(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"ARCCOS")==0){
        double x=atof(stack[counter]);
        double z=acos(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"ARCTAN")==0){
        double x=atof(stack[counter]);
        double z=atan(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"MIN")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=fmin(y,x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"MAX")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=fmax(y,x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"<COMMENT>")==0){
        ; 
    } else{
        counter++;
        for(int i=0;i<sizeof(nextword);i++){
             if(nextword[i]=='&'){
                  nextword[i]=' ';
             }
             stack[counter][i]=nextword[i];
        }
    }
  eval();
}
int main(int argc, char *argv[]){
  init(argc,argv);
  eval();
}
