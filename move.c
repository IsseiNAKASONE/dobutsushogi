#include<stdio.h>
#include<stdlib.h>
#include "shogi.h"

void reverseIX(Piece list[BAN_EX_SIZE]) {
	Piece swap[BAN_EX_SIZE];

	for(int d = DAN; d>0; d--){
		for(int s = SUJI; s>0; s--)
			swap[sd2banIX(s, d)] = list[sd2banIX(SUJI-s+1, DAN-d+1)];
	}
	for(int d = 1; d<=DAN; d++)
		for(int s = 1; s<=SUJI; s++)
			list[sd2banIX(s, d)] = swap[sd2banIX(s, d)]; 
}


bool canMove(Piece list[BAN_EX_SIZE], Piece p, PBanIX m_src, PBanIX m_dst) {
	int dan1, suji1, dan2, suji2; 

	/** 進行方向に自分の駒があるとき */
	//要修正　AIの場合も考える
	if(isFriendPiece(p) && isFriendPiece(list[m_dst])){
		//printf("error: move.c>canMove>isFriendPiece.\n");
		return false;
	} else if(isEnemyPiece(p) && isEnemyPiece(list[m_dst])){
		//printf("error: move.c>canMove>isFriendPiece.\n");
		return false;
	/** 進行方向に壁があるとき */
	} else if(list[m_dst] == WALL){
		//printf("error: move.c>canMove>WALL.\n");
		return false;
	/** 動いていないとき */
	} else if(m_src == m_dst){
		//printf("error: move.c>canMove>NouMove.\n");
		return false;
	} else {
		//printf("error: move.c>canMove>PieceMove.\n");
		dan1  = banIX2dan(m_src);
		suji1 = banIX2suji(m_src);
		dan2  = banIX2dan(m_dst);
		suji2 = banIX2suji(m_dst);

		/** それぞれの駒の動きを制限 */
		switch(toRawPiece(p)){
			case HIYOKO:
				if(isEnemyPiece(p) && dan2-dan1==1 && suji1 == suji2)  return true;
				if(isFriendPiece(p) && dan1-dan2==1 && suji1 == suji2) return true;
				break;
			case ZOU:
				if(dan1-dan2==1 && suji1-suji2==1) return true;
				if(dan1-dan2==1 && suji2-suji1==1) return true;
				if(dan2-dan1==1 && suji1-suji2==1) return true;
				if(dan2-dan1==1 && suji2-suji1==1) return true;
				break;
			case KIRIN:
				if(dan1==dan2 && suji1-suji2==1) return true;
				if(dan1==dan2 && suji2-suji1==1) return true;
				if(dan1-dan2==1 && suji1==suji2) return true;
				if(dan2-dan1==1 && suji1==suji2) return true;
				break;
			case LION:
				if(dan1-dan2==1 && suji1-suji2==1) return true;
				if(dan1-dan2==1 && suji2-suji1==1) return true;
				if(dan2-dan1==1 && suji1-suji2==1) return true;
				if(dan2-dan1==1 && suji2-suji1==1) return true;
				if(dan1==dan2 && suji1-suji2==1) return true;
				if(dan1==dan2 && suji2-suji1==1) return true;
				if(dan1-dan2==1 && suji1==suji2) return true;
				if(dan2-dan1==1 && suji1==suji2) return true;
				break;
			case NIWATORI:
				if(isEnemyPiece(p)) {
					if(dan2-dan1==1 && suji1-suji2==1) return true;
					if(dan2-dan1==1 && suji2-suji1==1) return true;
					if(dan1==dan2 && suji1-suji2==1) return true;
					if(dan1==dan2 && suji2-suji1==1) return true;
					if(dan1-dan2==1 && suji1==suji2) return true;
					if(dan2-dan1==1 && suji1==suji2) return true;
				} else {
					if(dan2-dan1==1 && suji1-suji2==1) return true;
					if(dan2-dan1==1 && suji2-suji1==1) return true;
					if(dan1==dan2 && suji1-suji2==1) return true;
					if(dan1==dan2 && suji2-suji1==1) return true;
					if(dan1-dan2==1 && suji1==suji2) return true;
					if(dan2-dan1==1 && suji1==suji2) return true;
				}
				break;
		}
		return false;
	}
}


void Move(Piece list[BAN_EX_SIZE], Capt *frndlst, Capt *enmylst, Piece p, PBanIX m_src, PBanIX m_dst){
	if(isFriendPiece(p) && isEnemyPiece(list[m_dst])){
		if(list[m_dst] == E_NIWATORI) list[m_dst] = E_HIYOKO;
		insert(toFriendPiece(list[m_dst]), frndlst, frndlst);
	}
	if(isEnemyPiece(p) && isFriendPiece(list[m_dst])){
		if(list[m_dst] == F_NIWATORI) list[m_dst] = F_HIYOKO;
		insert(toEnemyPiece(list[m_dst]), enmylst, enmylst);
	}

	if(p == F_HIYOKO && banIX2dan(m_dst) == 1) p = toPromote(p);
	if(p == E_HIYOKO && banIX2dan(m_dst) == 4) p = toPromote(p);
	list[m_dst] = p;
	list[m_src] = EMPTY;
}


bool canPut(Piece list[BAN_EX_SIZE], Piece p, PBanIX m_dst) {
	if(list[m_dst] == WALL){
		return false;
	} else if(list[m_dst] != EMPTY){
		return false;
	} else {
		return true;
	}
}


void Put(Piece list[BAN_EX_SIZE], Capt *frndlst, Capt *enmylst, Piece p, PBanIX m_dst) {
	if(isFriendPiece(p)) {
		Capt *q = previous(locate(p, frndlst), frndlst);
		delete(q, frndlst);
	}
	if(isEnemyPiece(p)) {
		Capt *q = previous(locate(p, enmylst), enmylst);
		delete(q, enmylst);
	}
	list[m_dst] = p;
}
