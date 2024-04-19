#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],int M[16641],char ptr[16641],int m,int n)
{
  int i;
  int j;
  int x;
  int y;
  int _in_min;
  int _in_max;
  int _out_min;
  int _out_max;
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  init_row:
  for (i = 0; i < 128; i++) {
    M[i] = ((int )SEQA[i]);
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  init_col:
  for (i = 0; i < 128; i++) {
    M[i * 128] = ((int )SEQB[i]);
  }
// Matrix multiplication
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  fill_out:
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    fill_in:
    for (j = 0; j < 128; j++) {
      x = 0;
      y = 0;
      _in_min = ((int )(i - 1));
      if (_in_min < 0) {
        _in_min = 0;
      }
      _in_max = ((int )(i + 1));
      if (_in_max > 127) {
        _in_max = 127;
      }
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      score_row:
      for (x; x < _in_max - _in_min; x++) {
        _in_val = M[x + _in_min * 128];
        _out_min = ((int )(j - 1));
        if (_out_min < 0) {
          _out_min = 0;
        }
        _out_max = ((int )(j + 1));
        if (_out_max > 127) {
          _out_max = 127;
        }
        
#pragma ACCEL PIPELINE auto{__PIPE__L3}
        
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
        
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
        score_col:
        for (y; y < _out_max - _out_min; y++) {
          if (x == 0 && y == 0) {
            M[i * 128 + j] = (_in_val + (int )SEQB[j]);
          }
          else {
            if (x == 0) {
              M[i * 128 + j] = (M[i * 128 + j] + (int )SEQB[y + _out_min] - SEQA[j]);
            }
            else {
              if (y == 0) {
                M[i * 128 + j] = (M[i * 128 + j] + (int )SEQB[j] - SEQA[x + _in_min]);
              }
              else {
                M[i * 128 + j] = (M[i * 128 + j] + (int )SEQB[y + _out_min] - SEQA[x + _in_min] - ((int )SEQA[j] - SEQB[y + _out_min]));
              }
            }
          }
        }
      }
      ptr[i * 128 + j] = ((char )(x + _in_min));
      alignedA[i * 64] = ((char )'\000';
      alignedB[j * 64] = ((char )'\000';
      trace_row:
      for (x = i; x >= 0; x--) {
        trace_col:
        for (y = j; y >= 0; y--) {
          if (M[x * 128 + y] + ((int )SEQB[y]) == M[i * 128 + j]) {
            alignedA[x * 64 + 63] = SEQA[y];
            alignedB[j * 64 + 63] = SEQB[y];
            x = 0;
            y = 0;
          }
          else {
            if (M[x * 128 + y] + ((int )SEQB[y + 1]) == M[i * 128 + j]) {
              alignedA[x * 64 + 63] = SEQA[y];
              alignedB[j * 64 + 63] = SEQB[y + 1];
              y++;
            }
            else {
              if (M[x * 128 + y + 1] + ((int )SEQB[y]) == M[i * 128 + j]) {
                alignedA[x * 64 + 63] = SEQA[y + 1];
                alignedB[j * 64 + 63] = SEQB[y];
                x++;
              }
              else {
                if (M[x * 128 + y + 1] + ((int )SEQB[y + 1]) == M[i * 128 + j]) {
                  alignedA[x * 64 + 63] = SEQA[y + 1];
                  alignedB[j * 64 + 63] = SEQB[y + 1];
                  x++;
                  y++;
                }
                else {
                  x = 0;
                  y = 0;
                }
              }
            }
          }
        }
      }
    }
  }
}