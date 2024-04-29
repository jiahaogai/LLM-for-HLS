#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[25])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = ((0 + filter[0]) * orig[i][j]) + ((0 + filter[1]) * (orig[i][j - 1]) + ((0 + filter[2]) * (orig[i][j + 1])) + ((0 + filter[3]) * (orig[i - 1][j])) + ((0 + filter[4]) * (orig[i + 1][j])));
    }
  }
//#pragma endscop
}