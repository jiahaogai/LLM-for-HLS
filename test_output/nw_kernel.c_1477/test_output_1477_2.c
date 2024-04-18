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
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx;
    ptr[a_idx] = - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx;
    ptr[b_idx * 64] = - 1;
  }
// Matrix multiplication loop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  fill_out:
  for (b_idx = 1; b_idx < 64; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    fill_out_a:
    for (a_idx = 1; a_idx < 64; a_idx++) {
      score = ((int )SEQA[a_idx - 1]) - 48 <=> ((int )SEQB[b_idx - 1]) - 48;
      row_up = (b_idx - 1) * 64;
      row = b_idx * 64;
      up_left = M[row_up + (a_idx - 1)] + score;
      up = M[row_up + a_idx] + - 1;
      left = M[row + (a_idx - 1)] + - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[row + a_idx] = max;
      if (max == left) {
        ptr[row + a_idx] = row + (a_idx - 1);
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      fill_out_b:
      for (b_str_idx = 0; b_str_idx < 13 - 1; b_str_idx++) {
        score = ((int )SEQA[a_idx - 1]) - 48 <=> ((int )SEQB[b_idx * 13 + b_str_idx]) - 48;
        up_left = M[row_up + (a_idx - 1) + 1] + score;
        up = M[row_up + a_idx + 1] + - 1;
        left = M[row + (a_idx - 1) + 1] + - 1;
        max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
        M[row + a_idx + 1] = max;
        if (max == left) {
          ptr[row + a_idx + 1] = row + (a_idx - 1) + 1;
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  a_idx = 63;
  b_idx = 63;
  a_str_idx = 0;
  b_str_idx = 0;
/*
    traceBack: while(a_idx > 0 || b_idx > 0) {
      if (a_idx * 64 + b_idx == 0) {
        break;
      }
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      if (b_idx == 0) {
        a_idx = ptr[a_idx * 64];
        alignedA[a_str_idx++] = SEQA[a_idx];
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      if (a_idx == 0) {
        b_idx = ptr[b_idx];
        alignedB[b_str_idx++] = SEQB[b_idx];
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      if (b_idx * 64 + a_idx == 64 * 64 - 1) {
        a_idx = ptr[a_idx * 64 + 1];
        alignedA[a_str_idx++] = SEQA[a_idx];
        b_idx = ptr[b_idx + 1];
        alignedB[b_str_idx++] = SEQB[b_idx];
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L5}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      else if (a_idx * 64 + b_idx == 64 * 64 - 1) {
        a_idx = ptr[a_idx + 1];
        alignedA[a_str_idx++] = SEQA[a_idx];
        b_idx = ptr[b_idx * 64 + 1];
        alignedB[b_str_idx++] = SEQB[b_idx];
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L6}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      else {
        if (M[b_idx * 64 + a_idx + 1] > M[b_idx * 64 + a_idx] && M[b_idx * 64 + a_idx + 1] > M[(b_idx + 1) * 64 + a_idx]) {
          b_idx = ptr[b_idx * 64 + a_idx + 1];
          alignedB[b_str_idx++] = SEQB[b_idx];
        }
        
#pragma ACCEL IF{M[b_idx * 64 + a_idx] > M[b_idx * 64 + a_idx + 1] && M[b_idx * 64 + a_idx] > M[(b_idx + 1) * 64 + a_idx]}
        if (M[b_idx * 64 + a_idx] > M[b_idx * 64 + a_idx + 1] && M[b_idx * 64 + a_idx] > M[(b_idx + 1) * 64 + a_idx]) {
          a_