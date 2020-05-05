#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5}; //efecto de arreglo circular
    for(int i = 0; i < 25; ++i) {
        printf("%d ", arr[i % 5]);
    }
    return 0;
}