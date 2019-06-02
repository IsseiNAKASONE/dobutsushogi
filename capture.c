#include<stdio.h>
#include<stdlib.h>
#include "shogi.h"
#include "param.h"


Capt *newlist() {
    Capt *p = (Capt *)malloc(sizeof(Capt));
    p->piece = EMPTY;
    p->next = NULL;
    return p;
}


Capt *insert(Piece piece, Capt *p, Capt *init) {
    Capt *q, *r;

    r = (Capt *)malloc(sizeof(Capt));
    if(p == NULL){
        q = init;
        init = r;
    } else {
        q = p->next;
        p->next = r;
    }
    r->piece = piece;
    r->next = q;
    return init;
}


Capt *delete(Capt *p, Capt *init) {
    Capt *q;
    
    if(isEmpty(init)) {
	    printf("Empty Error: capture.c > *delete\n");
	    exit(1);
    }
    if(p == NULL) {
        q = init;
        init = init->next;
        free(q);
    } else {
        if(p->next == NULL) {
            printf("error: no element to remove.\n");
            exit(1);
        } else {
            q = p->next;
            p->next = q->next;
            free(q);
        }
    }
    return init;
}


Capt *locate(Piece piece, Capt *init) {
    Capt *q;

    if(isEmpty(init)) {
	    printf("Empty Error: capture.c > *locate\n");
	    //exit(1);
	    return NULL; 
    }
    q = init;
    do {
        q = q->next;
	//printf("%d, ",q->piece);
        if(q->piece == piece) {
            return q;
            break;
        }
    } while(q->next != NULL);
    printf("error: cannot find of element %d\n", piece);
    //exit(1);
    return NULL;
}


Capt *previous(Capt *p, Capt *init){
    int offset = 0;
    Capt *q;
    
     if(isEmpty(init)) {
	    printf("Empty Error: capture.c > previous\n");
	    exit(1);
    }
    q = init;
    do {
        q = q->next;
        offset++;
    } while(q != p);
    q = init;
    if(offset < 1){
        printf("error: don't exist previous element.\n");
        exit(1);
    }
    for(int i=0; i<offset-1; i++) q = q->next;
    return q;
}


void printlist(Capt *init) {
    Capt *q;
    char c;

    q = init;
    printf("[");
   
    while(q != NULL) {
	switch(toRawPiece(q->piece)){
		case NIWATORI: c = 'N';  break;
		case LION:     c = 'L';  break;
		case ZOU:      c = 'Z';  break;
		case KIRIN:    c = 'K';  break;
		case HIYOKO:   c = 'H';  break;
	}
	printf("%c ", c);
	q = q->next;
    }

    printf("]\n");
}


int eval_capt(Capt *init) {
	int score = 0;
	Capt *q;

	q = init;
	while(q->next != NULL) {
		q = q->next;
		switch(toRawPiece(q->piece)) {
			case LION:     score += (int)HAS*DLION;     break;
			case ZOU:      score += (int)HAS*DZOU;      break;
			case KIRIN:    score += (int)HAS*DKIRIN;    break;
			case HIYOKO:   score += (int)HAS*DHIYOKO;   break;
		}

		if(q->next == NULL)         break;
		if(q->next->piece == EMPTY) break;
	}
	return score;
}


Capt *cptcpy(Capt *d) {
	Capt *s = NULL;
	while (d != NULL) {
		s = insert(d->piece, s, s);
		d = d->next;
	}
	return s;
}


void free_list(Capt *init) {
	Capt *tmp;
	while(init != NULL) {
		tmp = init->next;
		free(init);
		init = tmp;
	}
	free(init);
}


bool isEmpty(Capt *init){
    if(init->next == NULL) return true;
    return false;
}

