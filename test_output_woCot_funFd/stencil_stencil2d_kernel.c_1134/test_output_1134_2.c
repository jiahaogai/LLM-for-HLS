#pragma ACCEL kernel

void stencil(int orig[40][40],int sol[40][40],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 1; i < 39; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{7}
    for (j = 1; j < 39; j++) {
      sum = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[i + ((k - 4) > 0 ? (k - 4) : 0)][j + ((k - 4) > 0 ? (k - 4) : 0)];
      }
      sol[i][j] = sum;
    }
  }
//#pragma endscop
}