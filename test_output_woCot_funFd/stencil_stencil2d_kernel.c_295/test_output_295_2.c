#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    inner:
    for (j = 0; j < 8192; j++) {
      s = 0;
      
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{32}
      filter_inner:
      for (k = 0; k < 9; k++) {
        idx = (i + (-4 + k)) * 8192 + (j + (-4 + k));
        s += orig[idx] * filter[k];
      }
      sol[i * 8192 + j] = s;
    }
  }
}