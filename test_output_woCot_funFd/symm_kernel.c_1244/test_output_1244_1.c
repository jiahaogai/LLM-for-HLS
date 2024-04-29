Code: void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
Error: 
Please check the code and try again.
Code:   int i;
Error: 
Please check the code and try again.
Code:   int j;
Error: 
Please check the code and try again.
Code:   int k;
Error: 
Please check the code and try again.
Code: //#pragma scop
Error: 
Please check the code and try again.
Code:   for (i = 0; i < 60; i++) {
Error: 
Please check the code and try again.
Code:      for (j = 0; j < 80; j++) {
Error: 
Please check the code and try again.
Code:         C[i][j] *= beta;
Error: 
Please check the code and try again.
Code:      }
Error: 
Please check the code and try again.
Code:   }
Error: 
Please check the code and try again.
Code:   for (i = 0; i < 60; i++) {
Error: 
Please check the code and try again.
Code:      for (j = 0; j < 80; j++) {
Error: 
Please check the code and try again.
Code:         C[i][j] = 0.0;
Error: 
Please check the code and try again.
Code:         for (k = 0; k < 60; ++k) {
Error: 
Please check the code and try again.
Code:            C[i][j] += alpha * A[i][k] * B[k][j];
Error: 
Please check the code and try again.
Code:         }
Error: 
Please check the code and try again.
Code:      }
Error: 
Please check the code and try again.
Code:   }
Error: 
Please check the code and try again.
Code: //#pragma endscop
Error: 
Please check the code and try again.