#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (tj = 0;tj < 20;tj++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (tk = 0;tk < 20;tk++) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L5}
      for (i = 0;i < 40;i++) {
        tmp += A[i][tj][tk] * x[i];
      }
      B[tj][tk] = tmp;
    }
    tmp2 = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp2 FACTOR=auto{__PARA__L4}
    for (tk = 0;tk < 20;tk++) {
      tmp2 += B[tj][tk] * f[tk];
    }
    y[tj] = tmp2;
  }
  float check = 0.0;
  
#pragma ACCEL PARALLEL reduction=check
  for (tj = 0;tj < 20;tj++) {
    check += A[tj][tj][tj];
  }
  if (fabs(check - 60.928) > 1e-4) {
    printf("Mismatch in kernel 3:\n");
    printf("  check= %f\n",check);
    printf("  A[16][16][16]: %f\n",A[16][16][16]);
    exit - 1;
  }
  else {
    printf("Match in kernel 3.\n");
  }
}