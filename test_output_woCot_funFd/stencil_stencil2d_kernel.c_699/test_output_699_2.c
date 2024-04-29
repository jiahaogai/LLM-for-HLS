#pragma ACCEL kernel stencil


#pragma ACCEL PARAMS

int A[8192];
int B[8192];
int filter[9] = { 1, 1, 1, 1, 0, 1, 1, 1, 1 };
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int A[8192],int B[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  double scalar;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      sum = 0;
      scalar = ((double )1) / 9.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{8}
      for (k = 0; k < 9; k++) {
        sum += filter[k] * A[i + ((k - 4) * 8191)];
      }
      B[i * 8191 + j] = (sum * scalar);
    }
  }
}