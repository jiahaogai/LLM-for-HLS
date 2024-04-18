#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],int M[1664],char ptr[1664],int m,int n)
{
  int i;
  int j;
  int x;
  int y;
  int score;
  int up_left;
  int up;
  int left;
  i = 0;
  j = 0;
  x = 0;
  y = 0;
  while (i < 128) {
    j = 0;
    y = 4 * i;
    while (j < 128) {
      if (((int )SEQA[i]) == MATCH) {
        if (((int )SEQB[j]) == MATCH) {
          score = 2;
        } else {
          score = -4;
        }
      } else {
        if (((int )SEQB[j]) == MATCH) {
          score = -4;
        } else {
          score = 0;
        }
      }
      if (i == 0 && j == 0) {
        M[0] = 0;
        ptr[0] = 0;
      } else {
        if (i == 0) {
          up_left = M[j - 1] - 4;
          up = M[j] - 1;
          left = M[y] - 1;
          M[y] = (up_left > left)?up_left:left;
          ptr[y] = left - M[y];
        } else {
          if (j == 0) {
            up_left = M[y - 1] - 4;
            up = M[y] - 1;
            left = M[y - 1] - 1;
            M[y] = (up_left > up)?up_left:up;
            ptr[y] = up - M[y];
          } else {
            up_left = M[y - 1] - 4;
            up = M[y] - 1;
            left = M[y - 1] - 1;
            if (up_left > left) {
              if (up > up_left) {
                M[y] = up;
                ptr[y] = 1;
              } else {
                M[y] = up_left;
                ptr[y] = -1;
              }
            } else {
              if (up > left) {
                M[y] = up;
                ptr[y] = 1;
              } else {
                M[y] = left;
                ptr[y] = -1;
              }
            }
          }
        }
      }
      j++;
      y++;
    }
    i++;
  }
  i = 0;
  j = 0;
  x = 0;
  y = 0;
  while (i < 128) {
    j = 0;
    y = 4 * i;
    while (j < 128) {
      if (M[y] >= 0) {
        alignedA[x] = ((char )((int )SEQA[i]));
        alignedB[x] = ((char )((int )SEQB[j]));
        x++;
      }
      if (M[y] < 0) {
        alignedA[x] = ((char )((int )'-'));
        alignedB[x] = ((char )((int )SEQB[j]));
        x++;
        j++;
        y++;
      }
      if (M[y] == 0) {
        alignedA[x] = ((char )((int )SEQA[i]));
        alignedB[x] = ((char )((int )'-'));
        x++;
        i++;
      }
    }
    i++;
    y = 4 * i;
  }
}