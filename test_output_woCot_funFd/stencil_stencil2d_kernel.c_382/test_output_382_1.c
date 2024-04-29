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
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 39; j++) {
      sol[i][j] = 0;
      for (k = 0; k < 9; k++) {
        fr = filter[k];
        sol[i][j] += fr * orig[i + (-1 + (k >> 1))][j + (-1 + (k & 1))];
      }
    }
  }
}