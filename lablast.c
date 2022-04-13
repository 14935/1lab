#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
typedef struct PolimVector{
    int len;
    int type;
    void *data;
}PolimVector;

int inputint(bool *b)
{
    char c = getchar();
    int inp = 0;
    if (c == 45){
        c = getchar();
        if (c>48 && c<58){
                inp = c - 48;
                inp *= -1;
                *b = true;
                c = getchar();
        }
        else return 0;
    }
    while(c>47 && c<58){
        inp *= 10;
        if (inp == 0 && c == 48 && *b){
            *b = false;
            return 0;
        }
        inp += c - 48;
        *b = true;
        c = getchar();
    }
    if( c != 10) *b = false;
    return inp;
}
double inputdouble(bool *b)
{
    char c = getchar();
    bool sign = false;
    double inp = 0;
    if (c == 45){
        c = getchar();
        sign = true;
    }
    while(c>47 && c<58){
        inp *= 10;
        if (inp == 0 && c == 48 && *b){
            *b = false;
            return 0;
        }
        inp += c - 48;
        *b = true;
        c = getchar();
    }
    if (c == 46 && *b){
        *b = false;
        c = getchar();
        double dec = 0.1;
        while(c>47 && c<58){
            inp += (c - 48)*dec;
            *b = true;
            c = getchar();
            dec*=0.1;
        }
    }
    if(c != 10) *b = false;
    if (inp == 0 && sign) *b = false;
    if (sign) return inp*(-1);
    else return inp;
}

PolimVector newvector(int type,int len)
{
    PolimVector vector;
    if(type){
        vector.data = calloc(sizeof(int),len);
    }
    else{
        vector.data = calloc(sizeof(double),len);
    }
    vector.type = type;
    vector.len = len;
    return vector;
}
PolimVector input(PolimVector vector)
{
    int i;
    bool rightinp = false;
    if(vector.type){
        int inp;
        for(i = 0;i < vector.len;i++){
            printf("input %d elem ",i+1);
            inp = inputint(&rightinp);
            if(!rightinp){
                printf("Wrong value\n");
                free(vector.data);
                vector.data = NULL;
                return vector;
            }
            rightinp = false;
            memcpy(vector.data+i*sizeof(int) ,&inp ,4 );
        }
    }
    else{
        double inp;
        for(i = 0;i < vector.len;i++){
            printf("input %d elem ",i+1);
            inp = inputdouble(&rightinp);
            if(!rightinp){
                printf("Wrong value\n");
                free(vector.data);
                vector.data = NULL;
                return vector;
            }
            rightinp = false;
            memcpy(vector.data+i*sizeof(double) ,&inp ,8 );
        }
    }
    return vector;
}
void output(PolimVector vector)
{
    int i;
    if(vector.type){
        for(i = 0;i < vector.len;i++){
            printf("%d ",*((int*)(vector.data+i*sizeof(int))));
        }
    }
    else{
        for(i = 0;i < vector.len;i++){
            printf("%lf ",*((double*)(vector.data+i*sizeof(double))));
        }
    }
}
PolimVector sum(PolimVector vector1,PolimVector vector2)
{
    int i;
    if(vector1.type && vector2.type){
        PolimVector vector=newvector(1,vector1.len);
        int res;
        for(i = 0;i < vector1.len;i++){
            res =  *((int*)(vector1.data+i*sizeof(int))) +  *((int*)(vector2.data+i*sizeof(int)));
            memcpy(vector.data+i*sizeof(int),&res,4);
        }
        return vector;
    }
    else{
        PolimVector vector=newvector(0,vector1.len);
        int i;
        double res,figure1,figure2;
        for(i = 0;i < vector1.len;i++){

            if(vector1.type) figure1 = *((int*)(vector1.data + i * sizeof(int)));
            else figure1 =  *((double*)(vector1.data + i * sizeof(double)));

            if(vector2.type) figure2 = *((int*)(vector2.data + i * sizeof(int)));
            else figure2 =  *((double*)(vector2.data + i *  sizeof(double)));

            res =  figure1+figure2;
            memcpy(vector.data+i*sizeof(double),&res,sizeof(double));
        }
        return vector;
    }

}
void scalar(PolimVector vector1,PolimVector vector2)
{
    int i;
    if(vector1.type && vector2.type){
        int res = 0;
        for(i = 0;i < vector1.len;i++){
            res +=  *((int*)(vector1.data+i*sizeof(int))) +  *((int*)(vector2.data+i*sizeof(int)));
        }
        printf("%d\n",res);
        return;
    }
    else{
//        PolimVector vector=newvector(0,vector1.len);
        int i;
        double res = 0,figure1,figure2;
        for(i = 0;i < vector1.len;i++){

            if(vector1.type) figure1 = *((int*)(vector1.data + i * sizeof(int)));
            else figure1 =  *((double*)(vector1.data + i * sizeof(double)));

            if(vector2.type) figure2 = *((int*)(vector2.data + i * sizeof(int)));
            else figure2 =  *((double*)(vector2.data + i *  sizeof(double)));

            res +=  figure1+figure2;
        }
        printf("%lf\n",res);
        return;
    }
}

