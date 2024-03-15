

5. "Transform this for loop into a parallelized reduction loop"
   - `#pragma ACCEL PIPELINE auto{off}`
   - `#pragma ACCEL TILE FACTOR=auto{1}`
   - `#pragma ACCEL PARALLEL FACTOR=auto{15} reduction=A`
