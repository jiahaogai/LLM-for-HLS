6. #pragma ACCEL PIPELINE auto{__PIPE__L2}
  
7. #pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
8. #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  
9. #pragma ACCEL PIPELINE auto{__PIPE__L3}
  
10. #pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
11. #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  
12. #pragma ACCEL PIPELINE auto{__PIPE__L4}
  
13. #pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
14. #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  
15. #pragma ACCEL PIPELINE auto{__PIPE__L5}
  
16. #pragma ACCEL TILE FACTOR=auto{__TILE__L5}
  
17. #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
  
18. #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (i = 0; i < 40; i++) {
    E[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      for (k = 0; k < 60; k++) {
        E[i] += A[i][k] * B[k][j];
      }
    }
  }
  
19. #pragma ACCEL PIPELINE auto{__PIPE__L6}
  
20. #pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  
21. #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
  for (i = 0; i < 50; i++) {
    F[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6_0}
    for (j = 0; j < 40; j++) {
      for (k = 0; k < 70; k++) {
        F[i] += C[j][k] * D[k][i];
      }
    }
  }
  
22. #pragma ACCEL PIPELINE auto{__PIPE__L7}
  
23. #pragma ACCEL TILE FACTOR=auto{__TILE__L7}
  
24. #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
  for (i = 0; i < 40; i++) {
    G[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7_0}
    for (j = 0; j < 50; j++) {
      G[i] += E[i][j] * F[j];
    }
  }