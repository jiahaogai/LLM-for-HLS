- #pragma ACCEL PIPELINE auto{off}: Do not automatically pipeline the inner loop to allow for manual optimization.
- #pragma ACCEL TILE FACTOR=auto{1}: Keep the inner loop whole without dividing it into smaller parts.