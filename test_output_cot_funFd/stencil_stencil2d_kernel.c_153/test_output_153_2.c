#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int ti;
  int tj;
  int tk;
  int idx;
  int idy;
  int idz;
  int fl;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{fl=8}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      inner:
      for (k = 0; k < 8; k++) {
        ti = i - 4 + 0;
        tj = j - 4 + 0;
        tk = k - 4 + 0;
        idx = ti * 64 + tj * 8 + tk;
        idy = i * 64 + j * 8 + k;
        sol[idy] = 0;
        inner_1:
        for (fl = 0; fl < 9; fl++) {
          tk = k - 4 + (fl - 4);
          if ((((ti >= 0) && (ti < 8)) && ((tj >= 0) && (tj < 8))) && ((tk >= 0) && (tk < 8))) {
            idz = ti * 8 * 8 + tj * 8 + tk;
            sol[idy] += filter[fl] * orig[idz];
          }
        }
      }
    }
  }
}