#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Declaration of the needwun function
void needwun(char SEQA[128], char SEQB[128], char alignedA[256], char alignedB[256], int M[16641], char ptr[16641]);

int main() {
    char SEQA[128] = "AGTACGCA";
    char SEQB[128] = "TATGC";
    char alignedA[256];
    char alignedB[256];
    int M[16641];  // Matrix of size (128+1) x (128+1)
    char ptr[16641];  // Pointer matrix of the same size as M

    // Initialize sequences
    memset(alignedA, 0, sizeof(alignedA));
    memset(alignedB, 0, sizeof(alignedB));
    memset(M, 0, sizeof(M));
    memset(ptr, 0, sizeof(ptr));

    // Fill the rest of SEQA and SEQB with zeros
    memset(SEQA + strlen(SEQA), 0, sizeof(SEQA) - strlen(SEQA));
    memset(SEQB + strlen(SEQB), 0, sizeof(SEQB) - strlen(SEQB));

    // Call the needwun function
    needwun(SEQA, SEQB, alignedA, alignedB, M, ptr);

    // Output the results for validation
    printf("Aligned A: %s\n", alignedA);
    printf("Aligned B: %s\n", alignedB);

    return 0;
}
