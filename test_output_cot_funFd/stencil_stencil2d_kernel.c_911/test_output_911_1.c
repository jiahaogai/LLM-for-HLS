#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int batch;
  int batch_col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 256; j++) {
      int sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        int k_col = i + ((k / 3) - 1);
        int batch_col = j + ((k % 3) - 1);
        if ((k_col >= 0) && (k_col < 256) && (batch_col >= 0) && (batch_col < 256)) {
          int index = k_col * 256 + batch_col;
          sum += filter[k] * orig[index];
        }
      }
      sol[i * 256 + j] = sum;
    }
  }
}