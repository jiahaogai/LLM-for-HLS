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
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  init_row:
  for (a_idx = 0; a_idx < 52; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_col:
  for (b_idx = 0; b_idx < 52; b_idx++) {
    M[b_idx * 52] = b_idx * - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (b_idx = 1; b_idx < 52; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    fill_inner:
    for (a_idx = 1; a_idx < 52; a_idx++) {
      a_str_idx = 52 * a_idx;
      b_str_idx = 52 * b_idx;
      a_str_idx_p1 = a_str_idx + 1;
      b_str_idx_p1 = b_str_idx + 1;
      a = (SEQA[a_str_idx]);
      b = (SEQB[b_str_idx]);
      score = (((a == b) ? 1 : 0)) + M[b_str_idx_p1 * 52 + a_idx_p1];
      up_left = M[b_str_idx_p1 * 52 + a_idx] + (- 1);
      up = M[b_str_idx_p1 * 52 + a_idx_p1 + 52] + (- 1);
      left = M[b_str_idx * 52 + a_idx_p1] + (- 1);
      max = (score > ((up_left > left) ? up_left : left)) ? score : ((up_left > left) ? up_left : left);
      M[b_str_idx_p1 * 52 + a_idx] = max;
      row_up = b_str_idx_p1 * 52;
      if (max == left) {
        ptr[row_up + a_idx_p1] = ((int )6);
      }
      
      if (max == up_left) {
        if (M[b_str_idx_p1 * 52 + a_idx_p1] == M[b_str_idx * 52 + a_idx_p1 + 1]) {
          ptr[row_up + a_idx_p1] = ((int )1);
        }
        
        if (M[b_str_idx_p1 * 52 + a_idx_p1] == M[b_str_idx * 52 + a_idx_p1]) {
          ptr[row_up + a_idx_p1] = ((int )2);
        }
        
        if (M[b_str_idx_p1 * 52 + a_idx_p1] == M[b_str_idx_p1 * 52 + a_idx_p1 + 1]) {
          ptr[row_up + a_idx_p1] = ((int )3);
        }
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  row = 51 * 52;
  r = 0;
  a_idx = 51;
  b_idx = 51;
  a_str_idx = (51 * 52) + 51;
  b_str_idx = (51 * 52) + 51;
/*
    traceBack: while(a_idx>0 || b_idx>0) {
      b_str_idx = b_idx*52;
      a_str_idx = a_idx*52;
      if (ptr[b_str_idx + a_idx] == 0) {
        a_idx--;
        b_idx--;
        a = SEQA[a_str_idx];
        b = SEQB[b_str_idx];
        alignedA[r] = a;
        alignedB[r] = b;
        r++;
      }
      else if (ptr[b_str_idx + a_idx] == 1) {
        a_idx--;
        a = SEQA[a_str_idx];
        alignedA[r] = a;
        alignedB[r] = '_';
        r++;
      }
      else if (ptr[b_str_idx + a_idx] == 2) {
        b_idx--;
        b = SEQB[b_str_idx];
        alignedA[r] = '_';
        alignedB[r] = b;
        r++;
      }
      else if (ptr[b_str_idx + a_idx] == 3) {
        a_idx--;
        b_idx--;
        a = SEQA[a_str_idx];
        b = SEQB[b_str_idx];
        alignedA[r] = a;
        alignedB[r] = b;
        r++;
        alignedA[r] = '_';
        alignedB[r] = '_';
        r++;
      }
    }
    alignedA[r] = 0;
    alignedB[r] = 0;
*/
}