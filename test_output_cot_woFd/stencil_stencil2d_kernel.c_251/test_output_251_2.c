#pragma ACCEL kernel

int orig[8192];
int sol[8192];
int filter[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 0; j < 256; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{32}
      inner:
      for (k = -4; k < 5; k++) {
        int cur_filter;
        int cur_index;
        cur_filter = filter[4 + k];
        cur_index = i * 256 + j + k;
        if (cur_index < 0) {
          cur_index = 0;
        }
         else if (cur_index > 8191) {
          cur_index = 8191;
        }
        sum += cur_filter * orig[cur_index];
      }
      sol[i * 256 + j] = sum;
    }
  }
}