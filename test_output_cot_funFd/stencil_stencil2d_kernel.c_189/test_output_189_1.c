#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[25])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = ((orig[i - 1][j - 1] + orig[i - 1][j] + orig[i - 1][j + 1] + orig[i][j - 1] + orig[i][j] + orig[i][j + 1] + orig[i + 1][j - 1] + orig[i + 1][j] + orig[i + 1][j + 1]) + filter[0]) / ((25 - 2) * (25 - 2));
    }
  }
//#pragma endscop
}