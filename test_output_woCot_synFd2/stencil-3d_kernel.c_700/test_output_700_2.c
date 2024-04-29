#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[390][390][390],double sol[32][32][32])
{
  long i;
  long j;
  long k;
  long r;
  long s;
  long t;
  double _tmp_0;
  double _tmp_1;
  double _tmp_2;
  double _tmp_3;
  double _tmp_4;
  double _tmp_5;
  double _tmp_6;
  double _tmp_7;
  double _tmp_8;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_i:
  for (i = 1; i < 390 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 390 - 1; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
      for (k = 1; k < 390 - 1; k++) {
        _tmp_0 = 0.5 * (orig[i][j][k] - (orig[i - 1][j][k] + orig[i + 1][j][k] + orig[i][j - 1][k] + orig[i][j + 1][k] + orig[i][j][k - 1] + orig[i][j][k + 1]));
        _tmp_1 = 0.5 * (_tmp_0 - (orig[i - 1][j - 1][k] + orig[i - 1][j + 1][k] + orig[i + 1][j - 1][k] + orig[i + 1][j + 1][k] + orig[i - 1][j][k - 1] + orig[i - 1][j][k + 1] + orig[i + 1][j][k - 1] + orig[i + 1][j][k + 1] + orig[i][j - 1][k - 1] + orig[i][j - 1][k + 1] + orig[i][j + 1][k - 1] + orig[i][j + 1][k + 1]));
        _tmp_2 = 0.5 * (_tmp_1 - (orig[i - 1][j - 1][k - 1] + orig[i - 1][j - 1][k + 1] + orig[i - 1][j + 1][k - 1] + orig[i - 1][j + 1][k + 1] + orig[i + 1][j - 1][k - 1] + orig[i + 1][j - 1][k + 1] + orig[i + 1][j + 1][k - 1] + orig[i + 1][j + 1][k + 1] + orig[i - 1][j][k - 1] + orig[i - 1][j][k + 1] + orig[i + 1][j][k - 1] + orig[i + 1][j][k + 1]));
        _tmp_3 = 0.5 * (_tmp_2 - (orig[i - 1][j - 1][k - 1] + orig[i - 1][j + 1][k - 1] + orig[i + 1][j - 1][k - 1] + orig[i + 1][j + 1][k - 1] + orig[i - 1][j - 1][k + 1] + orig[i - 1][j + 1][k + 1] + orig[i + 1][j - 1][k + 1] + orig[i + 1][j + 1][k + 1] + orig[i - 1][j][k - 1] + orig[i - 1][j][k + 1] + orig[i + 1][j][k - 1] + orig[i + 1][j][k + 1]));
        _tmp_4 = ((C1 * (_tmp_3 * _tmp_3)) / (C0 * C0));
        _tmp_5 = 1.0 / (1.0 + _tmp_4);
        _tmp_6 = (-1 * _tmp_5) * _tmp_3;
        _tmp_7 = _tmp_5 * _tmp_6;
        _tmp_8 = _tmp_7 * _tmp_7;
        sol[i - 1][j - 1][k - 1] = _tmp_7;
        sol[i - 1][j - 1][k] = _tmp_8;
        sol[i - 1][j - 1][k + 1] = _tmp_8;
        sol[i - 1][j][k - 1] = _tmp_8;
        sol[i - 1][j][k] = 1.0 + 2.0 * _tmp_5;
        sol[i - 1][j][k + 1] = _tmp_8;
        sol[i - 1][j + 1][k - 1] = _tmp_8;
        sol[i - 1][j + 1][k] = _tmp_8;
        sol[i - 1][j + 1][k + 1] = _tmp_8;
        sol[i][j - 1][k - 1] = _tmp_8;
        sol[i][j - 1][k] = _tmp_7;
        sol[i][j - 1][k + 1] = _tmp_7;
        sol[i][j][k - 1] = _tmp_7;
        sol[i][j][k] = 1.0 + 4.0 * _tmp_5 + 2.0 * _tmp_6 * _tmp_6;
        sol[i][j][k + 1] = _tmp_7;
        sol[i][j + 1][k - 1] = _tmp_7;
        sol[i][j + 1][k] = _tmp_7;
        sol[i][j + 1][k + 1] = _tmp_7;
        sol[i + 1][j - 1][k - 1] = _tmp_7;
        sol[i + 1][j - 1][k] = _tmp_8;
        sol[i + 1][j - 1][k + 1] = _tmp_8;
        sol[i + 1][j][k - 1] = _tmp_8;
        sol[i + 1][j][k] = _tmp_6;
        sol[i + 1][j][k + 1] = _tmp_8;
        sol[i + 1][j + 1][k - 1] = _tmp_8;
        sol[i + 1][j + 1][k] = _tmp_8;
        sol[i + 1][j + 1][k + 1] = _tmp_8;
      }
    }
  }
}