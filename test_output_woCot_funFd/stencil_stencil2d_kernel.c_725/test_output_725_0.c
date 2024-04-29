However, the ACCEL compiler is not bound by these directives. It is free to make trade-offs between performance and area in the implementation.
#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[3][3])
{
  int i;
  int j;
  int k;
  int l;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 3; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (l = 0; l < 3; l++) {
          sol[i][j] += filter[k][l] * orig[i + k - 1][j + l - 1];
        }
      }
    }
  }
//#pragma endscop
}