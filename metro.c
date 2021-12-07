/**
 * @file
 * @section LEÍRÁS
 * A fájl kezeli a játék változóit, a menetét
 * */
#include <stdio.h>
#include "string.h"
#include "stdlib.h"

/**A megállók adatait tároló struktúra**/
typedef struct megallo{
    //*A megálló neve*/
    char* megallo_nev;
    //*A megállón átmenő metró*/
    char* metro_vonal;
    //*Az átszálláshoz szükséges idő*/
    int atszallas;
    //*A listában a megállóhoz közvetlen "felfele" lévő megálló eljutásához szükséges menetidő*/
    int menetido_f;
    //*A listában a megállóhoz közvetlen "lefele" lévő megálló eljutásához szükséges menetidő*/
    int menetido_l;
    //*A megállóhoz tartozó előző és következő megállóra mutató pointer*/
    struct megallo *next, *prev;
}megallo;

/**A dijkstra algoritmushoz kellő adatat tároló struktúra **/
typedef struct dijkstra{
    //*az egy megállóra mutató pointer*/
    megallo* megallo;
    //*A megállóhoz szükséges menetidő*/ 
    int menetido;
    //*Amegállóhoz való eljutáshoz kellő átszállások száma*/
    int atszallasok_szama;
    //*Az átszállóhelyek neve*/
    char* atszallasok[16];
    //*Megmutatja, hogy a megálló be volt-e már járva*/
    int bejart;
}dijkstra;

//*Dijksra struktúrához tartozó globális változó*/
dijkstra dijk[500];

/**
 * Kitörli a cmd-t
 * @return nincs
 */
void clear(){
    system("cls");
}

/**
 * Felszabadítja a memóriát
 * @param p-re lett foglalva a memória 
 * @return A kilépés helyes értéke 1
 */
int freeway(megallo** p){
    int index=0;
    while(index<sizeof(p)/2){
        free(p[index]->metro_vonal);
        while(p[index]!=NULL){
            megallo* szabad=p[index];
            p[index]=p[index]->next;
            free(szabad->megallo_nev);
            free(szabad);
        }
        index++;
    }
    free(p);
    exit(1);
}

/**
 * Megnyitja a bemeneti fájlokat
 * @param file Egy bemeneti fájl
 * @return Az első bemeneti fájt adja vissza 
 */
FILE* metro_megnyito(char* file){
    return fopen(file,"r");
}

/**
 * Lefoglalja a programnak dinamikusan a memóriahelyeket
 * @param p-re lesz foglalva a memórai
 * @param metro_szam A fájlban szereplő összes metró darabszáma
 * @return A metrókat tartalmazó tömb 
 */
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

/**
 * Beláncolja a struktúrát
 * @param uj Az uj megálló neve
 * @param elem A metró vonal következő megállója
 * @return Az új megálló neve 
 */
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

/**
 * Beirja a 2.bemeneti fájl adatait//
 * @param t1 A megálló neve
 * @param t2 A menetidőtket és az átszállást tartalmazó tömb
 * @param elem Megálló neve
 * @return Nincs
 */
void lancolo2(char* t1,int* t2, megallo* elem)
{
    int beirt=0;
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

/**
 * Beírja a listába az 1. bemeneti fájl adatait 
 * @param p Az adatokat tartalmazó lista
 * @param fajl Az első bemeneti fájl
 * @return A metrókat tartalmazó tömb
 */
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

/**
 * Beírja a 2. bemeneti fájl adatait
 * @param p A metrókat tartalmazó tömb
 * @param fajl A 2. bemeneti fájl neve
 * @return A metrókat tartalmazó tömb
 */
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

/**
 * Előkészíti a Dijkstra algoritmust
 * @param p A metrókat tartalmazó tömb
 * @param indulas Az induló megálló neve
 * @return Az egyező megálló neve 
 */
megallo* elokeszito(megallo **p, char* indulas){
    int sorszam=0;  
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
                dijk[sorszam].megallo=csucs;
                dijk[sorszam].menetido=0;
                dijk[sorszam].atszallasok_szama=0;
                dijk[sorszam].bejart=0;
                for (int i = 0; i < 16; i++)
                {
                    dijk[sorszam].atszallasok[i]="\0";
                }
                egyezes=1;
                ki=csucs;
            }
            else
            {
                dijk[sorszam].megallo=csucs;
                dijk[sorszam].menetido=1000;
                dijk[sorszam].atszallasok_szama=0;
                dijk[sorszam].bejart=0;
                for (int i = 0; i < 16; i++)
                {
                    dijk[sorszam].atszallasok[i]="\0";
                }
            }
            sorszam++;
            csucs=csucs->next;
        }
        index++;
    }
    if(egyezes==1)return ki;
    else return NULL;
}

