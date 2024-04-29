- `#pragma ACCEL PARALLEL reduction=C FACTOR=auto{8}`: Execute iterations of the reduction loop with the reduction variable C being performed in parallel with a factor of 8.


#pragma ACCEL kernel