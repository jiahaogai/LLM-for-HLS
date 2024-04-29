#pragma ACCEL kernel

int filter[9] = {1, 1, 1, 1, 0, 1, 1, 1, 1};
int i;
int j;
int k;
int idx;
int end;
int orig[8192];
int sol[8192];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int end;
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  loopj:
  for (j = 1; j < 31; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    loopk:
    for (k = 1; k < 31; k++) {
      idx = (j - 1) * 32 + k - 1;
      end = (j - 1) * 32 + 32;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      loopi:
      for (i = 0; i < 32; i++) {
        sol[idx] = ((0 + filter[0]) * orig[idx] + (0 + filter[1]) * orig[idx + 1] + (0 + filter[2]) * orig[idx + 32] + (0 + filter[3]) * orig[idx + 33] + (0 + filter[4]) * orig[idx + 64] + (0 + filter[5]) * orig[idx + 65] + (0 + filter[6]) * orig[idx + 96] + (0 + filter[7]) * orig[idx + 97] + (0 + filter[8]) * orig[idx + 128]) / (0 + filter[0]) + ((1 + filter[1]) * orig[end + i - 1] + (1 + filter[2]) * orig[end + i - 32] + (1 + filter[3]) * orig[end + i - 33] + (1 + filter[4]) * orig[end + i - 64] + (1 + filter[5]) * orig[end + i - 65] + (1 + filter[6]) * orig[end + i - 96] + (1 + filter[7]) * orig[end + i - 97] + (1 + filter[8]) * orig[end + i - 128]);
      }
    }
  }
}