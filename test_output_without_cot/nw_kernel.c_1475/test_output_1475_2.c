#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[129],char alignedB[129],int M[16641],char ptr[16641])
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
      row_up = (b_idx - 1) * (128 + 1);
      up_left = M[row_up + (a_idx - 1)] + score;
      up = M[row_up + a_idx] + - 1;
      left = M[b_idx * (128 + 1) + (a_idx - 1)] + - 1;
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[b_idx * (128 + 1) + a_idx] = max;
      if (max == left) {
        ptr[b_idx * (128 + 1) + a_idx] = 2;
      }
       else {
        if (max == up) {
          ptr[b_idx * (128 + 1) + a_idx] = 1;
        }
         else {
          ptr[b_idx * (128 + 1) + a_idx] = 0;
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  row = ((128 + 1) * (128 + 1)) - 1;
  a_idx = 128;
  b_idx = 128;
  alignedA[a_idx] = '\0';
  alignedB[b_idx] = '\0';
/*
    trace: while(a_idx>0 || b_idx>0) {
      if (ptr[row] == 0) {
        a_idx--;
        b_idx--;
        alignedA[a_idx] = SEQA[a_idx];
        alignedB[b_idx] = SEQB[b_idx];
        row = row - ((128 + 1));
      }
       else
      if (ptr[row] == 1) {
        a_idx--;
        alignedA[a_idx] = SEQA[a_idx];
        alignedB[b_idx] = '_';
        row = row - ((128 + 1));
      }
       else
      if (ptr[row] == 2) {
        b_idx--;
        alignedA[a_idx] = '_';
        alignedB[b_idx] = SEQB[b_idx];
        row = row - 1;
      }
    }
    alignedA[a_idx] = '\0';
    alignedB[b_idx] = '\0';
  }
  */
}