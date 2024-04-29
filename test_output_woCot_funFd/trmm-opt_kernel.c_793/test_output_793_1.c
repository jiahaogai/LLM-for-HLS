Code: #pragma ACCEL PIPELINE auto{off}
11. `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
12. `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Break the loop into parts which are executed concurrently.
13. `#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}`: Perform reduction operation on the variable `A` in parallel with a factor of 1.
14. `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
15. `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
16. `#pragma ACCEL PARALLEL FACTOR=auto{8}`: Break the loop into parts which are executed concurrently.
17. `#pragma ACCEL PARALLEL reduction=A FACTOR=auto{1}`: Perform reduction operation on the variable `A` in parallel with a factor of 1.
18. `#pragma ACCEL PIPELINE auto{flatten}`: Flatten the loops.
19. `#pragma ACCEL TILE FACTOR=auto{80}`: Keep this loop whole, without dividing it into smaller parts.
20. `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
21. `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
22. `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
23. `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
24. `#pragma ACCEL PARALLEL reduction=B FACTOR=auto{8}`: Perform reduction operation on the variable `B` in parallel with a factor of 8.
25. `#pragma ACCEL kernel`