#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int fid;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i - 4 + 0;
      idy = j - 4 + 0;
      int sum = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{9}
      inner:
      for (k = 0; k < 9; k++) {
        fid = idx + k % 5;
        int fval = filter[k];
        int oval = orig[fid * 256 + idy + k / 5];
        sum += fval * oval;
      }
      sol[i * 256 + j] = sum;
    }
  }
}