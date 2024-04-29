Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: #pragma ACCEL PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{32}
Code: #pragma ACCEL PARALLEL FACTOR=auto{8}
Code: int filter[9] = {1, 1, 1, 1, 0, 1, 1, 1, 1};
Code: int i;
Code: int j;
Code: int k;
Code: int sum;
Code: int orig_row;
Code: int orig_col;
Code: int sol_row;
Code: int sol_col;
Code: int orig[8192];
Code: int sol[8192];
Code: int flatten_idx;
Code: int unflatten_row;
Code: int unflatten_col;
Code: int unflatten_idx;
Code: 
Code: // Flatten 2d index
Code: flatten_idx = 0;
Code: unflatten_row = 0;
Code: unflatten_col = 0;
Code: 
Code: // Pad the input
Code: sol[0] = 0;
Code: 
Code: // Iterate over all input elements
Code: for (i = 0; i < 256; i++) {
Code:   orig_row = i / 32;
Code:   orig_col = i % 32;
Code:   sum = 0;
Code:   for (j = 0; j < 9; j++) {
Code:     unflatten_row = orig_row + ((j / 3) - 1);
Code:     unflatten_col = orig_col + ((j % 3) - 1);
Code:     if (unflatten_row < 0 || unflatten_row > 8 || unflatten_col < 0 || unflatten_col > 8) {
Code:       // Padding
Code:       unflatten_val = 0;
Code:     }
Code:     else {
Code:       unflatten_idx = ((unflatten_row * 32) + unflatten_col);
Code:       unflatten_val = orig[unflatten_idx];
Code:     }
Code:     sum += filter[j] * unflatten_val;
Code:   }
Code:   sol_row = i / 32;
Code:   sol_col = i % 32;
Code:   sol[flatten_idx] = sum;
Code:   flatten_idx++;
Code: }