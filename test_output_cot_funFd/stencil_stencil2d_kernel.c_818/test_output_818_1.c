#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int buf[9];
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 8191; j++) {
      buf[0] = orig[i - 1, j - 1];
      buf[1] = orig[i - 1, j];
      buf[2] = orig[i - 1, j + 1];
      buf[3] = orig[i, j + 1];
      buf[4] = orig[i + 1, j + 1];
      buf[5] = orig[i + 1, j];
      buf[6] = orig[i + 1, j - 1];
      buf[7] = orig[i, j - 1];
      buf[8] = orig[i - 1, j - 1];
      sol[i, j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sol[i, j] += filter[k] * buf[k];
      }
    }
  }
}