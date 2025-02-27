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
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      ti = ((8 * i) + 1) - 1;
      tj = ((8 * j) + 1) - 1;
      val = ((orig[ti + 0 + (tj + 0) * 8192]) + (orig[ti + 1 + (tj + 0) * 8192]) + (orig[ti + 0 + (tj + 1) * 8192]) + (orig[ti + 1 + (tj + 1) * 8192]) + (orig[ti + 0 + (tj - 1) * 8192]) + (orig[ti + 1 + (tj - 1) * 8192]) + (orig[ti - 1 + (tj + 0) * 8192]) + (orig[ti - 1 + (tj + 1) * 8192]) + (orig[ti - 1 + (tj - 1) * 8192])) / 9;
      idx = i + (j * 8);
      sol[idx] = val;
    }
  }
}