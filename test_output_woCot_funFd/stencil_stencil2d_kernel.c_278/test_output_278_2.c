Code: #pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopk:
    for (k = 0; k < 8; k++) {
      i = 8 * j + k - 8;
      sum = ((double )0);
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      loopk_col:
      for (k_col = 0; k_col < 8; k_col++) {
        i_col = 8 * (j - 1) + k_col;
        sum += filter[k_col] * orig[i_col];
      }
      sol[i] = sum;
    }
  }
}
Error: 
Please check the code and try again.