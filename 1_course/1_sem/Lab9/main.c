#include <stdio.h>

int abs(int val) {
    if (val >= 0) {
        return val;
    }
    return -val;
}

int max(int a, int b) {
    if (a >= b) {
        return a;
    }
    return b;
}

int min(int a, int b) {
    if (a <= b) {
        return a;
    }
    return b;

}

int sign(int val) {
    if (val < 0) {
        return -1;
    }
    if (val > 0) {
        return 1;
    }
    return 0;
}

int mod(int a, int b) {
    if (a >= 0) {
        return a % b;
    }
    return (b - ((-a) % b)) % b;
}

int main() {
    const int i0 = -25;
    const int j0 = -9;
    const int l0 = -8;
    int j = j0;
    int i = i0;
    int l = l0;
    int ti = 0;
    int tj = 0;
    int tl = 0;
    int k = 0;
    while (sign(i + j + 10) == sign(i + j + 20) && k < 50) {
        tl = l;
        ti = i;
        tj = j;
        i = mod((abs(ti - tj) * tl - abs(tj - tl) * ti + abs(ti - tl) * tj), 20) - k;
        j = mod(min(ti, tj) * max(tj, tl) * min(ti, tl), 25) + 5 * sign(ti) + k;
        l = abs(tl) * sign(ti - tj) - abs(ti) * sign(tj - tl) + abs(tj) * sign(ti - tl);
        k++;
    }
    if (k < 50) printf("success\n k=%d i=%d j=%d l=%d", k, i, j, l);
    else printf("Out of the area\n k=%d i=%d j=%d l=%d \n", 49, i, j, l);   
    return 0;
}
