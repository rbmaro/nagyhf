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

megallo* lancolo(char* uj,megallo* elem){
    megallo* nev=(megallo*)malloc(sizeof(megallo));
    if(strlen(uj)==2) {
        nev->metro_vonal=(char*)malloc(sizeof(char)*3);
        strcpy(nev->metro_vonal,uj);
        nev->metro_vonal[2]='\0';
        nev->next=elem;
        return nev;
    }else{
        if(elem==NULL){
            nev=elem;
        }
        nev->metro_vonal=(char*)malloc(sizeof(char)*2);
        strcpy(nev->metro_vonal,elem->metro_vonal);
        nev->megallo_nev=(char*)malloc(sizeof(char)*(strlen(uj)+1));
        strcpy(nev->megallo_nev,uj);
        nev->megallo_nev[strlen(uj)]='\0';
        nev->next=elem;
        return nev;
    }
}

megallo* lancolo2(char* t1,int* t2, megallo* elem)
{
    int beirt=0;
    int nevek;
    int hely=0;
    while (beirt == 0)
    {
        nevek=strcmp(t1,elem->megallo_nev);
        if (nevek=0)
        {
            elem->atszallas=t2[hely++];
            elem->menetido_f=t2[hely++];
            elem->menetido_l=t2[hely];
            hely=0;
        }
        else
        {
            elem->next=elem;
        }
    }
    return elem;
}

megallo** metro_beiro1(megallo** p, FILE* fajl){
    int metrok_szama=0;
    p[metrok_szama]=NULL;
    int karakter=0;
    char nev[50];
    while(!feof(fajl))
    {
        char c = fgetc(fajl);
        if(c==' ')
        {
            nev[karakter]='\0';
            p[metrok_szama]=lancolo(nev,p[metrok_szama]);
            karakter=0;
        }
        else if(c == '\n')
        {
            p[metrok_szama]=lancolo(nev,p[metrok_szama]);
            karakter=0;
            metrok_szama++;
            p=metro_foglalo(p,metrok_szama+1);
            p[metrok_szama]=NULL;
            nev[karakter]='\0';
        }
        else
        {
            nev[karakter]=c;
            karakter++;
        }
    }
    return p;
}

megallo** metro_beiro2(megallo** p, FILE* fajl){
    char nev[50]={0};
    int idok[3]={0};
    int ido=0;
    int metrok_szama=0;
    int space=0;
    int karakter=0;
    while (!feof(fajl))
    {
        char c=fgetc(fajl);
        if (c == '\n')
        {
            p[metrok_szama]=lancolo2(nev,idok,p[metrok_szama]);
            karakter=0;
            metrok_szama++;
            p[metrok_szama]=NULL;
            nev[karakter]='\0';
        }
        else
        {
            if (c == ' ')
            {
                space++;
                if (space==4)
                {
                    nev[karakter]='\0';
                    p[metrok_szama]=lancolo2(nev,idok,p[metrok_szama]);
                    karakter=0;
                    ido=0;
                    space=0;
                }
            }
            else
            {
                if (space == 0)
                {
                    nev[karakter]=c;
                    karakter++;
                }
                else
                {
                    idok[ido++]=c;
                }
            }
        }
    }
    return p;
}

int main(){
    FILE* metrok_file=metro_megnyito("bemeneti1.txt");
    megallo** metro;
    metro=metro_foglalo(metro,1);
    metro=metro_beiro1(metro,metrok_file); 
    FILE* metrok_file2=metro_megnyito("bemeneti2.txt");
    metro=metro_beiro2(metro,metrok_file2);
}
