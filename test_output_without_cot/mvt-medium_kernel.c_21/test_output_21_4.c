- #pragma ACCEL TILE FACTOR=auto{1}: Keep the following loop whole, without dividing it into smaller parts, with auto-tuned factor settings.
- #pragma ACCEL PARALLEL FACTOR=auto{1}: Execute loop iterations sequentially, not concurrently, with auto-tuned factor settings.
- #pragma ACCEL PARALLEL reduction = x2 FACTOR=auto{2}: Execute loop iterations sequentially, not concurrently, with reduction operation on x2 and auto-tuned factor settings.
 
#pragma ACCEL kernel

void kernel_mvt(double x1[400],double x2[400],double y_1[400],double y_2[400],double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x1[i] = ((double )0);
    x2[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{2}
    for (j = 0; j < 400; j++) {
      x1[i] += A[i][j] * y_1[j];
      x2[i] += A[i][j] * y_2[j];
    }
  }
}