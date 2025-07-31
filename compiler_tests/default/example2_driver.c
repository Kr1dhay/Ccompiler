#include <stdio.h>

int f();

int main() {
    int result = f();
    printf("Result from f(): %d\n", result);
    return !(result == 8);  // exits with 0 if correct, 1 if wrong
}
