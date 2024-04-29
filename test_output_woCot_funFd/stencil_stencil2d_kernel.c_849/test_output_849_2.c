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
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 8; j < 8184; j += 8) {
      ti = i - 8;
      tj = j - 8;
      ft = filter[0];
      idx = ti * 8192 + tj;
      ft *= orig[idx];
      idy = i * 8192 + j;
      sol[idy] = ft;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (j = 1; j < 9; j++) {
        idx = ti * 8192 + j + tj - 1;
        ft *= orig[idx];
        sol[idy] += ft;
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (j = 1; j < 9; j++) {
        idx = (ti + j - 1) * 8192 + tj;
        ft *= orig[idx];
        sol[idy] += ft;
      }
    }
  }
}