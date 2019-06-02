#include<stdbool.h>

#define BAN_EX_WIDTH 0x10
#define BAN_EX_HEIGHT (3+2)
#define SUJI 3
#define DAN 4
#define BAN_EX_SIZE (BAN_EX_WIDTH*BAN_EX_HEIGHT)
#define MDEPTH 6

enum Piece {
	EMPTY = 0,
	HIYOKO = 1,
	ZOU,
	KIRIN,
	LION,
	NIWATORI,
	PROMOTED = NIWATORI - HIYOKO, 
	PIECE_MASK = 0x0f,
	F_MASK = 0x10,
	F_HIYOKO = HIYOKO + F_MASK,
	F_ZOU,
	F_KIRIN,
	F_LION,
	F_NIWATORI,
	E_MASK = 0x20,
	E_HIYOKO = HIYOKO + E_MASK,
	E_ZOU,
	E_KIRIN,
	E_LION,
	E_NIWATORI,
	WALL = 0x80
};

typedef struct capt {
	enum Piece piece;
	struct capt *next;
} Capt;

extern Capt *friendlist;
extern Capt *enemylist;
extern bool isAiSente;
extern bool isAiturn;
extern int count;
extern int node_count;


/** shogi.c */
typedef unsigned char Piece;
extern bool isFriendPiece(Piece p);
extern bool isEnemyPiece(Piece p);
extern Piece toRawPiece(Piece p);
extern Piece toFriendPiece(Piece p);
extern Piece toEnemyPiece(Piece p);
extern Piece toPromote(Piece p);
extern Piece unPromote(Piece p);

typedef unsigned char PBanIX;
extern PBanIX sd2banIX(char s, char d);
extern int banIX2dan(PBanIX ix);
extern int banIX2suji(PBanIX ix);
bool cmpban(Piece p[BAN_EX_SIZE], Piece q[BAN_EX_SIZE]);

typedef struct node {
	Piece list[BAN_EX_SIZE];
	Capt *fl;
	Capt *el;
	struct node *branch;
	struct node *next;
} Node;
extern Piece nlist[BAN_EX_SIZE];

void cpy_nlist(Node *p);
void cpy_nodelist(Node *p);


/** io.c */ 
extern void init_ban(void);
extern void init_test(void);
extern void toss(void);
extern void print(Piece list[BAN_EX_SIZE], Capt *frndlst, Capt *enmylst, PBanIX ix, bool visible);
extern void debug_print(Piece list[BAN_EX_SIZE]);
extern void usr_move(double tree_time, double seaerch_time, int node_cnt);
extern bool input_error(int s, int d, char c);
extern bool index_error(int s, int d, char c, PBanIX m_src);
extern Piece found_piece(char c);


/** move.c */
extern void reverseIX(Piece list[BAN_EX_SIZE]);
extern bool canMove(Piece list[BAN_EX_SIZE], Piece p, PBanIX m_src, PBanIX m_dst);
extern void Move(Piece list[BAN_EX_SIZE], Capt *frndlst, Capt *enmylst, Piece p, PBanIX m_src, PBanIX m_dst);
extern bool canPut(Piece list[BAN_EX_SIZE], Piece p, PBanIX m_dst);
extern void Put(Piece list[BAN_EX_SIZE], Capt *frndlst, Capt *enmylst, Piece p, PBanIX m_dst);


/** capture.c */
extern Capt *newlist(void);
extern Capt *insert(Piece piece, Capt *p, Capt *init);
extern Capt *delete(Capt *p, Capt *init);
extern Capt *locate(Piece piece, Capt *init);
extern Capt *previous(Capt *p, Capt *init);
extern void printlist(Capt *init);
extern int eval_capt(Capt *init);
extern Capt *cptcpy(Capt *d);
extern void free_list(Capt *init);
extern bool isEmpty(Capt *init);


/** judge.c */
extern bool judge(void);
extern bool is_settle(Piece list[BAN_EX_SIZE]);
extern bool can_catch(Piece list[BAN_EX_SIZE], PBanIX ix, bool ai_piece);
extern bool restart(void);
//extern void isDraw(void);


/** tree.c */
extern Node *new_node(Piece list[BAN_EX_SIZE], Capt *frndlst, Capt *enmylst);
extern void make_branch(Node *p, bool ai_turn);
extern void insert_node(Node *p, Node *child);
extern Node *search_node(Node *p, Piece list[BAN_EX_SIZE]);
extern void make_tree(Node *p, bool ai_turn, int depth);
extern void free_tree(Node *init);
extern void free_node(Node *p);
extern void remove_branch(Node *p, Node *r);


/** evaluate.c */ 
extern int evaluate(Node *node);
extern int eval_piece(Piece list[BAN_EX_SIZE]);
extern int eval_try(Piece list[BAN_EX_SIZE]);
extern int eval_effect(Piece list[BAN_EX_SIZE], int s, int d);


/** attack.c */
extern int MinMax(Node *node, bool ai_turn);
extern int alphabeta(Node *node, bool ai_turn, int alpha, int beta);
extern Node *attack(Node *root);
extern int max(int n, int m);
extern int min(int n, int m);

