#pragma ACCEL PIPELINE auto{flatten}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{31}
 void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idx0;
  int idx1;
  int idx2;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 128 + 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 64 + 1; j++) {
      idx0 = (i - 1) * 64 + (j - 1);
      idx1 = (i - 1) * 64 + j;
      idx2 = (i - 1) * 64 + (j + 1);
      idx = idx0 * 3;
      val = orig[idx0] + orig[idx1] + orig[idx2];
      sol[idx0] = val;
      sol[idx1] = val;
      sol[idx2] = val;
    }
  }
}