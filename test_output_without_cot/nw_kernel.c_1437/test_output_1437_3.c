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
  int score_row;
  int a_str_idx_p1;
  int b_str_idx_p1;
  int a_str_idx_p2;
  int b_str_idx_p2;
  int a_str_idx_m1;
  int b_str_idx_m1;
  int a_str_idx_m2;
  int b_str_idx_m2;
  char a_char;
  char b_char;
  char a_char_up;
  char b_char_up;
  char a_char_left;
  char b_char_left;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_row:
  for (a_idx = 0; a_idx < 128; a_idx++) {
    M[a_idx] = a_idx * - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  init_col:
  for (b_idx = 0; b_idx < 128; b_idx++) {
    M[b_idx * 128] = b_idx * - 1;
  }
// Matrix filling loop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  fill_out:
  for (b_idx = 1; b_idx < 128 - 1; b_idx++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{128}
    fill_in:
    for (a_idx = 1; a_idx < 128 - 1; a_idx++) {
      a_str_idx = 128 * a_idx;
      b_str_idx = 128 * b_idx;
      a_str_idx_p1 = a_str_idx + 1;
      b_str_idx_p1 = b_str_idx + 1;
      a_str_idx_p2 = a_str_idx + 2;
      b_str_idx_p2 = b_str_idx + 2;
      a_str_idx_m1 = a_str_idx - 1;
      b_str_idx_m1 = b_str_idx - 1;
      a_str_idx_m2 = a_str_idx - 2;
      b_str_idx_m2 = b_str_idx - 2;
      a_char = ((SEQA[a_str_idx]) - 64);
      b_char = ((SEQB[b_str_idx]) - 64);
      a_char_up = ((SEQA[a_str_idx_p1]) - 64);
      b_char_up = ((SEQB[b_str_idx_p1]) - 64);
      a_char_left = ((SEQA[a_str_idx_m1]) - 64);
      b_char_left = ((SEQB[b_str_idx_m1]) - 64);
      up_left = M[b_str_idx_m1 * 128 + a_str_idx_m1] + ((a_char != b_char) ? 1 : 0);
      up = M[b_str_idx_m1 * 128 + a_str_idx] + ((a_char != b_char_up) ? 1 : 0);
      left = M[b_str_idx * 128 + a_str_idx_m1] + ((a_char != b_char_left) ? 1 : 0);
      max = (up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left);
      score = max - 1;
      M[b_str_idx * 128 + a_str_idx] = score;
      if (score == left) {
        ptr[b_str_idx * 128 + a_str_idx] = 2;
      }
      
#pragma ACCEL PIVOT FACTOR=auto{1}
      if (score == up) {
        ptr[b_str_idx * 128 + a_str_idx] = 1;
      }
      
#pragma ACCEL PIVOT FACTOR=auto{2}
      if (score == up_left) {
        ptr[b_str_idx * 128 + a_str_idx] = 3;
      }
    }
  }
// TraceBack (n.b. aligned sequences are backwards to avoid string appending)
  row = 127;
  score_row = 127 * 128;
  a_idx = 127;
  b_idx = 127;
  a_str_idx = 127 * 128;
  b_str_idx = 127 * 128;
  a_str_idx_p1 = a_str_idx + 1;
  b_str_idx_p1 = b_str_idx + 1;
  a_str_idx_p2 = a_str_idx + 2;
  b_str_idx_p2 = b_str_idx + 2;
  a_str_idx_m1 = a_str_idx - 1;
  b_str_idx_m1 = b_str_idx - 1;
  a_str_idx_m2 = a_str_idx - 2;
  b_str_idx_m2 = b_str_idx - 2;
  a_char = ((SEQA[a_str_idx]) - 64);
  b_char = ((SEQB[b_str_idx]) - 64);
  a_char_up = ((SEQA[a_str_idx_p1]) - 64);
  b_char_up = ((SEQB[b_str_idx_p1]) - 64);
  a_char_left = ((SEQA[a_str_idx_m1]) - 64);
  b_char_left = ((SEQB[b_str_idx_m1]) - 64);
  up_left = M[b_str_idx_m1 * 128 + a_str_idx_m1] + ((a_char != b_char) ? 1 : 0);
  up = M[b_str_idx_m1 * 128 + a_str_idx] + ((a_char != b_char_up) ? 1 : 0);
  left = M[b_str_idx * 128 + a_str_idx_m1] + ((a_char != b_char_left) ? 1 : 0);
  max = (up_left > ((up > left) ? up : left)) ? up_left : ((up > left) ? up : left);
  row_up = b_idx - 1;
  a_idx_up = a_idx - 1;
  b_idx_up = b_idx - 1;
  a_str_idx_up = a_str_idx - 1;
  b_str_idx_up = b_str_idx - 1;
  a_str_idx_up_p1 = a_str_idx_up + 1;
  b_str_idx_up_p1 = b_str_idx_up + 1;
  a_str_idx_up_p2 = a_str_idx_up + 2;
  b_str