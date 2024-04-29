### #pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{8}

#pragma ACCEL PARALLEL FACTOR=auto{3}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    sum = 0;
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
    for (k = -4; k <= 4; k++) {
      sum += orig[i + k] * filter[4 + k];
    }
    sol[i] = sum;
  }
}