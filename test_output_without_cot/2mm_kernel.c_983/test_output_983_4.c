- Inside the third loop (for `k`), additional pragma directives are used to guide the loop optimizations as follows:
     - `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline the specified loops.
     - `#pragma ACCEL TILE FACTOR=auto{1}` - Keep the specified loops whole without dividing them into smaller parts.
     - `#pragma ACCEL PARALLEL FACTOR=auto{4}` - Execute loop iterations in parallel, with a factor of 4.
   - Inside the fourth loop (for `j`), additional pragma directives are used to guide the loop optimizations as follows:
     - `#pragma ACCEL PIPELINE auto{off}` - Do not automatically pipeline the specified loops.
     - `#pragma ACCEL TILE FACTOR=auto{1}` - Keep the specified loops whole without dividing them into smaller parts.
     - `#pragma ACCEL PARALLEL FACTOR=auto{1}` - Execute loop iterations sequentially, not concurrently, while taking advantage of parallelism where possible.
     
#pragma ACCEL kernel