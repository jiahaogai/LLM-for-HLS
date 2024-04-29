#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int t;
  int pass;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  orig_copy:
  for (i = 0; i < 8192; i++) {
    sol[i] = orig[i];
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  solve:
  for (pass = 0; pass < 40; pass++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    apply_filter:
    for (i = 0; i < 8; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_row:
      for (j = 0; j < 8; j++) {
        t = i * 8 + j;
        sum = 0;
        
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
        inner_col:
        for (k = 0; k < 8; k++) {
          sum += filter[k] * orig[t + k - 8];
        }
	sol[t] = sum;
      }
    }
  }
}