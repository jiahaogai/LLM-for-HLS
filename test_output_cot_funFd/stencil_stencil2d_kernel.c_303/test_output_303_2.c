#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{14}
    loopi:
    for (i = 1; i < 8191; i++) {
      sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      loopk:
      for (k = -4; k <= 4; k++) {
        sum += filter[4 + k] * orig[i + k * 8192];
      }
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{16}
      sol[i + j * 8192] = sum;
    }
  }
}