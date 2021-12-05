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

typedef struct dijkstra{
    char* megallok_nevei;
    int menetido;
    int atszallasok_szama;
    int bejart;
}dijkstra;

dijkstra dijk[500]; //AZT BASSZAM KI A DINAMIKUS TOMBODET//

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
        nev->megallo_nev=NULL;
        strcpy(nev->metro_vonal,uj);
        nev->metro_vonal[2]='\0';
        nev->next=elem;
        return nev;
    }else{
        if(elem->megallo_nev==NULL){
            free(nev);
            nev=elem;
            nev->metro_vonal=elem->metro_vonal;
            nev->megallo_nev=(char*)malloc(sizeof(char)*(strlen(uj)+1));
            strcpy(nev->megallo_nev,uj);
            nev->megallo_nev[strlen(uj)]='\0';
            elem->prev=nev;
        }else{
        nev->metro_vonal=elem->metro_vonal;
        nev->megallo_nev=(char*)malloc(sizeof(char)*(strlen(uj)+1));
        strcpy(nev->megallo_nev,uj);
        nev->megallo_nev[strlen(uj)]='\0';
        elem->prev=nev;
        nev->next=elem;
        return nev;
    }
    }
}

megallo* lancolo2(char* t1,int* t2, megallo* elem)
{
    int beirt=0;
    int nevek;
    int hely=0;
    while (beirt == 0)
    {
        if (strcmp(t1,elem->megallo_nev)==0)
        {
            elem->atszallas=t2[hely++];
            elem->menetido_f=t2[hely++];
            elem->menetido_l=t2[hely];
            beirt++;
        }
        else
        {
            elem=elem->next;
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
            nev[karakter]='\0';
            p[metrok_szama]=lancolo(nev,p[metrok_szama]);
            karakter=0;
            p[metrok_szama]->prev=NULL;
            metrok_szama++;
            p=metro_foglalo(p,metrok_szama+1);
            p[metrok_szama]=NULL;
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
            nev[karakter]='\0';
            lancolo2(nev,idok,p[metrok_szama]);
            karakter=0;
            space=0;
            ido=0;
            metrok_szama++;
        }
        else
        {
            if (c == ' ')
            {
                space++;
                if (space==4)
                {
                    nev[karakter]='\0';
                    lancolo2(nev,idok,p[metrok_szama]);
                    karakter=0;
                    ido=0;
                    space=0;
                }
                else
                {
                    c=fgetc(fajl);
                    idok[ido++]=c-'0';
                }
            }
            else
            {
                if (space == 0)
                {
                    nev[karakter]=c;
                    karakter++;
                }

            }
        }
    }
    return p;
}

megallo* elokeszito(megallo **p, char* indulas){

    int faszom=0;   
    int index=0;
    megallo* csucs;
    megallo* jocsucs;
    while (csucs!=NULL)
    {
        csucs=p[index];
        while(csucs!=NULL){
            if (strcmp(indulas, csucs->megallo_nev)==0)
            {
                dijk[faszom].megallok_nevei=csucs->megallo_nev;
                dijk[faszom].menetido=0;
                dijk[faszom].atszallasok_szama=0;
                dijk[faszom].bejart=0;
                jocsucs=csucs;
            }
            else
            {
                dijk[faszom].megallok_nevei=csucs->megallo_nev;
                dijk[faszom].menetido=150;
                dijk[faszom].atszallasok_szama=0;
                dijk[faszom].bejart=0;
            }
            faszom++;
            csucs=csucs->next;
        }
        index++;
    }
    return jocsucs;
}

