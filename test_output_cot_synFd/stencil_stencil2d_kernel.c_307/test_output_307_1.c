#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int ti;
  int tj;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    sol[i] = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 9; j++) {
      ti = i - 4 + ((j + 4) >> 5);
      tj = (j + 4) & 31;
      idx = ti * 32 + tj;
      val = filter[j] * orig[idx];
      sol[i] += val;
    }
  }
}