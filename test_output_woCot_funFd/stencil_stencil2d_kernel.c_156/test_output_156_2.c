<<<<<<< HEAD
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute the stencil iterations concurrently, with a factor of 1.

#pragma ACCEL kernel
=======
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{126}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
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
Code: int filter[9];
Error: 
Please check the code and try again.
Code: filter[0] = -1;
Error: 
Please check the code and try again.
Code: filter[1] = -1;
Error: 
Please check the code and try again.
Code: filter[2] = -1;
Error: 
Please check the code and try again.
Code: filter[3] = 8;
Error: 
Please check the code and try again.
Code: filter[4] = -1;
Error: 
Please check the code and try again.
Code: filter[5] = -1;
Error: 
Please check the code and try again.
Code: filter[6] = -1;
Error: 
Please check the code and try again.
Code: filter[7] = -1;
Error: 
Please check the code and try again.
Code: filter[8] = -1;
Error: 
Please check the code and try again.
Code: int result = 0;
Error: 
Please check the code and try again.
Code: for(i = 0; i < 9; i++) {
Error: 
Please check the code and try again.
Code:   idx = i - 4;
Error: 
Please check the code and try again.
Code:   if(idx < 0 || idx > 8 || orig[idx] == 0) {
Error: 
Please check the code and try again.
Code:     result = 0;
Error: 
Please check the code and try again.
Code:   }
Error: 
Please check the code and try again.
Code:   else {
Error: 
Please check the code and try again.
Code:     result += orig[idx] * filter[i];
Error: 
Please check the code and try again.
Code:   }
Error: 
Please check the code and try again.
Code: }
Error: 
Please check the code and try again.
Code: sol[4] = result;
Error: 
Please check the code and try again.
Code: result = 0;
Error: 
Please check the code and try again.
Code: for(i = 0; i < 9; i++) {
Error: 
Please check the code and try again.
Code:   idx = i - 4 + 1;
Error: 
Please check the code and try again.
Code:   if(idx < 0 || idx > 8 || sol[idx] == 0) {
Error: 
Please check the code and try again.
Code:     result = 0;
Error: 
Please check the code and try again.
Code:   }
Error: 
Please check the code and try again.
Code:   else {
Error: 
Please check the code and try again.
Code:     result += sol[idx] * filter[i];
Error: 
Please check the code and try again.
Code:   }
Error: 
Please check the code and try again.
Code: }
Error: 
Please check the code and try again.
Code: sol[4] = result;
Error: 
Please check the code and try again.
Code: result = 0;
Error: 
Please check the code and try again.
Code: for(i = 0; i < 9; i++) {
Error: 
Please check the code and try again.
Code:   idx = i - 4 - 1;
Error: 
Please check the code and try again.
Code:   if(idx < 0 || idx >
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
