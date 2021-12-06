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
    char* vonal;
    int menetido;
    int atszallasok_szama;
    int bejart;
}dijkstra;

dijkstra dijk[500];

void clear(){
    system("cls");
}

int freeway(){
    exit(1);
}

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

void lancolo2(char* t1,int* t2, megallo* elem)
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
    int egyezes=0;
    megallo* csucs;
    megallo* ki=NULL;
    while (p[index]!=NULL)
    {
        csucs=p[index];
        while(csucs!=NULL){
            if (strcmp(indulas, csucs->megallo_nev)==0)
            {
                dijk[faszom].megallok_nevei=csucs->megallo_nev;
                dijk[faszom].vonal=csucs->metro_vonal;
                dijk[faszom].menetido=0;
                dijk[faszom].atszallasok_szama=0;
                dijk[faszom].bejart=0;
                egyezes=1;
                ki=csucs;
            }
            else
            {
                dijk[faszom].megallok_nevei=csucs->megallo_nev;
                dijk[faszom].vonal=csucs->metro_vonal;
                dijk[faszom].menetido=1000;
                dijk[faszom].atszallasok_szama=0;
                dijk[faszom].bejart=0;
            }
            faszom++;
            csucs=csucs->next;
        }
        index++;
    }
    if(egyezes==1)return ki;
    else return NULL;
}

int fel(megallo* csucs,megallo* csucsontul){
    int index=0;
    int egyez;
    int honnan;
    int hova;
    if(csucs==NULL) return 0;
    if (csucsontul==NULL)
    {
        return 0;
    }
    egyez=strcmp(dijk[index].megallok_nevei,csucs->megallo_nev);
    egyez=strcmp(dijk[index].vonal,csucs->metro_vonal);
    honnan=index;
    while(egyez!=0)
    {
        index++;
        egyez=strcmp(dijk[index].megallok_nevei,csucs->megallo_nev);
        egyez=strcmp(dijk[index].vonal,csucsontul->metro_vonal);
        honnan=index;  
    }
    index=0;
    egyez=strcmp(dijk[index].megallok_nevei,csucsontul->megallo_nev);
    egyez=strcmp(dijk[index].vonal,csucsontul->metro_vonal);
    hova=index;
    while(egyez!=0)
    {
        index++;
        egyez=strcmp(dijk[index].megallok_nevei,csucsontul->megallo_nev);
        egyez=strcmp(dijk[index].vonal,csucsontul->metro_vonal);
        hova=index;  
    }
    if(dijk[hova].menetido<csucsontul->menetido_f+dijk[honnan].menetido || !dijk[hova].bejart){
        dijk[hova].menetido=csucsontul->menetido_f+dijk[honnan].menetido;
        dijk[hova].bejart=1;
        dijk[hova].atszallasok_szama=dijk[honnan].atszallasok_szama;
    }
    return 1;
}

int le(megallo* csucs,megallo* csucsontul){
    int index=0;
    int egyez;
    int honnan;
    int hova;
    if(csucs==NULL) return 0;
    if (csucsontul==NULL)
    {
        return 0;
    }
    egyez=strcmp(dijk[index].megallok_nevei,csucs->megallo_nev);
    egyez=strcmp(dijk[index].vonal,csucs->metro_vonal);
    honnan=index;
    while(egyez!=0)
    {
        index++;
        egyez=strcmp(dijk[index].megallok_nevei,csucs->megallo_nev);
        egyez=strcmp(dijk[index].vonal,csucsontul->metro_vonal);
        honnan=index; 
    }
    index=0;
    egyez=strcmp(dijk[index].megallok_nevei,csucsontul->megallo_nev);
    egyez=strcmp(dijk[index].vonal,csucsontul->metro_vonal);
    hova=index;
    while(egyez!=0)
    {
        index++;
        egyez=strcmp(dijk[index].megallok_nevei,csucsontul->megallo_nev);
        egyez=strcmp(dijk[index].vonal,csucsontul->metro_vonal);
        hova=index;  
    }
    if(dijk[hova].menetido<csucsontul->menetido_l+dijk[honnan].menetido || !dijk[hova].bejart){
        dijk[hova].menetido=csucsontul->menetido_l+dijk[honnan].menetido;
        dijk[hova].bejart=1;
        dijk[hova].atszallasok_szama=dijk[honnan].atszallasok_szama;
    }
    return 1;
}

