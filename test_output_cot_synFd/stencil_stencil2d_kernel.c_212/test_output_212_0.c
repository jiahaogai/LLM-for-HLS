#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idx0;
  int idx1;
  int idx2;
  int val0;
  int val1;
  int val2;
  int sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      idx0 = (i - 1) * 256 + (j - 1);
      idx1 = (i - 1) * 256 + j;
      idx2 = (i - 1) * 256 + (j + 1);
      val0 = orig[idx0];
      val1 = orig[idx1];
      val2 = orig[idx2];
      sum = val0 + val1 + val2;
      sol[idx1] = sum;
    }
  }
}