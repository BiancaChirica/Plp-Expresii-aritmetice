// calculator de expresii aritmetice cu variabile si functii
// Chirica Bianca II B5

#include <fstream>
#include <math.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <queue>
#include <string>

using namespace std;
ifstream fin ("intrare.in");
ofstream fout("iesire.out");

int evalueaza(char sir[100]);
int stare (char a[101]);
int prec(char c);
int assoc(char c);
int strtoint (char s[101]);
void inttostr(int n, char temp[1000]);
int eoperator (char c);
int efunctie(char sir1[100]);
 int functbin(char str[100]);

struct variabila{
char nume[50]={};
char val[100]={};
}var[100];

int nrvar=0;

int main ()
{
char x[101]={}; // in x citesc liniile pe rand
while(fin.getline(x,100))
{
     // elimin spatiile de la inceput
    while(x[0]==' ')
    strcpy(x,x+1);

    char str[100]={};
    strncpy(str, x, 4);

    if(strcmp(str,"eval")==0) //testez daca e instructiune de evaluare sau declaratie de variabila
       {   strcpy(x,x+5);
           while(x[0]==' ')
              strcpy(x,x+1);

    fout<<x<<endl;
           evalueaza(x);
       }
    else
      {
          stare(x);
      }

}

  return 0;
}


