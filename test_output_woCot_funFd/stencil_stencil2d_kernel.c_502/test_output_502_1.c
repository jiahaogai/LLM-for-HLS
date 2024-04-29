Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{18}
Error: 
Please check the code and try again.
Code: 
 #pragma ACCEL PIPELINE auto{flatten}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{4}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: stencil_label1: for(r = 0; r < 128 - 2; r++) {
Error: 
Please check the code and try again.
Code: 
 #pragma ACCEL PIPELINE auto{flatten}
Error: 
Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{1}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{4}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
Code: stencil_label2: for(c = 0; c < 64 - 2; c++) {
Error: 
Please check the code and try again.
Code: temp = ((int )0);
Error: 
Please check the code and try again.
Code: stencil_label3: for(k1 = 0; k1 < 3; k1++) {
Error: 
Please check the code and try again.
Code: stencil_label4: for(k2 = 0; k2 < 3; k2++) {
Error: 
Please check the code and try again.
Code: mul = filter[k1 * 3 + k2] * orig[(r + k1) * 64 + c + k2];
Error: 
Please check the code and try again.
Code: temp += mul;
Error: 
Please check the code and try again.
Code: }
Error: 
Please check the code and try again.
Code: }
Error: 
Please check the code and try again.
Code: sol[r * 64 + c] = temp;
Error: 
Please check the code and try again.
Code: }
Error: 
Please check the code and try again.
Summary: 0