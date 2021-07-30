/*#include <stdio.h>
#include <string.h>

void hi(char thing[], char thing1[]) {
	printf(thing, thing1);
   if(2 > 1) {
      printf("hi you  very cool");
   }
}

int main() {
   // printf() displays the string inside quotation
   printf("Hello, World!");
   hi("hisdfsdf", "sdfsdfsdf4");
   return 0;
}*/

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

int main() {
    printf("Hello World");
    printf(function1());
    printf(function2());
    printf(function3());
    printf(function4());
    printf(function5());
    printf(function6());
    return 0;
}

