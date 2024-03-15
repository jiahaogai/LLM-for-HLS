#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (tj = 0; tj <= 31; tj++) {
    double Si = 0.0;
    double Sj = 0.0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (ti = 0; ti <= 31; ti++) {
      Si += A[tj * 32 + ti] * B[ti];
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (ti = 0; ti <= 31; ti++) {
      Sj += A[ti * 32 + tj] * B[ti];
    }
    P[tj] = Sj + Si;
  }
}