c
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
  char a;
  char b;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    M[a_idx] = a_idx;
    alignedA[a_idx] = '-';
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx;
    alignedB[b_idx] = '-';
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (b_idx = 1; b_idx < 5; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_in:
    for (a_idx = 1; a_idx < 5; a_idx++) {
      a_str_idx = ((5 * a_idx) - 1);
      b_str_idx = ((5 * b_idx) - 1);
      a_str_idx_p1 = ((5 * a_idx) - 1) + 1;
      b_str_idx_p1 = ((5 * b_idx) - 1) + 1;
      a = ((char )*((SEQA + a_str_idx)));
      b = ((char )*((SEQB + b_str_idx)));
      up_left = M[b_str_idx_p1 + a_str_idx_p1];
      up = M[b_str_idx_p1 + a_str_idx] + 1;
      left = M[b_str_idx_p1 + a_str_idx_p1] + 1;
      if (((int )a) == ((int )b)) {
        score = 0;
      }
       else {
        score = 1;
      }
      max = (up_left > ((up > left)?up : left))?up_left : ((up > left)?up : left);
      M[b_str_idx_p1 + a_str_idx_p1] = max;
      if (max == left) {
        row = b_idx_p1;
      }
       else {
        if (max == up) {
          row = b_idx;
        }
         else {
          row = b_idx_p1 + a_idx_p1;
        }
      }
      ptr[b_str_idx_p1 + a_str_idx_p1] = ((char )(row + 1));
      if (((int )a) != ((int )b)) {
        alignedA[a_str_idx_p1] = a;
        alignedB[b_str_idx_p1] = '-';
      }
       else {
        alignedA[a_str_idx_p1] = '-';
        alignedB[b_str_idx_p1] = b;
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  row = 5L;
  a_idx = 5L;
  b_idx = 0L;
  a_str_idx = ((5 * a_idx) - 1);
  b_str_idx = ((5 * b_idx) - 1);
  a = ((char )*((SEQA + a_str_idx)));
  b = ((char )*((SEQB + b_str_idx)));
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  trace:
  while(1) {
//#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    if (((int )a) == ((int )b)) {
      alignedA[a_str_idx] = a;
      alignedB[b_str_idx] = b;
      a_str_idx --;
      b_str_idx --;
      a_idx --;
      b_idx --;
      b = ((char )*((SEQB + b_str_idx)));
      a = ((char )*((SEQA + a_str_idx)));
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    else if (row > ((5 - 1) * (5 - 1))) {
      alignedA[a_str_idx] = a;
      alignedB[b_str_idx] = b;
      a_str_idx --;
      b_str_idx --;
      a_idx --;
      b_idx --;
      b = ((char )*((SEQB + b_str_idx)));
      a = ((char )*((SEQA + a_str_idx)));
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    else {
      row_up = ((b_idx + 1) * 5) - 1;
      if (M[row_up + a_idx] > M[row + a_idx]) {
        b_idx = ptr[row_up + a_idx] - 1L;
        b_str_idx = ((b_idx * 5) - 1);
        b = ((char )*((SEQB + b_str_idx)));
      }
       else {
        a_idx = ptr[row + a_idx] - 1L;
        a_str_idx = ((a_idx * 5) - 1);
        a = ((char )*((SEQA + a_str_idx)));
      }
    }
  }
}