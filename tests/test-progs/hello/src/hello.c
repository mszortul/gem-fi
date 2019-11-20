
#include <stdio.h>

int main(int argc, char* argv[])
{
    int i, j, k;
    int r = 0;
    for (i = 0; i<6; i++) {
        for (j = 0; j<3; j++) {
            for (k = 0; k<2; k++) {
                r += (k + j + i);
            }
        }
    }
    printf("result: %d \n", r);
    return r;
}
