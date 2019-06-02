#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "shogi.h"

bool isAiSente = true;
bool isAiturn = true;
int count = 1;
Capt *friendlist = NULL;
Capt *enemylist = NULL;
Piece nlist[BAN_EX_SIZE];


void init_ban(void) {
	count = 1;

	for(int i = 0; i<BAN_EX_SIZE; i++) nlist[i] = -1;

	for(int d = 1; d<=DAN; d++)
		for(int s = 1; s<=SUJI; s++)
			nlist[sd2banIX(s, d)] = EMPTY;

	for(int d = 0; d<=DAN+1; d++) {
		nlist[sd2banIX(0, d)] = WALL;
		nlist[sd2banIX(SUJI+1, d)] = WALL;
	}

	for(int s = 1; s<=SUJI; s++) {
		nlist[sd2banIX(s, 0)] = WALL;
		nlist[sd2banIX(s, DAN+1)] = WALL;
	}
	
	nlist[sd2banIX(3, 1)] = E_ZOU;
	nlist[sd2banIX(2, 1)] = E_LION;
	nlist[sd2banIX(1, 1)] = E_KIRIN;
	nlist[sd2banIX(2, 2)] = E_HIYOKO;
	nlist[sd2banIX(2, 3)] = F_HIYOKO;
	nlist[sd2banIX(3, 4)] = F_KIRIN;
	nlist[sd2banIX(2, 4)] = F_LION;
	nlist[sd2banIX(1, 4)] = F_ZOU;

	friendlist = newlist();
	enemylist = newlist();
}


void init_test(void) {
	count = 1;

	for(int i = 0; i<BAN_EX_SIZE; i++) nlist[i] = -1;

	for(int d = 1; d<=DAN; d++)
		for(int s = 1; s<=SUJI; s++)
			nlist[sd2banIX(s, d)] = EMPTY;

	for(int d = 0; d<=DAN+1; d++) {
		nlist[sd2banIX(0, d)] = WALL;
		nlist[sd2banIX(SUJI+1, d)] = WALL;
	}

	for(int s = 1; s<=SUJI; s++) {
		nlist[sd2banIX(s, 0)] = WALL;
		nlist[sd2banIX(s, DAN+1)] = WALL;
	}
	
	nlist[sd2banIX(1, 1)] = E_KIRIN;
	nlist[sd2banIX(2, 1)] = E_LION;
	nlist[sd2banIX(2, 3)] = F_LION;
	nlist[sd2banIX(1, 3)] = F_ZOU;

	friendlist = newlist();
	enemylist = newlist();
	insert(F_KIRIN, friendlist, friendlist);
	insert(F_HIYOKO, friendlist, friendlist);
	insert(E_ZOU, enemylist, enemylist);
	insert(E_HIYOKO, enemylist, enemylist);
}


void toss(void) {
	system("clear");
	srand((unsigned)time(NULL));
	if(rand()%2 == 0){
		//printf("あなたが後手です.\n");
	} else {
		//printf("あなたが先手です.\n");
		isAiSente =false;
		isAiturn = false;
	}
}


void print(Piece list[BAN_EX_SIZE], Capt *frndlst, Capt *enmylst, PBanIX ix, bool visible) {
	system("clear");
	if(isAiSente){
		if(isAiturn)  printf("現在 \x1b[32m先手▼\x1b[39m\n");
		else          printf("現在 \x1b[31m後手△\x1b[39m\n");
	} else {
		if(isAiturn) printf("現在 \x1b[32m後手▽\x1b[39m\n");
		else         printf("現在 \x1b[31m先手▲\x1b[39m\n");
	}
	
	printf("相手 持ち駒 ");
	printlist(enmylst);
	printf(" A  B  C \n");
	for(int d = 1; d<=DAN; d++) {
		for(int s = 1; s<=SUJI; s++) {
			if(list[sd2banIX(s, d)] == EMPTY) {
				printf(" - ");
			} else {
				if(isFriendPiece(list[sd2banIX(s ,d)]))
					printf("\x1b[31m");
				if(isEnemyPiece(list[sd2banIX(s ,d)]))
					printf("\x1b[32m");
				if(visible && (ix == sd2banIX(s, d)))
					printf("\x1b[43m");
				switch(toRawPiece(list[sd2banIX(s, d)])){
					case NIWATORI:
						printf(" N ");
						break;
					case LION:
						printf(" L ");
						break;
					case ZOU:
						printf(" Z ");
						break;
					case KIRIN:
						printf(" K ");
						break;
					case HIYOKO:
						printf(" H ");
						break;
				}
				printf("\x1b[49m\x1b[39m");
			}
		}
		switch(d){
			case 1:
				printf(" １");
				break;
			case 2:
				printf(" ２");
				break;
			case 3:
				printf(" ３");
				break;
			case 4:
				printf(" ４");
				break;
		}
		printf("\n");
	}
	printf("自分 持ち駒 ");
	printlist(frndlst);
	printf("%d 手目\n",count);
}


