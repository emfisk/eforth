#include<math.h>
#include<stdio.h>  
#include<string.h>
#include<stdlib.h>
#include<string.h>
#include<utility>
#include<map>
#include<iostream>
map<string,int> variables;
char stack[65536][256];
char input[256];
char filepath[201];
int counter=-1;
int varcounter=-1;
FILE *file;

int init(int x,char *y[]){
  if(x==1){
    printf("ERROR : NO INPUT FILE.\n");
    exit(0);
  }
  if(x>2){
    printf("NOTE : EFORTH TAKES ONLY ONE INPUT FILE.\nEFORTH WILL ONLY INTERPRET %s.\n",y[1]);
  }
  file=fopen(y[1],"r");
  if(file==NULL){
    printf("ERROR : %s DOES NOT EXIST OR EFORTH DOES NOT HAVE PERMISSION TO READ IT.\n",y[1]);
    exit(0);
  }
}

int interpret(){
    fscanf(file,"%256s",input);
    if(feof(file)){
      exit(0);
    }
     for(int i=0;i<=sizeof(input);i++){
            if(input[0]=='#'){
                strcpy(input,"<COMMENT>");
            } 
            if(input[0]=='*'){
                strcpy(input,"<COMMENT>");
            } 
            if(input[0]=='"'){
                for(int i=0;i<sizeof(input);i++){
                    
                }
            }
     }
    if(counter>65535)
        printf("STACK OVERFLOW ERROR");
     else if(strcmp(input,"LOOP")==0){
           
     } else if(strcmp(input,"PI")==0){
        counter++;
        strcpy(stack[counter],"3.141592653589793");
    } else if(strcmp(input,">")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        if(isgreater(y,x)){
            counter=counter-1;
            strcpy(stack[counter],"TRUE");
            interpret();
        }else{
            counter=counter-1;
            strcpy(stack[counter],"FALSE");
            interpret();
        }
    } else if(strcmp(input,"<")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        if(isless(y,x)){
            counter=counter-1;
            strcpy(stack[counter],"TRUE");
            interpret();
        }else{
            counter=counter-1; 
            strcpy(stack[counter],"FALSE");  
            interpret();
        }
    } else if(strcmp(input,"==")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        if(y==x){
            counter=counter-1;
            strcpy(stack[counter],"TRUE");
            interpret();
        }else{
            counter=counter-1; 
            strcpy(stack[counter],"FALSE");  
            interpret();
        }
    } else if(strcmp(input,"!=")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        if(y!=x){
            counter=counter-1;
            strcpy(stack[counter],"TRUE");
            interpret();
        }else{
            counter=counter-1; 
            strcpy(stack[counter],"FALSE");  
            interpret();
        }
    } else if(strcmp(input,"<=")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        if(islessequal(y,x)){
            counter=counter-1;
            strcpy(stack[counter],"TRUE");


        }else{
            counter=counter-1; 
            strcpy(stack[counter],"FALSE");  
            interpret();
        }
    } else if(strcmp(input,">=")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        if(isgreaterequal(y,x)){
            counter=counter-1;
            strcpy(stack[counter],"TRUE");
            interpret();
        }else{
            counter=counter-1; 
            strcpy(stack[counter],"FALSE");  
            interpret();
        }
    } else if(strcmp(input,"IF")==0){ 
        if(strcmp(stack[counter],"TRUE")==0){
            counter=counter-1;
            interpret();
        }else if(strcmp(stack[counter],"FALSE")==0){
            fscanf(file,"%256s",input);
            strcpy(stack[counter],"FALSE");
        }else{
            printf("ERROR : %s DOES NOT EVAL TO TRUE OR FALSE.",stack[counter]);
            exit(0);
        }
    } else if(strcmp(input,"ELSE")==0){
         if(strcmp(stack[counter],"FALSE")==0){
            interpret();
         }else{
            fscanf(file,"%256s",input);
            strcpy(stack[counter],"FALSE");
         }
    } else if(strcmp(input,"VARIABLE")==0){
        char name[256];
        char data[256];
        strcpy(name,stack[counter-1]);
        strcpy(data,stack[counter]);
        variables[name]=data;
    } else if(strcmp(input,"SWAP")==0){
        char x[256];
        char y[256];
        strcpy( x,stack[counter]);
        strcpy (y,stack[counter-1]);
        strcpy(stack[counter-1],x);
        strcpy(stack[counter],y);
    } else if(strcmp(input,"PEEK")==0){
        char x[256];
        strcpy(x,stack[counter]);
        if(input[0]=='<'){
            ;
        }else{
        printf("%s\n",x);
        }
    } else if(strcmp(input,"POP")==0){
        char x[256];
        strcpy(x,stack[counter]);	
        counter=counter-1;
        if(input[0]=='<'){
            ;
        }else{
        printf("%s\n",x);
        }
    } else if(strcmp(input,"POPS")==0){
        counter=counter-1;
    } else if(strcmp(input,"CLEAR")==0){
        counter=-1;
    } else if(strcmp(input,"LIST")==0){
        printf("{ ");
        for(int i=0;i<=counter;i++){  
            if(stack[i][0]=='<'){
                ;
            }else{
              printf("`%s' ",stack[i]);
            }
        }
        printf("}\n");
    } else if(strcmp(input,"BYE")==0){
        exit(0);
    } else if(strcmp(input,"STRCMP")==0){
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
        
    } else if(strcmp(input,"GETWORD")==0){
        char thing[2048];
        scanf("%2048s",thing);
        counter++;
        strcpy(stack[counter],thing);
    } else if(strcmp(input,"+")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=x+y;
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"-")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=y-x;
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"*")==0){       
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=x*y;
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"/")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=y/x;
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"^")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=pow(y,x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"TAN")==0){
        double x=atof(stack[counter]);
        double z=tan(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"SIN")==0){
        double x=atof(stack[counter]);
        double z=sin(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"COS")==0){
        double x=atof(stack[counter]);
        double z=cos(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"TRUNC")==0){
        double x=atof(stack[counter]);
        double z=trunc(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"HYPOT")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=hypot(x,y);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"ROUNDU")==0){
        double x=atof(stack[counter]);
        double z=ceil(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"ROUND")==0){
        double x=atof(stack[counter]);
        double z=rint(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"ABS")==0){
        double x=atof(stack[counter]);
        double z=abs(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"SQRT")==0){
        double x=atof(stack[counter]);
        double z=sqrt(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"CBRT")==0){
        double x=atof(stack[counter]);
        double z=cbrt(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"ARCSIN")==0){
        double x=atof(stack[counter]);
        double z=asin(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"ARCCOS")==0){
        double x=atof(stack[counter]);
        double z=acos(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"ARCTAN")==0){
        double x=atof(stack[counter]);
        double z=atan(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"MIN")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=fmin(y,x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"MAX")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=fmax(y,x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(input,"<COMMENT>")==0){
        ; 
    } else{
        counter++;
        for(int i=0;i<sizeof(input);i++){
             if(input[i]=='&'){
                  input[i]=' ';
             }
             stack[counter][i]=input[i];
        }
    }
  interpret();
}
int main(int argc, char *argv[]){
  init(argc,argv);
  interpret();
}
