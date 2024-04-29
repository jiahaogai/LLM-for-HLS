#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 64; j++) {
      idx = i * 64 + j;
      val = orig[idx] * filter[0];
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 1; k < 9; k++) {
        val += orig[idx + k] * filter[k];
      }
      sol[idx] = val;
    }
  }
}