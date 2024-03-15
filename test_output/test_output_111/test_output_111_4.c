
- Do not parallelize the inner loop when the TILE FACTOR is 4: '#pragma ACCEL PARALLEL FACTOR=auto{1}'
- Do not parallelize the outer loop when the TILE FACTOR is 4: '#pragma ACCEL PARALLEL FACTOR=auto{1}'
- Automatically pipeline this loop and fully unroll the inner loop: '#pragma ACCEL PIPELINE auto{__PIPE__L2}' and '#pragma ACCEL TILE FACTOR=auto{__TILE__L2}'
- Do not parallelize the inner loop when the TILE FACTOR is 2: '#pragma ACCEL PARALLEL FACTOR=auto{1}'
- Do not parallelize the outer loop when the TILE FACTOR is 4: '#pragma ACCEL PARALLEL FACTOR=auto{1}'
- Automatically pipeline this loop: '#pragma ACCEL PIPELINE auto{__PIPE__L3}'
- Parallelize this loop with 24000000/4=6000000 threads: '#pragma ACCEL PARALLEL FACTOR=auto{4}'
  for (tint_t r = 0;r < 120;r++) {
    tmp[r] = U[r][0] * f[0][r] + U[r][1] * f[1][r];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (tint_t r = 0;r < 120;r++) {
    f[0][r] = tmp[r];
  }
}
