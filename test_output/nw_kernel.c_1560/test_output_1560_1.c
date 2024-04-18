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
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    alignedA[a_idx] = SEQA[a_idx];
    M[a_idx] = (- 1) * a_idx;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    alignedB[b_idx] = SEQB[b_idx];
    M[b_idx] = (- 1) * b_idx;
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  fill_out:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    fill_in:
    for (a_idx = 0; a_idx < 5; a_idx++) {
      score = 0;
      if ( ((int )SEQA[a_idx]) == ((int )SEQB[b_idx]) ) {
        score = 1;
      }
      a_str_idx = (a_idx + 1) << 3;
      b_str_idx = (b_idx + 1) << 3;
//#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      row_up = a_idx << 3;
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      row = b_str_idx;
      up_left = M[row_up] + ((int )SEQA[a_str_idx]);
      up = M[row_up + 1] + ((int )SEQA[a_str_idx + 1]);
      left = M[row] + ((int )SEQB[b_str_idx]);
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[b_str_idx] = max + score;
      ptr[b_str_idx] = ((max == up_left?2 : ((max == up?1 : 0))));
    }
  }
// TraceBack
  a_idx = 255;
  b_idx = 255;
  a_str_idx = 64;
  b_str_idx = 64;
  r = 32;
//#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  trace:
  while (1) {
//#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
    if (ptr[b_str_idx] == 0) {
      b_idx = b_str_idx;
      b_str_idx -= 1;
    }
//#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
    else if (ptr[b_str_idx] == 1) {
      a_idx = a_str_idx;
      b_idx = b_str_idx;
      a_str_idx -= 1;
      b_str_idx -= 1;
    }
//#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
    else {
      a_idx = a_str_idx;
      b_idx = b_str_idx;
      a_str_idx -= 1;
      up_left = M[a_str_idx] + M[b_str_idx];
      up = M[a_str_idx + 1] + M[b_str_idx];
      left = M[a_str_idx] + M[b_str_idx + 1];
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      if (max == up) {
        a_str_idx += 1;
      }
      if (max == left) {
        b_str_idx += 1;
      }
    }
    if (a_idx == 0 && b_idx == 0) {
      break;
    }
  }
}