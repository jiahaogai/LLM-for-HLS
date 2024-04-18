#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256])
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
  int A_str[128];
  int B_str[128];
  int M[65536];
  int PTR[65536];
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_A_STR(A_str,SEQA);
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_B_STR(B_str,SEQB);
  a_str_idx = 0;
  a_idx = A_str[0];
  b_str_idx = 0;
  b_idx = B_str[0];
  row = 0;
  row_up = 1;
  M[0] = 0;
  PTR[SCORE_MISSING_VALUE] = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  init_M(M,SCORE_BLANK_A,SCORE_BLANK_B);
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  needwun_label1_: for (r = 1; r < 128; r++)
  {
    a_str_idx = A_str[r];
    b_str_idx = B_str[r];
    row_up = row_up + 1;
    row = row + 1;
    up_left = M[((row_up - 1) * 128) + (a_str_idx - 1)];
    up = M[((row_up - 1) * 128) + a_str_idx];
    left = M[((row - 1) * 128) + b_str_idx];
    max = (up_left > up ? up_left : up);
    max = (left > max ? left : max);
    M[((row * 128) + b_str_idx)] = max + SCORE_MATCH;
    if (max == left) {
      PTR[((row * 128) + b_str_idx)] = ((row_up * 128) + a_str_idx) - 1;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    needwun_label2_: for (b_idx = 1; b_idx < 128; b_idx++)
    {
      up_left = M[((row_up * 128) + (a_str_idx - 1))] + SCORE_MISSING_B;
      up = M[((row_up * 128) + a_str_idx)] + SCORE_MISSING_A;
      left = M[((row * 128) + b_str_idx)] + SCORE_MISSING_B;
      max = (up_left > up ? up_left : up);
      max = (left > max ? left : max);
      M[((row * 128) + b_str_idx)] = max;
      if (max == left) {
        PTR[((row * 128) + b_str_idx)] = ((row_up * 128) + a_str_idx) - 1;
      }
    }
  }
  a_idx = A_str[127];
  b_idx = B_str[127];
  score = M[((127 * 128) + 127)];
  alignedA[0] = (char )0;
  alignedB[0] = (char )0;
//#pragma ACCEL PIPELINE auto{off}
//#pragma ACCEL TILE FACTOR=auto{1}
//#pragma ACCEL PARALLEL FACTOR=auto{1}
  needwun_label3: for (r = 1; r < 128; r++) {
//#pragma ACCEL PIPELINE auto{__PIPE__L3}
//#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
//#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    needwun_label4: for (c = 1; c < 128; c++) {
      a_idx = PTR[((r * 128) + c)];
      b_idx = (c + 1) - 1;
      alignedA[(((128 - r) - 1) * 64) + 1] = SEQA[a_idx];
      alignedB[(((128 - c) - 1) * 64) + 1] = SEQB[b_idx];
    }
  }
}