PolimVector inputrand(PolimVector vector)
{
    int i;
    if(vector.type){
        int inp;
        for(i = 0;i < vector.len;i++){
            inp = rand()%(1000) - 500;
            memcpy(vector.data+i*sizeof(int),&inp,4);
        }
    }
    else{
        double inp;
        for(i = 0;i < vector.len;i++){
            inp = rand()%100000 - 50000;
            inp /= 100;
            memcpy(vector.data+i*sizeof(double),&inp,8);
        }
    }
    printf("Random Vector\n");
    output(vector);
    return vector;
}

bool isbininpwrong(bool rightinp,int inptype)
{
    if (!rightinp){
        printf("Wrong type\n");
        return 1;
    }
    if(inptype != 1 && inptype != 0){
        printf("Wrong value\n");
        return 1;
    }
    return 0;
}

int main()
{
    int seed = (int) clock();
    srand(seed);
    int type, len, inptype,i;
    bool rightinp = false;
    printf("len\n");
    printf("1 random input 0 console input\n");

    inptype = inputint(&rightinp);
    if (isbininpwrong(rightinp,inptype)) return 0;

    rightinp = false;
    if (inptype) {
            len = 1+rand()%20;
            printf("len = %d\n",len);
    }
    else{
        printf("input len\n");
        len = inputint(&rightinp);
        if (!rightinp){
            printf("Wrong type\n");
            return 0;
        }
        if (len<1){
            printf("Wrong value\n");
            return 0;
        }
    }

    rightinp = false;


    printf("input first vector type \n");
    printf("1 random input 0 console input\n");

    inptype = inputint(&rightinp);
    if (isbininpwrong(rightinp,inptype)) return 0;

    rightinp = false;
    if (inptype) type = rand()%2;
    else{
        printf("1 int 0 double\n");
        type = inputint(&rightinp);
        if (isbininpwrong(rightinp,inptype)) return 0;
    }
    rightinp = false;

    if (type) printf("type int\n");
    else printf("type double\n");

    PolimVector vector1=newvector(type,len);
    printf("input first vector\n");
    printf("1 random input 0 console input\n");

    inptype = inputint(&rightinp);
    if (isbininpwrong(rightinp,inptype)){
		free(vector1.data);
		return 0;
	}

    if (inptype) vector1=inputrand(vector1);
    else vector1=input(vector1);
    if (vector1.data == NULL){
        return 0;
    }



    printf("\ninput second vector type \n");
    printf("1 random input 0 console input\n");
	rightinp = false;
    inptype = inputint(&rightinp);
    if (isbininpwrong(rightinp,inptype)) {
		printf("adf\n");
		free(vector1.data);
		return 0;
	}
    rightinp = false;
    if (inptype) type = rand()%2;
    else{
        printf("1 int 0 double\n");
        type = inputint(&rightinp);
        if (isbininpwrong(rightinp,inptype)) {
			free(vector1.data);
			return 0;
		}
    }
    rightinp = false;

    if (type) printf("type int\n");
    else printf("type double\n");

    PolimVector vector2 = newvector(type,len);
    printf("input second vector\n");
    printf("1 random input 0 console input\n");

    inptype = inputint(&rightinp);
    if (isbininpwrong(rightinp,inptype)) {
		free(vector1.data);
		free(vector2.data);
		return 0;
	}
    if (inptype) vector2 = inputrand(vector2);
    else vector2 = input(vector2);
    if (vector2.data == NULL){
        free(vector1.data);
        return 0;
    }



    PolimVector vectorsum=sum(vector1,vector2);
    printf("\nvector sum\n");
    output(vectorsum);
    printf("\nscalar product\n");
    scalar(vector1,vector2);
    free(vector1.data);
    free(vector2.data);
    free(vectorsum.data);
    return 0;
}
