#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int fa;
  int fb;
  int ft;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i - 4 + ((int )0);
      idy = j - 4 + ((int )0);
      fa = ((int )0);
      fb = ((int )0);
      ft = 0;
      
#pragma ACCEL PARALLEL reduction=fa FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        if (idx + ((int )filter[k]) >= 0 && idx + ((int )filter[k]) < 256 && idy + ((int )filter[k]) >= 0 && idy + ((int )filter[k]) < 256) {
          fb = idx + ((int )filter[k]) == ((int )fa) ? fb + orig[idx + ((int )filter[k]) + (idy + ((int )filter[k])) * 256] : 0;
        }
      }
      sol[i + j * 256] = ft = fb;
    }
  }
}