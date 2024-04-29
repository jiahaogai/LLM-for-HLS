#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  double fit;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    sum = 0;
    middle:
    for (j = 0; j < 9; j++) {
      fit = (double )filter[j];
      k = i - 4 + j;
      if (k < 0) {
        k += 8192;
      }
       else {
        if (k > 8191) {
          k -= 8192;
        }
      }
      sum += ((int )fit) * orig[k];
    }
    sol[i] = sum;
  }
}