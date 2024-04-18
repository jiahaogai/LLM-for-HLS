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
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx;
    ptr[a_idx] = - 1;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx;
    ptr[b_idx * 64] = - 1;
  }
// Matrix multiplication loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  loop_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    a_str_idx = a_idx * 64;
    row = M[a_str_idx];
    row_up = M[a_str_idx + 64];
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    loop_col:
    for (b_idx = 0; b_idx < 64; b_idx++) {
      b_str_idx = b_idx * 64;
      left = row;
      up = row_up;
      up_left = M[b_str_idx + a_idx];
      score = ((int )SEQA[a_str_idx]) == ((int )SEQB[b_str_idx]) ? 1 : ((int )MISMATCH_SCORE);
      max = (up_left + score) > ((up + ((int )GAP_SCORE))) ? (up_left + score) : (up + ((int )GAP_SCORE));
      max = max > (left + ((int )GAP_SCORE)) ? max : left + ((int )GAP_SCORE);
      M[b_str_idx + a_idx] = max;
      if (max == up_left + score) {
        ptr[b_str_idx + a_idx] = 2;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      loop_r:
      for (r = 1; r < 64; r++) {
        r_idx = r * 64;
        up = left;
        left = M[r_idx + a_idx];
        up_left = M[r_idx + a_idx + 64];
        score = ((int )SEQA[r_idx + a_str_idx]) == ((int )SEQB[b_str_idx]) ? 1 : ((int )MISMATCH_SCORE);
        max = (up_left + score) > ((up + ((int )GAP_SCORE))) ? (up_left + score) : (up + ((int )GAP_SCORE));
        max = max > (left + ((int )GAP_SCORE)) ? max : left + ((int )GAP_SCORE);
        M[b_str_idx + a_idx + 64] = max;
        if (max == up_left + score) {
          ptr[b_str_idx + a_idx + 64] = 0;
        }
        
#pragma ACCEL PIPELINE auto{__PIPE__L4}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      }
    }
    row = M[a_str_idx + 64];
    row_up = M[a_str_idx + 128];
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  
#pragma ACCEL PIPELINE auto{__PIPE__L5}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  trace:
  for (a_idx = 50; a_idx > 0; a_idx--) {
    a_str_idx = (64 - 1 - a_idx) * 64;
    b_idx = 50;
    b_str_idx = (64 - 1 - b_idx) * 64;
    score = M[b_str_idx + a_str_idx];
    while(1) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L6}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      if (ptr[b_str_idx + a_str_idx] == - 1) {
        alignedA[0] = '\0';
        alignedB[0] = '\0';
        return;
      }
      else {
        if (ptr[b_str_idx + a_str_idx] == 0) {
          up = M[b_str_idx + a_str_idx + 64] + ((int )GAP_SCORE);
          left = M[b_str_idx + a_str_idx] + ((int )GAP_SCORE);
        }
        else {
          if (ptr[b_str_idx + a_str_idx] == 1) {
            up = M[b_str_idx + a_str_idx + 64] + ((int )GAP_SCORE);
            left = M[b_str_idx + a_str_idx] + ((int )MISMATCH_SCORE);
          }
          else {
            up = M[b_str_idx + a_str_idx + 64] + ((int )MISMATCH_SCORE);
            left = M[b_str_idx + a_str_idx] + ((int )GAP_SCORE);
          }
        }
      }
      if (up > left) {
        b_idx--;
        b_str_idx -= 64;
      }
      else {
        a_idx--;
        a_str_idx -= 64;
      }
      score = M[b_str_idx + a_str_idx];
    }
  }
  alignedA[0] = '\0';
  alignedB[0] = '\0';
}