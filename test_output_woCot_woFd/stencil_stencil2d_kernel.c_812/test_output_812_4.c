- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep the innermost loop whole without dividing it into smaller parts, with automatic factor calculation.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute the innermost loop iterations sequentially with automatic factor calculation.

#pragma ACCEL PIPELINE auto

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    for (j = 0; j < 8; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      for (k = 0; k < 8; k++) {
        sum += filter[k] * orig[i * 8 + k] * sol[j * 8 + k];
      }
      sol[i * 8 + j] = sum;
    }
  }
//#pragma endscop
}