#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int k;
  int m;
  int n;
  int pad_width;
  pad_width = 1;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 400 + 2 * 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 400 + 2 * 1; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      inner:
      for (k = 0; k < 3; k++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        inner_middle:
        for (m = 0; m < 3; m++) {
          n = k - 1 + pad_width;
          int _in_n = n;
          if (_in_n > 399) {
            _in_n = 399;
          }
          else {
            if (_in_n < 0) {
              _in_n = 0;
            }
          }
          n = m - 1 + pad_width;
          int _in_n_0 = n;
          if (_in_n_0 > 399) {
            _in_n_0 = 399;
          }
          else {
            if (_in_n_0 < 0) {
              _in_n_0 = 0;
            }
          }
          sol[i][j] += orig[i][_in_n] * filter[k] * orig[j][_in_n_0] * filter[m];
        }
      }
    }
  }
}