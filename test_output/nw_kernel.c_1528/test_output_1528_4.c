#pragma ACCEL kernel

void needwun(char SEQA[128],char SEQB[128],char alignedA[256],char alignedB[256],int M[16641],char ptr[16641])
{
  int score;
  int up_left;
  int up;
  int left;
  int max;
  int row;
  int row_up;
  int r;
  int a_idx;
  int b_idx;
  int a_str_idx;
  int b_str_idx;
  int a_str_idx_p1;
  int b_str_idx_p1;
  int a_str_idx_p2;
  int b_str_idx_p2;
  char a_char;
  char b_char;
  int idx;
  int next_idx;
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
  init_row:
  for (a_idx = 0; a_idx < 64; a_idx++) {
    M[a_idx] = a_idx * - 1;
    ptr[a_idx] = ((char )0);
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  init_col:
  for (b_idx = 0; b_idx < 64; b_idx++) {
    M[b_idx * 64] = b_idx * - 1;
    ptr[b_idx * 64] = ((char )'\000');
  }
// Matrix multiplication
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// |A|  | 1 0 0 1 0 0 1 0 |
// |B|  | 0 1 0 1 0 0 1 0 |
// |--|  | 0 0 1 0 1 0 1 0 |
// |C|  | 1 0 0 1 0 0 1 0 |
// |D|  | 0 1 0 1 0 0 1 0 |
// |E|  | 0 0 1 0 1 0 1 0 |
// |F|  | 1 0 0 1 0 0 1 0 |
// |G| 
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// DP table
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// |A|B|C|D|E|F|G|
// |B|-| 1| 1| 1| 1| 1| 1|2|
// |C| 1|-| 1| 1| 1| 1| 1|2|
// |D| 1| 1|-| 1| 1| 1| 1|2|
// |E| 1| 1| 1|-| 1| 1| 1|2|
// |F| 1| 1| 1| 1|-| 2| 2|2|
// |G| 1| 1| 1| 1| 2|-| 2|2|
// |A|B|C|D|E|F|G|
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// TraceBack Table
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// |A|B|C|D|E|F|G|
// |B|-|A|.|.|.|.|.|
// |C|A|-|B|.|.|.|.|
// |D|A|B|-|C|.|.|.|
// |E|A|B|C|-|D|.|.|
// |F|A|B|C|D|-|E|.|
// |G|A|B|C|D|E|-|
// |A|B|C|D|E|F|G|
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// |A|B|C|D|E|F|G| score
// |B|-| 1| 2| 4| 5| 6|7|
// |C| 1|-| 1| 3| 4| 5|6|
// |D| 1| 1|-| 1| 3| 4|5|
// |E| 1| 1| 1|-| 1| 3|4|
// |F| 1| 1| 1| 1|-| 2|3|
// |G| 1| 1| 1| 1| 2|-| 1|
// |A|B|C|D|E|F|G|
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// DP table
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// |A|B|C|D|E|F|G|
// |B|-| 1| 2| 4| 5| 6|7|
// |C| 1|-| 1| 3| 4| 5|6|
// |D| 1| 1|-| 1| 3| 4|5|
// |E| 1| 1| 1|-| 1| 3|4|
// |F| 1| 1| 1| 1|-| 2|3|
// |G| 1| 1| 1| 1| 2|-| 1|
// |A|B|C|D|E|F|G|
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// TraceBack Table
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// |A|B|C|D|E|F|G|
// |B|-|A|.|.|.|.|.|
// |C|A|-|B|.|.|.|.|
// |D|A|B|-|C|.|.|.|
// |E|A|B|C|-|D|.|.|
// |F|A|B|C|D|-|E|.|
// |G|A|B|C|D|E|-|
// |A|B|C|D|E|F|G|
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// TraceBack Table
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// |A|B|C|D|E|F|G|
// |B|-|A|.|.|.|.|.|
// |C|A|-|B|.|.|.|.|
// |D|A|B|-|C|.|.|.|
// |E|A|B|C|-|D|.|.|
// |F|A|B|C|D|-|E|.|
// |G|A|B