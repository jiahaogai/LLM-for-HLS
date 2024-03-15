

5. "Use the following space-time transform for the outer-most loop"
   - `#pragma ACCEL PIPELINE auto{__PIPE__L1}`
   - `#pragma ACCEL TILE FACTOR=auto{__TILE__L1}`
   - `#pragma ACCEL REGISTER FACTOR=auto{__REGISTER__L1}`
  
6. "Use the following space-time transform for the middle-most loop"
   - `#pragma ACCEL PIPELINE auto{__PIPE__L2}`
   - `#pragma ACCEL TILE FACTOR=auto{__TILE__L2}`
   - `#pragma ACCEL REGISTER FACTOR=auto{__REGISTER__L2}`
  
7. "Use the following space-time transform for the inner-most loop"
   - `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}`
  
8. "Use the following space-time transform for the inner-most loop"
   - `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}`
  
