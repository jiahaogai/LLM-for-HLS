#pragma ACCEL kernel

void needwun(char seq1[128],char seq2[128],char aligned_seq1[128],char aligned_seq2[128],int scores[16641],char ptr[16641])
{
  int score;
  int up_left;
  int up;
  int left;
  int max;
  int row;
  int row_up;
  int r;
  int c;
  int index;
  int last_row;
  int last_row_up;
  char seq1_tmp;
  char seq2_tmp;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (r = 0; r < 128; r++) {
    aligned_seq1[r] = ((char )0);
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  init_col:
  for (r = 0; r < 128; r++) {
    aligned_seq2[r] = ((char )0);
  }
// Matrix score
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  init_score:
  for (r = 0; r < 128; r++) {
    aligned_seq1[r] = seq1[r];
    aligned_seq2[r] = seq2[r];
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    init_score_row:
    for (c = 0; c < 128; c++) {
      if (r == 0 || c == 0) {
        if (r == 0) {
          seq1_tmp = aligned_seq1[r];
        }
        if (c == 0) {
          seq2_tmp = aligned_seq2[c];
        }
        if (r == 0 && c == 0) {
          score = 0;
        }
        else if (seq1_tmp == seq2_tmp) {
          score = 1;
        }
        else {
          score = -1;
        }
      }
      else {
        up_left = scores[(((r - 1) * 128) + (c - 1))];
        up = scores[(((r - 1) * 128) + c)];
        left = scores[(((r) * 128) + (c - 1))];
        max = (up_left > ((up > left)?up:left))?up_left:((up > left)?up:left);
        row_up = (r - 1);
        row = r;
        index = ((row_up * 128) + c);
        if (max == left) {
          scores[index] = (score + ((int )'-'));
          ptr[index] = ((char )'D');
        }
        else {
          if (max == up) {
            scores[index] = (score + ((int )'|'));
            ptr[index] = ((char )'I');
          }
          else {
            scores[index] = (score + ((int )' '));
            ptr[index] = ((char )'M');
          }
        }
        seq1_tmp = aligned_seq1[row_up];
        seq2_tmp = aligned_seq2[c];
        score = scores[index];
      }
    }
  }
// TraceBack
  last_row = 127;
  last_row_up = 127;
  row = 127;
  c = 127;
  score = scores[(((last_row) * 128) + (last_row))];
  aligned_seq1[last_row] = seq1[last_row];
  aligned_seq2[last_row] = seq2[last_row];
/*
    trace: while(row > 0 || c > 0) {
      if (row == 0) {
        c--;
        aligned_seq1[0] = '-';
        aligned_seq2[0] = seq2[c];
        score = ((int )'-');
      }
      else if (c == 0) {
        row--;
        aligned_seq1[row] = seq1[row];
        aligned_seq2[row] = '-';
        score = ((int )'|');
      }
      else {
        up_left = scores[(((row - 1) * 128) + (c - 1))];
        up = scores[(((row - 1) * 128) + c)];
        left = scores[(((row) * 128) + (c - 1))];
        max = (up_left > ((up > left)?up:left))?up_left:((up > left)?up:left);
        if (max == left) {
          c--;
          row_up = row - 1;
          aligned_seq1[row] = aligned_seq1[row_up];
          aligned_seq2[row] = seq2[c];
          score = (score + ((int )'-'));
        }
        else {
          if (max == up) {
            row--;
            aligned_seq1[row] = seq1[row];
            aligned_seq2[row] = aligned_seq2[row + 1];
            score = (score + ((int )'|'));
          }
          else {
            aligned_seq1[row] = aligned_seq1[row_up];
            aligned_seq2[row] = aligned_seq2[c];
          }
        }
      }
    }
  }
*/
}