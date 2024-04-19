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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx * - 1;
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx * - 1;
    ptr[b_idx * 64] = 0;
  }
// Matrix multiplication loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  loop_row:
  for (a_idx = 1; a_idx < 64; a_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    loop_col:
    for (b_idx = 1; b_idx < 64; b_idx++) {
      a = (SEQA[a_idx * 64 - 1]);
      b = (SEQB[b_idx * 64 - 1]);
      up_left = M[(b_idx - 1) * 64 + (a_idx - 1)] + ((a == b) ? 1 : - 1);
      up = M[(b_idx - 1) * 64 + a_idx] + - 1;
      left = M[b_idx * 64 + (a_idx - 1)] + - 1;
      max = (up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left);
      score = ((up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left));
      row_up = (b_idx - 1) * 64;
      M[b_idx * 64 + a_idx] = score;
      if (score == left) {
        ptr[b_idx * 64 + a_idx] = 2;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      loop_filler:
      for (r = 0; r < 1; r++) {
        row = row_up + a_idx;
        a_idx_up = (a_idx - 1);
        b_idx_up = (b_idx - 1) * 64;
        a_idx_left = (a_idx - 1) * 64;
        b_idx_left = (b_idx - 1);
        a = ((a_idx_up < 0) ? 0 : ((b_idx_up < 0) ? 0 : SEQA[a_idx_up]));
        b = ((b_idx_up < 0) ? 0 : ((a_idx_left < 0) ? 0 : SEQB[b_idx_up]));
        up_left = M[b_idx_left + a_idx_left] + ((a == b) ? 1 : - 1);
        up = M[b_idx_left + a_idx] + - 1;
        left = M[b_idx_left + a_idx_left] + - 1;
        max = (up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left);
        score = ((up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left));
        M[row] = score;
        if (score == left) {
          ptr[row] = 2;
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  a_idx = 63;
  b_idx = 63;
  row = 63 * 64;
  alignedA[row] = '\0';
  alignedB[row] = '\0';
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  trace: while(a_idx || b_idx) {
    if (ptr[b_idx * 64 + a_idx] == 0) {
      a--;
      b--;
      a_idx--;
      b_idx--;
      alignedA[row] = a;
      alignedB[row] = b;
      row -= 64;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    else if (ptr[b_idx * 64 + a_idx] == 1) {
      a--;
      alignedA[row] = a;
      alignedB[row] = '_';
      row -= 64;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
    else if (ptr[b_idx * 64 + a_idx] == 2) {
      b--;
      alignedA[row] = '_';
      alignedB[row] = b;
      row -= 64;
    }
  }
}