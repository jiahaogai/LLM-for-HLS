#pragma ACCEL kernel

void stencil(char orig[25][25],char sol[25][25],char filter[25][25])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = ((filter[0][0] * orig[i - 1][j - 1]) + (filter[0][1] * orig[i - 1][j]) + (filter[0][2] * orig[i - 1][j + 1]) + (filter[1][0] * orig[i][j - 1]) + (filter[1][1] * orig[i][j]) + (filter[1][2] * orig[i][j + 1]) + (filter[2][0] * orig[i + 1][j - 1]) + (filter[2][1] * orig[i + 1][j]) + (filter[2][2] * orig[i + 1][j + 1])) / 25;
    }
  }
//#pragma endscop
}