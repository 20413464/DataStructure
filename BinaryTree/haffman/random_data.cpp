#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){
    srand(time(0));
    printf("26\n");
    for (int i = 0;  i<26;i++){
        printf("%c %d\n",'a'+i,rand()%100000);
    }
    return 0;
}