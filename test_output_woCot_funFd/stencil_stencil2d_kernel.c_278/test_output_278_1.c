Code: #pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
<<<<<<< HEAD
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    middle:
    for (j = 0; j < 8; j++) {
      sum = 0.0;
      inner:
      for (k = 0; k < 9; k++) {
        k_col = i + ((k % 3) - 1);
        k_row = i + ((k / 3) - 1);
        if ((((k_col >= 0) && (k_col < 8192)) && ((k_row >= 0) && (k_row < 8192))) && is_valid(k_col,k_row)) {
          sum += filter[k] * orig[k_row * 8192 + k_col];
        }
      }
      sol[i * 8 + j] = sum;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:1:38: warning: missing terminating ' character
    1 | #pragma ACCEL PARALLEL FACTOR=auto{1}': The number of available processor cores is 1.
      |                                      ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:1: error: expected identifier or ‘(’ before ‘-’ token
    2 | - '#pragma ACCEL PIPELINE auto{off}': Do not automatically pipeline this loop.
      | ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:3: warning: character constant too long for its type
    2 | - '#pragma ACCEL PIPELINE auto{off}': Do not automatically pipeline this loop.
      |   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:3:3: warning: character constant too long for its type
    3 | - '#pragma ACCEL TILE FACTOR=auto{1}': Keep this loop whole, without dividing it into smaller parts.
      |   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:3: warning: character constant too long for its type
    4 | - '#pragma ACCEL PARALLEL FACTOR=auto{1}': The number of available processor cores is 1.
      |   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:5:3: warning: character constant too long for its type
    5 | - '#pragma ACCEL PIPELINE auto{off}': Do not automatically pipeline this loop.
      |   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:6:3: warning: character constant too long for its type
    6 | - '#pragma ACCEL TILE FACTOR=auto{1}': Keep this loop whole, without dividing it into smaller parts.
      |   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:3: warning: character constant too long for its type
    7 | - '#pragma ACCEL PARALLEL FACTOR=auto{1}': The number of available processor cores is 1.
      |   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:8:3: warning: character constant too long for its type
=======
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 8192; i++) {
    sum = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 9; j++) {
      k_col = i - 4 + j;
      if (k_col < 0 || k_col > 8191) {
        k_col = 0;
      }
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{8}
      inner:
      for (k = 0; k < 9; k++) {
        k_row = k_col - 4 + k;
        if (k_row < 0 || k_row > 8191) {
          k_row = 0;
        }
        sum += filter[k] * orig[k_row];
      }
    }
    sol[i] = sum;
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 8192; i++) {
    sum = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 9; j++) {
      k_col = i - 4 + j;
      if (k_col < 0 || k_col > 8191) {
        k_col = 0;
      }
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        k_row = k_col - 4 + k;
        if (k_row < 0 || k_row > 8191) {
          k_row = 0;
        }
        sum += filter[k] * orig[k_row];
      }
    }
    sol[i] = sum;
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 8192; i++) {
    sum = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