megallo* csomopont(megallo* csucs,megallo** p){
    int ind=0;
    int index=0;
    int egyez=1;
    int honnan,hova;
    megallo* mozgo;
    while (ind<sizeof(p)/2)
    {
        mozgo=p[ind];
        while(mozgo!=NULL){
            if(strcmp(csucs->megallo_nev,mozgo->megallo_nev)==0){
                if(mozgo!=csucs){
                    egyez=strcmp(dijk[index].megallok_nevei,csucs->megallo_nev);
                    while(egyez!=0)
                    {
                        index++;
                        egyez=strcmp(dijk[index].megallok_nevei,csucs->megallo_nev);
                        honnan=index;  
                    }
                    index=0;
                    egyez=strcmp(dijk[index].megallok_nevei,mozgo->megallo_nev);
                    while(egyez!=0)
                    {
                        index++;
                        egyez=strcmp(dijk[index].megallok_nevei,mozgo->megallo_nev);
                        hova=index;  
                    }
                    if(!dijk[hova].bejart){
                        dijk[hova].menetido=mozgo->atszallas+dijk[honnan].menetido;
                        dijk[hova].bejart=1;
                        dijk[hova].atszallasok_szama=dijk[honnan].atszallasok_szama;
                    }
                    return mozgo;
                }
                else mozgo=mozgo->next;
            }else{
                mozgo=mozgo->next;
            }
        }
        ind++;
    }
    return csucs;
}

void menetrend(megallo** p,megallo* csucs){
    int irany=0;
    int felfele=1;
    int lefele=1;
    megallo* csucsontul=csucs;
    if (irany==0)
    {
        while(felfele==1){
            felfele=fel(csucsontul,csucsontul->prev);
            csucsontul=csucsontul->prev;
        }
        irany++;
    }
    csucsontul=csucs;
    if (irany==1)
    {
        while(lefele==1){
            lefele=le(csucsontul,csucsontul->next);
            csucsontul=csucsontul->next;        
        }
        irany++;
    }
    csucsontul=csucs;
    megallo* ideiglenes=csucsontul;
    lefele=1;
    //átszállásos esetben//
    while(csucsontul->prev!=NULL){
         csucsontul=csomopont(csucsontul,p);
        if(ideiglenes!=csucsontul){
            while(lefele==1){
            lefele=le(csucsontul,csucsontul->prev);
            }
        }
        csucsontul=csucsontul->prev;
        ideiglenes=csucsontul;
    }
    csucsontul=csucs;
    felfele=1;
    //átszállásos esetben//
    while(csucsontul->next!=NULL){
        csucsontul=csomopont(csucsontul,p);
        if(ideiglenes!=csucsontul){
            while(lefele==1){
            lefele=le(csucsontul,csucsontul->next);
            csucsontul=csucsontul->next;
            }
        }
        csucsontul=csucsontul->next;
        ideiglenes=csucsontul;
    }
}

megallo* kivalaszto1(megallo** p){
    clear();
    printf("Honnan szeretnél indulni?\n");
    printf("Kérjük írja be a megálló nevét.\n");
    printf("(Kérjük space karakterek helyett aláhúzást használjon)\n\n");
    char indulo_allomas[80];
    scanf("%s",&indulo_allomas);
    megallo* ki=elokeszito(p,indulo_allomas);
    if (ki!=NULL)
    {
        printf("jó a név");
    }
    else
    {
        do
        {
            clear();
            printf("Nem létezik ilyen állomás!\n");
            printf("Kérjük próbálja újra\n\n");
            scanf("%s",&indulo_allomas);
            ki=elokeszito(p,indulo_allomas);
        } while (ki==NULL);
    }
    return ki;
}

megallo* letezike(megallo** p, char* cel){
    int index=0;
    int egyezes=0;
    int faszomgeci;
    megallo* megallo;
    megallo=p[index];
    while (p[index]!=NULL)
    {
        megallo=p[index];
        faszomgeci=strcmp(cel,megallo->megallo_nev);
        if(faszomgeci==0)return megallo;
        while (faszomgeci!=0)
        {
            faszomgeci=strcmp(cel,megallo->megallo_nev);
            if(faszomgeci==0)return megallo;
            else megallo=megallo->next;
            if(megallo==NULL) break;
        }
        index++;
    }
    return NULL;
}

