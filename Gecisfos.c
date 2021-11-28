#include <stdio.h>
#include "string.h"
#include "stdlib.h"

typedef struct megallo{
    char* megallo_nev;
    char* metro_vonal;
    int atszallas;
    int menetido_f;
    int menetido_l;
    struct megallo *next, *prev;
}megallo;

FILE* metro_megnyito(char* file){
    return fopen(file,"r");
}

megallo** metro_foglalo(megallo **p,int metro_szam){
    if(metro_szam==1){
        p=(megallo**)malloc(metro_szam*sizeof(megallo*));
        return p;
    }
    else{
        megallo** t;
        t=p;
        p=(megallo**)malloc(metro_szam*sizeof(megallo*));
        for (int i = 0; i < metro_szam-1; i++)
        {
            p[i]=t[i];
        }
        free(t);
        return p;
    }
}

megallo* lancol(char* uj,megallo* elem){
    megallo* temp=(megallo*)malloc(sizeof(megallo));
    if(strlen(uj)==2) {
        temp->metro_vonal=(char*)malloc(sizeof(char)*3);
        strcpy(temp->metro_vonal,uj);
        temp->metro_vonal[2]='\0';
        temp->next=elem;
        return temp;
    }else{
        if(elem==NULL){
            temp=elem;
        }
        temp->metro_vonal=(char*)malloc(sizeof(char)*2);
        strcpy(temp->metro_vonal,elem->metro_vonal);
        temp->megallo_nev=(char*)malloc(sizeof(char)*(strlen(uj)+1));
        strcpy(temp->megallo_nev,uj);
        temp->megallo_nev[strlen(uj)]='\0';
        temp->next=elem;
        return temp;
    }

}

megallo** metro_beiro(megallo** p, FILE* fajl){
    int metrok_szama=0;
    p[metrok_szama]=NULL;
    int karakter=0;
    char temp[50];
    while(!feof(fajl))
    {
        char c = fgetc(fajl);
        if(c==' '){
            temp[karakter]='\0';
            p[metrok_szama]=lancol(temp,p[metrok_szama]);
            karakter=0;
        }
        else if(c == '\n')
        {
            p[metrok_szama]=lancol(temp,p[metrok_szama]);
            karakter=0;
            metrok_szama++;
            p=metro_foglalo(p,metrok_szama+1);
            p[metrok_szama]=NULL;
            temp[karakter]='\0';
        }
        else{
            temp[karakter]=c;
            karakter++;
        }

    }
    return p;
}

faszxd

int main(){
    FILE* metrok_file=metro_megnyito("bemeneti1.txt");
    megallo** metro;
    metro=metro_foglalo(metro,1);
    metro=metro_beiro(metro,metrok_file); 
}