/**
 * Dijkstra a listában feljebb lévő elemekre
 * @param csucs Az állomás neve
 * @param csucsontul A csúcshoz képest a következő állomás a listában felfele
 * @return A függvény helyes return értéke 1 
 */
int fel(megallo* csucs,megallo* csucsontul){
    int index=0;
    int honnan;
    int hova;
    if(csucs==NULL) return 0;
    if (csucsontul==NULL)
    {
        return 0;
    }
    while(dijk[index].megallo!=csucs)
    {
        index++;  
    }
    honnan=index;
    index=0;
    while(dijk[index].megallo!=csucsontul)
    {
        index++;
    }
    hova=index;
    if(!dijk[hova].bejart || dijk[hova].menetido>csucsontul->menetido_f+dijk[honnan].menetido){
        dijk[hova].menetido=csucsontul->menetido_f+dijk[honnan].menetido;
        dijk[hova].bejart=1;
        dijk[hova].atszallasok_szama=dijk[honnan].atszallasok_szama;
        for (int i = 0; i < 16; i++)
        {   
            if(dijk[honnan].atszallasok[i]=="\0")break;   
            dijk[hova].atszallasok[i]=dijk[honnan].atszallasok[i];
        }

    }
    return 1;
}

/**
 * Dijkstra a listában lejjebb lévő elemekre
 * @param csucs Az állomás neve
 * @param csucsontul A csúcshoz képest a következő állomást a listában lefele
 * @return A függvény helyes kimeneti értéke 1
 */
int le(megallo* csucs,megallo* csucsontul){
    int index=0;
    int honnan;
    int hova;
    if(csucs==NULL) return 0;
    if (csucsontul==NULL)
    {
        return 0;
    }
    while(dijk[index].megallo!=csucs)
    {
        index++;  
    }
    honnan=index;
    index=0;
    while(dijk[index].megallo!=csucsontul)
    {
        index++;
    }
    hova=index;
    if(!dijk[hova].bejart || dijk[hova].menetido>csucsontul->menetido_l+dijk[honnan].menetido){
        dijk[hova].menetido=csucsontul->menetido_l+dijk[honnan].menetido;
        dijk[hova].bejart=1;
        dijk[hova].atszallasok_szama=dijk[honnan].atszallasok_szama;
        for (int i = 0; i < 16; i++)
        {      
            if(dijk[honnan].atszallasok[i]=="\0")break;   
            dijk[hova].atszallasok[i]=dijk[honnan].atszallasok[i];
        }
    }
    return 1;
}

/**
 * A megálló benne van-e már az átszállásokban
 * @param atszallasok Az átszállásokat tartalmazó tömb 
 * @param atszallas A megálló
 * @return Ha már benne van, akkor a helyes return érték 1, ha nem, akkor 0 
 */
int benne(megallo** atszallasok,megallo* atszallas){
    int i=0;
    while(atszallasok[i]!=0){
        if(strcmp(atszallas->megallo_nev,atszallasok[i]->megallo_nev)==0){
            return 1;
        }
        i++;
    }
    return 0;
}

/**
 * Átszállás helyeket keres
 * @param csucs A megálló neve
 * @param p A metrókat tartalmazó tömb
 * @param atszallasok Az átszállásokat tartalazó tömb
 * @return visszaadja a megállót ahol van átszállás 
 */
