#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[25][25])
{
  int i;
  int j;
  int k;
  int l;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = 0; k < 25; k++) {
        for (l = 0; l < 25; l++) {
          sol[i][j] += filter[k][l] * orig[i + k - 1][j + l - 1];
        }
      }
    }
  }
//#pragma endscop
}