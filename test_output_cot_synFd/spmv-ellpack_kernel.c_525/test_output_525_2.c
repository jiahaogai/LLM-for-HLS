Code: #pragma ACCEL kernel
Error: 

Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}
Error: 

Please check the code and try again.
Code: #pragma ACCEL TILE FACTOR=auto{4}
Error: 

Please check the code and try again.
Code: #pragma ACCEL PARALLEL FACTOR=auto{2}
Error: 

Please check the code and try again.
Code: 
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  ellpack_1:
  for (i = 0; i < 494; i++) {
    double sum = ((double )0);
    ellpack_2:
    for (j = 0; j < 10; j++) {
      Si = nzval[j + i * 10] * vec[cols[j + i * 10]];
      sum += Si;
    }
    out[i] = sum;
  }
Error: 

Please check the code and try again.