megallo* csomopont(megallo* csucs,megallo** p,megallo** atszallasok){
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
                    index=0;
                    while(dijk[index].megallo!=mozgo)
                    {
                        index++;
                    }
                    if(dijk[index].bejart==1)break;
                    index=0;
                    while(dijk[index].megallo!=csucs)
                    {
                        index++;
                    }
                    honnan=index;
                    index=0;
                    while(dijk[index].megallo!=mozgo)
                    {
                        index++;
                    }
                    hova=index;
                    if(!dijk[hova].bejart){
                        if(benne(atszallasok,dijk[hova].megallo)){
                            dijk[hova].atszallasok_szama=dijk[honnan].atszallasok_szama;
                            dijk[hova].menetido=dijk[honnan].menetido;
                            for (int i = 0; i < 16; i++)
                            {      
                                if(dijk[honnan].atszallasok[i]=="\0")break;   
                                dijk[hova].atszallasok[i]=dijk[honnan].atszallasok[i];
                            }
                        }
                        else{
                            dijk[hova].atszallasok_szama=dijk[honnan].atszallasok_szama+1;
                            dijk[hova].menetido=mozgo->atszallas+dijk[honnan].menetido;
                            for (int i = 0; i < 16; i++)
                            {      
                                if(dijk[honnan].atszallasok[i]=="\0")break;   
                                dijk[hova].atszallasok[i]=dijk[honnan].atszallasok[i];
                            }
                            dijk[hova].atszallasok[dijk[hova].atszallasok_szama-1]=dijk[hova].megallo->megallo_nev;
                        }
                        dijk[hova].bejart=1;
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
}

/**
 * A dijkstra algoritmus irányításáért felelős függvény
 * @param csucs A megálló neve
 * @param index index
 * @param atszallasok A átszállásokat tartalmazó tömb
 * @param p A metrókat tartalmazó tömb
 */
void vegigjar(megallo* csucs,int* index,megallo** atszallasok,megallo** p){
    megallo* csucsontul=csucs;
    int irany=0;
    int felfele=1;
    int lefele=1;
    if (irany==0)
    {
        while(felfele==1){
            megallo* ideiglenes=csomopont(csucsontul,p,atszallasok);
            if(ideiglenes!=NULL){
                atszallasok[*index]=ideiglenes;
                *index+=1;
            }
            felfele=fel(csucsontul,csucsontul->prev);
            csucsontul=csucsontul->prev;
        }
        irany++;
    }
    csucsontul=csucs;
    if (irany==1)
    {
        while(lefele==1){
            megallo* ideiglenes=csomopont(csucsontul,p,atszallasok);
            if(ideiglenes!=NULL){
                atszallasok[*index]=ideiglenes;
                *index+=1;
            }
            lefele=le(csucsontul,csucsontul->next);
            csucsontul=csucsontul->next;        
        }
        irany++;
    }
}

/**
 * Maga a Dijkstra algoritmus
 * @param csucs A megálló neve
 * @param p A metrókat tartalmazó tömb
 * @return Nincs
 */
void menetrend(megallo* csucs,megallo** p){
    int index=0;
    megallo* atszallasok[300];
    for (int i = 0; i < 300; i++)
    {
        atszallasok[i]=NULL;
    }
    vegigjar(csucs,&index,atszallasok,p);
    int i=0;
    while(atszallasok[i]!=NULL){
        vegigjar(atszallasok[i],&index,atszallasok,p);
        i++;
    }
}

/**
 * Az induló állomás kiválasztásáért felelős függvény
 * @param p A metrókat tartalmazó tömb
 * @return Az induló állomás neve
 */
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

/**
 * A célállomás létezéséért felelős függvény
 * @param p A metrókat tartalmazó tömb
 * @param cel A cél állomás neve
 * @return A célállomás neve,ha létezik
 */
megallo* letezike(megallo** p, char* cel){
    int index=0;
    int egyezes=0;
    int sorszamok;
    megallo* megallo;
    megallo=p[index];
    while (p[index]!=NULL)
    {
        megallo=p[index];
        sorszamok=strcmp(cel,megallo->megallo_nev);
        if(sorszamok==0)return megallo;
        while (sorszamok!=0)
        {
            sorszamok=strcmp(cel,megallo->megallo_nev);
            if(sorszamok==0)return megallo;
            else megallo=megallo->next;
            if(megallo==NULL) break;
        }
        index++;
    }
    return NULL;
}

/**
 * A célállomást kiválasztó függvény
 * @param p A metrókat tartalmazó tömb
 * @return A célállomás neve
 */
megallo* kivalaszto2(megallo** p){
    clear();
    printf("Hova szeretnél menni?\n");
    printf("Kérjük írja be a megálló nevét.\n");
    printf("(Kérjük space karakterek helyett aláhúzást használjon)\n\n");
    char celallomas[80];
    scanf("%s",&celallomas);
    megallo* cel=letezike(p,celallomas);
    if(cel!=NULL){
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

/**
 * A végső keresésért felelős függvény
 * @param p A metrókat tartalmazó tömb
 * @param ind Az induló állomás neve
 * @param cel A célállomás neve
 * @return megadja futhat e tovább a program
 */
int kereses(megallo** p,megallo* ind, megallo* cel){
    clear();
    printf("Szeretnél keresést indítani ezekkel a megállókkal?\n");
    printf("Indulási állomás:%s\n", ind->megallo_nev);
    printf("Celállomás:%s\n\n", cel->megallo_nev);
    printf("1.Igen.\n");
    printf("2.Vissza a menübe.\n");
    fflush(stdin);
    fflush(stdin);
    int allapot = getc(stdin)-'0';
    fflush(stdin);
    while(1){
        switch(allapot){
            case 1:
                return 1;
                break;
            case 2:
                clear();
                menu(p);
                break;
            default:
                clear();
                printf("Szeretnél keresést indítani ezekkel a megállókkal?\n");
                printf("Indulási állomás:%s\n", ind->megallo_nev);
                printf("Celállomás:%s\n\n", cel->megallo_nev);
                printf("1.Igen.\n");
                printf("2.Kilépés\n");
                printf("Nincs ilyen opció!\nKérjük próbáld újra.\n");
                allapot = getc(stdin)-'0';
                fflush(stdin);
                break;
        }
    }
}

/**
 * A kimeneti értékek kiírásáért felelős függvény
 * @param p A metrókat tartalmazó tömb
 * @param cel A célállomás neve
 * @return nincs
 */
void befejezes(megallo** p,megallo* cel){
    int sorszam=0;
    int allapot=0;
    int str;
    while(cel!=dijk[sorszam].megallo){
        sorszam++;
    }
    printf("Átszállások:");
    for (int i = 0; i < dijk[sorszam].atszallasok_szama; i++)
    {
        printf(" %s",dijk[sorszam].atszallasok[i]);
    }
    printf("\nMenetidő:%d perc\n", dijk[sorszam].menetido);
    printf("\nnyomj spacet a kilépéshez");
    char kilep=getc(stdin);
    while (kilep!=' ')
    {
        kilep=getc(stdin);
    }
}

/**
 * A program befejezését elindító függgvény
 * @param p A metrókat tartalmazó tömb
 * @param cel A cél állomás neve
 * @return nincs
 */
void befejezo(megallo** p,megallo* cel){
    befejezes(p,cel);
    freeway(p);
}

/**
 * A menük készítő függvény
 * @param p A metrókat tartalmazó tömb
 * @return nincs
 */
void menu(megallo** p){
    megallo* ind;
    megallo* celt;
    megallo* atszallas;
    printf("Üdvözöllek a Metróban!\n");
    printf("A program megmutatja, mennyi idő eljutni A-ból, B-be,\n");
    printf("illetve hol kell átszállni.\n\n");
    printf("Kérjük válaszon!\n");
    printf("1.Keresés indítása\n");
    printf("2.Kilépés\n");
    int menuk = getc(stdin)-'0';
    fflush(stdin);
    switch(menuk){
        case 1:
            ind=kivalaszto1(p);
            celt=kivalaszto2(p);
            break;
        case 2:
            freeway(p);
            break;
        default:
            clear();
            printf("Nincs ilyen opció!\nKérjük próbáld újra.\n");
            menu(p);
            break;
    }
    clear();
    if(kereses(p,ind,celt)==1){
        menetrend(ind,p);
    }
    befejezo(p,celt);
}

/**
 * Main függvény
 * @return nincs, mert a program egy másik függvénnyel fejeződik be
 */
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
}