#include <stdio.h>

int main() {
    int i = -2147483648;

    while (i < 0) {
        if (i * 4 == 44) {
            printf("%d - %d - %u\n", i, i * 4, i);
            break;
        }
        i++;

    }
    return (0);
}