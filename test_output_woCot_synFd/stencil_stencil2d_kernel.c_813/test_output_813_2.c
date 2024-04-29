#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int ti;
  int tj;
  int idx;
  int idy;
  int ft;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 256; j++) {
      ti = i - 4;
      tj = j - 4;
      idx = 0;
      idy = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      for (ft = 0; ft < 9; ft++) {
        if (ti + ft > -1 && ti + ft < 256 && tj + idx > -1 && tj + idx < 256) {
          sol[i * 256 + j] += filter[ft] * orig[(ti + ft) * 256 + tj + idx];
        }
        idy += 256;
      }
      idx = 1;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      for (ft = 0; ft < 9; ft++) {
        if (ti + idy + ft > -1 && ti + idy + ft < 256 && tj + idx > -1 && tj + idx < 256) {
          sol[i * 256 + j] += filter[ft] * orig[(ti + idy + ft) * 256 + tj + idx];
        }
        idx++;
      }
      idy = 1;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      for (ft = 0; ft < 9; ft++) {
        if (ti + idy + ft > -1 && ti + idy + ft < 256 && tj + idx > -1 && tj + idx < 256) {
          sol[i * 256 + j] += filter[ft] * orig[(ti + idy + ft) * 256 + tj + idx];
        }
        idx++;
      }
    }
  }
}