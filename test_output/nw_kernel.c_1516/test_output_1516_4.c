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
  int a_idx_up;
  int b_idx_up;
  int a_idx_left;
  int b_idx_left;
  char a;
  char b;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 128 + 1; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_col:
  for (b_idx = 0; b_idx < 128 + 1; b_idx++) {
    M[b_idx * (128 + 1)] = b_idx * - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  fill_out:
  for (b_idx = 1; b_idx < 128 + 1; b_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    fill_in:
    for (a_idx = 1; a_idx < 128 + 1; a_idx++) {
      if (((int )SEQA[a_idx - 1]) == ((int )SEQB[b_idx - 1])) {
        score = 1;
      }
       else {
        score = - 1;
      }
      row_up = (b_idx - 1) * (128 + 1);
      row = b_idx * (128 + 1);
      up_left = M[row_up + (a_idx - 1)] + score;
      up = M[row_up + a_idx] - 1;
      left = M[row + (a_idx - 1)] - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[row + a_idx] = max;
      if (max == left) {
        ptr[row + a_idx] = ((char )60);
      }
       else {
        if (max == up) {
          ptr[row + a_idx] = ((char )94);
        }
         else {
          ptr[row + a_idx] = ((char )92);
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  a_idx = 128;
  b_idx = 128;
  a_idx_up = 128 + 1;
  b_idx_up = 128 + 1;
  a_idx_left = 128 + 1;
  b_idx_left = 128 + 1;
  a = ((char )0);
  b = ((char )0);
  r = 0;
/*
    trace_out:
    while (a_idx > 0 || b_idx > 0) {
      if (ptr[a_idx_left * (128 + 1) + b_idx] == ALIGN){
        a = SEQA[a_idx - 1];
        b = SEQB[b_idx - 1];
        a_idx--;
        b_idx--;
        alignedA[r] = a;
        alignedB[r] = b;
        r++;
      }
      else if (ptr[a_idx_left * (128 + 1) + b_idx] == SKIP_A){
        a = SEQA[a_idx - 1];
        b = '-';
        a_idx--;
        alignedA[r] = a;
        alignedB[r] = b;
        r++;
      }
      else if (ptr[a_idx_left * (128 + 1) + b_idx] == SKIP_B){
        a = '-';
        b = SEQB[b_idx - 1];
        b_idx--;
        alignedA[r] = a;
        alignedB[r] = b;
        r++;
      }
      a_idx_up = a_idx - 1;
      b_idx_up = b_idx - 1;
      a_idx_left = M[b_idx_left * (128 + 1) + a_idx];
      b_idx_left = M[b_idx_left * (128 + 1) + a_idx_up];
    }
*/
}