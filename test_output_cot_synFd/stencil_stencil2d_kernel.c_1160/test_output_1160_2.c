#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int t;
  int jj;
  int kk;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 8; j < 8176; j += 8) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; ++k) {
        jj = j + k - 4;
        kk = i + k - 4;
        t = (jj >= 0 ? (kk >= 0 ? (kk < 8192 ? orig[kk] : 0) : 0) : 0);
        tmp += filter[k] * t;
      }
      sol[j + 8184] = tmp;
    }
  }
}