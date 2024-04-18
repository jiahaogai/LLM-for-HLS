### ACCEL kernel
 #pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],int M[16641],char ptr[16641])
{
  int score;
  int up_left;
  int up;
  int left;
  int max;
  int row;
  int row_up;
  int r;
  int a_idx;
  int b_idx;
  int a_str_idx;
  int b_str_idx;
  int a_str_idx_p1;
  int b_str_idx_p1;
  char a;
  char b;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx * - 1;
  }
// Matrix multiplication: M = A*B
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loop_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    a_str_idx = a_idx * 16;
    a_str_idx_p1 = (a_idx + 1) * 16;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_col:
    for (b_idx = 0; b_idx < 64; b_idx++) {
      b_str_idx = b_idx * 16;
      score = ((int )SEQA[a_str_idx]) * ((int )SEQB[b_str_idx]);
      row_up = (a_idx + 1) * 64;
      row = a_idx * 64;
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      loop_inner_row:
      for (r = 0; r < 16; r++) {
        up_left = M[row_up + (b_idx + 15)] + ((int )SEQA[a_str_idx_p1 + r]) * (- 1) * ((int )SEQB[b_str_idx + 15]);
        up = M[row_up + b_idx] + ((int )SEQA[a_str_idx_p1 + r]) * (- 1);
        left = M[row + (b_idx + 15)] + ((int )SEQB[b_str_idx_p1 + r]) * (- 1);
        max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
        M[row + b_idx] = max;
        if (max == left) {
          ptr[row + b_idx] = 2;
        }
        
#pragma ACCEL PIPELINE auto{__PIPE__L3}
        if (max == up) {
          ptr[row + b_idx] = 1;
        }
        
#pragma ACCEL PIPELINE auto{}
      }
    }
  }
// TraceBack
  a_idx = 63;
  b_idx = 63;
  a_str_idx = a_idx * 16;
  b_str_idx = b_idx * 16;
/*
    traceBack:
    while (a_idx != 0 || b_idx != 0) {
      if (ptr[a_idx * 64 + b_idx] == 0) {
        a_idx = a_idx - 1;
        b_idx = b_idx - 1;
        a_str_idx = a_idx * 16;
        b_str_idx = b_idx * 16;
      }
      else if (ptr[a_idx * 64 + b_idx] == 1) {
        a_idx = a_idx - 1;
        b_str_idx = b_idx * 16;
      }
      else {
        b_idx = b_idx - 1;
        a_str_idx = a_idx * 16;
        b_str_idx = b_idx * 16;
      }
    }
  }
*/
  a = ((void *) 0);
  b = ((void *) 0);
/*
    trace:
    while (a_idx < 0 || b_idx < 0) {
      if (ptr[a_idx * 64 + b_idx] == 0) {
        a = SEQA[a_str_idx];
        b = SEQB[b_str_idx];
        a_idx = a_idx - 1;
        b_idx = b_idx - 1;
        a_str_idx = a_idx * 16;
        b_str_idx = b_idx * 16;
      }
      else if (ptr[a_idx * 64 + b_idx] == 1) {
        a = SEQA[a_str_idx];
        b = SEQB[b_str_idx + 15];
        a_idx = a_idx - 1;
        b_str_idx = b_idx * 16;
      }
      else {
        a = SEQA[a_str_idx + 15];
        b = SEQB[b_str_idx];
        a_str_idx = a_idx * 16;
        b_idx = b_idx - 1;
      }
      alignedA[a_idx + 8] = a;
      alignedB[b_idx + 8] = b;
    }
  }
*/
}