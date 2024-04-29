#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int fid;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i - 1;
      idy = j - 1;
      sol[idx * 256 + idy] = 0;
      
#pragma ACCEL PIPELINE auto{off}
      inner:
      for (fid = 0; fid < 9; fid++) {
        if (idx + filter[fid] >= 0 && idy + filter[fid] >= 0 && idx + filter[fid] < 256 && idy + filter[fid] < 256) {
          sol[idx * 256 + idy] += orig[idx * 256 + idy + filter[fid]] * filter[fid];
        }
      }
    }
  }
}