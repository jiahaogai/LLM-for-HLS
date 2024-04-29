#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopk_col:
    for (k_col = 0; k_col < 9; k_col++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      loopk_row:
      for (k_row = 0 - 4; k_row < 5; k_row++) {
        k = k_row + 4 + j;
        if (k < 0) {
          k += 8192;
        }
        
#pragma ACCEL PIPELINE auto{flatten}
        else if (k > 8191) {
          k -= 8192;
        }
        sum += filter[k_row] * orig[k * 8192 + k_col];
      }
      sol[j * 8192 + k_col] = sum;
    }
  }
}