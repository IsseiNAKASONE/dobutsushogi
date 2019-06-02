#include<stdio.h>
#include<time.h>
#include "shogi.h"

int main(void) {
start:
	init_ban();
	//init_test();

	clock_t start, end;
	double tree_time = 0, search_time = 0;
	int node_cnt = 0;
	toss();
	Node *tree = new_node(nlist, friendlist, enemylist);
	make_tree(tree, isAiturn, 0);
	node_count = 0;

	while(1){
		if(isAiturn) {
			print(nlist, friendlist, enemylist, 0, false);
			printf("先読み中...\n");
			start = clock();
			make_tree(tree, isAiturn, 0);
			end = clock();
			node_cnt = node_count;
			tree_time = (double)(end - start) / CLOCKS_PER_SEC;
			
			printf("α-β実行中...\n");
			start = clock();
			tree = attack(tree);
			end = clock();
			search_time = (double)(end - start) / CLOCKS_PER_SEC;
		} else {
			usr_move(tree_time, search_time, node_cnt);
			tree = search_node(tree, nlist);
		}
		isAiturn = !isAiturn;
		if(judge()) break;
	}
	if(restart()) goto start;
}

