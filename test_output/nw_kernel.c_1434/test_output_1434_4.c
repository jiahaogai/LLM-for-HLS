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
    M[a_idx] = a_idx;
    ptr[a_idx] = -1;
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 5; b_idx++) {
    M[b_idx * 5] = b_idx;
    ptr[b_idx * 5] = -1;
  }
// Matrix multiplication loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  mul_blk:
  for (a_idx = 0; a_idx < 5; a_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    mul_seq:
    for (b_idx = 0; b_idx < 5; b_idx++) {
      score = ((SEQA[a_idx] == SEQB[b_idx]) ? 1 : (-1));
      row_up = a_idx * 5;
      row = (a_idx + 1) * 5;
      up_left = M[row_up + b_idx];
      up = M[row_up + b_idx + 1];
      left = M[row + b_idx];
      up_left = left + ((up - left) > ((up_left - left) + score) ? ((up - left)) : ((up_left - left) + score));
      up = left + ((up - left) > ((up - up_left)) ? ((up - left)) : ((up - up_left)));
      M[row + b_idx + 1] = up;
      b_str_idx = ((b_idx == 0) ? 0 : (b_idx * 1));
      a_str_idx = ((a_idx == 0) ? 0 : (a_idx * 5));
      if (up_left < left) {
        if (up_left < up) {
          ptr[row + b_idx + 1] = row_up + b_idx + 1;
          alignedA[a_str_idx + 1] = '-';
          alignedB[b_str_idx + 1] = SEQB[b_idx];
        }
        else {
          ptr[row + b_idx + 1] = row_up + b_idx;
          alignedA[a_str_idx + 1] = SEQA[a_idx];
          alignedB[b_str_idx + 1] = SEQB[b_idx];
        }
      }
      else {
        if (left < up) {
          ptr[row + b_idx + 1] = row + b_idx;
          alignedA[a_str_idx + 1] = SEQA[a_idx];
          alignedB[b_str_idx + 1] = '-';
        }
        else {
          max = up_left;
          r = row_up + b_idx;
          r_up = row + b_idx;
          if (up > r_up) {
            max = up;
            r = r_up;
          }
          if (left > max) {
            max = left;
            r = row + b_idx;
          }
          ptr[row + b_idx + 1] = r;
          alignedA[a_str_idx + 1] = SEQA[a_idx];
          alignedB[b_str_idx + 1] = SEQB[b_idx];
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  a_idx = 4;
  b_idx = 4;
  a_str_idx = ((4) * 1);
  b_str_idx = ((4) * 1);
/*
    traceBack: while(a_idx != 0 || b_idx != 0) {
      if (ptr[a_idx*5+b_idx] == -1 ) {
        alignedA[a_str_idx++] = SEQA[a_idx];
        alignedB[b_str_idx++] = SEQB[b_idx];
        a_idx = a_idx - 1;
        b_idx = b_idx - 1;
      }
      else {
        if (ptr[a_idx*5+b_idx] < a_idx*5 + b_idx) {
          alignedA[a_str_idx++] = SEQA[a_idx];
          alignedB[b_str_idx++] = '-';
          a_idx = a_idx - 1;
        }
        else {
          alignedA[a_str_idx++] = '-';
          alignedB[b_str_idx++] = SEQB[b_idx];
          b_idx = b_idx - 1;
        }
      }
    }
*/
}