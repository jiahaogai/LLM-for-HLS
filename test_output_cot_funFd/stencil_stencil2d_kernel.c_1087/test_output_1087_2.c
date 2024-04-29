#pragma ACCEL kernel

void stencil(int orig[40][40],int sol[40][40],int filter[9])
{
  int i;
  int j;
  int flatten_filter[81];
  int idx = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 0; i < 9; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    for (j = 0; j < 9; j++) {
      flatten_filter[idx] = filter[i * 9 + j];
      idx++;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 1; i < 39; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    for (j = 1; j < 39; j++) {
      sol[i][j] = flatten_filter[0] * orig[i][j] + flatten_filter[1] * (orig[i][j - 1]) + flatten_filter[2] * (orig[i][j + 1]) + flatten_filter[3] * (orig[i - 1][j]) + flatten_filter[4] * (orig[i + 1][j]) + flatten_filter[5] * (orig[i - 1][j - 1]) + flatten_filter[6] * (orig[i - 1][j + 1]) + flatten_filter[7] * (orig[i + 1][j - 1]) + flatten_filter[8] * (orig[i + 1][j + 1]);
    }
  }
}