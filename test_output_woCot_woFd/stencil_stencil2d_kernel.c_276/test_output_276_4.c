#pragma ACCEL kernel

void stencil(int orig[SIZE][SIZE],int sol[SIZE][SIZE],int filter[FILTER_SIZE][FILTER_SIZE])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < SIZE - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < SIZE - 1; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < FILTER_SIZE; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (int l = 0; l < FILTER_SIZE; l++) {
          sol[i][j] += filter[k][l] * orig[i + -1 + k][j + -1 + l];
        }
      }
    }
  }
//#pragma endscop
}