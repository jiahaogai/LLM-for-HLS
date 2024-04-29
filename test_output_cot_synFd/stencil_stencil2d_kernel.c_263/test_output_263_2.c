#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int batch;
  int batch_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 256; j++) {
      int tmp_sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp_sum FACTOR=auto{8}
      inner:
      for (k = -4; k < 5; k++) {
        int k_col_int = k_col = k + j;
        int batch_col_int = batch_col = i * 64 + k_col_int;
        int index = batch + batch_col * 8;
        if ((((i >= 0) && (i < 256)) && ((j >= 0) && (j < 256))) && ((k_col >= 0) && (k_col < 256))) {
          tmp_sum += filter[k + 4] * orig[index];
        }
      }
      sol[batch_col] = tmp_sum;
    }
  }
}