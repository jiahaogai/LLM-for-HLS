Code: #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void gemm(double A[4940],double B[4940],double C[4940])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 494; i += 16) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 494; j += 16) {
      i_col:
      for (i_col = 0; i_col < 16; i_col++) {
        double sum = (double )0;
        k_col:
        for (k_col = 0; k_col < 16; k_col++) {
          mult = A[i + i_col] * B[j + k_col];
          sum += mult;
        }
        C[j + i_col] += sum;
      }
    }
  }
}