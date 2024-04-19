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
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx * (-1);
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx * (-1);
    ptr[b_idx * 5] = 0;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  fill_in:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_row:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      a_str_idx = ((5 * a_idx) + 1);
      b_str_idx = ((5 * b_idx) + 1);
      score = ((SEQA[a_str_idx - 1] == SEQB[b_str_idx - 1]) ? 1 : 0);
      up_left = M[(b_str_idx - 1) * 5] + ((SEQA[a_str_idx - 1] == '\0') ? 1 : 0);
      up = M[b_str_idx * 5] + ((SEQA[a_str_idx - 1] == '\0') ? 1 : 0);
      left = M[a_str_idx] + ((SEQB[b_str_idx - 1] == '\0') ? 1 : 0);
      max = (up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left);
      M[b_str_idx * 5 + a_idx] = max + score;
      if (max == left) {
        ptr[b_str_idx * 5 + a_idx] = ((char )60);
      }
      
      if (max == up) {
        ptr[b_str_idx * 5 + a_idx] = ((char )94);
      }
      
      if (max == up_left) {
        ptr[b_str_idx * 5 + a_idx] = ((char )126);
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  row = 255;
  b_idx = 0;
  a_idx = 0;
  b_str_idx = ((5 * b_idx) + 1);
  a_str_idx = ((5 * a_idx) + 1);
/* Standardize from: // TraceBack
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  trace:
  while (1) {
    if (b_str_idx == ((5 * 5) + 1)) {
      break;
    }
    if (a_str_idx == ((5 * 5) + 1)) {
      break;
    }
    row_up = b_str_idx - 5;
    if (M[row_up * 5 + a_idx] >= M[b_str_idx * 5 + a_idx]) {
      if (M[row_up * 5 + a_idx] >= M[row_up * 5 + (a_idx + 1)]) {
        b_idx = row_up;
        b_str_idx = ((5 * b_idx) + 1);
      } else {
        a_idx++;
        a_str_idx = ((5 * a_idx) + 1);
      }
    } else {
      if (M[b_str_idx * 5 + a_idx] >= M[b_str_idx * 5 + (a_idx + 1)]) {
        a_idx++;
        a_str_idx = ((5 * a_idx) + 1);
      } else {
        a_idx++;
        a_str_idx = ((5 * a_idx) + 1);
      }
    }
  }
*/
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  pad_a:
  for (r = 0; r < 5; r++) {
    alignedA[r] = ((char )0);
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  pad_b:
  for (r = 0; r < 5; r++) {
    alignedB[r] = ((char )0);
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  trace_a:
  while (a_str_idx > 0) {
    if (ptr[b_str_idx * 5 + a_idx] == 60) {
      alignedA[row] = SEQA[a_str_idx - 1];
      alignedB[row] = SEQB[b_str_idx - 1];
      a_str_idx -= 1;
      b_str_idx -= 1;
      row--;
    } else {
      if (ptr[b_str_idx * 5 + a_idx] == 94) {
        alignedA[row] = SEQA[a_str_idx - 1];
        alignedB[row] = '\0';
        a_str_idx -= 1;
      } else {
        alignedA[row] = '\0';
        alignedB[row] = SEQB[b_str_idx - 1];
        b_str_idx -= 1;
      }
      row--;
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L5}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  trace_b:
  while (b_str_idx > 0) {
    if (ptr[b_str_idx * 5 + a_idx] == 62) {
      alignedA[row] = SEQA[a_str_idx - 1];
      alignedB[row] = SEQB[b_str_idx - 1];
      a_str_idx -= 1;
      b_str_idx -= 1;
      row--;
    } else {
      if (ptr[b_