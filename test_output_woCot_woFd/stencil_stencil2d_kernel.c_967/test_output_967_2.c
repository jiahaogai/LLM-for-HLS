#pragma ACCEL kernel

void stencil(int orig[40][40],int sol[40][40],int filter[9])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 1; i < 39; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 1; j < 39; j++) {
      sol[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{9}
      for (k = 0; k < 9; k++) {
        sol[i][j] += filter[k] * orig[i + (-4 + k)][j + (-4 + k)];
      }
    }
  }
//#pragma endscop
}