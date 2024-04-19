#pragma ACCEL PARALLEL FACTOR=auto{2}
 #pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}

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
  char pad = '*';
  
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
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = - 1;
      }
      up_left = (M[(b_idx - 1) * (128 + 1) + (a_idx - 1)] + score);
      up = M[b_idx * (128 + 1) + (a_idx - 1)] + - 1;
      left = M[(b_idx - 1) * (128 + 1) + a_idx] + - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[b_idx * (128 + 1) + a_idx] = max;
      row_up = (b_idx - 1) * (128 + 1);
      if (max == left) {
        ptr[b_idx * (128 + 1) + a_idx] = ((char )((row_up + a_idx) + 1));
      }
       else {
        if (max == up) {
          ptr[b_idx * (128 + 1) + a_idx] = ((char )((row_up + a_idx - 1) + 1));
        }
         else {
          ptr[b_idx * (128 + 1) + a_idx] = ((char )((row_up + a_idx - 1) + 1));
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  a_idx = 128;
  b_idx = 128;
  a_str_idx = 0;
  b_str_idx = 0;
  r = 128 + 1;
  a_str_idx_p1 = a_str_idx + 1;
  b_str_idx_p1 = b_str_idx + 1;
/* Standardize from:
						
						#pragma ACCEL PIPELINE auto{flatten}
						
						#pragma ACCEL TILE FACTOR=auto{1}
						
						#pragma ACCEL PARALLEL FACTOR=auto{1}
						
*/
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  trace: while(a_idx != 0 || b_idx != 0) {
    row = b_idx * (128 + 1);
    if (((int )ptr[row + a_idx]) == ((int )((row + a_idx) + 1))) {
      a_idx++;
      b_idx++;
      alignedA[a_str_idx] = pad;
      alignedB[b_str_idx] = pad;
      a_str_idx = a_str_idx + 1;
      b_str_idx = b_str_idx + 1;
    }
     else {
      if (((int )ptr[row + a_idx]) == ((int )((row + a_idx - 1) + 1))) {
        a_idx--;
        b_idx++;
        a = SEQA[a_idx];
        alignedA[a_str_idx] = a;
        alignedB[b_str_idx] = pad;
        a_str_idx = a_str_idx + 1;
        b_str_idx = b_str_idx + 1;
      }
       else {
        if (((int )ptr[row + a_idx]) == ((int )((row + a_idx - 1) + 1))) {
          a_idx--;
          b_idx--;
          b = SEQB[b_idx];
          alignedA[a_str_idx] = b;
          alignedB[b_str_idx] = b;
          a_str_idx = a_str_idx + 1;
          b_str_idx = b_str_idx + 1;
        }
         else {
          a_idx--;
          b_idx--;
          a = SEQA[a_idx];
          b = SEQB[b_idx];
          alignedA[a_str_idx] = a;
          alignedB[b_str_idx] = b;
          a_str_idx = a_str_idx + 1;
          b_str_idx = b_str_idx + 1;
        }
      }
    }
  }
}