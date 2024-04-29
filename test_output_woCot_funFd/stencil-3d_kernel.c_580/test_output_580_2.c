<<<<<<< HEAD
#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1 + 0; j <= 392 + 0; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1 + 0; k <= 392 + 0; k++) {
      k_col = 392 - k;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1 + 0; i <= 392 + 0; i++) {
        i_col = 392 - i;
        idx = i + (392 * (k + (392 * j)));
        idx_col = i_col + (392 * (k_col + (392 * j)));
        t = ((((HX(i,k,j) + HX(i_col,k,j)) + HX(i,k_col,j)) + HX(i_col,k_col,j)) - ((((FX(i,k,j) + FX(i_col,k,j)) + FX(i,k_col,j)) + FX(i_col,k_col,j)) * 2));
        sol[idx] = t;
      }
    }
  }
}
=======
Code: #pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
8. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep this loop whole, without dividing it into smaller parts.
9. `#pragma ACCEL PIPELINE auto{flatten}` - Flatten this loop, which means break it down into smaller sequential loops.
10. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep this loop whole, without dividing it into smaller parts.
11. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
12. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep this loop whole, without dividing it into smaller parts.
13. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
14. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep this loop whole, without dividing it into smaller parts.
15. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
16. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep this loop whole, without dividing it into smaller parts.
17. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
18. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep this loop whole, without dividing it into smaller parts.
19. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
20. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep this loop whole, without dividing it into smaller parts.
21. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
22. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep this loop whole, without dividing it into smaller parts.
23. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
24. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep this loop whole, without dividing it into smaller parts.
25. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
26. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep this loop whole, without dividing it into smaller parts.
27. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
28. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep this loop whole, without dividing it into smaller parts.
29. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
30. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep this loop whole, without dividing it into smaller parts.
31. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
32. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep this loop whole, without dividing it into smaller parts.
33. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
34. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep this loop whole, without dividing it into smaller parts.
35. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
36. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep this loop whole, without dividing it into smaller parts.
37. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
38. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep this loop whole, without dividing it into smaller parts.
39. `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline this loop.
40. `#pragma ACCEL TILE FACTOR=auto{1}` - Keep this loop whole, without dividing it into smaller parts.
41. `#pragma ACCEL PIPELINE auto
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
