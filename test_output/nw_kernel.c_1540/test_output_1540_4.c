#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],int M[128][128])
{
  int a;
  int b;
  int score;
  int up_left;
  int up;
  int left;
  int max;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_A:
  for (a = 0; a < 5; a++) {
    alignedA[a] = SEQA[a];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_B:
  for (a = 0; a < 5; a++) {
    alignedB[a] = '-';
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  init_M:
  for (a = 0; a < 5; a++) {
    alignedB[a + 5] = SEQB[a];
    init_A_row:
    for (b = 0; b < 5; b++) {
      if (a == 0 && b == 0) {
        M[b][a] = ((int )SEQA[0]) * ((int )SEQB[0]) * 1;
      }
      
      else if (a == 0) {
        M[b][a] = M[b][a + 1] - 1;
      }
      
      else if (b == 0) {
        M[b][a] = M[a + 1][b] - 1;
      }
      
      else {
        up_left = M[b][a - 1] + ((int )SEQA[a]) * ((int )SEQB[b]) - ((int )SEQA[a]) * ((int )SEQB[a]);
        up = M[b][a + 1] - 1;
        left = M[a + 1][b] - 1;
        M[b][a] = (up_left > ((int )0)) ? ((up_left > left) ? up_left : left) : ((up > left) ? up : left);
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  track:
  for (a = 0; a < 5; a++) {
    alignedB[a + 11] = SEQB[a];
    trace_A_row:
    for (b = 0; b < 5; b++) {
      score = M[b + 1][a + 1];
      up = M[b][a + 1] - 1;
      left = M[b + 1][a] - 1;
      max = ((up > left) ? up : left);
      max = (score > max) ? score : max;
      up_left = M[b][a] + ((int )SEQA[a]) * ((int )SEQB[b]) - ((int )SEQA[a]) * ((int )SEQB[a]);
      M[b][a] = (max == left) ? left : ((max == up) ? up : ((max == up_left) ? up_left : ((int )0)));
    }
  }
}