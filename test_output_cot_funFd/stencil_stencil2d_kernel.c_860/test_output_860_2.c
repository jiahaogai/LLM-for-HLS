#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int t;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 8192; i++) {
    t = orig[i] * filter[0] + ((i > 0) ? orig[i - 1] * filter[1] : 0) + ((i < 8191) ? orig[i + 1] * filter[1] : 0);
    sum = t + filter[2] * ((i > 2) ? orig[i - 2] : 0) + ((i < 8190) ? filter[2] * orig[i + 2] : 0);
    sol[i] = sum;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  inner:
  for (i = 0; i < 8192; i++) {
    t = sol[i] * filter[0] + ((sol[i] > 0 ? sol[i - 1] : 0) * filter[1]) + ((sol[i] < 8191 ? sol[i + 1] : 0) * filter[1]) + ((sol[i] > 2 ? sol[i - 2] : 0) * filter[2]) + ((sol[i] < 8190 ? sol[i + 2] : 0) * filter[2]);
    j = i - 4;
    k = i + 4;
    sum = t;
    middle:
    for (j = (j > 0 ? j : 0); j < (j < 8191 ? j + 1 : 8191); j++) {
      sum += ((sol[j] > 0 ? sol[j - 1] : 0) * filter[1]) + ((sol[j] < 8191 ? sol[j + 1] : 0) * filter[1]) + (sol[j] * filter[0]) + ((sol[j] > 2 ? sol[j - 2] : 0) * filter[2]) + ((sol[j] < 8190 ? sol[j + 2] : 0) * filter[2]);
    }
    k = (k < 8191 ? k : 8191);
    mid:
    for (k = (k < 8191 ? k : 8191); k > (k > 0 ? k - 1 : 0); k--) {
      sum += ((sol[k] > 0 ? sol[k - 1] : 0) * filter[1]) + ((sol[k] < 8191 ? sol[k + 1] : 0) * filter[1]) + (sol[k] * filter[0]) + ((sol[k] > 2 ? sol[k - 2] : 0) * filter[2]) + ((sol[k] < 8190 ? sol[k + 2] : 0) * filter[2]);
    }
    sol[i] = sum;
  }
}