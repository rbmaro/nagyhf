#include <stdio.h>
#include <string.h>

typedef struct{
    cim;lista;kover;dolt;kod;link;
}tipus;

void enter(int *p){
    if (*p==0)
    {
        printf("<p>\n");
        *p=1;
    }
    else{
        printf("</p>\n");
        *p=0;
    }
}

void cimes(char t[]){
    int j=0,k=0;
    for (int i = 0; i < 6; i++)
    {
        if (t[i]=="#")
        {
            j++;
        }
    }
    printf("<h%d>", &j);
    while (t[k]!="\n")
    {
        printf("%c", t[k++]);
    }
    printf("</h1>\n");
}

void listas(char t[]){
    if (t[0]=="-")
    {
        /* code */
    }
    
}

void dagi(char t[]){
    int j=0,k=0,l=0;
    while (t[j]!="\n"){
        if (t[j]=="*"){
            if (l==0)
            {
                l=1;
                if (k=0)
                {
                printf("<em>");
                j++,k=1;
                }
                else{
                printf("</em>");
                j++,k=0;
                }
            }
            else{
                l=0;
            }
        }
        else{
            printf("%c",t[j++]);
        }
    }
}

void pizza(char t[]){
    int j=0,k=0;
    while (t[j]!="\n"){
        if (t[j]=="*"){
            if (k=0)
            {
                printf("<em>");
                j++,k=1;
            }
            else{
                printf("</em>");
                j++,k=0;
            }
        }
        else{
            printf("%c",t[j++]);
        }
    }
}

void matrix(char t[]){
    char apple[100];
    int j=0, c=0, k,l=0;
    while (t[j]!="\n")
    {
        if (t[j]=="`" && c==0)
        {
            k=j+1;
            while (t[k]!="`")
            {
                apple[l++]=t[k++];
            }
            c=c+1;
            break;
        }
    }
    for (int i = 0; i < j; i++)
    {
        printf("%c", t[i]);
    }
    for (int i = 0; i < l; i++)
    {
        printf("%c", apple[i]);
    }
    int i=k+j;
    while (t[i]!="\n")
    {
        printf("%c", t[i++]);
    }
}

void zelda(char t[]){
    char cim[100]={0};
    char link[100]={0};
    int i=0, j, k=0,l=0, m, n;
    while (t[i]!="\n"){
        if (t[i]=="[")
        {
            m=i-1;
            j=i+1;
            while (t[j]!="]")
            {
                cim[k++]=t[j++];
            }
        }
        if (t[i]=="(")
        {
            j=i+1;
            while (t[j]!=")")
            {
                link[l++]=t[j++];
            }
            n=j+1;
        }
    for (int x= 0; i < m; x++)
    {
        printf("%c", t[x]);
    }
    printf("<a href=");
    printf("\"");
    for (int x=0; x < k; x++)
    {
        printf("%c", link[x]);
    }
    printf("\">");
    for (int x = 0; x < l; x++)
    {
        printf("%c", cim[x]);
    }
    printf("</a>");
    while (t[n]!="n")
    {
        printf("%c", t[n++]);
    }  
    }
}

int main(){
    char bemeneti[1000]={0};
    int i=0;
    int p=0;
    while (fgets(bemeneti[i],1000,stdin)!=NULL)
    {
        
    }
    return 0;
}