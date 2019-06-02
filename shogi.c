#include<stdio.h>
#include "shogi.h"

bool isFriendPiece(Piece p) { return (p & F_MASK) != 0; }
bool isEnemyPiece(Piece p) { return (p & E_MASK) != 0; }
Piece toRawPiece(Piece p) { return p & PIECE_MASK; }
Piece toFriendPiece(Piece p) { return (p & PIECE_MASK) | F_MASK; }
Piece toEnemyPiece(Piece p) { return (p & PIECE_MASK) | E_MASK; }
Piece toPromote(Piece p) { return p | PROMOTED; }
Piece unPromote(Piece p) { return p & ~PROMOTED; }

PBanIX sd2banIX(char s, char d) { return d + s * BAN_EX_WIDTH; }
int banIX2dan(PBanIX ix) { return ix % BAN_EX_WIDTH; }
int banIX2suji(PBanIX ix) { return ix / BAN_EX_WIDTH; }

bool cmpban(Piece p[BAN_EX_SIZE], Piece q[BAN_EX_SIZE]) {
	for(int i = 0; i<BAN_EX_SIZE; i++) if(p[i] != q[i]) return false;
	return true;
}

void cpy_nlist(Node *p) {
	for(int i = 0; i<BAN_EX_SIZE; i++) p->list[i] = nlist[i];
	p->fl = cptcpy(friendlist);
	p->el = cptcpy(enemylist);
}

void cpy_nodelist(Node *p) {
	for(int i = 0; i<BAN_EX_SIZE; i++) nlist[i] = p->list[i];
	friendlist = cptcpy(p->fl);
	enemylist  = cptcpy(p->el);
}

