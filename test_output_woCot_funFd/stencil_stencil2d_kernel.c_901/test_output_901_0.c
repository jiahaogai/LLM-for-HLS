#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flatten_row;
  int flatten_col;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loop:
/* Standardize from: for(i = 0; i < 32; i++) {...} */
  row:
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    col:
    for (j = 0; j < 32; j++) {
      flatten_row = i * 32;
      flatten_col = j * 32;
      idx = flatten_row + flatten_col;
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
      filter:
      for (k = 0; k < 9; k++) {
        val += orig[idx + k] * filter[k];
      }
      sol[idx] = val;
    }
  }
}