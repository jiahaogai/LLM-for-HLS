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
      for (k = 0; k < 60; ++k) {
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
      F[i] += E[j][i] * C[j][i];
    }
  }
  
22. #pragma ACCEL PIPELINE auto{__PIPE__L7}
  
23. #pragma ACCEL TILE FACTOR=auto{__TILE__L7}
  
24. #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
  for (i = 0; i < 40; i++) {
    G[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7_0}
    for (j = 0; j < 70; j++) {
      G[i] += F[j][i] * D[j][i];
    }
  }
  
25. #pragma ACCEL PIPELINE auto{__PIPE__L8}
  
26. #pragma ACCEL TILE FACTOR=auto{__TILE__L8}
  
27. #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
  for (i = 0; i < 50; i++) {
    H[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8_0}
    for (j = 0; j < 40; j++) {
      H[i] += F[j][i] * G[j];
    }
  }
// Matrix multiplication
  
28. #pragma ACCEL PIPELINE auto{__PIPE__L9}
  
29. #pragma ACCEL TILE FACTOR=auto{__TILE__L9}
  
30. #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
  for (i = 0; i < 40; i++) {
    E[i] = 0.0;
    
#pragma ACCEL PIPELINE auto{__PIPE__L9_0}
    for (j = 0; j < 50; j++) {
      for (k = 0; k < 60; ++k) {
        E[i] += A[i][k] * B[k][j];
      }
    }
  }
  
31. #pragma ACCEL PIPELINE auto{__PIPE__L10}
  
32. #pragma ACCEL TILE FACTOR=auto{__TILE__L10}
  
33. #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L10}
  for (i = 0; i < 50; i++) {
    F[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L10_0}
    for (j = 0; j < 40; j++) {
      F[i] += E[j][i] * C[j][i];
    }
  }
  
34. #pragma ACCEL PIPELINE auto{__PIPE__L11}
  
35. #pragma ACCEL TILE FACTOR=auto{__TILE__L11}
  
36. #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L11}
  for (i = 0; i < 40; i++) {
    G[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L11_0}
    for (j = 0; j < 70; j++) {
      G[i] += F[j][i] * D[j][i];
    }
  }
  
37. #pragma ACCEL PIPELINE auto{__PIPE__L12}
  
38. #pragma ACCEL TILE FACTOR=auto{__TILE__L12}
  
39. #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L12}
  for (i = 0; i < 50; i++) {
    H[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L12_0}
    for (j = 0; j < 40; j++) {
      H[i] += F[j][i] * G[j];
    }
  }
// Matrix multiplication
}