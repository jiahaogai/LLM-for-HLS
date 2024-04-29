#pragma ACCEL kernel

void stencil(int orig[40][40],int sol[40][40],int filter[9])
{
  int i;
  int j;
  int k;
  int fr;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 39; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 39; j++) {
      fr = filter[0] * orig[i - 1][j - 1] + filter[1] * orig[i - 1][j] + filter[2] * orig[i - 1][j + 1] + filter[3] * orig[i][j - 1] + filter[4] * orig[i][j] + filter[5] * orig[i][j + 1] + filter[6] * orig[i + 1][j - 1] + filter[7] * orig[i + 1][j] + filter[8] * orig[i + 1][j + 1];
      sol[i][j] = fr;
    }
  }
}