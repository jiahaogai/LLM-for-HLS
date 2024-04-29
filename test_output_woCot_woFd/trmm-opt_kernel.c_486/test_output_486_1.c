#pragma scop
   int M = 60;
   int N = 80;
   int P = 60;
   double alpha = 1.5;
   for (int i = 0; i < 60; i++) {
      for (int j = 0; j < 80; j++) {
         double sum = 0.0;
         for (int k = 0; k < 60; k++) {
            sum += alpha * A[i][k] * B[k][j];
         }
         B[i][j] = sum;
      }
   }
#pragma endscop