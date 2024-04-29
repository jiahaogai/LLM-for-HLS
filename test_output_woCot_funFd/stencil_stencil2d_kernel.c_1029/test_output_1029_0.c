#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  double ft;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      sum = 0;
      ft = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = -4; k <= 4; k++) {
        sum += ((int )filter[4 + k]) * orig[i + k * 8192];
        ft += (double )filter[4 + k];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      sol[i * 8192 + j] = (sum / ft);
    }
  }
}