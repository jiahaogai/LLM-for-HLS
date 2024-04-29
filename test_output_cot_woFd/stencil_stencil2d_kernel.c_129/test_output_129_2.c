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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 256; j++) {
      ti = i - 4;
      tj = j - 4;
      ft = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (idx = 0; idx < 5; idx++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (idy = 0; idy < 5; idy++) {
          ft += filter[idx * 5 + idy] * orig[ti + idx][tj + idy];
        }
      }
      sol[i][j] = ft;
    }
  }
}