/*1.Операции сложения и вычитания.*/
#include <stdio.h>

extern int f1();

extern int f2();

int main(){

    int a,b;

    a = f1();
    b = f2();

    printf("f1() = %d\n" , a);
    printf("f2() = %d\n" , b);
    printf("Сумма f1 и f2 = %d\n", a+b);
    printf("Разность f1 и f2 = %d\n", a-b);


    return 0;
}