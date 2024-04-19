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
  int P[65536];
  int S[65536];
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_A_STR(A_str,SEQA);
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  init_B_STR(B_str,SEQB);
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  needwun_score_0:
  for (a_idx = 0; a_idx < 128; a_idx++) {
    A_str[a_idx] = A_str[a_idx] - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  needwun_score_1:
  for (b_idx = 0; b_idx < 128; b_idx++) {
    B_str[b_idx] = B_str[b_idx] - 1;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  needwun_score_2:
  for (a_idx = 0; a_idx < 126; a_idx++) {
    a_str_idx = 1 + a_idx;
    A_str[a_idx] = ((int )A_str[a_str_idx]) - ((int )32);
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  needwun_score_3:
  for (b_idx = 0; b_idx < 126; b_idx++) {
    b_str_idx = 1 + b_idx;
    B_str[b_idx] = ((int )B_str[b_str_idx]) - ((int )32);
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  needwun_score_4:
  for (a_idx = 0; a_idx < 128; a_idx++) {
    S[a_idx] = ((int )alignedA[a_idx]) - ((int )64);
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  needwun_score_5:
  for (b_idx = 0; b_idx < 128; b_idx++) {
    T[b_idx] = ((int )alignedB[b_idx]) - ((int )64);
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L5}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  needwun_score_6:
  for (a_idx = 0; a_idx < 128; a_idx++) {
    M[a_idx] = ((int )S[a_idx]) * ((int )T[a_idx]);
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
  needwun_score_7:
  for (a_idx = 0; a_idx < 128; a_idx++) {
    P[a_idx] = a_idx;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L7}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
  needwun_score_8:
  for (b_idx = 0; b_idx < 128; b_idx++) {
    Q[b_idx] = b_idx;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L8}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
  needwun_score_9:
  for (a_idx = 0; a_idx < 128; a_idx++) {
    row_up = A_str[a_idx] - 1;
//#pragma ACCEL PIPELINE auto{__PIPE__L9}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L9}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
    needwun_score_10:
    for (b_idx = 0; b_idx < 128; b_idx++) {
      up_left = M[S[row_up] + T[b_idx]];
      up = M[S[row_up] + B_str[b_idx]];
      left = M[S[a_idx] + T[b_idx]];
      max = (up_left > up ? up_left : up);
      max = (left > max ? left : max);
      M[S[a_idx] + B_str[b_idx]] = max + A_str[a_idx] * B_str[b_idx];
      if (max == left) {
        P[S[a_idx] + B_str[b_idx]] = 2;
      }
      
      if (max == up) {
        P[S[a_idx] + B_str[b_idx]] = 1;
      }
      
      if (max == up_left) {
        P[S[a_idx] + B_str[b_idx]] = 3;
      }
    }
  }
//#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L10}
  needwun_score_11:
  for (a_idx = 0; a_idx < 128; a_idx++) {
    r = 0;
    a_str_idx = A_str[a_idx];
    b_str_idx = B_str[a_idx];
    score = M[a_str_idx + b_str_idx];
    b_idx = b_str_idx;
    while (b_idx > 1) {
      if (P[a_str_idx + b_idx] == 2) {