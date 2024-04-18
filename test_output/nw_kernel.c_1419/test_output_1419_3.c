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
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_row:
  for (a_str_idx = 0; a_str_idx < 128 + 1; a_str_idx++) {
    M[a_str_idx] = a_str_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  init_col:
  for (b_str_idx = 0; b_str_idx < 128 + 1; b_str_idx++) {
    M[b_str_idx * (128 + 1)] = b_str_idx * - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (a_str_idx = 0; a_str_idx < 128; a_str_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_in:
    for (b_str_idx = 0; b_str_idx < 128; b_str_idx++) {
      a_str_idx_p1 = a_str_idx + 1;
      b_str_idx_p1 = b_str_idx + 1;
      up_left = ((int )M[b_str_idx * (128 + 1) + a_str_idx]) + ((int )SEQA[a_str_idx]);
      up = ((int )M[(b_str_idx * (128 + 1)) + a_str_idx_p1]) + ((int )SEQB[b_str_idx_p1]);
      left = ((int )M[b_str_idx_p1 * (128 + 1) + a_str_idx]) + ((int )SEQA[a_str_idx_p1]);
      max = (up_left > ((up > left?up : left))?up_left : ((up > left?up : left)));
      M[b_str_idx_p1 * (128 + 1) + a_str_idx_p1] = max;
      row = b_str_idx_p1 * (128 + 1);
      row_up = row + a_str_idx_p1;
      if (max == left) {
        ptr[row_up] = ((char )60);
      }
      else {
        if (max == up) {
          ptr[row_up] = ((char )94);
        }
        else {
          ptr[row_up] = ((char )124);
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  a_idx = 128;
  b_idx = 128;
  a_str_idx = 128 + 1;
  b_str_idx = (128 + 1) * 128;
/*
    traceBack: while(a_idx > 0 || b_idx > 0) {
      b_str_idx = b_idx*(ALEN + 1);
      if (ptr[b_str_idx + a_idx] == ALIGN){
        alignedA[a_idx] = SEQA[a_idx];
        alignedB[b_idx] = SEQB[b_idx];
        a_idx--;
        b_idx--;
      }
      else if (ptr[b_str_idx + a_idx] == SKIP_A){
        alignedA[a_idx] = '-';
        alignedB[b_idx] = SEQB[b_idx];
        b_idx--;
      }
      else{ // SKIP_B
        alignedA[a_idx] = SEQA[a_idx];
        alignedB[b_idx] = '-';
        a_idx--;
      }
    }
  }
*/
}