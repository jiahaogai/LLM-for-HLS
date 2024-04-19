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
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx * - 1;
    ptr[a_idx] = 0;
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx * - 1;
    ptr[b_idx * 64] = 0;
  }
// Matrix multiplication loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  mul_out:
  for (a_idx = 1; a_idx < 64; a_idx++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    mul_in:
    for (b_idx = 1; b_idx < 64; b_idx++) {
      score = (SEQA[a_idx - 1] == SEQB[b_idx - 1]) ? 1 : (- 1);
      row_up = (a_idx - 1) * 64;
      row = a_idx * 64;
      up_left = M[row_up + b_idx - 1] + score;
      up = M[row_up + b_idx] - 1;
      left = M[row + b_idx - 1] - 1;
      max = (up_left > (up > left ? up : left)) ? up_left : (up > left ? up : left);
      M[row + b_idx] = max;
      if (max == left) {
        ptr[row + b_idx] = 2;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
      b_str_idx = b_idx * 128;
      a_str_idx = a_idx * 128;
      if (max == up) {
        ptr[row + b_idx] = 1;
        alignedA[a_str_idx + str_idx] = SEQA[a_idx - 1];
        alignedB[b_str_idx + str_idx] = '_';
      }
      
      if (max == left) {
        ptr[row + b_idx] = 0;
        alignedA[a_str_idx + str_idx] = '_';
        alignedB[b_str_idx + str_idx] = SEQB[b_idx - 1];
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  a_idx = 63;
  b_idx = 63;
  a_str_idx = a_idx * 128;
  b_str_idx = b_idx * 128;
/*
    trace: while(a_idx>0 || b_idx>0) {
        if(ptr[a_idx*64 + b_idx] == 0){
            alignedA[a_str_idx + STR_IDX] = '_';
            alignedB[b_str_idx + STR_IDX] = SEQB[b_idx - 1];
            b_idx--;
            b_str_idx -= 128;
        }
        else if(ptr[a_idx*64 + b_idx] == 1){
            alignedA[a_str_idx + STR_IDX] = SEQA[a_idx - 1];
            alignedB[b_str_idx + STR_IDX] = '_';
            a_idx--;
            a_str_idx -= 128;
        }
        else{
            alignedA[a_str_idx + STR_IDX] = SEQA[a_idx - 1];
            alignedB[b_str_idx + STR_IDX] = SEQB[b_idx - 1];
            a_idx--;
            b_idx--;
            a_str_idx -= 128;
            b_str_idx -= 128;
        }
        STR_IDX++;
    }
*/
}