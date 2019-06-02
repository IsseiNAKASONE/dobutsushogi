#include<stdio.h>
#include<stdlib.h>
#include "shogi.h"

bool judge(void){
	PBanIX ix;
	bool aiHasLion = false,
	     usrHasLion = false,
	     tryAi = false,
	     tryUsr = false;

	for(int d = 1; d<=DAN; d++) {
		for(int s = 1; s<=SUJI; s++) {
			ix = sd2banIX(s, d);
			if(nlist[ix] == F_LION){
				usrHasLion = true;
				if(d == 1){
					if(!can_catch(nlist, ix, false)) {
						tryUsr = true;
						break;
					}
				}
			}
			if(nlist[ix] == E_LION){
				aiHasLion = true;
				if(d == 4){
					if(!can_catch(nlist, ix, true)) {
						tryAi = true;
						break;
					}
				}
			}
		}
	}

	if(!usrHasLion && aiHasLion) {
		system("clear");
		print(nlist, friendlist, enemylist, 0, false);
		printf("\x1b[32mキャッチ！\nあなたの負けです.\x1b[39m\n");
		return true;
	} else if(usrHasLion && !aiHasLion) {
		system("clear");
		print(nlist, friendlist, enemylist, 0, false);
		printf("\x1b[31mキャッチ！\nあなたの勝ちです.\x1b[39m\n");
		return true;
	} else if(tryUsr) {
		system("clear");
		print(nlist, friendlist, enemylist, 0, false);
		printf("\x1b[31mトライ！\nあなたの勝ちです.\x1b[39m\n");
		return true;
	} else if(tryAi) {
		system("clear");
		print(nlist, friendlist, enemylist, 0, false);
		printf("\x1b[32mトライ！\nあなたの負けです.\x1b[39m\n");
		return true;
	} else {
		return false;
	}
}


bool is_settle(Piece list[BAN_EX_SIZE]) {
	bool aiHasLion = false,
	     usrHasLion = false;

	for(int i = 0; i<BAN_EX_SIZE; i++) {
		if(list[i] == F_LION) {
			usrHasLion = true;
			if(banIX2dan(i) == 1 && !can_catch(list, i, false)) return true;
		}
		if(list[i] == E_LION) {
			aiHasLion = true;
			if(banIX2dan(i) == 4 && !can_catch(list, i, true)) return true;
		}
	}
	return !(aiHasLion && usrHasLion);
}


bool can_catch(Piece list[BAN_EX_SIZE], PBanIX ix, bool ai_piece) {
	int s = banIX2suji(ix);
	int d = banIX2dan(ix);
	if(ai_piece) {
		for(int i = s-1; i<=s+1; i++) {
			for(int j = d-1; j<=d+1; j++) {
				if((i-s)*(j-d) == 0) {
					switch(list[sd2banIX(i, j)]) {
						case F_LION:
						case F_KIRIN:
						case F_NIWATORI:
							return true;
					}
				} else {
					switch(list[sd2banIX(i, j)]) {
						case F_LION:
						case F_ZOU:
							return true;
					}
				}
				if(j==d+1 && i==s) {
					int piece = list[sd2banIX(i, j)];
					int hiyoko = F_HIYOKO;
					if(piece == hiyoko) return true;
				}
				if((i==s-1 || i==s+1) && j==d+1) {
					int piece = list[sd2banIX(i, j)];
					int niwatori = F_NIWATORI;
					if(piece == niwatori) return true;
				}
			}
		}
		return false;
	} else {
		for(int i = s-1; i<=s+1; i++) {
			for(int j = d-1; j<=d+1; j++) {
				if((i-s)*(j-d) == 0) {
					switch(list[sd2banIX(i, j)]) {
						case E_LION:
						case E_KIRIN:
						case E_NIWATORI:
							return true;
					}
				} else {
					switch(list[sd2banIX(i, j)]) {
						case E_LION:
						case E_ZOU:
							return true;
					}
				}
				if(j==d-1 && i==s) {
					int piece = list[sd2banIX(i, j)];
					int hiyoko = E_HIYOKO;
					if(piece == hiyoko) return true;
				}
				if((i==s-1 || i==s+1) && j==d-1) {
					int piece = list[sd2banIX(i, j)];
					int niwatori = E_NIWATORI;
					if(piece == niwatori) return true;
				}
			}
		}
		return false;
	}
}


bool restart(void) {
	char arg[3];

input0:
	for(int i = 0; i<3; i++) arg[i]='\0';
	printf("もう１回やりますか. y/n：");
	scanf("%s",arg);
	if(arg[0] == 'y') {
		return true;
	} else if(arg[0] == 'n') {
		return false;
	} else {
		printf("入力に誤りがあります.\n");
		goto input0;
	}
}
