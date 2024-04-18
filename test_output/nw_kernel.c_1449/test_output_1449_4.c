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
  char a_char;
  char b_char;
  char a_char_up;
  char b_char_up;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 128 + 1; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (b_idx = 0; b_idx < 128 + 1; b_idx++) {
    M[b_idx * (128 + 1)] = b_idx * - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  fill_out:
  for (b_idx = 1; b_idx < 128 + 1; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    fill_in:
    for (a_idx = 1; a_idx < 128 + 1; a_idx++) {
      a_str_idx = 1 * a_idx;
      b_str_idx = 1 * b_idx;
      a_str_idx_p1 = a_str_idx + 1;
      b_str_idx_p1 = b_str_idx + 1;
      a_char = (char )0;
      b_char = SEQA[a_str_idx];
      a_char_up = SEQA[a_str_idx_p1];
      b_char_up = SEQB[b_str_idx];
      up_left = M[b_str_idx_p1 * (128 + 1) + a_str_idx_p1] + ((int )b_char == (int )a_char) * 1;
      up = M[b_str_idx_p1 * (128 + 1) + a_str_idx] + - 1;
      left = M[b_str_idx * (128 + 1) + a_str_idx_p1] + - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      score = max;
      M[b_str_idx * (128 + 1) + a_str_idx] = score;
      if (score == left) {
        ptr[b_str_idx * (128 + 1) + a_str_idx] = 2;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      if (score == up) {
        ptr[b_str_idx * (128 + 1) + a_str_idx] = 1;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L5}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
      if (score == up_left) {
        ptr[b_str_idx * (128 + 1) + a_str_idx] = (char )(b_str_idx_p1 * (128 + 1) + a_str_idx_p1);
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  row = 128;
  r = 0;
  b_idx = 128 + 1;
  a_idx = 128 + 1;
  b_str_idx = ((b_idx - 1) * (128 + 1)) + (a_idx - 1);
  a_str_idx = ((1 - 1) * (128 + 1)) + (a_idx - 1);
  a_str_idx_p1 = a_str_idx + 1;
  alignedA[r] = SEQA[a_str_idx];
  alignedB[r] = SEQB[b_str_idx];
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  trace:
  while (a_idx > 0 && b_idx > 0) {
    if (ptr[b_str_idx] == 2) {
      a_idx = a_str_idx;
      b_idx = b_str_idx;
      b_str_idx = ((b_idx - 1) * (128 + 1)) + (a_idx - 1);
      a_str_idx = ((1 - 1) * (128 + 1)) + (a_idx - 1);
      a_str_idx_p1 = a_str_idx + 1;
      r++;
      alignedA[r] = alignedA[r - 1];
      alignedB[r] = alignedB[r - 1];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L7}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
    if (ptr[b_str_idx] == 1) {
      a_idx = a_str_idx_p1;
      b_idx = b_str_idx;
      b_str_idx = ((b_idx - 1) * (128 + 1)) + (a_idx - 1);
      a_str_idx = ((1 - 1) * (128 + 1)) + (a_idx - 1);
      a_str_idx_p1 = a_str_idx + 1;
      r++;
      alignedA[r] = alignedA[r - 1];
      alignedB[r] = alignedB[r - 1];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L8}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
    if (ptr[b_str_idx] == 0) {
      a_idx = a_str_idx_p1;
      b_idx = b_str_idx_p1;
      b_str_idx = ((b_idx - 1) * (128 + 1)) + (a_idx - 1);
      a_str_idx = ((1 - 1) * (128 + 1)) + (a_idx - 1);
      a_str_idx_p1 = a_str_idx + 1;
      r++;
      alignedA[r] = SEQA[a_str_idx];
      alignedB[r] = SEQB[b_str_idx];
    }
  }
}