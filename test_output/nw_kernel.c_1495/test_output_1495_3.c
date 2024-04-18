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
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx;
    ptr[a_idx] = - 1;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx;
    ptr[b_idx * 64] = - 1;
  }
// Matrix multiplication loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  mul_blk:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    mul_seq:
    for (b_idx = 0; b_idx < 64; b_idx++) {
      a_str_idx = a_idx * 8;
      b_str_idx = b_idx * 8;
      score = ((int )SEQA[a_str_idx + 0]) * ((int )SEQB[b_str_idx + 0]) + ((int )SEQA[a_str_idx + 1]) * ((int )SEQB[b_str_idx + 1]) + ((int )SEQA[a_str_idx + 2]) * ((int )SEQB[b_str_idx + 2]) + ((int )SEQA[a_str_idx + 3]) * ((int )SEQB[b_str_idx + 3]) + ((int )SEQA[a_str_idx + 4]) * ((int )SEQB[b_str_idx + 4]) + ((int )SEQA[a_str_idx + 5]) * ((int )SEQB[b_str_idx + 5]) + ((int )SEQA[a_str_idx + 6]) * ((int )SEQB[b_str_idx + 6]) + ((int )SEQA[a_str_idx + 7]) * ((int )SEQB[b_str_idx + 7]);
      row_up = a_idx * 64;
      row = (a_idx + 1) * 64;
      up_left = M[row_up + b_idx];
      up = M[row_up + b_idx + 1];
      left = M[row + b_idx];
      max = (up_left + ((int )SEQA[a_str_idx + 0]) * ((int )SEQB[b_str_idx + 0]));
      up = up + ((int )SEQA[a_str_idx + 1]) * ((int )SEQB[b_str_idx + 1]);
      max = (up > max?up : max);
      left = left + ((int )SEQA[a_str_idx + 1]) * ((int )SEQB[b_str_idx + 0]);
      max = (left > max?left : max);
      M[row + b_idx + 1] = max;
      if (max == left) {
        ptr[row + b_idx + 1] = ((int )64) + b_idx;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      blk:
      for (r = 2; r < 8; r++) {
        up_left = M[row_up + b_idx + r];
        up = M[row_up + 1 + (b_idx + r)];
        left = M[row + (b_idx + r)];
        max = (up_left + ((int )SEQA[a_str_idx + r]) * ((int )SEQB[b_str_idx + 0]));
        up = up + ((int )SEQA[a_str_idx + r + 1]) * ((int )SEQB[b_str_idx + 1]);
        max = (up > max?up : max);
        left = left + ((int )SEQA[a_str_idx + r + 1]) * ((int )SEQB[b_str_idx + r]);
        max = (left > max?left : max);
        M[row + (b_idx + r)] = max;
        if (max == left) {
          ptr[row + (b_idx + r)] = ((int )64) + b_idx + r;
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  a_idx = 63;
  b_idx = 63;
  a_str_idx = ((int )64) * 8 - 1;
  b_str_idx = ((int )64) * 8 - 1;
/*
    trace: while(a_idx >= 0 && b_idx >= 0) {
      if (ptr[a_idx*64 + b_idx] == -1){
        alignedA[a_str_idx--] = SEQA[a_idx*8];
        alignedB[b_str_idx--] = SEQB[b_idx*8];
        a_idx--;
        b_idx--;
      }
      else {
        if (ptr[a_idx*64 + b_idx] == a_idx + 1){
          alignedA[a_str_idx--] = '-';
          alignedB[b_str_idx--] = SEQB[b_idx*8];
          b_idx--;
        }
        else{
          if (ptr[a_idx*64 + b_idx] == b_idx + 1){
            alignedA[a_str_idx--] = SEQA[a_idx*8];
            alignedB[b_str_idx--] = '-';
            a_idx--;
          }
          else{
            alignedA[a_str_idx--] = SEQA[a_idx*8];
            alignedB[b_str_idx--] = SEQB[b_idx*8];
            a_idx -= ptr[a_idx*64 + b_idx];
            b_idx -= ptr[a_idx*64 + b_idx];
          }
        }
      }
    }
    trace: while(a_str_idx >= 0) {
      alignedA[a_str_idx] = SEQA[a_idx*8];
      a_str_idx--;
      a_idx--;
    }
    trace: while(b_str_idx >= 0) {
      alignedB[b_str_idx] = SEQB[b_idx*8];
      b_str_idx--;
      b_idx--;
    }
*/
}