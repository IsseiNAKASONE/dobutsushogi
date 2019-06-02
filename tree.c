#include<stdio.h>
#include<stdlib.h>
#include "shogi.h"
int node_count = 0;

Node *new_node(Piece list[BAN_EX_SIZE], Capt *frndlst, Capt *enmylst) {
	Node *node = (Node *)malloc(sizeof(Node));
	if(node != NULL) {
		for(int i = 0; i<BAN_EX_SIZE; i++) node->list[i] = list[i];
		node->fl = cptcpy(frndlst);
		node->el = cptcpy(enmylst);
		node->branch = NULL;
		node->next   = NULL;
	}
	return node;
}


void make_branch(Node *p, bool ai_turn) {
	int s, d;

	if(ai_turn) {
		/** 相手の指し手を調べる 
		 *  盤上の駒を動かす選択肢
		 */
		for(int i = 0; i<BAN_EX_SIZE; i++) {
			if(isFriendPiece(p->list[i])) {
				s = banIX2suji(i);
				d = banIX2dan(i);
				switch(p->list[i]) {
					case F_HIYOKO:
						if(canMove(p->list, F_HIYOKO, i, sd2banIX(s, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_HIYOKO, i, sd2banIX(s, d-1));
							insert_node(p, node);
						}
						break;
					case F_ZOU:
						if(canMove(p->list, F_ZOU, i, sd2banIX(s-1, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_ZOU, i, sd2banIX(s-1, d-1));
							insert_node(p, node);
						}
						if(canMove(p->list, F_ZOU, i, sd2banIX(s+1, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_ZOU, i, sd2banIX(s+1, d-1));
							insert_node(p, node);		
						}  
						if(canMove(p->list, F_ZOU, i, sd2banIX(s-1, d+1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_ZOU, i, sd2banIX(s-1, d+1));
							insert_node(p, node);
						} 
						if(canMove(p->list, F_ZOU, i, sd2banIX(s+1, d+1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_ZOU, i, sd2banIX(s+1, d+1));
							insert_node(p, node);
						}
						break;
					case F_KIRIN:
						if(canMove(p->list, F_KIRIN, i, sd2banIX(s, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_KIRIN, i, sd2banIX(s, d-1));
							insert_node(p, node);
						}  
						if(canMove(p->list, F_KIRIN, i, sd2banIX(s, d+1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_KIRIN, i, sd2banIX(s, d+1));
							insert_node(p, node);
						}  
						if(canMove(p->list, F_KIRIN, i, sd2banIX(s-1, d))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_KIRIN, i, sd2banIX(s-1, d));
							insert_node(p, node);
						}  
						if(canMove(p->list, F_KIRIN, i, sd2banIX(s+1, d))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_KIRIN, i, sd2banIX(s+1, d));
							insert_node(p, node);
						}
						break;
					case F_LION:
						if(canMove(p->list, F_LION, i, sd2banIX(s, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_LION, i, sd2banIX(s, d-1));
							insert_node(p, node);
						}
						if(canMove(p->list, F_LION, i, sd2banIX(s, d+1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_LION, i, sd2banIX(s, d+1));
							insert_node(p, node);
						} 
						if(canMove(p->list, F_LION, i, sd2banIX(s-1, d))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_LION, i, sd2banIX(s-1, d));
							insert_node(p, node);
						} 
						if(canMove(p->list, F_LION, i, sd2banIX(s+1, d))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_LION, i, sd2banIX(s+1, d));
							insert_node(p, node);
						} 
						if(canMove(p->list, F_LION, i, sd2banIX(s-1, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_LION, i, sd2banIX(s-1, d-1));
							insert_node(p, node);
						} 
						if(canMove(p->list, F_LION, i, sd2banIX(s+1, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_LION, i, sd2banIX(s+1, d-1));
							insert_node(p, node);
						} 
						if(canMove(p->list, F_LION, i, sd2banIX(s-1, d+1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_LION, i, sd2banIX(s-1, d+1));
							insert_node(p, node);
						} 
						if(canMove(p->list, F_LION, i, sd2banIX(s+1, d+1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_LION, i, sd2banIX(s+1, d+1));
							insert_node(p, node);
						}
						break;
					case F_NIWATORI:
						if(canMove(p->list, F_NIWATORI, i, sd2banIX(s, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_NIWATORI, i, sd2banIX(s, d-1));
							insert_node(p, node);
						} 
						if(canMove(p->list, F_NIWATORI, i, sd2banIX(s, d+1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_NIWATORI, i, sd2banIX(s, d+1));
							insert_node(p, node);
						} 
						if(canMove(p->list, F_NIWATORI, i, sd2banIX(s-1, d))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_NIWATORI, i, sd2banIX(s-1, d));
							insert_node(p, node);
						} 
						if(canMove(p->list, F_NIWATORI, i, sd2banIX(s+1, d))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_NIWATORI, i, sd2banIX(s+1, d));
							insert_node(p, node);
						} 
						if(canMove(p->list, F_NIWATORI, i, sd2banIX(s-1, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_NIWATORI, i, sd2banIX(s-1, d-1));
							insert_node(p, node);
						} 
						if(canMove(p->list, F_NIWATORI, i, sd2banIX(s+1, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, F_NIWATORI, i, sd2banIX(s+1, d-1));
							insert_node(p, node);
						} 
						break;	
				}	
			}
		
			/** begin test code */
			
			if(p->list[i] == EMPTY) {
				if(!isEmpty(p->fl)) {
					Capt *fc = cptcpy(p->fl);
					while(fc != NULL) {
						if(fc->piece != EMPTY) {
							if(canPut(p->list, fc->piece, i)) {
								Node *node = new_node(p->list, p->fl, p->el);
								Put(node->list, node->fl, node->el, fc->piece, i);
								insert_node(p, node);
							}
						}
						fc = fc->next;
					}
					free_list(fc);
				}
			}
			
			/** end test code */
		}
	} else {
		/** 自分の指し手を調べる */
		for(int i = 0; i<BAN_EX_SIZE; i++) {
			if(isEnemyPiece(p->list[i])) {
				s = banIX2suji(i);
				d = banIX2dan(i);
				switch(p->list[i]) {
					case E_HIYOKO:
						if(canMove(p->list, E_HIYOKO, i, sd2banIX(s, d+1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_HIYOKO, i, sd2banIX(s, d+1));
							insert_node(p, node);
						}
						break;
					case E_ZOU:
						if(canMove(p->list, E_ZOU, i, sd2banIX(s-1, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_ZOU, i, sd2banIX(s-1, d-1));
							insert_node(p, node);
						} 
						if(canMove(p->list, E_ZOU, i, sd2banIX(s+1, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_ZOU, i, sd2banIX(s+1, d-1));
							insert_node(p, node);
						}
						if(canMove(p->list, E_ZOU, i, sd2banIX(s-1, d+1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_ZOU, i, sd2banIX(s-1, d+1));
							insert_node(p, node);
						} 
						if(canMove(p->list, E_ZOU, i, sd2banIX(s+1, d+1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_ZOU, i, sd2banIX(s+1, d+1));
							insert_node(p, node);
						}
						break;
					case E_KIRIN:
						if(canMove(p->list, E_KIRIN, i, sd2banIX(s, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_KIRIN, i, sd2banIX(s, d-1));
							insert_node(p, node);
						} 
						if(canMove(p->list, E_KIRIN, i, sd2banIX(s, d+1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_KIRIN, i, sd2banIX(s, d+1));
							insert_node(p, node);
						} 
						if(canMove(p->list, E_KIRIN, i, sd2banIX(s-1, d))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_KIRIN, i, sd2banIX(s-1, d));
							insert_node(p, node);
						} 
						if(canMove(p->list, E_KIRIN, i, sd2banIX(s+1, d))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_KIRIN, i, sd2banIX(s+1, d));
							insert_node(p, node);
						}
						break;
					case E_LION:
						if(canMove(p->list, E_LION, i, sd2banIX(s, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_LION, i, sd2banIX(s, d-1));
							insert_node(p, node);
						}
						if(canMove(p->list, E_LION, i, sd2banIX(s, d+1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_LION, i, sd2banIX(s, d+1));
							insert_node(p, node);
						} 
						if(canMove(p->list, E_LION, i, sd2banIX(s-1, d))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_LION, i, sd2banIX(s-1, d));
							insert_node(p, node);
						} 
						if(canMove(p->list, E_LION, i, sd2banIX(s+1, d))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_LION, i, sd2banIX(s+1, d));
							insert_node(p, node);
						} 
						if(canMove(p->list, E_LION, i, sd2banIX(s-1, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_LION, i, sd2banIX(s-1, d-1));
							insert_node(p, node);
						} 
						if(canMove(p->list, E_LION, i, sd2banIX(s+1, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_LION, i, sd2banIX(s+1, d-1));
							insert_node(p, node);
						} 
						if(canMove(p->list, E_LION, i, sd2banIX(s-1, d+1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_LION, i, sd2banIX(s-1, d+1));
							insert_node(p, node);
						}  
						if(canMove(p->list, E_LION, i, sd2banIX(s+1, d+1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_LION, i, sd2banIX(s+1, d+1));
							insert_node(p, node);
						}
						break;
					case E_NIWATORI:
						if(canMove(p->list, E_NIWATORI, i, sd2banIX(s, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_NIWATORI, i, sd2banIX(s, d-1));
							insert_node(p, node);
						} 
						if(canMove(p->list, E_NIWATORI, i, sd2banIX(s, d+1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_NIWATORI, i, sd2banIX(s, d+1));
							insert_node(p, node);
						} 
						if(canMove(p->list, E_NIWATORI, i, sd2banIX(s-1, d))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_NIWATORI, i, sd2banIX(s-1, d));
							insert_node(p, node);
						} 
						if(canMove(p->list, E_NIWATORI, i, sd2banIX(s+1, d))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_NIWATORI, i, sd2banIX(s+1, d));
							insert_node(p, node);
						} 
						if(canMove(p->list, E_NIWATORI, i, sd2banIX(s-1, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_NIWATORI, i, sd2banIX(s-1, d-1));
							insert_node(p, node);
						} 
						if(canMove(p->list, E_NIWATORI, i, sd2banIX(s+1, d-1))) {
							Node *node = new_node(p->list, p->fl, p->el);
							Move(node->list, node->fl, node->el, E_NIWATORI, i, sd2banIX(s+1, d-1));
							insert_node(p, node);
						} 
						break;	
				}
			} 
			
			/** begin test code */
			
			if(p->list[i] == EMPTY) {
				if(!isEmpty(p->el)) {
					Capt *ec = cptcpy(p->el);
					while(ec != NULL) {
						if(ec->piece != EMPTY) {
							if(canPut(p->list, ec->piece, i)) {
								Node *node = new_node(p->list, p->fl, p->el);
								Put(node->list, node->fl, node->el, ec->piece, i);
								insert_node(p, node);
							}
						}
						ec = ec->next;
					}
					free_list(ec);
				}
			}
			
			/** end test code */

		}
	}
}


void insert_node(Node *p, Node *child) {
	if(p->branch == NULL) {
		p->branch = child;
	} else {
		Node *r = p->branch;
		while(r->next != NULL) r = r->next;
		r->next = child;
	}
}


Node *search_node(Node *p, Piece list[BAN_EX_SIZE]) {
	if(p->branch == NULL) { 
		cpy_nlist(p);
		return p;
	} else {
		Node *q = p->branch;
		Node *r;
		while(q != NULL) {
			if(cmpban(q->list, list)) {
				r = q;
				break;
			}
			q = q->next;
		}
		remove_branch(p, r);
		return r;
	}
}


void make_tree(Node *p, bool ai_turn, int depth) {
	if(depth < MDEPTH) {
		ai_turn = !ai_turn;
		if(p->branch == NULL) make_branch(p, ai_turn);
		Node *q = p->branch;
		while(q != NULL) {
			node_count++;
			
			/** begin test code */
		/*	
			print(q->list, q->fl, q->el, 0, false);
			printf("⬆︎ depth: %d	node: %d\n", depth+1, node_count);
		*/	
			/** end test code */

			if(!is_settle(q->list)) make_tree(q, ai_turn, depth+1);
			q = q->next;
		}
	}
}


void free_tree(Node *init) {
	if(init->branch != NULL) {
		Node *p = init->branch;
		Node *tmp;
		while(p != NULL) {
			tmp = p->next;
			free_tree(p);			
			p = tmp;
		}
	}

	free_node(init);
	node_count = 0;
}


void free_node(Node *p) {
	free_list(p->fl);
	free_list(p->el);
	free(p);
}


void remove_branch(Node *p, Node *r) {
	Node *tmp;
	Node *q = p->branch;
	while(q != NULL) {
		tmp = q->next;
		if(q != r) free_tree(q);
		q = tmp;
	}
	free_node(p);
	r->next = NULL;
}

