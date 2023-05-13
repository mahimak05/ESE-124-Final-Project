enum itch_state {NONE, LEFT, RIGHT, FORWARD, BACKWARD};
extern enum itch_state itch;

int empty_spot(int row, int col);
int start();
void mark();
void move_forward();
void move_backward();
void move_left();
void move_right();
void CWL();
void CWR();
void CWF();
void CWB();
void BJPI();
void CJPI();

int is_full();
int is_empty();
void PUSH();
void POP();
void PEEK();
void CLEAR();
void BACKTRACK();
void RP(void (*n)(), int t);

