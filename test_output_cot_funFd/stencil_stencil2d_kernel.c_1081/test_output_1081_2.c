#pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{6}
 void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int buff[9];
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      inner:
      for (k = 0, k_col = 0; k < 9; k++, k_col++) {
        buff[k] = orig[i * 8 + j + ((k_col - 4) * 8)] ;
      }
      sol[i * 8 + j] = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      stencil_label3:
      for (k = 4; k < 9; k++) {
        sol[i * 8 + j] += filter[k] * buff[k];
      }
    }
  }
}