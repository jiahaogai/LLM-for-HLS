Code: #pragma ACCEL PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: #  ifndef _P_
Code: #    define _P_ 8192
Code: #  endif
Code: #  ifndef _S_
Code: #    define _S_ 8192
Code: #  endif
Code: 
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: int filter[9] = {1, 1, 1, 1, 0, 1, 1, 1, 1};
Code: int sum;
Code: int i;
Code: int j;
Code: int k;
Code: int x;
Code: int y;
Code: int orig[8192];
Code: int sol[8192];
Code: int k_col;
Code: int i_col;
Code: int k_row;
Code: int i_row;
Code: int pad;
Code: pad = 4;
Code: i_row = 4;
Code: i_col = 4;
Code: k_row = 3;
Code: k_col = 3;
Code: sum = 0;
Code: y = 0;
Code: 
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: while (y < 4100) {
Code:   sum = 0;
Code:   j = 0;
Code:   
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code:   while (j < 4100) {
Code:     x = 0;
Code:     
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code:     while (x < 3) {
Code:       sum = sum + orig[((pad + i_row - 1) + (pad + i_col - 1) * 4100) + x] * filter[x];
Code:       x++;
Code:     }
Code:     sol[y] = sum;
Code:     j = j + 4100;
Code:     y++;
Code:   }
Code:   i_col = i_col + 1;
Code:   if (i_col > 4100) {
Code:     i_col = 4;
Code:     i_row = i_row + 1;
Code:   }
Code:   if (i_row > 4100) {
Code:     i_row = 4;
Code:   }
Code:   sum = 0;
Code: }