void debug_print(Piece list[BAN_EX_SIZE]) {
	printf(" A  B  C \n");
	for(int d = 1; d<=DAN; d++) {
		for(int s = 1; s<=SUJI; s++) {
			if(list[sd2banIX(s, d)] == EMPTY) {
				printf(" - ");
			} else {
				if(isFriendPiece(list[sd2banIX(s ,d)]))
					printf("\x1b[31m");
				if(isEnemyPiece(list[sd2banIX(s ,d)]))
					printf("\x1b[32m");
				switch(toRawPiece(list[sd2banIX(s, d)])){
					case NIWATORI:
						printf(" N ");
						break;
					case LION:
						printf(" L ");
						break;
					case ZOU:
						printf(" Z ");
						break;
					case KIRIN:
						printf(" K ");
						break;
					case HIYOKO:
						printf(" H ");
						break;
				}
				printf("\x1b[49m\x1b[39m");
			}
		}
		switch(d){
			case 1:
				printf(" １");
				break;
			case 2:
				printf(" ２");
				break;
			case 3:
				printf(" ３");
				break;
			case 4:
				printf(" ４");
				break;
		}
		printf("\n");
	}
}


void usr_move(double tree_time, double search_time, int node_cnt) {
	char s, d, c, E, arg[10];
	PBanIX m_src, m_dst = 0;

input0:
	print(nlist, friendlist, enemylist, 0, false);
	printf("思考時間　　：%.3f\n", tree_time+search_time);
	printf("列挙時間    ：%.3f  (%.3f%%)\n", tree_time, tree_time/(tree_time+search_time)*100);
	printf("探索時間    ：%.3f  (%.3f%%)\n", search_time, search_time/(tree_time+search_time)*100);
	printf("ノード展開数：%d\n", node_cnt);

input1:
	for(int i = 0; i<10; i++) arg[i]='\0';
	printf("動かす駒を入力して下さい.\n>>> ");
	scanf("%s",arg);
	if(strncmp("cancel", arg, 6) == 0) goto input0;
	if(strncmp("use", arg, 3) == 0) goto input3;
	if(arg[0] > 96) s = arg[0]-96; 
	else            s = arg[0]-64;
	d = arg[1]-'0';
	c = arg[2];
	if(!input_error(s, d, c)) goto input1;
	m_src = sd2banIX(s, d);
	system("clear");
	print(nlist, friendlist, enemylist, m_src, true);

input2:
	printf("動かす先の座標を入力して下さい.\n>>> ");
	scanf("%s",arg);
	if(strncmp("cancel", arg, 6) == 0) goto input1;
	if(arg[0] > 96) s = arg[0]-96; 
	else            s = arg[0]-64;
	d = arg[1]-'0';
	m_dst = sd2banIX(s, d);
	if(!canMove(nlist, nlist[m_src], m_src, m_dst)){
		printf("このマスへは進めません.\n");
		goto input2;
	}
	Move(nlist, friendlist, enemylist, nlist[m_src], m_src, m_dst);
	goto success;

input3:
	c = arg[3];
	if(found_piece(c) == 0){
		printf("存在しない駒です.\n");
		goto input1;
	}
	Piece p = found_piece(c);
	if(locate(p, friendlist) == NULL){
		printf("この駒は持っていません.\n");
		printf("Piece: %d\n",p);
		goto input1;
	}
	//system("clear");
	//print(0, false, p, true);

input4:
	printf("駒を置く場所を入力して下さい.\n>>> ");
	scanf("%s",arg);
	if(strncmp("cancel", arg, 6) == 0) goto input1;
	if(arg[0] > 96) s = arg[0]-96; 
	else            s = arg[0]-64;
	d = arg[1]-'0';
	m_dst = sd2banIX(s, d);
	if(!canPut(nlist, p, m_dst)){
		printf("このマスへは置けません.\n");
		goto input4;
	}
	//Capt *q = previous(locate(p, friendlist), friendlist);
	//delete(q, friendlist);
	Put(nlist, friendlist, enemylist, p, m_dst);

success:
	count++;
}


bool input_error(int s, int d, char c) {
	if(s > SUJI || s < 1 || d > DAN || d < 1){
		printf("存在しない座標です:(s, d)=(%d, %d)\n",s,d);
		return false;
	}
	if(found_piece(c) == 0){
		printf("存在しない駒です.%c\n",c);
		return false;
	}
	if(nlist[sd2banIX(s, d)] != found_piece(c)){
		printf("駒と座標が一致しません：%d (%d, %d)\n", nlist[sd2banIX(s, d)] , s, d);
		return false;
	}
	return true;
}


Piece found_piece(char c) {
	if(c == 'h' || c == 'H'){
		return F_HIYOKO;
	} else if(c == 'z' || c == 'Z'){
		 return F_ZOU;
	} else if(c == 'k' || c == 'K'){
		return F_KIRIN;
	} else if(c == 'l' || c == 'L'){
		return F_LION;
	} else if(c == 'n' || c == 'N'){
		return F_NIWATORI;
	} else {
		return EMPTY;
	}
}
