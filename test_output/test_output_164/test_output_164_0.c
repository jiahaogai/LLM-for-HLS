

5. "Unroll this loop by a factor of 32" - Use `#pragma ACCEL PIPELINE auto{__PIPE__L1}` attribute to automatically unroll the loop by a factor of 32.

6. " #pragma ACCEL PIPELINE auto{__PIPE__L2}"

7. " #pragma ACCEL PIPELINE auto{__PIPE__L3}"

8. " #pragma ACCEL PIPELINE auto{__PIPE__L4}"

9. " #pragma ACCEL PIPELINE auto{__PIPE__L5}"

10. " #pragma ACCEL PIPELINE auto{__PIPE__L6}"

11. " #pragma ACCEL PIPELINE auto{__PIPE__L7}"

12. " #pragma ACCEL PIPELINE auto{__PIPE__L8}"

13. " #pragma ACCEL PIPELINE auto{__PIPE__L9}"

14. " #pragma ACCEL PIPELINE auto{__PIPE__L10}"

15. " #pragma ACCEL PIPELINE auto{__PIPE__L11}"

16. " #pragma ACCEL PIPELINE auto{__PIPE__L12}"

17. " #pragma ACCEL PIPELINE auto{__PIPE__L13}"

18. " #pragma ACCEL PIPELINE auto{__PIPE__L14}"

19. " #pragma ACCEL PIPELINE auto{__PIPE__L15}"

20. " #pragma ACCEL PIPELINE auto{__PIPE__L16}"

21. " #pragma ACCEL PIPELINE auto{__PIPE__L17}"

22. " #pragma ACCEL PIPELINE auto{__PIPE__L18}"

23. " #pragma ACCEL PIPELINE auto{__PIPE__L19}"

24. " #pragma ACCEL PIPELINE auto{__PIPE__L20}"

25. " #pragma ACCEL PIPELINE auto{__PIPE__L21}"

26. " #pragma ACCEL PIPELINE auto{__PIPE__L22}"

27. " #pragma ACCEL PIPELINE auto{__PIPE__L23}"

28. " #pragma ACCEL PIPELINE auto{__PIPE__L24}"

29. " #pragma ACCEL PIPELINE auto{__PIPE__L25}"

30. " #pragma ACCEL PIPELINE auto{__PIPE__L26}"

31. " #pragma ACCEL PIPELINE auto{__PIPE__L27}"

32. " #pragma ACCEL PIPELINE auto{__PIPE__L28}"

33. " #pragma ACCEL PIPELINE auto{__PIPE__L29}"

34. " #pragma ACCEL PIPELINE auto{__PIPE__L30}"

35. " #pragma ACCEL PIPELINE auto{__PIPE__L31}"

36. " #pragma ACCEL PIPELINE auto{__PIPE__L32}"

 #pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 240; j++) {
      ey[0][j] = _fict_[t];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (i = 1; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (j = 0; j < 240; j++) {
        ey[i][j] = ey[i][j] - 0.5 * (hz[i][j] - hz[i - 1][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    for (i = 0; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      for (j = 1; j < 240; j++) {
        ex[i][j] = ex[i][j] - 0.5 * (hz[i][j] - hz[i][j - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L7}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
    for (i = 0; i < 200 - 1; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
      for (j = 0; j < 240 - 1; j++) {
        z_pe[i][j] = hz[i][j] - 0.25 * (ex[i][j + 1] - ex[i][j] + ey[i + 1][j] - ey[i][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L9}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L9}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L9}
    for (i = 0; i < 200 - 1; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L10}
      for (j = 0; j < 240 - 1; j++) {
        ex[i][j] = ex[i][j] + 0.25 * (z_pe[i][j] - z_se[i][j + 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L11}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L11}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L11}
    for (i = 0; i < 200 - 1; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L12}
      for (j = 0; j < 240 - 1; j++) {
        ey[i][j] = ey[i][j] + 0.25 * (z_se[i][j] - z_pe[i + 1][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L13}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L13}
    
#pragma