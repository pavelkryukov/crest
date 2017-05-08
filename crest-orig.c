#include <stdio.h>
#include <stdlib.h>

typedef enum {
    ZERO = 1,
    CROSS = 2,
    NONE = 0,
} Field;

typedef struct {
    Field array[3][3];
} CrossZeroes;

int isFull(const CrossZeroes* cz) {
    for (unsigned i = 0; i < 3; ++i) {
        for (unsigned j = 0; j < 3; ++j) {
            if (cz->array[i][j] == NONE) {
                return 0;
            }
        }
    }
    return 1;
}

Field isWin(const CrossZeroes* cz) {
    for (unsigned i = 0; i < 3; ++i) {
        if ((cz->array[0][i] == cz->array[1][i]) && (cz->array[2][i] == cz->array[1][i]) && cz->array[2][i] != NONE)
            return cz->array[0][i];
        if ((cz->array[i][0] == cz->array[i][1]) && (cz->array[i][2] == cz->array[i][1]) && cz->array[i][2] != NONE)
            return cz->array[i][0];
    }
    if ((cz->array[0][0] == cz->array[1][1]) && (cz->array[2][2] == cz->array[1][1]) ||
        (cz->array[2][0] == cz->array[1][1]) && (cz->array[0][2] == cz->array[1][1]))
        return cz->array[1][1];
    return NONE;
}

unsigned good(const CrossZeroes* cz, unsigned steps, Field last) {
    if (isWin(cz) == ZERO) {
        return (1 << (steps << 1));
    }

    unsigned goodness = 0;
    Field curr = (last == CROSS) ? ZERO : CROSS;

    unsigned k = 0;
    for (unsigned i = 0; i < 3; ++i) {
        for (unsigned j = 0; j < 3; ++j) {
            if (cz->array[i][j] == NONE) {
                CrossZeroes temp = *cz;
                temp.array[i][j] = curr;
                if (isWin(&temp) != NONE) {
                    return isWin(&temp) == CROSS ? 0 : (1 << ((steps - 1) << 1));
                }
                goodness += isFull(&temp) ? 1 : good(&temp, steps - 1, curr);
            }
        }
    }

    return goodness;
}
    
void dump(const CrossZeroes* cz) {
    printf("--\n");
    for (unsigned i = 0; i < 3; ++i) {
        for (unsigned j = 0; j < 3; ++j) {
            printf("%c", cz->array[j][i] == NONE ? ' ' : cz->array[j][i] == ZERO ? 'O' : 'X');
        }
        printf("\n");
    }
    printf("--\n");
 }
 
CrossZeroes moveAI(CrossZeroes *cz, unsigned steps) {
        unsigned k = 0;
        signed max = -1;
        CrossZeroes best;
        for (unsigned i = 0; i < 3; ++i) {
            for (unsigned j = 0; j < 3; ++j) {
                if (cz->array[i][j] == NONE) {
                    CrossZeroes temp = *cz;
                    temp.array[i][j] = ZERO;
                    signed goodness = good(&temp, steps - 1, ZERO);
                    if (goodness > max) {
                        best = temp;
                        max = goodness;
                    }
                    k++;
                }
            }
        }
        if (k != steps) {
            printf("internal error\n");
        }
        return best;
}

void moveUser(CrossZeroes *cz) {
            srand(rand());
            unsigned x, y;
            do {
                x = rand() / (RAND_MAX / 3);
                y = rand() / (RAND_MAX / 3);
   //           scanf("%d %d", &x, &y);
            } while (cz->array[x][y] != NONE);
        
            cz->array[x][y] = CROSS;
        }
int main() {
    Field result;
    do {
        CrossZeroes cz;        
        for (unsigned i = 0; i < 3; ++i) {
            for (unsigned j = 0; j < 3; ++j) {
                cz.array[i][j] = NONE;
            }
        }
        unsigned steps = 9;
        while (!isFull(&cz) && (isWin(&cz) == NONE)) {        
        
            moveUser(&cz);
            dump(&cz);        
            --steps;
        
            if (isFull(&cz) || (isWin(&cz) != NONE))
                break;
        
            printf("thinking\n");
            cz = moveAI(&cz, steps);
            dump(&cz);
        
            --steps;
        }
    result = isWin(&cz);
    switch (result) {
        case CROSS:
            printf("Cross Wins\n");
            break;
        case ZERO:
            printf("Zeroes Wins\n");
            break;
        case NONE:
            printf("Draw\n");
            break;
    }
   }
    while (result != CROSS);
    return 0;
}
