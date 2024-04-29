Code: #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
for (i = 1; i < 8190; i++) {
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (j = 1; j < 8176; j++) {
    s = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = -4; k <= 4; k++) {
      idx = (8191 + i + k) % 8191;
      s += filter[4 + k] * sol[8191 * idx + j];
    }
    sol[8191 * i + j] = s;
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
for (i = 1; i < 8190; i++) {
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (j = 1; j < 8176; j++) {
    s = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = -4; k <= 4; k++) {
      idx = (8191 + i + k) % 8191;
      s += filter[4 + k] * sol[8191 * idx + j];
    }
    sol[8191 * i + j] = s;
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
for (i = 1; i < 8190; i++) {
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (j = 1; j < 8176; j++) {
    s = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = -4; k <= 4; k++) {
      idx = (8191 + i + k) % 8191;
      s += filter[4 + k] * sol[8191 * idx + j];
    }
    sol[8191 * i + j] = s;
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
for (i = 1; i < 8190; i++) {
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (j = 1; j < 8176; j++) {
    s = 0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = -4; k <= 4; k++) {
      idx = (8191 + i + k) % 8191;
      s += filter[4 + k] * sol[8191 * idx + j];
    }
    sol[8191 * i + j] = s;
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
for (i = 1; i < 819