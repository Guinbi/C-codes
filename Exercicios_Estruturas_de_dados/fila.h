typedef struct Fila *Fila;

Fila* init_queue();
void destroy_queue(Fila* Q);
void print_queue(Fila* Q);
void insert_elem(Fila* Q, int x);
void remove_elem(Fila* Q);
