#include <stdio.h>
int main()
{
    int data[5]={0};
    double average=0;;
    char c;
    int j;
    for (int i=1; i<142; i++)
    {
        scanf("%c", &c);
    }
    for (j=0; (scanf("%c", &c))!=EOF ; j++)
    {
    for (int i = 0; i < 7; i++)
    {
        scanf("%c", &c);
    }
    double pontos[3]={0};// 0-lec, 1-pra, 2-lab,
    int egesz[18]={0};// 0t1,1t2,2t3,3t4,4t5,5t6,6exam1,7exam2,8hw1,9hw2,10hw3,11hwp,12bonus,13imsc,14jelenlet,15kiszh,16nagyzh,17hazi//
    for (int i = 0; i < 3; i++)
    {
        scanf("%lf %c", &pontos[i], &c); //lebegőpontos beolvasás//
        if (pontos[i]>0.77)
        {
            egesz[14]++;
        }
    }
    for (int i = 0; i < 15; i++)
    {
        if (i==13)
        {
            scanf("%d", &egesz[i]);
            break;
        }
        scanf("%d %c", &egesz[i], &c); //pontos beolvasás//
    }
    if (egesz[14]==3)
    {
        egesz[14]=1; //jelenlét feltétel//
    }
    else
    {
        data[4]++;
        break;
    }
    if(egesz[1]>egesz[0])
    {
        egesz[0]=egesz[1]; //kis zh csoport 1//
    }
    if(egesz[3]>egesz[2])
    {
        egesz[2]=egesz[3]; //kis zh csoport 2//
    }
    if(egesz[5]>egesz[4])
    {
        egesz[4]=egesz[5]; //kis zh csoport 3//
    }
    for (int i = 0; i < 5; i++)
    {
        if (egesz[i]>3)
        {
            egesz[15]++;
        }
        i++;
    }
    if (egesz[15]==3)
    {
        egesz[15]=1; //kis zh feltétel//
    }
    else
    {
        data[4]++;
        break;
    }
    egesz[16]=egesz[6]+egesz[7], egesz[17]=egesz[8]+egesz[9]+egesz[10];    
    if (egesz[6]+egesz[7]>39 )
    {
        egesz[16]=1; //nagy zh feltétel//
    }
    else
    {
        data[4]++;
        break;
    }
    if (egesz[8]+egesz[9]+egesz[10]>5 && egesz[10]>3)
    {
        egesz[17]=1; //hazi feltetel//
    }
    else
    {
        data[4]++;
        break;
    }
        if ((egesz[18]=egesz[0]+egesz[2]+egesz[4]+egesz[6]+egesz[7]+egesz[8]+egesz[9]+egesz[10]+egesz[11]+egesz[12])>112)
        {
            data[0]++;
        }
        if (egesz[18]<113 && egesz[18]>94)
        {
            data[1]++;
        }
        if (egesz[18]<95 && egesz[18]>76)
        {
            data[2]++;
        }
        if (egesz[18]<77 && egesz[18]>57)
        {
            data[3]++;
        }
        if (egesz[18]<58)
        {
            data[4]++;
        }
    }
    for (int i=0; i<5; i++)
    {
        if (i==0)
        {
            average+=5;
            j++;
        }
        else
        {
            if (i==1)
            {
                average+=4;
                j++;
            }
            else
            {
                if (i==2)
                {
                    average+=3;
                    j++;
                }
                else
                {
                    if (i==3)
                    {
                        average+=2;
                        j++;
                    }
                    else
                    {
                        average++;
                        j++;
                    }             
                }
            }
        }
    }
    j--;
    average=average/j;
    printf("Average: %.2f\n", average);
    printf("Histogram:\n");
    j=5, data[4]--;
    for (int i = 0; i<5; j--, i++)
    {
        printf("%d -> %d\n", j, data[i]);
    }
    return 0;
}