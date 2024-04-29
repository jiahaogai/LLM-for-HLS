#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[25])
{
  int i;
  int j;
  int f;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (f = 0; f < 25; f++) {
        sol[i][j] += filter[f] * orig[i + (-1 + f)][j + (-1 + f)];
      }
    }
  }
//#pragma endscop
}