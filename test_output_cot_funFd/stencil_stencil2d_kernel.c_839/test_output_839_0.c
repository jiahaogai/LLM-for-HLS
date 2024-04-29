#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{8}

#pragma ACCEL PARALLEL FACTOR=auto{2}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    for (j = 1; j < 8176; j++) {
      idx = (8 * i) + j;
      val = orig[idx] + filter[0] * (orig[idx - 8] + orig[idx + 8]) + filter[1] * (orig[idx - 7] + orig[idx + 7]) + filter[2] * (orig[idx - 6] + orig[idx + 6]) + filter[3] * (orig[idx - 5] + orig[idx + 5]) + filter[4] * (orig[idx - 4] + orig[idx + 4]) + filter[5] * (orig[idx - 3] + orig[idx + 3]) + filter[6] * (orig[idx - 2] + orig[idx + 2]) + filter[7] * (orig[idx - 1] + orig[idx + 1]);
      sol[idx] = val;
    }
  }
}