#ifndef bit2_INCLUDED
#define bit2_INCLUDED

#define T Bit2_T

typedef struct T *T;

extern int Bit2_width(T bitarray2);
extern int Bit2_height(T bitarray2);

extern T Bit2_new(int width, int height);
extern void Bit2_free(T *bitarray2);

extern int  Bit2_get(T bitarray2, int i, int j);
extern int  Bit2_put(T bitarray2, int i, int j, int bit);

extern void Bit2_map_row_major(T bitarray2, void apply(int row, int col, 
                               T bitarray2, int bit, void *cl),
                               void *cl);
extern void Bit2_map_col_major(T bitarray2, void apply(int col, int row, 
                               T bitarray2, int bit, void *cl),
                               void *cl);


#undef T
#endif