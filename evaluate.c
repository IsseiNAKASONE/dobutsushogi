#include<stdio.h>
#include "shogi.h"
#include "param.h"

int evaluate(Node *node) {
	int score = 0;

	/** 駒の価値 */
	score += eval_piece(node->list);
	score -= eval_capt(node->fl);
	score += eval_capt(node->el);

	/** トライ・トライ逃れ */
	score += eval_try(node->list);

	return score;
}


int eval_piece(Piece list[BAN_EX_SIZE]) {
	int score = 0;

	for(int d = 1; d<=DAN; d++) {
		for(int s = 1; s<=SUJI; s++) {
			switch(list[sd2banIX(s, d)]) {
				case F_HIYOKO:   score  -= DHIYOKO;   break;
				case F_ZOU:      score  -= DZOU;      break;
				case F_KIRIN:    score  -= DKIRIN;    break;
				case F_LION:     score  -= DLION;     break;
				case F_NIWATORI: score  -= DNIWATORI; break;
				case E_HIYOKO:   score  += DHIYOKO;   break;
				case E_ZOU:      score  += DZOU;      break;
				case E_KIRIN:    score  += DKIRIN;    break;
				case E_LION:     score  += DLION;     break;
				case E_NIWATORI: score  += DNIWATORI; break;
			}
			//score += eval_effect(list, s, d);
		}
	}

	return score;
}


int eval_try(Piece list[BAN_EX_SIZE]) {
	for(int s = 1; s<=SUJI; s++) {
		if(list[sd2banIX(s, 1)] == F_LION && !can_catch(list, sd2banIX(s, 1), false)) return -DLION;		
		if(list[sd2banIX(s, 4)] == E_LION && !can_catch(list, sd2banIX(s, 4), true))  return DLION;
	}
	return 0;
}


int eval_effect(Piece list[BAN_EX_SIZE], int s, int d) {
	int score = 0;

	for(int i = s-1; i <= s+1; i++) {
		for(int j = d-1; j <= d+1; j++) {
			if((i != s) || (j != d)) {
				if((i-s)*(j-d) == 0) {
					switch(list[sd2banIX(i, j)]) {
						case E_LION:     score += (int)EFFECT*ELION;     break;
						case E_KIRIN:    score += (int)EFFECT*DKIRIN;    break;
						case E_NIWATORI: score += (int)EFFECT*DNIWATORI; break;
						case E_HIYOKO:   if(j == d-1) {score += (int)EFFECT*DHIYOKO; break;}
						case F_LION:     score -= (int)EFFECT*ELION;     break;
						case F_KIRIN:    score -= (int)EFFECT*DKIRIN;    break;
						case F_NIWATORI: score -= (int)EFFECT*DNIWATORI; break;
						case F_HIYOKO:   if(j == d+1) {score -= (int)EFFECT*DHIYOKO; break;}
					}
				} else if(j == d-1) {
					switch(list[sd2banIX(i, j)]) {
						case E_LION:     score += (int)EFFECT*ELION;     break;
						case E_ZOU:      score += (int)EFFECT*DZOU;      break;
						case E_NIWATORI: score += (int)EFFECT*DNIWATORI; break;
						case F_LION:     score -= (int)EFFECT*ELION;     break; 
						case F_ZOU:      score -= (int)EFFECT*DZOU;      break;
					}
				} else {
					switch(list[sd2banIX(i, j)]) {
						case E_LION:     score += (int)EFFECT*ELION;     break;
						case E_ZOU:      score += (int)EFFECT*DZOU;      break;
						case F_LION:     score -= (int)EFFECT*ELION;     break; 
						case F_ZOU:      score -= (int)EFFECT*DZOU;      break;
						case F_NIWATORI: score -= (int)EFFECT*DNIWATORI; break;
					}
				}
			}
		}
	}

	return score;
}

