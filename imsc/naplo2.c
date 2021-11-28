#include <stdio.h>
int main(){
    char c; int i; int j; int k; int l; int m; int h; int o; int zsg;
    double data[18]={0}; double adat[8]={0};
    for (i=0; i<142; i++){ //0-elo,1-gyak,2-lab,3-kzh1,4-zkh2,5-kzh3,6-kzh4,7-kzh5,8-kzh6,9-nzh1,10-nzh2,11-h1,12-h2,13-h3,14-h+,15-b,16-imdc,17-ave//
        scanf("%c", &c);} //0-5,1-4,2-3,3-2,4-1,5-db,6-max,7-feltetel//
    while (scanf("%c", &c)!=EOF){
        for ( zsg=0; zsg<17; zsg++){
            data[zsg]=0;}
        adat[7]=0;
        for (k=0; k<6; k++){                 
            scanf("%c", &c);}
        for (l=0; l<17; l++){ 
            scanf("%lf", &data[l]); scanf("%c", &c);}
        if (data[0]<0.7 || data[1]<0.7 || data[2]<0.7){
            adat[7]++;}
        if ((data[3]<4 && data[4]<4) || (data[5]<4 && data[6]<4) || (data[7]<4 && data[8]<4)){
            adat[7]++;}    
        if ((data[9]+data[10])<40){
            adat[7]++;}
        if (((data[11]+data[12]+data[13])<6) || (data[13]<4)){
            adat[7]++;}
        for (m=3; m<8; m++){ 
            if (data[m+1]>data[m]){
                data[m]=data[m+1];m++;}}
        adat[6]=data[3]+data[5]+data[7]+data[9]+data[10]+data[11]+data[12]+data[13]+data[14]+data[15];
        if (adat[7]>0){
            data[17]++;adat[4]++;adat[5]++;}
        else{
        if (adat[6]>112){
            adat[0]++;adat[5]++;data[17]+=5;}
        else{if (adat[6]<113 && adat[6]>94){
                adat[1]++;adat[5]++;data[17]+=4;}
            else{if (adat[6]<95 && adat[6]>76){
                    adat[2]++;adat[5]++;data[17]+=3;}
                else{if (adat[6]<77 && adat[6]>57){
                        adat[3]++;adat[5]++;data[17]+=2;}
                    else{adat[4]++;adat[5]++;data[17]+=1;}}}}}}
    data[17]=data[17]/adat[5];
    printf("Average: %.2f\n", data[17]);
    printf("Histogram:\n");
    for (h=0, o=5; h<5; h++, o--){
        printf("%d -> %g\n", o, adat[h]);}
    return 0;}