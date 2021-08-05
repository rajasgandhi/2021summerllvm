#include <stdio.h>
#include <string.h>

int function1() {
    return 1;
}

int function2() {
    return 2;
}

int function3() {
    return 3;
}

int function7() {
    return 5;
}

int function4() {
    return function7();
}

int function5() {
    return 4;
}

int function6() {
    return function5() + 2;
}

int function8() {
    return function3() + function6();
}

int main() {
    printf("Hello World");
    printf(function1());
    printf(function2());
    printf(function3());
    printf(function4());
    printf(function5());
    printf(function6());
    printf(function8());
    return 0;
}

