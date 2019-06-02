#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "shogi.h"


int MinMax(Node *node, bool ai_turn) {
	if(node->branch == NULL) {
		return evaluate(node);
	} else {
		if(ai_turn) {
			int sb = 0;
			Node *p = node->branch;
			int max = INT_MIN;
			while(p != NULL) {
				sb = MinMax(p, !ai_turn);
				if(sb > max) max = sb;
				p = p->next;
			}
			return max;
		} else {
			int ss = 0;
			Node *q = node->branch;
			int min = INT_MAX;
			while(q != NULL) {
				ss = MinMax(q, !ai_turn);
				if(ss < min) min = ss;
				q = q->next;
			}
			return min;
		}
	}
}


int alphabeta(Node *node, bool ai_turn, int alpha, int beta) {
	if(node->branch == NULL) {
		if(ai_turn) return evaluate(node);
	}

	Node *q = node->branch;
	if(ai_turn) {
		while(q != NULL) {
			alpha = max(alpha, alphabeta(q, !ai_turn, alpha, beta));
			if(alpha >= beta) break;
			q = q->next;
		}
		return alpha;
	} else {
		while(q != NULL) {
			beta = min(beta, alphabeta(q, !ai_turn, alpha, beta));
			if(alpha >= beta) break;
			q = q->next;
		}
		return beta;
	}
}


Node *attack(Node *root) {
	if(!isAiturn) {
		printf("error: attack.c > _attack\n");
		exit(1);
	}

	Node *q = root->branch;
	Node *r = q;
	int score = 0;
	int max = INT_MIN;
	while(q != NULL) {
		//score = MinMax(q, false);
		score = alphabeta(q, false, INT_MIN, INT_MAX);

			/** begin debug code */
		/*
			debug_print(q->list);
			printf("↑score: %d\n\n", score);
		*/	
			/** end debug code */ 

		if(score > max) {
			max = score;
			r = q;
		}
		q = q->next;
	}

	remove_branch(root, r);
	cpy_nodelist(r);
	count++;
	return r;
}


int max(int n, int m) {
	if(n > m) return n;
	else      return m;
}


int min(int n, int m) {
	if(n > m) return m;
	else      return n;
}

