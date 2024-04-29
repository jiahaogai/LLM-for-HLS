#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int oidx;
  int fi;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    inner:
    for (j = 0; j < 256; j++) {
      oidx = i * 256 + j;
      sol[oidx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner_filter:
      for (k = 0; k < 9; k++) {
        fi = filter[k];
        idx = oidx + ((k - 4) * 256);
        sol[oidx] += fi * orig[idx];
      }
    }
  }
}