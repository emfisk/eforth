// by Ethan Fisk
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cstring>
#include<utility>
#include<map>
#include<iostream>
#include<list>


using namespace std;
bool inloop=false;
int stacksize=100;
map <string,string> globalvariables;
map <string,int> functions;
char stack[100][1000];
char nextword[1000];
char filepath[1000];
int counter=-1;
FILE *file;
const char * errors []={
  "(error) no input file\n",
  "(error) more than one input file\n",
  "(error) file does not exist\n",
  "(error) stack overflow\n",
  "(error) unexpected EOF\n",
  "(error) stack underflow\n",
  "(error) %s does not eval to 1 or 0\n",
};

int init(int x,char *y[]){
  if(x==1){
    printf("%s",errors[0]);
    exit(0);
  }
  if(x>2){
    printf("%s",errors[1]);
    exit(0);
  }
  file=fopen(y[1],"r");
  if(file==NULL){
    printf("%s",errors[2]);
    exit(0);
  }
}

int eval(char nextword[1000]){
    if(feof(file)){
      exit(0);
    } else if(counter>=stacksize){
        printf("%s",errors[3]);
        exit(0);

    } else if(nextword[0]=='*'){
      counter++;
      strcpy(stack[counter], nextword+1);
      if (nextword[strlen(nextword)-1] != '\n') {
        while (fscanf(file, "%1000s",nextword) != EOF) {
          strcat(stack[counter], nextword);
          if (nextword[strlen(nextword)-1] == '\n') {
            break;
          }
        }
      }
      stack[counter][strlen(stack[counter])-1] = '\0';
      counter=counter-1;
    } else if(nextword[0]=='('){
      counter++;
      if (nextword[strlen(nextword)-1] != ')') {
        while (fscanf(file, "%1000s",nextword) != EOF) {
          if (nextword[strlen(nextword)-1] == ')') {
            break;
          }
        }
      }
      stack[counter][strlen(stack[counter])-1] = '\0';
      counter=counter-1;
    } else if(nextword[0]=='"'){
      counter++;
      strcpy(stack[counter], nextword+1);

      if (nextword[strlen(nextword)-1] != '"') {
        if(feof(file)){
          printf("%s",errors[5]);
          exit(0);
        }
        while (fscanf(file, "%1024s",nextword) != EOF) {
          strcat(stack[counter], " ");
          strcat(stack[counter], nextword);
          if (nextword[strlen(nextword)-1] == '"') {
            break;
          }
        }
      }
      stack[counter][strlen(stack[counter])-1] = '\0';
    } else if(strcmp(nextword,"=")==0){
      if(counter<1){
        printf("%s",errors[5]);
        exit(0);
      }
        char name[1024];
        char data[1024];
        strcpy(name,stack[counter]);
        strcpy(data,stack[counter-1]);
        counter=counter-2;
        variables[string(name)]=data;
    } else if(nextword[0]=='$'){
      counter++;
      strcpy(stack[counter],globalvariables[nextword+1].c_str());
    } else if(strcmp(nextword,"while")==0){
        list <string> test;
        list <string> code;
        inloop=true;
        if(counter<0){
          printf("%s",errors[5]);
          exit(0);
        }
        
    } else if(strcmp(nextword,"pi")==0){
        counter++;
        strcpy(stack[counter],"3.141592653589793");
    } else if(strcmp(nextword,"!")==0){
      if(counter<0){
        printf("%s",errors[5]);
        exit(0);
      }
      if(strcmp(stack[counter],"1")==0){
        strcpy(stack[counter],"0");
      }
      else if(strcmp(stack[counter],"0")==0){
        strcpy(stack[counter],"1");
      }
    } else if(strcmp(nextword,"&")==0){
      if(counter<1){
        printf("%s",errors[5]);
        exit(0);
      }
      if(strcmp(stack[counter],"1")==0 && strcmp(stack[counter-1],"1")==0 ){
        counter=counter-1;
        strcpy(stack[counter],"1");

      } else {
        counter=counter-1;
        strcpy(stack[counter],"0");
      }
    } else if(strcmp(nextword,">")==0){
      if(counter<1){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        if(isgreater(y,x)){
            counter=counter-1;
            strcpy(stack[counter],"1");
            fscanf(file,"%s",nextword);
            eval(nextword);
        }else{
            counter=counter-1;
            strcpy(stack[counter],"0");
            fscanf(file,"%s",nextword);
            eval(nextword);
        }
    } else if(strcmp(nextword,"<")==0){
      if(counter<1){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        if(isless(y,x)){
            counter=counter-1;
            strcpy(stack[counter],"1");
            fscanf(file,"%s",nextword);
            eval(nextword);
        }else{
            counter=counter-1;
            strcpy(stack[counter],"0");
            fscanf(file,"%s",nextword);
            eval(nextword);
        }
    } else if(strcmp(nextword,"==")==0){
      if(counter<1){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        if(y==x){
            counter=counter-1;
            strcpy(stack[counter],"1");
            fscanf(file,"%s",nextword);
            eval(nextword);
        }else{
            counter=counter-1;
            strcpy(stack[counter],"0");
            fscanf(file,"%s",nextword);
            eval(nextword);
        }
    } else if(strcmp(nextword,"<=")==0){
      if(counter<1){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        if(islessequal(y,x)){
            counter=counter-1;
            strcpy(stack[counter],"1");


        }else{
            counter=counter-1;
            strcpy(stack[counter],"0");
            fscanf(file,"%s",nextword);
            eval(nextword);
        }
    } else if(strcmp(nextword,">=")==0){
      if(counter<1){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        if(isgreaterequal(y,x)){
            counter=counter-1;
            strcpy(stack[counter],"1");
            fscanf(file,"%s",nextword);
            eval(nextword);
        }else{
            counter=counter-1;
            strcpy(stack[counter],"0");
            fscanf(file,"%s",nextword);
            eval(nextword);
        }
    } else if(strcmp(nextword,"if")==0){
      if(counter<0){
        printf("%s",errors[5]);
        exit(0);
      } else if(strcmp(stack[counter],"0")==0){
          counter=counter-1;
          while(fscanf(file,"%1000s",nextword)){
            if(strcmp(nextword,"then")==0){
              break;
            }
            if(feof(file)){
              break;
            }
          }
        }
        else if(strcmp(stack[counter],"1")==0){
          counter=counter-1;
          while(!feof(file)){
            fscanf(file,"%s",nextword);
            eval(nextword);
            if(strcmp(nextword,"then")==0){
              break;
            }
          }
        }
        else{
          printf(errors[6],stack[counter]);
          exit(0);
        }
    } else if(strcmp(nextword,"rot")==0){
        if(counter<2){
        printf("%s",errors[5]);
        exit(0);
        }
        char x[1000];
        char y[1000];
        char z[1000];
        strcpy(x,stack[counter]);
        strcpy(y,stack[counter-1]);
        strcpy(z,stack[counter-2]);
        strcpy(stack[counter-2],x);
        strcpy(stack[counter-1],z);
        strcpy(stack[counter],y);
    } else if(strcmp(nextword,"dup")==0){
        if(counter<0){
        printf("%s",errors[5]);
        exit(0);
      }
        counter++;
        strcpy(stack[counter],stack[counter-1]);
    } else if(strcmp(nextword,"swap")==0){
      if(counter<1){
        printf("%s",errors[5]);
        exit(0);
      }
        char x[1000];
        char y[1000];
        strcpy( x,stack[counter]);
        strcpy (y,stack[counter-1]);
        strcpy(stack[counter-1],x);
        strcpy(stack[counter],y);
    } else if(strcmp(nextword,"?")==0){
        char thing[1000];
        scanf("%s",thing);
        counter++;
        strcpy(stack[counter],thing);
    } else if(strcmp(nextword,"print")==0){
        if(counter<0){
          printf("%s",errors[5]);
          exit(0);
        }
        printf("%s\n",stack[counter]);
        counter=counter-1;
    } else if(strcmp(nextword,"drop")==0){
        counter=counter-1;
    } else if(strcmp(nextword,"stack")==0){
        printf("===========================\n");
        printf("#\tContents\n\n");
        for(int i=counter;i>=0;i-=1){
              printf("%d\t%s\n",i,stack[i]);
        }
        printf("\n");
    } else if(strcmp(nextword,"bye")==0){
        exit(0);
    } else if(strcmp(nextword,"===")==0){
      if(counter<1){
        printf("%s",errors[5]);
        exit(0);
      }
        char first[1000];
        char second[1000];
        strcpy(first,stack[counter-1]);
        strcpy(second,stack[counter]);
        if(strcmp(first,second)==0){
            counter=counter-1;
            strcpy(stack[counter],"1");
        }else{
            counter=counter-1;
            strcpy(stack[counter],"0");
        }
    } else if(strcmp(nextword,"+")==0){
        if(counter<1){
          printf("%s",errors[5]);
          exit(0);
        }
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=x+y;

        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"-")==0){
      if(counter<1){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=y-x;

        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"*")==0){
      if(counter<1){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=x*y;

        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"/")==0){
      if(counter<0){
        printf("%s",errors[5]);
        exit(0);
      }
      if(counter<1){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=y/x;

        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"^")==0){
      if(counter<0){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=pow(y,x);

        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"tan")==0){
      if(counter<0){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double z=tan(x);
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"sin")==0){
      if(counter<0){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double z=sin(x);
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"cos")==0){
      if(counter<0){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double z=cos(x);
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"trunc")==0){
      if(counter<0){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double z=trunc(x);
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"hypot")==0){
      if(counter<1){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=hypot(x,y);
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"ceil")==0){
      if(counter<0){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double z=ceil(x);
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"rint")==0){
      if(counter<0){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double z=rint(x);
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"abs")==0){
      if(counter<0){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double z=abs(x);
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"sqrt")==0){
      if(counter<0){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double z=sqrt(x);
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"cbrt")==0){
      if(counter<0){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double z=cbrt(x);
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"asin")==0){
      if(counter<0){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double z=asin(x);
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"acos")==0){
      if(counter<0){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double z=acos(x);
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"atan")==0){
        if(counter<0){
        printf("%s",errors[5]);
        exit(0);
        }
        double x=atof(stack[counter]);
        double z=atan(x);
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"min")==0){
      if(counter<1){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=fmin(y,x);
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(nextword,"max")==0){
      if(counter<1){
        printf("%s",errors[5]);
        exit(0);
      }
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=fmax(y,x);
        sprintf(stack[counter],"%f",z);
    } else{
        counter++;
        strcpy(stack[counter],nextword);
    }
  fscanf(file,"%s",nextword);
  eval(nextword);
}
int main(int argc, char *argv[]){
  init(argc,argv);
  fscanf(file,"%s",nextword);
  eval(nextword);
}
