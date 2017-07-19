#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char stack[65536][256];
char thing[256];
char filepath[101];
int counter=-1;
FILE *file;

int init(int x,char *y[]){
  if(x!=2){
    printf("There are too few or too many input files.\n");
    exit(0);
  }
  file=fopen(y[1],"r");
  if(file==NULL){
    printf("That file does not exist or eforth is not allowed to read it.\n");
    exit(0);
  }
}

int interpret(){
while(!feof(file)){ 
    fscanf(file,"%256s",thing);
    if(thing[0]=='#'){
       strcpy(thing,"comment");
    }
    else if(thing[0]=='*'){
      strcpy(thing,"comment");
    }if(feof(file)){
      break;
    }
    if(counter>65536){
    } else if(strcmp(thing,"peek")==0){
        char x[256];
        strcpy(x,stack[counter]);
        printf("%s\n",x);
    } else if(strcmp(thing,"pop")==0){
        char x[256];
        strcpy(x,stack[counter]);	
        counter=counter-1;
        printf("%s\n",x);
    } else if(strcmp(thing,"pops")==0){
        char x[256];
        strcpy(x,stack[counter]);	
        counter=counter-1;
    } else if(strcmp(thing,"clear")==0){
        counter=-1;
    } else if(strcmp(thing,"list")==0){
        printf("\n|");
        for(int i=0;i<=counter;i++){  
            printf(" %s |",stack[i]);
        }
        printf("\n");
    } else if(strcmp(thing,"+")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=x+y;
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);

        
    } else if(strcmp(thing,"-")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=y-x;
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(thing,"*")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=x*y;
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(thing,"/")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=y/x;
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(thing,"^")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=pow(y,x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(thing,"tan")==0){
        double x=atof(stack[counter]);
        double z=tan(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(thing,"sin")==0){
        double x=atof(stack[counter]);
        double z=sin(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(thing,"cos")==0){
        double x=atof(stack[counter]);
        double z=cos(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(thing,"trunc")==0){
        double x=atof(stack[counter]);
        double z=trunc(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(thing,"hypot")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=hypot(x,y);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(thing,"round")==0){
        double x=atof(stack[counter]);
        double z=rint(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(thing,"abs")==0){
        double x=atof(stack[counter]);
        double z=abs(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(thing,"sqrt")==0){
        double x=atof(stack[counter]);
        double z=sqrt(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(thing,"cbrt")==0){
        double x=atof(stack[counter]);
        double z=cbrt(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(thing,"arcsin")==0){
        double x=atof(stack[counter]);
        double z=asin(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(thing,"arccos")==0){
        double x=atof(stack[counter]);
        double z=acos(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(thing,"arctan")==0){
        double x=atof(stack[counter]);
        double z=atan(x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(thing,"min")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=fmin(y,x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(thing,"max")==0){
        double x=atof(stack[counter]);
        double y=atof(stack[counter-1]);
        double z=fmax(y,x);
        printf("%f\n",z);
        counter=counter-1;
        sprintf(stack[counter],"%f",z);
    } else if(strcmp(thing,"comment")==0){
        ; 
    } else{
        for(int i=0;i<sizeof(thing);i++){
            if(thing[i]=='&'){
                thing[i]=' ';
            }
        }
        counter++;
        strcpy(stack[counter],thing);
    }
  }
  fclose(file);
}
int main(int argc, char *argv[]){
  init(argc,argv);
  interpret();
}

      


