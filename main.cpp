using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <errno.h>
#include "Tree_node.h"
#include "Tree_node.cpp"
#include "util.c"

string print_path(Tree_node *last_node, bool error = false, bool newLine = false) {
	string str = "";
	while(last_node != NULL && last_node->parent != NULL) {
		str =last_node->byte + str;
		last_node = last_node->parent;
	}
	if(error) cerr << str;
	else cout << str;
	if(newLine) cerr << "\n";
	return str;
}

void encrypt(bool ascii_compress, int max_label) {
	int count = 1;
	Tree_node * head = new Tree_node(NULL, 0, (Tree_node *)NULL);
	Tree_node *cur = head;
	while(cin.peek() != EOF) {
		char c;
		cin.get(c);
		//cerr << (int)c << "\n";
		//fprintf(stderr, "%x\n", (int)c);
		Tree_node * loc = cur->find_child(c);
		if(loc == NULL) {
			if ( ascii_compress ) {
				cout << cur->label << " ";
				cout.put(c);
			} else {
				print_label(cur->label, max_label);
				print_letter(c);
			}
			cur->insert_child(c, count);
			count++;
			if(count >= max_label) {
				cerr << "ERROR: Number of labels exceeded maximum number set.\n\n";
				return;
			}
			cur = head;
		} else {
			cur = loc;
		}
	}
	if(!ascii_compress) {
		print_final_label(cur->label, max_label);
	} else {
		cout << cur->label << "";
	}
}

Tree_node **all;

void expand_array(long size) {
	long newsize = size * 2;
	Tree_node **oldAll = all;
	all = new Tree_node*[newsize];
	for(int i = 0; i < newsize; i++)
		all[i] = NULL;
	for(int i = 0; i < size; i++) {
		if(oldAll[i] == NULL) { continue; }
		all[i] = oldAll[i];
	}
}


void decrypt_ascii() {
	int count = 1;
	Tree_node * head = new Tree_node(NULL, 0, (Tree_node *)NULL);
	Tree_node *cur = head;
	
	long size = 256;
	all = new Tree_node*[size];
	all[0] = head;
	
	int label, nextLabel;
	char junk, c, nextC;
	
	cin >> label;
	cin.get(junk);
	c = NULL; //cin will just keep the value the same if nothing new
	cin.get(c);
	
	while(cin.peek() != EOF) {
		cin >> nextLabel;
		cin.get(junk);
		cin.get(nextC);
		if(label < size && all[label] != NULL) {
			Tree_node * newN;
			if( &c == NULL ) {
				newN = all[label];
			} else {
				Tree_node * cur = all[label];
				newN = cur->insert_child(c, count);
				while(count >= size) {
					expand_array(size);
					size = size*2;
				}
				all[count] = newN;
			}
			print_path(newN);
			count++;
		}
		c = nextC;
		label = nextLabel;
	}
	if(label < size && all[label] != NULL) {
		Tree_node * newN;
		newN = all[label];
		print_path(newN);
		count++;
	}
}

void decrypt(int max_label) {
	int count = 1;
	Tree_node * head = new Tree_node(NULL, 0, (Tree_node *)NULL);
	Tree_node *cur = head;
	
	long size = 256;
	all = new Tree_node*[size];
	all[0] = head;
	int nextLabel;
	char c = NULL;
	char nextC = NULL;
	int label = read_label(max_label);
	read_letter(c);
	while( (nextLabel = read_label(max_label)) != -1 && read_letter(nextC) != -1 ) {
		if(label < size && all[label] != NULL) {
			Tree_node * newN;
			Tree_node * cur = all[label];
			if( &c == NULL ) {
				newN = cur;
			} else {
				newN = cur->insert_child(c, count);
				while(count >= size) {
					expand_array(size);
					size = size*2;
				}
				all[count] = newN;
			}
			print_path(newN);
			count++;
		}
		c = nextC;
		label = nextLabel;
		nextC = NULL;
	}
	
	if(label < size && all[label] != NULL) {
		Tree_node * newN;
		Tree_node * cur = all[label];
		newN = cur;
		print_path(newN);
		count++;
	}
}

void usage() {
	cout << "./lz78 [opts] < input > output \n";
	cout << "Options:\n";
	cout << "Must choose either -e for encrypt or -d for decrypt\n";
	cout << "-b int where int is the number of bits to shift 2 for max_label, default is 25\n";
	cout << "-a for ascii encoding\n";
	cout << "-h help\n";
	return;
}

int main(int argc, char *argv[]) {

	bool ascii = false;
	bool enc = false;
	bool dec = false;
	int bits = 25;
	
	for(int i = 1; i < argc; i++ ) {
		if(argv[i][0] == '-'){
			if(argv[i][1] == 'a') {
				ascii = true;
			} else if (argv[i][1] == 'e') {
				enc = true;
			} else if (argv[i][1] == 'd') {
				dec = true;
			} else if (argv[i][1] == 'b') {
				i += 1;
				bits = (int) atol(argv[i]);
			} else if (argv[i][1] == 'h') {
				usage();
				exit(1);
			}
		}
		
		
	}
	
	if(enc) {
		encrypt(ascii, (1 << bits));
	} else if( dec ) {
		if(ascii) decrypt_ascii();
		else decrypt((1 << bits));
	} else {
		usage();
	}
	return 0;
}