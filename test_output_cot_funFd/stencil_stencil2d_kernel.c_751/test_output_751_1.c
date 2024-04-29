#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 256; j++) {
      int sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
      inner:
      for (k = -4; k < 5; k++) {
        int k_col = clip(k, 0, 256 - 1);
        int i_col = clip(i + k, 0, 256 - 1);
        int j_col = clip(j, 0, 256 - 1);
        sum += filter[k + 4] * orig[i_col * 256 + j_col] ;
      }
      sol[i * 256 + j] = sum;
    }
  }
}