int evalueaza(char sir[])
{
    stack <string> stivaop;
     char coada[100][100]={};

      char temp[1000];
      int len=strlen(sir);
      int i,k,j;
      int nr=0;
    int contor=1;
      for(i=0;i<len;) //parcurg expresia
      {   k=0;
         temp[100]={0};

          if(int(sir[i])>=48 && int(sir[i])<=57) // verific daca e cifra
          {
              while( int(sir[i])>='0' && int(sir[i])<='9' )
                {temp[k++]=sir[i]; i++;}
                temp[k]='\0';
               strcpy(coada[contor++],temp);
               continue;
          }

          if ((int(sir[i])>='A' && int(sir[i])<='Z' )|| (int(sir[i])>='a' && int(sir[i])<='z')||(int(sir[i])>=48 && int(sir[i])<=57)) //daca e text
          {
              while ((int(sir[i])>='A' && int(sir[i])<='Z' )|| (int(sir[i])>='a' && int(sir[i])<='z')||(int(sir[i])>=48 && int(sir[i])<=57))
              {
                  temp[k++]=sir[i]; i++;
              }
                temp[k]='\0';

                if(efunctie(temp)==1) //daca e functie o pun pe stiva operatorilor
                {
                  stivaop.push(temp);
                continue;
                }

            int ok=0;         //verifica daca e o variabila declarata
                for(j=0;j<nrvar&&ok==0;j++)
                    if(strcmp(var[j].nume,temp)==0)
                {

                   strcpy(coada[contor++],var[j].val);
                 ok=1;
                }
               if(ok==1)
               continue;

                fout<<"Sintaxa gresita la expresia evaluata.Functie necunoscuta sau variabila nu este declarata." <<endl;
                return -1;
          }

          if (eoperator(sir[i])==1)// daca e operator
             {

                 if(!stivaop.empty())
                    stivaop.top().copy(temp,50,0);

                while( (efunctie(temp)==1 || prec(sir[i]) < prec(temp[0]) || (prec(sir[i])== prec(temp[0])&& assoc(temp[0])==1)) && temp[0]!='(' && !stivaop.empty() )
                    {
                        if(efunctie(temp)!=1)  //8+9*7
                        {
                          temp[1]='\0';
                        }
                        strcpy(coada[contor++],temp );
                       stivaop.pop();
                   if(!stivaop.empty())
                    stivaop.top().copy(temp,50,0);
                    }

                   temp[0]=sir[i];
                    temp[1]='\0';
                stivaop.push(temp);
                i++;
                continue;
             }

                if(sir[i]=='(') ////////////paranteze//////////////////
             {
                 temp[0]=sir[i];
                    temp[1]='\0';
                stivaop.push(temp);
                i++;
                continue;
             }

             if(sir[i]==')'||sir[i]==',')
             {
                 if(!stivaop.empty())
                    stivaop.top().copy(temp,50,0);

                    while(temp[0]!='(' && !stivaop.empty())
                    {
                        if(efunctie(temp)!=1)  //8+9*7
                        {
                          temp[1]='\0';
                        }
                        strcpy(coada[contor++],temp );
                       stivaop.pop();
                   if(!stivaop.empty())
                    stivaop.top().copy(temp,50,0);
                    }

                    if(temp[0]!='(')
                    {
                        fout<<"Sintaxa gresita. Paranteze gresite."<<endl;
                        return -1;
                    }
                    else if(sir[i]==')') stivaop.pop();
                 i++;
                continue;
             }

       if(sir[i]==' ')
        {i++;continue;}

        fout<<"Sintaxa gresita." <<endl;
        return -1;
      }

      if(!stivaop.empty())
       stivaop.top().copy(temp,50,0);

      while (!stivaop.empty())
    {
        if(temp[0]=='(')
         {
             fout<<"Sintaxa gresita. Paranteze gresite."<<endl;
             return -1;
         }
       if(efunctie(temp)!=1)
          {
              temp[1]='\0';
            }
           strcpy(coada[contor++],temp );
           stivaop.pop();
         if(!stivaop.empty())
       stivaop.top().copy(temp,50,0);
       }

       //////////
/*
  fout<<"Expresia in ordinde postfixata din coada :";
       for (i=1;i<contor;i++)
        fout<<coada[i]<<" ";
       fout<<endl;
*/

///////////////////////////// expresia se afla in coada in postordine,stiva e goala ////////

char temp2[1000];

int ok;
for (i=1;i<contor;i++)
  {
    memset(temp,0,1000);
    memset(temp2,0,1000);
    j=0;
    k=0;

        if( (eoperator(coada[i][0])==1 && !(coada[i][1]>='0' && coada[i][1]<='9' )) || functbin(coada[i])==1) // 2 argumente la functie sau operator
            {
                char c=coada[i][0];
                ok=0;
                 if(!stivaop.empty())
                    { stivaop.top().copy(temp,50,0); stivaop.pop();ok=1; }
                 if((!stivaop.empty())&&ok==1)
                      { stivaop.top().copy(temp2,50,0); stivaop.pop(); ok=2; }

                 if(ok!=2)
                 {
                     fout<<"Sintaxa gresita."<<endl;
                     return -1;
                 }
                 j=strtoint(temp);
                 k=strtoint(temp2);


            if(eoperator(coada[i][0])==1) // operator
               {
                if(c=='+')
                    j=k+j;
                if(c=='-')
                   j=k-j;
                if(c=='*')
                    j=k*j;
                if(c=='/')
                    j=k/j;
                if(c=='^')
                   j=pow(k,j);
               }
               else      //functie
             {
                    if(strcmp(coada[i],"max")==0||strcmp(coada[i],"MAX")==0)
                        if(k>j)
                        j=k;
                    if(strcmp(coada[i],"min")==0||strcmp(coada[i],"MIN")==0)
                        if(k<j)
                        j=k;
                    if(strcmp(coada[i],"pow")==0||strcmp(coada[i],"POW")==0)
                        j=pow(k,j);
                }

            memset(temp,0,1000);
               inttostr(j,temp);
              stivaop.push(temp);
              continue;

            }

            else if (efunctie(coada[i])==1)//  functie cu un singur argument, operator cu un singur argument nu am
            {
                ok=0;
                 if(!stivaop.empty())
                    { stivaop.top().copy(temp,50,0); stivaop.pop();ok=1; }

                 if(ok!=1)
                 {
                     fout<<"Sintaxa gresita."<<endl;
                     return -1;
                 }
                 j=strtoint(temp);

                    if(strcmp(coada[i],"sin")==0||strcmp(coada[i],"SIN")==0)
                        j=sin(j);
                    if(strcmp(coada[i],"cos")==0||strcmp(coada[i],"COS")==0)
                        j=cos(j);
                    if(strcmp(coada[i],"asin")==0||strcmp(coada[i],"ASIN")==0)
                        j=asin(j);
                         if(strcmp(coada[i],"acos")==0||strcmp(coada[i],"ACOS")==0)
                        j=acos(j);
                         if(strcmp(coada[i],"tan")==0||strcmp(coada[i],"TAN")==0)
                        j=tan(j);
                         if(strcmp(coada[i],"log")==0||strcmp(coada[i],"LOG")==0)
                        j=log2(j);
                         if(strcmp(coada[i],"sqrt")==0||strcmp(coada[i],"SQRT")==0)
                        j=sqrt(j);
                         if(strcmp(coada[i],"ceil")==0||strcmp(coada[i],"CEIL")==0)
                        j=ceil(j);
                         if(strcmp(coada[i],"floor")==0||strcmp(coada[i],"FLOOR")==0)
                        j=floor(j);

               memset(temp,0,1000);
               inttostr(j,temp);
              stivaop.push(temp);
              continue;

            }//else

        ///////////daca e numar
            stivaop.push(coada[i]);

  }

  fout<<"Rezultatul expresiei este : "<<stivaop.top()<<endl;
  return 0;
}
int efunctie(char sir1[100])
{
 if(strcmp(sir1,"sin")==0||strcmp(sir1,"SIN")==0||strcmp(sir1,"cos")==0||strcmp(sir1,"COS")==0||strcmp(sir1,"max")==0||
    strcmp(sir1,"MAX")==0||strcmp(sir1,"min")==0||strcmp(sir1,"MIN")==0||strcmp(sir1,"asin")==0||strcmp(sir1,"ASIN")==0||
    strcmp(sir1,"acos")==0||strcmp(sir1,"ACOS")==0||strcmp(sir1,"tan")==0||strcmp(sir1,"TAN")==0||strcmp(sir1,"log")==0||
    strcmp(sir1,"LOG")==0||strcmp(sir1,"pow")==0||strcmp(sir1,"POW")==0||strcmp(sir1,"sqrt")==0||strcmp(sir1,"SQRT")==0||
    strcmp(sir1,"ceil")==0||strcmp(sir1,"CEIL")==0||strcmp(sir1,"floor")==0||strcmp(sir1,"FLOOR")==0)
        return 1;
 return 0;
}
 int functbin(char sir1[100])
 {
     if(strcmp(sir1,"max")==0||strcmp(sir1,"MAX")==0||strcmp(sir1,"min")==0||strcmp(sir1,"MIN")==0||
    strcmp(sir1,"pow")==0||strcmp(sir1,"POW")==0)
        return 1;
    return 0;

 }

