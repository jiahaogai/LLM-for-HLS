14. `#pragma ACCEL PIPELINE auto{__PIPE__L2}`: Automatically pipeline this loop with pipeline auto{__PIPE__L2}.
15. `#pragma ACCEL TILE FACTOR=auto{__TILE__L2}`: Tile this loop with tile auto{__TILE__L2}.
16. `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}`: Execute loop iterations concurrently with a concurrency level of auto{__PARA__L2}.
17. `#pragma ACCEL PARALLEL reduction=v1 FACTOR=auto{__PARA__P1}`: Perform reduction operation for the variable `v1` with a concurrency level of auto{__PARA__P1}.
18. `#pragma ACCEL PIPELINE auto{__PIPE__P1}`: Automatically pipeline this loop with pipeline auto{__PIPE__P1}.
19. `#pragma ACCEL TILE FACTOR=auto{__TILE__P1}`: Tile this loop with tile auto{__TILE__P1}.
20. `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__P1}`: Execute loop iterations concurrently with a concurrency level of auto{__PARA__P1}.
21. `#pragma ACCEL PARALLEL reduction=u1 FACTOR=auto{__PARA__P2}`: Perform reduction operation for the variable `u1` with a concurrency level of auto{__PARA__P2}.
22. `#pragma ACCEL PIPELINE auto{__PIPE__P2}`: Automatically pipeline this loop with pipeline auto{__PIPE__P2}.
23. `#pragma ACCEL TILE FACTOR=auto{__TILE__P2}`: Tile this loop with tile auto{__TILE__P2}.
24. `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__P2}`: Execute loop iterations concurrently with a concurrency level of auto{__PARA__P2}.
25. `#pragma ACCEL PARALLEL reduction=y FACTOR=auto{__PARA__L3}`: Perform reduction operation for the variable `y` with a concurrency level of auto{__PARA__L3}.
26. `#pragma ACCEL PIPELINE auto{__PIPE__L3}`: Automatically pipeline this loop with pipeline auto{__PIPE__L3}.
27. `#pragma ACCEL TILE FACTOR=auto{__TILE__L3}`: Tile this loop with tile auto{__TILE__L3}.
28. `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}`: Execute loop iterations concurrently with a concurrency level of auto{__PARA__L3}.
29. `#pragma ACCEL PARALLEL reduction=z FACTOR=auto{__PARA__L4}`: Perform reduction operation for the variable `z` with a concurrency level of auto{__PARA__L4}.
30. `#pragma ACCEL PIPELINE auto{__PIPE__L4}`: Automatically pipeline this loop with pipeline auto{__PIPE__L4}.
31. `#pragma ACCEL TILE FACTOR=auto{__TILE__L4}`: Tile this loop with tile auto{__TILE__L4}.
32. `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}`: Execute loop iterations concurrently with a concurrency level of auto{__PARA__L4}.
33. `#pragma ACCEL PARALLEL reduction=v2 FACTOR=auto{__PARA__P3}`: Perform reduction operation for the variable `v2` with a concurrency level of auto{__PARA__P3}.
34. `#pragma ACCEL PIPELINE auto{__PIPE__P3}`: Automatically pipeline this loop with pipeline auto{__PIPE__P3}.
35. `#pragma ACCEL TILE FACTOR=auto{__TILE__P3}`: Tile this loop with tile auto{__TILE__P3}.
36. `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__P3}`: Execute loop iterations concurrently with a concurrency level of auto{__PARA__P3}.
37. `#pragma ACCEL PARALLEL reduction=u2 FACTOR=auto{__PARA__P4}`: Perform reduction operation for the variable `u2` with a concurrency level of auto{__PARA__P4}.
38. `#pragma ACCEL PIPELINE auto{__PIPE__P4}`: Automatically pipeline this loop with pipeline auto{__PIPE__P4}.
39. `#pragma ACCEL TILE FACTOR=auto{__TILE__P4}`: Tile this loop with tile auto{__TILE__P4}.
40. `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__P4}`: Execute loop iterations concurrently with a concurrency level of auto{__PARA__P4}.

#pragma ACCEL kernel

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      A[i][j] += u1[i] * v1[j] + u2[i] * v2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{8}
    for (j = 0; j < 400; j++) {
      x[i] += beta * A[j][i] * y[j];
    }
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x[i] = x[i] + z[i];
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=w FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      w[i] += alpha * A[i][j] * x[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PARALLEL reduction=v1 FACTOR=auto{__PARA__P1}
    for (j = 0; j < 400; j++) {
      v1[i] += A[i][j] * y[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__P1}
  
#pragma ACCEL TILE FA