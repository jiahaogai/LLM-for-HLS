#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int ti;
  int tj;
  int idx;
  int fid;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 256; j++) {
      ti = i - 4;
      tj = j - 4;
      idx = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      inner:
      for (fid = 0; fid < 9; fid++) {
        if (ti + fid > -1 && tj + fid > -1 && ti + fid < 256 && tj + fid < 256) {
          idx += filter[fid] * orig[ti + fid + 8 * tj];
        }
      }
      sol[i * 256 + j] = idx;
    }
  }
}