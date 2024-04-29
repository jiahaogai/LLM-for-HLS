Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64 + 2; j++) {
      t = 0;
      inner:
      for (k = -4; k < 5; k++) {
        i_col = i + k;
        j_col = j - 4 + ((-4 + k) / 64);
        if ((((i_col >= 0) && (i_col < 8192))) && (((j_col >= 0) && (j_col < 64)))) {
          k_col = k_idx[k];
          t += orig[i_col * 64 + j_col] * filter[k_col];
        }
      }
      sol[i * 64 + j] = t;
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64 + 2; j++) {
      t = 0;
      inner:
      for (k = -4; k < 5; k++) {
        i_col = i + k;
        j_col = j - 4 + ((-4 + k) / 64);
        if ((((i_col >= 0) && (i_col < 8192))) && (((j_col >= 0) && (j_col < 64)))) {
          k_col = k_idx[k];
          t += orig[i_col * 64 + j_col] * filter[k_col];
        }
      }
      sol[i * 64 + j] = t;
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma A