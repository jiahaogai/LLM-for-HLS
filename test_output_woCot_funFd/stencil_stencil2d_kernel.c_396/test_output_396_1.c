#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  int flatten_idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopi:
    for (i = 1; i < 33; i++) {
      idx = i + (j * 32);
      center = orig[idx];
      flatten_idx = ((idx > 1) ? (idx - 1) : 1);
      k = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopk:
      for (; k < 9; k++) {
        sol[idx] += filter[k] * orig[flatten_idx + k - 1];
      }
      sol[idx] = center - (sol[idx] / 9.0);
    }
  }
}