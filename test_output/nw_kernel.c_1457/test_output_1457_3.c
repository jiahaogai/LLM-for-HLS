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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    alignedA[a_idx] = '-';
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    alignedB[b_idx] = '-';
  }
// Matrix initialization
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_main:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    init_str_a:
    for (b_idx = 0; b_idx < 64; b_idx++) {
      if (b_idx < a_idx) {
        M[a_idx * 64 + b_idx] = M[b_idx * 64 + a_idx];
        ptr[a_idx * 64 + b_idx] = ((char )1);
      }
      else if (b_idx == a_idx) {
        M[a_idx * 64 + b_idx] = 0;
        ptr[a_idx * 64 + b_idx] = ((char )0);
      }
      else {
        int _in_val;
        _in_val = 0;
        M[a_idx * 64 + b_idx] = _in_val;
        ptr[a_idx * 64 + b_idx] = ((char )2);
      }
    }
  }
// DP computation
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_a:
  for (a_idx = 1; a_idx < 64; a_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_b:
    for (b_idx = 1; b_idx < 64; b_idx++) {
      row_up = (a_idx - 1) * 64;
      up_left = M[row_up + (b_idx - 1)] + ((int )SEQA[a_idx - 1] != (int )SEQB[b_idx - 1]);
      up = M[row_up + b_idx] + ((int )SEQA[a_idx - 1] != (int )'*');
      left = M[a_idx * 64 + (b_idx - 1)] + ((int )SEQB[b_idx - 1] != (int )'*');
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      score = max - ((int )SEQA[a_idx] != (int )SEQB[b_idx]);
//#pragma ACCEL PARALLEL FACTOR=auto{1}
      if (a_idx == 1 && b_idx == 1) {
        M[a_idx * 64 + b_idx] = score;
        ptr[a_idx * 64 + b_idx] = ((char )0);
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      trace:
      if (score == left) {
        M[a_idx * 64 + b_idx] = left;
        ptr[a_idx * 64 + b_idx] = ((char )3);
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L5}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      else if (score == up) {
        M[a_idx * 64 + b_idx] = up;
        ptr[a_idx * 64 + b_idx] = ((char )1);
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L6}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      else if (score == up_left) {
        M[a_idx * 64 + b_idx] = up_left;
        ptr[a_idx * 64 + b_idx] = ((char )2);
      }
    }
  }
// TraceBack
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
  trace_a:
  for (a_idx = 56; a_idx >= 0; a_idx--) {
    a_str_idx = a_idx * 64;
    b_idx = 56;
    score = M[a_str_idx + b_idx];
    row_up = (a_idx + 1) * 64;
//#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
    trace_b:
    while (b_idx > 0) {
      b_str_idx = b_idx * 64;
      up_left = M[row_up + (b_idx - 1)];
      up = M[row_up + b_idx];
      left = M[a_str_idx + (b_idx - 1)];
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      if (score == left) {
        b_idx = b_idx - 1;
        b_str_idx = b_idx * 64;
        score = M[a_str_idx + b_idx];
      }
      else {
        if (score == up) {
          b_idx = b_idx - 1;
          b_str_idx = b_idx * 64;
          score = M[a_str_idx + b_idx];
        }
        else {
          b_idx = b_idx - 1;
          b_str_idx = b_idx * 64;
          score = M[a_str_idx + b_idx];
        }
      }
    }
    alignedA[a_idx + 64] = ((char )'\000');
    alignedB[b_idx + 64] = ((char )'\000');
    
#pragma ACCEL PIPELINE auto{__PIPE__L9}
    
#pragma ACCEL TILE FACTOR