#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  double SQRT81 = 8.7065280135461335;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    loopi:
    for (i = 1; i < 8191; i++) {
      sum = 0.0;
      loopk:
      for (k = -4; k <= 4; k++) {
        sum += filter[((k + 4) << 3) + ((j - 1) << 1) + i - 1] * orig[((k + 4) << 3) + ((j - 1) << 1) + i - 1];
      }
      sum /= 10.0;
      sol[((j - 1) << 11) + (i - 1)] = (int )sum;
    }
  }
}