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
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx;
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx;
    ptr[b_idx * 64] = 0;
  }
// Matrix multiplication loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  mul_blk:
  for (a_idx = 1; a_idx < 64; a_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    mul_seq:
    for (b_idx = 1; b_idx < 64; b_idx++) {
      score = ((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1]) && ((int )SEQA[a_idx - 1]) != 0 ? 1 : ((int )SEQA[a_idx - 1]) == 0 ? -4 : -4;
      row_up = a_idx * 64;
      up_left = M[row_up + (b_idx - 1)] + score;
      up = M[row_up + b_idx] + -4;
      left = M[row_up + (b_idx - 1)] + -4;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[row_up + b_idx] = max;
      if (max == left) {
        ptr[row_up + b_idx] = 2;
      }
      
      if (max == up) {
        ptr[row_up + b_idx] = 1;
      }
      
      if (max == up_left) {
        ptr[row_up + b_idx] = 3;
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  a_idx = 63;
  b_idx = 63;
  a_str_idx = 0;
  b_str_idx = 0;
/*
    trace_str: for(r = 0; r < 64; r++) {
      alignedA[a_str_idx++] = SEQA[a_idx];
      alignedB[b_str_idx++] = SEQB[b_idx];
      if (ptr[a_idx*64+b_idx] == 0) {
        a_idx--;
        b_idx--;
      } else if (ptr[a_idx*64+b_idx] == 1) {
        a_idx--;
      } else if (ptr[a_idx*64+b_idx] == 2) {
        b_idx--;
      } else if (ptr[a_idx*64+b_idx] == 3) {
        a_idx--;
        b_idx--;
      }
    }
*/
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  trace:
  while (a_idx >= 0 && b_idx >= 0) {
    row = a_idx * 64;
    if (ptr[row + b_idx] == 0) {
      alignedA[a_str_idx++] = SEQA[a_idx];
      alignedB[b_str_idx++] = SEQB[b_idx];
      a_idx--;
      b_idx--;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    else if (ptr[row + b_idx] == 1) {
      alignedA[a_str_idx++] = SEQA[a_idx];
      alignedB[b_str_idx++] = '_';
      a_idx--;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    else if (ptr[row + b_idx] == 2) {
      alignedA[a_str_idx++] = '_';
      alignedB[b_str_idx++] = SEQB[b_idx];
      b_idx--;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    else if (ptr[row + b_idx] == 3) {
      alignedA[a_str_idx++] = SEQA[a_idx];
      alignedB[b_str_idx++] = SEQB[b_idx];
      a_idx--;
      b_idx--;
    }
  }
}