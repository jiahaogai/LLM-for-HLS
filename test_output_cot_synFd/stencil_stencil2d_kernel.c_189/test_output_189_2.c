#pragma ACCEL kernel

void stencil(int orig[400],int sol[400],int filter[25])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int row;
  int col;
  int row_up;
  int row_down;
  int col_up;
  int col_down;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_up:
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    loop_left:
    for (j = 1; j < 400 - 1; j++) {
      i_col = -1 * i;
      col_up = i_col + 400;
      j_col = -1 * j;
      col_down = j_col + 400;
      row_up = col_up + 1;
      row_down = col_down + 1;
      sol[i] = ((orig[col_down] + orig[col_up]) + (orig[row_down] + orig[row_up])) - (orig[j_col] + orig[j_col + 1] + orig[j_col + 2] + orig[j_col + 3] + orig[j_col + 4] + orig[j_col + 5] + orig[j_col + 6] + orig[j_col + 7] + orig[j_col + 8] + orig[j_col + 9] + orig[j_col + 10] + orig[j_col + 11] + orig[j_col + 12] + orig[j_col + 13] + orig[j_col + 14] + orig[j_col + 15] + orig[j_col + 16] + orig[j_col + 17] + orig[j_col + 18] + orig[j_col + 19] + orig[j_col + 20] + orig[j_col + 21] + orig[j_col + 22] + orig[j_col + 23] + orig[j_col + 24] + orig[j_col + 25] + orig[j_col + 26] + orig[j_col + 27] + orig[j_col + 28] + orig[j_col + 29] + orig[j_col + 30] + orig[j_col + 31] + orig[j_col + 32] + orig[j_col + 33] + orig[j_col + 34] + orig[j_col + 35] + orig[j_col + 36] + orig[j_col + 37] + orig[j_col + 38] + orig[j_col + 39] + orig[j_col + 40] + orig[j_col + 41] + orig[j_col + 42] + orig[j_col + 43] + orig[j_col + 44] + orig[j_col + 45] + orig[j_col + 46] + orig[j_col + 47] + orig[j_col + 48] + orig[j_col + 49] + orig[j_col + 50] + orig[j_col + 51] + orig[j_col + 52] + orig[j_col + 53] + orig[j_col + 54] + orig[j_col + 55] + orig[j_col + 56] + orig[j_col + 57] + orig[j_col + 58] + orig[j_col + 59] + orig[j_col + 60] + orig[j_col + 61] + orig[j_col + 62] + orig[j_col + 63] + orig[j_col + 64] + orig[j_col + 65] + orig[j_col + 66] + orig[j_col + 67] + orig[j_col + 68] + orig[j_col + 69] + orig[j_col + 70] + orig[j_col + 71] + orig[j_col + 72] + orig[j_col + 73] + orig[j_col + 74] + orig[j_col + 75] + orig[j_col + 76] + orig[j_col + 77] + orig[j_col + 78] + orig[j_col + 79] + orig[j_col + 80] + orig[j_col + 81] + orig[j_col + 82] + orig[j_col + 83] + orig[j_col + 84] + orig[j_col + 85] + orig[j_col + 86] + orig[j_col + 87] + orig[j_col + 88] + orig[j_col + 89] + orig[j_col + 90] + orig[j_col + 91] + orig[j_col + 92] + orig[j_col + 93] + orig[j_col + 94] + orig[j_col + 95] + orig[j_col + 96] + orig[j_col + 97] + orig[j_col + 98] + orig[j_col + 99] + orig[j_col + 100] + orig[j_col + 101] + orig[j_col + 102] + orig[j_col + 103] + orig[j_col + 104] + orig[j_col + 105] + orig[j_col + 106] + orig[j_col + 107] + orig[j_col + 108] + orig[j_col + 109] + orig[j_col + 110] + orig[j_col + 111] + orig[j_col + 112] + orig[j_col + 113] + orig[j_col + 114] + orig[j_col + 115] + orig[j_col + 116] + orig[j_col + 117] + orig[j_col + 118] + orig[j_col + 119] + orig[j_col + 120] + orig[j_col + 121] + orig[j_col + 122] + orig[j_col + 123] + orig[j_col + 124] + orig[j_col + 125] + orig[j_col + 127] + orig[j_col + 126]) / 25;
    }
  }
}