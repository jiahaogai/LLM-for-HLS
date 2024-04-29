#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  double float_sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    loopi:
    for (i = 1; i < 8191; i++) {
      sum = 0.0;
      float_sum = 0.0;
      loopk:
      for (k = 0; k < 9; k++) {
        sum += ((double )filter[k]) * orig[i + (k - 4) * 8191];
        float_sum += ((double )filter[k]) * ((double )orig[i + (k - 4) * 8191]);
      }
      sol[i + j * 8191] = ((sum - float_sum) > 0.0 ? ((int )((sum - float_sum) + 0.5)) : ((int )((sum - float_sum) - 0.5)));
    }
  }
}