int eoperator(char c)
{
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='^')
        return 1;
    return 0;
}

int assoc(char c)
{
    if(c == '^')
    return 2;
    return 1;
}

int prec(char c)
{
    if(c == '^')
        return 4;
    if(c == '*' || c == '/')
         return 3;
    if(c == '+' || c == '-')
         return 2;

    return 1;
}

int stare(char s[100])
{
    char temp[100]={ };

    int i,k=0,count2;
    //verific sintaxa corecta si memorez in structura variabila numele si valoarea variavilelor declarate
 for(i=0;i<strlen(s);i++,k++)
       if( !((int(s[i])>='A' && int(s[i])<='Z') || (int(s[i])>='a' && int(s[i])<='z') || (int(s[i])>='0' && int(s[i])<='9')||s[i]=='-'))
      {
          if(s[i]==' '&& (s[i+1]==' '|| s[i+1]=='='))
             {k--; continue;}

        if(s[i]=='=')
          {
                strncpy(temp,s,k);
              for(count2=0;count2<nrvar;count2++)
                if(strcmp(var[count2].nume,temp)==0)
              {  fout<<"Variabila "<<temp<<" declarata anterior a fost inlocuita."<<endl;
               break;
              }

                strcpy(var[count2].nume,temp);

              strcpy(s,s+i+1);
            while(s[0]==' ')
                s=s+1;

for(k=0;k<strlen(s);k++)
    if (!((s[k]>= '0' && s[k]<= '9')||s[0]=='-') )
     {   fout<<"Sintaxa gresita pentru "<<var[count2].nume<<endl;
         return -1; }

        strcpy(var[count2].val,s);
        nrvar++;
              return 0;
         }

            fout<<"Sintaxa gresita pentru "<<s<<" Variabilele pot fi compuse doar din litere si cifre."<<endl;
            return -1;
      }

fout<<"Sintaxa gresita pentru "<<s<<endl;;
return -1;
}

int strtoint (char s[101])
{
     int n= strlen(s);
    int sign = 1;
    int place = 1;
    int ret = 0;

    int i;
    for (i = n-1; i >= 0; i--, place *= 10)
    {
        int c = (int)s[i];
        switch (c)
        {
            case '-':
                if (i == 0) sign = -1;
                else
                  {fout<<"Sintaxa gresita."<<endl; return -1; }
                break;
            default:
                if (c >= '0' && c <= '9')   ret += (c - '0') * place;
                else
                     { return -1; }
        }
    }
return sign*ret;
}

void inttostr(int n, char temp[100])
{
    int lg=0,neg=0;
    int i=0,k=0;
    if(n<0)
    {neg=1; n=n*(-1);}

    int cn=n;

    while (cn >9 )
   {
      i++;
      cn /=10;
   }

if(neg==1)
  {
      temp[0]='-';
        k=i+1;
         lg=1;
  }
  else {k=i; lg=0;}

  temp[k+1]='\0';

   for(;k>=lg;k--)
   {
    int c = n%10;
    temp[k]= char(c+48);
        n/=10;
   }

}
