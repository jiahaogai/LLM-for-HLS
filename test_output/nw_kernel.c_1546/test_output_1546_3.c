#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256])
{
  int score;
  int up_left;
  int up;
  int left;
  int max;
  int a_idx;
  int b_idx;
  int a_str_idx;
  int b_str_idx;