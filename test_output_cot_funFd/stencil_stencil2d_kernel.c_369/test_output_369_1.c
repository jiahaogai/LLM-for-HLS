Code: #pragma ACCEL PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{2}
Code: #pragma ACCEL PARALLEL FACTOR=auto{16}
Code: int filter[9] = {1, 1, 1, 1, 0, 1, 1, 1, 1};
Code: int i;
Code: int j;
Code: int k;
Code: int x;
Code: int y;
Code: int orig_row;
Code: int orig_col;
Code: int sol_row;
Code: int sol_col;
Code: int off;
Code: orig_row = 0;
Code: orig_col = 0;
Code: sol_row = 0;
Code: sol_col = 0;
Code: off = 45;
Code: 
Code: 
Code: #pragma ACCEL PIPELINE auto{flatten}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: int sum;
Code: sum = 0;
Code: i = -4;
Code: 
Code: 
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: int row;
Code: row = 0;
Code: 
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: int col;
Code: col = 0;
Code: 
Code: sum += orig[row * 64 + col] * filter[i + 4];
Code: 
Code: sol[sol_row * 64 + sol_col] = sum;
Code: if (sol_col == 63) {
Code: sol_col = 0;
Code: sol_row++;
Code: }
Code: else {
Code: sol_col++;
Code: }
Code: 
Code: 
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: int sum;
Code: sum = 0;
Code: i = -4;
Code: 
Code: 
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: int row;
Code: row = 1;
Code: 
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: int col;
Code: col = -4;
Code: 
Code: sum += orig[row * 64 + col] * filter[i + 4];
Code: 
Code: col = -3;
Code: 
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: sum += orig[row * 64 + col] * filter[i + 4];
Code: 
Code: col = -2;
Code: 
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: sum += orig[row * 64 + col] * filter[i + 4];
Code: 
Code: col = -1;
Code: 
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: sum += orig[row * 64 + col] * filter[i + 4];
Code: 
Code: col = 0;
Code: 
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: sum += orig[row * 64 + col] * filter[i + 4];
Code: 
Code: col = 1;
Code: 
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: sum += orig[row * 64 + col] * filter[i + 4];
Code: 
Code: col = 2;
Code: 
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: sum += orig[row * 64 +