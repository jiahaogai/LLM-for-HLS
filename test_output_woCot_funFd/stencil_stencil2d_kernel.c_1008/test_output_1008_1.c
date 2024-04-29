Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{4}
Error: 
Please check the code and try again.
Code: int i;
Error: 
Please check the code and try again.
Code: int j;
Error: 
Please check the code and try again.
Code: int k;
Error: 
Please check the code and try again.
Code: int idx;
Error: 
Please check the code and try again.
Code: int orig_idx;
Error: 
Please check the code and try again.
Code: int sol_idx;
Error: 
Please check the code and try again.
Code: int filter_idx;
Error: 
Please check the code and try again.
Code: int filter[9] = {1, 1, 1, 1, 0, 1, 1, 1, 1};
Error: 
Please check the code and try again.
Code: int stencil[9] = {
  orig[idx - 9],
  orig[idx - 8],
  orig[idx - 7],
  orig[idx - 6],
  orig[idx - 5],
  orig[idx - 4],
  orig[idx - 3],
  orig[idx - 2],
  orig[idx - 1]
};
Error: 
Please check the code and try again.
Code: int sum = 0;
Error: 
Please check the code and try again.
Code: int out = 0;
Error: 
Please check the code and try again.
Code: for(k = 0; k < 9; k++) {
Error: 
Please check the code and try again.
Code:   sum += filter[k] * stencil[k];
Error: 
Please check the code and try again.
Code: }
Error: 
Please check the code and try again.
Code: out = sum;
Error: 
Please check the code and try again.
Code: sol[sol_idx] = out;
Error: 
Please check the code and try again.
Code: idx++;
Error: 
Please check the code and try again.
Code: sol_idx++;
Error: 
Please check the code and try again.
Code: orig_idx++;
Error: 
Please check the code and try again.
Code: if (sol_idx == 8192) {
Error: 
Please check the code and try again.
Code:   sol_idx = 0;
Error: 
Please check the code and try again.
Code: }
Error: 
Please check the code and try again.
Code: if (orig_idx == 8192) {
Error: 
Please check the code and try again.
Code:   orig_idx = 0;
Error: 
Please check the code and try again.
Code: }
Error: 
Please check the code and try again.
Code: }
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{4}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{flatten}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{2}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
Please check the code and try again