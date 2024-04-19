#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char M[16641],char E[16641],char F[16641],char P[16641],char trace[16642])
{
  int i;
  int j;
  int max;
  int score;
  int up_left;
  int up;
  int left;
  int u;
  int l;
  int max_i;
  int max_j;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (i = 0; i < 128; i++) {
    M[i] = SEQA[i];
    E[i] = 0 - 1;
    F[i] = i - 1;
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (i = 0; i < 128; i++) {
    M[128 + i] = SEQB[i];
    E[128 + i] = 0 - 1;
    F[128 + i] = i - 1;
  }
// Matrix multiplication loop
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  pad_out_row:
  for (i = 0; i < 128; i++) {
    M[i + 16640] = 0;
    E[i + 16640] = 0;
    F[i + 16640] = 0;
  }
// Matrix A(n) times B(m)
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  pad_out_col:
  for (i = 0; i < 128; i++) {
    M[i * 16641] = 0;
    E[i * 16641] = 0;
    F[i * 16641] = 0;
  }
  pad_in_row:
  for (i = 0; i < 127; i++) {
    M[i] = 0;
    E[i] = 0;
    F[i] = 0;
  }
  pad_in_col:
  for (i = 0; i < 127; i++) {
    M[i + 16640] = 0;
    E[i + 16640] = 0;
    F[i + 16640] = 0;
  }
  loop_i:
  for (i = 1; i < 128 - 1; i++) {
    loop_j:
    for (j = 1; j < 128 - 1; j++) {
      up_left = M[i - 1][j - 1] + ((SEQA[i - 1] == SEQB[j - 1]) ? 1 : (-1));
      up = M[i - 1][j] + (-1);
      left = M[i][j - 1] + (-1);
      max_i = (up_left > ((up > left) ? up : left)) ? i - 1 : ((up > left) ? i : (j - 1));
      max_j = (up_left > ((up > left) ? up : left)) ? j - 1 : ((up > left) ? i : j);
      score = ((SEQA[i - 1] == SEQB[j - 1]) ? 1 : (-1));
//#pragma ACCEL PIPELINE auto{__PIPE__L4}
//#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      loop_k:
      for (k = 1; k < 128 - 1; k++) {
        if (k == 1) {
          u = M[i][k - 1] + (-1);
        }
        else {
          u = M[i][k - 1] + ((M[i][k - 1] > M[i][k + 1]) ? 1 : (-1));
        }
        if (k == 1) {
          l = M[k - 1][j] + (-1);
        }
        else {
          l = M[k - 1][j] + ((M[k - 1][j] > M[k + 1][j]) ? 1 : (-1));
        }
        max = u > l ? u : l;
        max = max > 0 ? max : 0;
        max = max > up_left ? max : up_left;
        M[i][j] = max;
        if (M[i][j] == up_left) {
          if (max_i == i - 1 && max_j == j - 1) {
            trace[z] = 2;
            z++;
          }
          else if (max_i == i - 1) {
            trace[z] = 4;
            z++;
          }
          else if (max_j == j - 1) {
            trace[z] = 3;
            z++;
          }
          i = max_i;
          j = max_j;
        }
        else if (M[i][j] == u) {
          trace[z] = 1;
          z++;
          i = max_i;
        }
        else {
          trace[z] = 5;
          z++;
          j = max_j;
        }
      }
    }
  }
}