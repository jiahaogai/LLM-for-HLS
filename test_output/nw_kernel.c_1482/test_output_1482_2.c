#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[128],char alignedB[128],int M[1664],char ptr[1664],int m,int n)
{
  int i;
  int j;
  int x;
  int y;
  int score;
  int up_left;
  int up;
  int left;
  int max;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_scan:
  for (i = 0; i < 128; i++) {
    M[i] = ((int )SEQA[i]) * ((int )SEQB[0]);
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  init_row:
  for (i = 0; i < 128; i++) {
    M[i * 128] = ((int )SEQA[i]) * ((int )SEQB[0]);
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  loopj:
  for (j = 1; j < 128; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    loopi:
    for (i = 0; i < 128; i++) {
      score = ((int )SEQA[i]) * ((int )SEQB[j]) + M[i * 128 + (j - 1)];
      up_left = M[(i - 1) * 128 + (j - 1)];
      up = M[(i - 1) * 128 + j];
      left = M[i * 128 + (j - 1)];
      max = (up_left > up ? up_left : up);
      max = (left > max ? left : max);
      M[i * 128 + j] = score > max ? score : max;
      ptr[i * 128 + j] = ((int )0);
      if (score == max) {
        if (up_left == max) {
          ptr[i * 128 + j] |= 4;
        }
        if (up == max) {
          ptr[i * 128 + j] |= 2;
        }
        if (left == max) {
          ptr[i * 128 + j] |= 1;
        }
      }
    }
  }
// TraceBack
  x = 127;
  y = 127;
  alignedA[0] = '\0';
  alignedB[0] = '\0';
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  trace:
  while (x != 0 || y != 0) {
    if (ptr[y * 128 + x] == 4) {
      up_left = M[(x - 1) * 128 + (y - 1)];
      up = M[(x - 1) * 128 + y];
      left = M[x * 128 + (y - 1)];
      if (up_left >= up && up_left >= left) {
        x--;
        y--;
        alignedA[0] = ((char )((int )((int )SEQA[x]) + 48));
        alignedB[0] = ((char )((int )((int )SEQB[y]) + 48));
      }
      else if (up >= left) {
        x--;
        alignedA[0] = ((char )((int )((int )SEQA[x]) + 48));
        alignedB[0] = ((char )((int )((int )SEQB[y]) + 48));
      }
      else {
        y--;
        alignedA[0] = ((char )((int )((int )SEQA[x]) + 48));
        alignedB[0] = ((char )((int )((int )SEQB[y]) + 48));
      }
    }
    else if (ptr[y * 128 + x] == 2) {
      up = M[(x - 1) * 128 + y];
      left = M[x * 128 + (y - 1)];
      if (up >= left) {
        x--;
        alignedA[0] = ((char )((int )((int )SEQA[x]) + 48));
        alignedB[0] = ((char )((int )((int )SEQB[y]) + 48));
      }
      else {
        y--;
        alignedA[0] = ((char )((int )((int )SEQA[x]) + 48));
        alignedB[0] = ((char )((int )((int )SEQB[y]) + 48));
      }
    }
    else {
      left = M[x * 128 + (y - 1)];
      if (left >= 0) {
        y--;
        alignedA[0] = ((char )((int )((int )SEQA[x]) + 48));
        alignedB[0] = ((char )((int )((int )SEQB[y]) + 48));
      }
      else {
        x--;
        alignedA[0] = ((char )((int )((int )SEQA[x]) + 48));
        alignedB[0] = ((char )((int )((int )SEQB[y]) + 48));
      }
    }
  }
}