megallo* kivalaszto2(megallo** p){
    clear();
    printf("Hova szeretnél menni?\n");
    printf("Kérjük írja be a megálló nevét.\n");
    printf("(Kérjük space karakterek helyett aláhúzást használjon)\n\n");
    char celallomas[80];
    scanf("%s",&celallomas);
    megallo* cel=letezike(p,celallomas);
    if(cel!=NULL){
        printf("jó a név");
    }
    else
    {
        do
        {
            clear();
            printf("Nem létezik ilyen állomás!\n");
            printf("Kérjük próbálja újra\n\n");
            scanf("%s",&celallomas);
            cel=letezike(p,celallomas);
        } while (cel==NULL);
    }
    return cel;
}

int kereses(megallo** p,megallo* ind, megallo* cel){
    clear();
    printf("Szeretnél keresést indítani ezekkel a megállókkal?\n");
    printf("Indulási állomás:%s\n", ind->megallo_nev);
    printf("Celállomás:%s\n\n", cel->megallo_nev);
    printf("1.Igen.\n");
    printf("2.Vissza a menübe.\n");
    fflush(stdin);
    int allapot = getc(stdin)-'0';
    fflush(stdin);
    if (allapot!=1 && allapot!=2)
    {
        do
        {
            clear();
            printf("Szeretnél keresést indítani ezekkel a megállókkal?\n");
            printf("Indulási állomás:%s\n", ind->megallo_nev);
            printf("Celállomás:%s\n\n", cel->megallo_nev);
            printf("1.Igen.\n");
            printf("2.Kilépés\n");
            printf("Nincs ilyen opció!\nKérjük próbáld újra.\n");
            allapot = getc(stdin)-'0';
            fflush(stdin);
        } while (allapot!=2 || allapot!=1);
    }
    if (allapot==1)
    {
        return 1;
    }
    else
    {
        freeway();
    }
}

void ido(megallo** p,megallo* cel){
    int index=0;
    char geci;
    int faszom=0;  
    megallo* csucs;
    megallo* ki=NULL;
    while (p[index]!=NULL)
    {
        csucs=p[index];
        while(csucs!=NULL){
            if (strcmp(cel->megallo_nev,csucs->megallo_nev)==0)
            {
                dijk[faszom].megallok_nevei=csucs->megallo_nev;
            }
        }
    }
    printf("Menetidő:%d", dijk[faszom].menetido);
    scanf("%c", &geci);
}

void befejezo(megallo** p,megallo* cel){
    ido(p,cel);
}

void menu(megallo** p){
    megallo* ind;
    megallo* celt;
    printf("Üdvözöllek a Metróban!\n");
    printf("A program megmutatja, mennyi idő eljutni A-ból, B-be,\n");
    printf("illetve hol kell átszállni.\n\n");
    printf("Kérjük válaszon!\n");
    printf("1.Keresés indítása\n");
    printf("2.Kilépés\n");
    int menuk = getc(stdin)-'0';
    fflush(stdin);
    if (menuk!=1 && menuk!=2)
    {
        do
        {
            clear();
            printf("Üdvözöllek a Metróban!\n");
            printf("A program megmutatja, mennyi idő eljutni A-ból, B-be,\n");
            printf("illetve hol kell átszállni.\n\n");
            printf("Kérjük válaszon!\n");
            printf("1.Keresés indítása\n");
            printf("2.Kilépés\n");
            printf("Nincs ilyen opció!\nKérjük próbáld újra.\n");
            menuk = getc(stdin)-'0';
            fflush(stdin);
        } while (menuk!=2 || menuk!=1);
    }
    if (menuk==1)
    {
        ind=kivalaszto1(p);
        celt=kivalaszto2(p);
    }
    else
    {
        freeway();
    }
    clear();
    if(kereses(p,ind,celt)==1){
        menetrend(p,ind);
    }
    befejezo(p,celt);
}

int main(){
    system("chcp 65001");
    clear();
    FILE* metrok_file=metro_megnyito("bemeneti1.txt");
    megallo** metro;
    metro=metro_foglalo(metro,1);
    metro=metro_beiro1(metro,metrok_file); 
    FILE* metrok_file2=metro_megnyito("bemeneti2.txt");
    metro=metro_beiro2(metro,metrok_file2);
    menu(metro);
    freeway();
}