/*
int csomopont(int* index,megallo* csucs,megallo** p,megallo** ujcsucs){
    int ind=0;
    megallo* mozgo;
    while (ind<sizeof(p)/2)
    {
        if(ind==*index)ind++;
        mozgo=p[ind];
        while(mozgo!=NULL){
            if(strcmp(csucs->megallo_nev,mozgo->megallo_nev)==0){
                *index=ind;
                ujcsucs=mozgo;
                return 1;
            }else{
                mozgo=mozgo->next;
            }
        }
        ind++;
    }
    ujcsucs=NULL;
    return 0;
}

void beirprev(megallo** p, megallo* csucs){
        megallo* kovi;
    int gecisfaszom=0;
    int eddig=0;
    int feltetel1=0, feltetel2=0;
    kovi=csucs->prev;
    while (feltetel1==0)
    {
        if(!strcmp(csucs->megallo_nev,dijk[gecisfaszom].megallok_nevei)){
            eddig=dijk[gecisfaszom].menetido;
            feltetel1++;
        }else gecisfaszom++;
    }
    gecisfaszom=0;
    while (feltetel2==0)
    {
        if(!strcmp(kovi->megallo_nev,dijk[gecisfaszom].megallok_nevei)){
            if((csucs->menetido_f+eddig)<dijk[gecisfaszom].menetido){
                dijk[gecisfaszom].menetido=csucs->menetido_f+eddig;
                feltetel2++;
            }
        }else gecisfaszom++;
    }
}

void beirnext(megallo** p, megallo* csucs){
    megallo* kovi;
    int gecisfaszom=0;
    int eddig=0;
    int feltetel1=0, feltetel2=0;
    kovi=csucs->next;
    while (feltetel1==0)
    {
        if(!strcmp(csucs->megallo_nev,dijk[gecisfaszom].megallok_nevei)){
            eddig=dijk[gecisfaszom].menetido;
            feltetel1++;
        }else gecisfaszom++;
    }
    while (feltetel2==0)
    {
        if(!strcmp(kovi->megallo_nev,dijk[gecisfaszom].megallok_nevei)){
            if((csucs->menetido_l+eddig)<dijk[gecisfaszom].menetido){
                dijk[gecisfaszom].menetido=csucs->menetido_l+eddig;
                feltetel2++;
            }else return;
        }else gecisfaszom++;
    }
}

void menetrend(megallo** p,megallo* csucs,int index){
    megallo* ujcsucs;
    if(csucs==0)return; //kilépési feltétel//
    if(csomopont(&index,csucs,p,&ujcsucs)){
        beirnext(p,csucs);
        menetrend(p,csucs,index); //atszallas es gyerekei
        beirprev(p,ujcsucs);
        menetrend(p,ujcsucs->prev,index); //elozo es gyerekei
        beirnext(p,ujcsucs);
        menetrend(p,ujcsucs->next,index); //kovetkezo es gyerekei
    }else{
        beirprev(p,csucs);
        menetrend(p,csucs->prev,index); //elozo es gyerekei
        beirnext(p,csucs);
        menetrend(p,csucs->next,index); //kovetkezo es gyerekei
    }
}
*/

int fel(megallo**p, megallo* csucs){
    int index=0;
    int egyez;
    if (csucs==NULL)
    {
        return 0;
    }
    egyez=strcmp(dijk[index].megallok_nevei,csucs->megallo_nev);
    while(egyez!=0)
    {
        index++;
        egyez=strcmp(dijk[index].megallok_nevei,csucs->megallo_nev);  
    }
    if(!dijk[index].bejart){
        dijk[index].menetido=csucs->menetido_f;
        dijk[index].bejart=1;
    }
    return 1;
}

int le(megallo**p, megallo* csucs){
    int index=0;
    if (csucs==NULL)
    {
        return 0;
    }
    int egyez=strcmp(dijk[index].megallok_nevei,csucs->megallo_nev);
    while(!egyez)
    {
        egyez=strcmp(dijk[index].megallok_nevei,csucs->megallo_nev);  
        index++;
    }
    if(!dijk[index].bejart){
        dijk[index].menetido=csucs->menetido_l;
        dijk[index].bejart=1;
    }
    return 1;
}


void menetrend(megallo** p,megallo* csucs,int index){
    int irany=0;
    int felfele=1;
    int lefele=1;
    megallo* csucsontul=csucs;
    if (irany==0)
    {
        while(felfele==1){
            csucsontul=csucsontul->prev;
            felfele=fel(*p,csucsontul);
        }
        irany++;
    }
    csucsontul=csucs;
    if (irany==1)
    {
        while(lefele==1){
            csucsontul=csucsontul->next;
            lefele=le(*p,csucsontul);
        }
        irany++;
    }
    //átszállásos esetben//
}

int main(){
    FILE* metrok_file=metro_megnyito("bemeneti1.txt");
    megallo** metro;
    metro=metro_foglalo(metro,1);
    metro=metro_beiro1(metro,metrok_file); 
    FILE* metrok_file2=metro_megnyito("bemeneti2.txt");
    metro=metro_beiro2(metro,metrok_file2);
    megallo* csucs=elokeszito(metro,"Mexikói_út");
    menetrend(metro,csucs,0);
}