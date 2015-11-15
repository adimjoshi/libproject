/*LIBRARY MANAGEMENT. Copyright (C) 2015 ADITI JOSHI 111403053


This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include <ncurses.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MENUMAX 12
#include "libmanagement.h"

int f = 0;
void drawmenu(int item) {

	char mainmenu[100] = "LIBRARY MANAGEMENT SYSTEM\0";
	f++;
	start_color();
	
	init_pair(1, COLOR_RED, COLOR_YELLOW);
	bkgd(COLOR_PAIR(1));
	
	init_pair(2, COLOR_WHITE, COLOR_MAGENTA);
	attron(COLOR_PAIR(2));
	int i;
	if(f == 1) {
	/*initial screen display*/
		for(i = 30;i < 93; i++)
		mvprintw(23, i, "*");
		for(i = 8;i < 23; i++)
		mvprintw(i, 30, "*");
		for(i = 30; i < 93;i++)
		mvprintw(8, i ,"*");
		for(i = 8; i < 24; i++)
		mvprintw(i, 93, "*");
	
		mvaddstr(15, 53, mainmenu);
		getch();
		clear();
	}

	int c;
	clear();
	char menu[MENUMAX][50] = {"LIST OF BOOKS", 
				"SEARCH A BOOK",
				"ISSUE A BOOK",
				"LIST ALL BOOKS OF AN AUTHOR",
				"LIST ALL BOOKS OF A CATEGORY",
				"RETURN BOOK",
				"LIST OF MEMBERS",
				"BECOME A MEMBER",
				"LIST OF ISSUED BOOKS",
				"ADD A BOOK",
				"DELETE A BOOK",
				"EXIT"};
	
	
	for(c = 0;c < MENUMAX;c++) {
		if( c == item )
			attron(A_REVERSE);
			/* highlight selection */
			
			mvaddstr(1+(c*2), 40, menu[c]);
		attroff(A_REVERSE);
		/* remove highlight */
	}
	
	
	/*display border*/
	for(i = 30;i < 75; i++)
	mvprintw(0, i, "*");
	for(i = 0;i < 25; i++)
	mvprintw(i, 30, "*");
	for(i = 30; i < 75;i++)
	mvprintw(25, i ,"*");
	for(i = 0; i < 26; i++)
	mvprintw(i, 75, "*");
	move(40, 100);
	addstr("Press Enter to Select");
	move(30, 0);
	
	
	
	/*attributes off*/
	attroff(COLOR_PAIR(2));
	attroff(COLOR_PAIR(1));
	refresh();

}

int main() {
	
	int key,menuitem = 0;
	
	initscr();
	
	label:
	
	drawmenu(menuitem);
	keypad(stdscr,TRUE);

	noecho();
	/*disable echo*/
	if(menuitem == 11)
		echo();

	do {
		key = getch();
		switch(key) {
			case KEY_DOWN:	menuitem++;
					if(menuitem > MENUMAX-1) menuitem = 0;
					break;
			case KEY_UP:	menuitem--;
					if(menuitem < 0) menuitem = MENUMAX-1;
					break;
			default:	break;

		}

		drawmenu(menuitem);

	} while(key != '\n');

	echo();

	switch(menuitem) {
	
		case 0: allbook_display();
			break;
		case 1: search_book();
			break;
		case 2: issue_book();
			break;
		case 3: Author_book();
			break;
		case 4: category_book();
			break;
		case 5: book_return();
			break;
		case 6: allmember_display();
			break;
		case 7: add_new_mem();
			break;
		case 8:  issued_display();
			break;
		case 9: add_book();
			break;
		case 10:delete_book();
			break;
		case 11:echo();
			exit(0);
			break;
			
	}
	getch();
	
	goto label;	
	
	endwin();
	return 0;
}

void search_book() {
	
	clear();
	int  flag = 0, x = 15;
	char bkname[100];
	
	
	refresh();
	int z;
	fflush(stdout);
	move(10,60);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	attron(COLOR_PAIR(3));
	addstr("***SEARCH A BOOK***");
	attroff(COLOR_PAIR(3));
	move(13,40);
	printw("NAME OF BOOK: ");
	getstr(bkname);
		
	bk = fopen("libbook.txt", "r");

	if(!bk) 
		printf("EMPTY FILE!!\n");
	fflush(stdout);
		while(!feof(bk)) {
	
		z = fscanf(bk, "%s %lu %s %s %d", book.bname, &book.bid, book.author, book.category, &book.rackno);		
			
		
		if(strcmp(bkname, book.bname) == 0 && z != -1) {
			flag = 1;
			x = x + 2;
			//mvprintw(x, y, "%s\t\t\t%lu\t\t\t%s\t\t\t%s\t\t\t%d", book.bname, book.bid, book.author, book.category, book.rackno);
			
			move(x, 0);
			printw("%s", book.bname);
			
			move(x, 28);
			printw("%lu", book.bid);
			
			move(x, 58);
			printw("%s", book.author);
			
			move(x, 88);
			printw("%s", book.category);
			
			move(x, 120);
			printw("%d", book.rackno);
			break;
	
		}
	}
	if(!flag) {
		move(15, 40);
		printw("BOOK NOT FOUND!!");
	}
	else {
		init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
		attron(COLOR_PAIR(4));
		mvprintw(15, 0, "NAME\t\t\tBOOKID\t\t\t\tAUTHOR\t\t\t\tCATEGORY\t\t\tRACKNO");
		attroff(COLOR_PAIR(4));
	}
	
		
	fclose(bk);
	
}

void issue_book() {

	refresh();
	clear();
	char issuebook[100], name[100];
	int rdd, rmm, ryy, flag1 = 0, flag2 = 0;
	move(10,60);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	attron(COLOR_PAIR(3));
	addstr("***ISSUE A BOOK***");
	attroff(COLOR_PAIR(3));
	move(13,40);
	printw("ENTER NAME: ");
	refresh();
	scanw("%s", name);
	mem = fopen("libmem.txt", "r");
	bkissue = fopen("bookissue.txt", "a");
	
	if(!mem) {
		move(15,40);
		printw("MEMBER FILE CANNOT OPEN!!\n");
	}
	else {	int g;
		while(!feof(mem)) {
			g = fscanf(mem, "%s %lu %lu", member.mname, &member.mid, &member.phoneno);
			if(strcmp(name, member.mname) == 0 && g != -1)
				flag1 = 1;
		}
		if(flag1) {
			bk = fopen("libbook.txt", "r");
			if(!bk) {
				move(15, 40);
				printw("BOOK FILE CANNOT OPEN!!\n");
			}
			else {
				move(15, 40);
				printw("BOOK NAME: ");
				scanw("%s", issuebook);
				while(fgetc(bk) != EOF) {
					fscanf(bk, "%s %lu %s %s %d", book.bname, &book.bid, book.author, book.category, &book.rackno);
					if(strcmp(issuebook, book.bname) == 0) {
						flag2 = 1;
					
					}
				}
				
				if(flag2) {
					bkissue = fopen("bookissue.txt", "a");
					if(!bkissue) {
						move(17,40);
						printw("FILE CANNOT BE OPENED!\n");
						exit(0);
					}
					
					move(17,40);
					printw("ENTER TODAY'S DATE IN dd-mm-yy FORMAT: ");
					scanw("%d-%d-%d", &d.dd, &d.mm, &d.yy);
					fprintf(bkissue, "%s %s %d %d %d\n", name, issuebook, d.dd, d.mm, d.yy);
											
					switch(d.mm) {
						case 1:
						case 3:
						case 5:
						case 7:
						case 8:
						case 10:	if(d.dd <= 24) {
									rmm = d.mm;
									rdd = d.dd + 7;
									ryy = d.yy;
								}
								else {
									rdd = d.dd - 24;
									rmm = d.mm + 1;
									ryy = d.yy;
								}
								break;
								
						case 2:		if((d.yy % 400 == 0) || (!(d.yy % 100 == 0) && (d.yy % 4 == 0))) {
									if(d.dd <= 22) {
										rdd = d.dd + 7;
										rmm = d.mm;
										ryy = d.yy;
									}	
									else {
										rmm = d.mm + 1;
										rdd = d.dd - 22;
										ryy = d.yy;
									}
								}
								else {
									if(d.dd <= 21) {
										rdd = d.dd + 7;
										rmm = d.mm;
										ryy = d.yy;
									}
									else {
										rmm = d.mm + 1;
										rdd = d.dd - 21;
										ryy = d.yy;
									}	
								}	
								break;
						
						case 4:
						case 6:
						case 9:
						case 11:	if(d.dd <= 23) {
									rdd = d.dd + 7;
									rmm = d.mm;
									ryy = d.yy;
								}
								else {
									rdd = d.dd - 23;
									rmm = d.mm + 1;
									ryy = d.yy;
								}	
								break;
								
						case 12:	if(d.dd <= 24) {
									rmm = d.mm;
									rdd = d.dd + 7;
									ryy = d.yy;
								}
								else {
									rmm = 1;
									rdd = d.dd - 24;
									ryy = d.yy + 1;
								}
								break;
					}
					move(19, 40);	
					printw("RETURN DUE DATE: %d-%d-%d", rdd, rmm, ryy);
						
				}
				
				else {	
					move(17, 40);
					printw("NO SUCH BOOK IN LIBRARY!!\n");
				}
			}
			
		}
		else {
			move(17, 40);
			printw("BOOK CANNOT BE ISSUED!!");
			move(19, 40);
			printw("YOU ARE NOT A LIBRARY MEMBER!!");
		}
	
	}
	fclose(bk);
	fclose(mem);
	fclose(bkissue);
	
}


void add_book() {

	clear();
	move(10,60);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	attron(COLOR_PAIR(3));
	addstr("***ADD A BOOK***");
	attroff(COLOR_PAIR(3));
	move(13,40);
	bk = fopen("libbook.txt", "a+");
	if(!bk)
		printw("FILE CANNOT BE OPENED!!");
	else {	
		move(15,40);
		printw("BOOK NAME: ");
		scanw(" %[^\n]s", book.bname);
		
		move(17,40);
		printw("BOOK ID NO: ");
		scanw("%lu", &book.bid);
		
		move(19,40);
		printw("AUTHOR NAME: ");
		scanw(" %[^\n]s", book.author);
		
		move(21,40);
		printw("CATEGORY: ");
		scanw(" %[^\n]s", book.category);
		
		move(23, 40);
		printw("RACKNO:  ");
		scanw("%d", &book.rackno);
		
		fprintf(bk, "%s %lu %s %s %d\n", book.bname, book.bid, book.author, book.category, book.rackno);
		fclose(bk);
		
		move(25, 40);
		printw("BOOK ADDED SUCCESSFULLY");
	}
}

void Author_book() {

	refresh();
	clear();
	fflush(stdout);

	char nameauth[100];
	int x = 4, flag = 0, y = 0, z;
	move(1,60);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	attron(COLOR_PAIR(3));
	addstr("***LIST ALL BOOKS OF AN AUTHOR***");
	attroff(COLOR_PAIR(3));
	move(3,40);
	printw("AUTHOR NAME: ");
	scanw("%s", nameauth);
	refresh();
	bk = fopen("libbook.txt","r");
	
	if(bk == NULL) {
		move(5, 40);
		printw("CANNOT OPEN FILE!!");
		exit(0);
	}
	while(!feof(bk)) {
	
		z = fscanf(bk, "%s %lu %s %s %d", book.bname, &book.bid, book.author, book.category, &book.rackno);
		
		if(strcmp(nameauth, book.author) == 0 && z != -1) {
			flag = 1;
			x = x + 2;
			move(x, y);
			move(x, 0);
			printw("%s", book.bname);
			
			move(x, 24);
			printw("%lu", book.bid);
			
			
			move(x, 49);
			printw("%s", book.category);
			
			move(x, 80);
			printw("%d", book.rackno);
			
			
		}
	}
	
	if(!flag) {
		move(5, 40);
		printw("NO BOOK OF THIS AUTHOR IS AVAILABLE!!");
	}
	else {
		init_pair(4,COLOR_WHITE, COLOR_MAGENTA);
		attron(COLOR_PAIR(4));
		move(5, 0);
		printw("NAME\t\t\tBOOKID\t\t\tCATEGORY\t\t\tRACKNO");
		attroff(COLOR_PAIR(4));
	}
			
		
	fclose(bk);
	

}

void add_new_mem() {

	clear();
	mem = fopen("libmem.txt", "a+");
	move(10,60);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	attron(COLOR_PAIR(3));
	addstr("***BECOME A MEMBER***");
	attroff(COLOR_PAIR(3));
	
	move(13,40);
	printw("MEMBER NAME: ");
	scanw("%s", member.mname);
	
	move(15, 40);
	printw("USER ID: ");
	scanw("%lu", &member.mid);
	
	move(17, 40);
	printw("MOBILE NUMBER: ");
	scanw("%lu", &member.phoneno);
	
	fprintf(mem, "%s %lu %lu\n", member.mname, member.mid, member.phoneno);
	
	move(19, 40);
	printw("NEW MEMBER ADDED SUCCESSFULLY");
	fclose(mem);
	
}
void delete_book() {

	clear();
	char bookname[100];
	FILE *bkk;
	int x, flag = 0;
	move(10,60);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	attron(COLOR_PAIR(3));
	addstr("***DELETE A BOOK***");
	attroff(COLOR_PAIR(3));
	move(13,40);
	
	printw("NAME OF THE BOOK TO BE DELETED: ");
	scanw("%s", bookname);
	
	bk = fopen("libbook.txt", "r");
	bkk = fopen("dummy.txt", "a");
	if(!bk) {
		move(15, 40);
		printw("FILE CANNOT BE OPENED\n");
	}
	else {
		while(!feof(bk)) {
			
			x = fscanf(bk, "%s %lu %s %s %d", book.bname, &book.bid, book.author, book.category, &book.rackno);
			if(strcmp(bookname, book.bname) == 0)
				flag = 1;
			if(strcmp(bookname, book.bname) != 0 && x != -1) {
				
				fprintf(bkk, "%s %lu %s %s %d\n", book.bname, book.bid, book.author, book.category, book.rackno);
			}
		}
	}
	fclose(bk);
	fclose(bkk);
	remove("libbook.txt");
	rename("dummy.txt", "libbook.txt");
	if(flag) {
		move(15, 40);
		printw("BOOK DELETED SUCCESSFULLY!");
		move(17, 40);
		printw("CHECK LIST OF BOOKS");
	
	}
	else {
		move(15, 40);
		printw("NO SUCH BOOK IN LIBRARY!");
	
	}
	
}

void category_book() {

	clear();
	char catg[100];
	int flag = 0, x = 4, y = 0, z;
	bk = fopen("libbook.txt", "r");
	move(1,60);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	attron(COLOR_PAIR(3));
	addstr("***LIST ALL BOOKS OF AN CATEGORY***");
	attroff(COLOR_PAIR(3));
		
	if(!bk) {
		move(3,40);

		printw("FILE CANNOT BE OPENED!");
	}
	else {
		move(3,40);
;
		printw("CATEGORY OF BOOKS: ");
		scanw("%s", catg);
		while(!feof(bk)) {
	
			z = fscanf(bk, "%s %lu %s %s %d", book.bname, &book.bid, book.author, book.category, &book.rackno);
		
			if(strcmp(catg, book.category) == 0 && z != -1) {
			
				flag = 1;
				x = x + 2;
				move(x, y);
					
				move(x, 0);
				printw("%s", book.bname);
					
				move(x, 28);
				printw("%lu", book.bid);
				
				move(x, 48);
				printw("%s", book.author);
				
				
				move(x, 72);
				printw("%d", book.rackno);
			
	
			
			}
	}
	if(!flag) {
		move(5, 40);
		printw("NO BOOK UNDER THIS CATEGORY!");
	}
	else {
		init_pair(4,COLOR_WHITE, COLOR_MAGENTA);
		attron(COLOR_PAIR(4));
		move(5, 0);
		printw("NAME\t\t\tBOOKID\t\t\tAUTHOR\t\t\tRACKNO");
		attroff(COLOR_PAIR(4));
	}
	
	fclose(bk);
	}
}

void book_return() {

	clear();
	FILE *issue;
	int flag1 = 0, flag3 = 0, fine, a, b, c, l;
	char retbookname[100], nm[100], ibook[100];
	long unsigned id;
	move(10,60);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	attron(COLOR_PAIR(3));
	addstr("***RETURN A BOOK***");
	attroff(COLOR_PAIR(3));
	move(13,40);
	printw("MEMBER ID: ");
	scanw("%lu", &id);
	mem = fopen("libmem.txt", "r");
	if(!mem) {
		move(15, 40);
		printw("File CANNOT OPEN!\n");
	}
	
	else {
		while(fgetc(mem) != EOF) {
		
			fscanf(mem, "%s %lu %lu", member.mname, &member.mid, &member.phoneno);
			if(member.mid == id)
				flag1 = 1;
		}
		if(flag1) {
			bk = fopen("libbook.txt", "r");
			if(!bk) {
				move(15, 40);
				printw("BOOK FILE CANNOT OPEN\n");
				exit(0);
			}
			move(15, 40);
			printw("NAME OF THE BOOK TO BE RETURNED: ");
			scanw("%s", retbookname);
			while(fgetc(bk) != EOF) {
				fscanf(bk, "%s", book.bname);
				if(strcmp(book.bname, retbookname) == 0) {
					flag3 = 1;
						
				}
			}
			fclose(bk);
			if(flag3) {

				bkissue = fopen("bookissue.txt", "r");
				if(!bkissue) {
					move(17, 40);
					printw("BOOK ISSUE FILE CANNOT OPEN!!");
					exit(0);
				}
				move(17, 40);
				printw("PRESENT DATE IN dd-mm-yy FORMAT: ");
				
				scanw("%d-%d-%d", &a, &b, &c);
				fine = calc_fine(d.dd, d.mm, d.yy, a, b, c);
				if(!fine) {
					move(19, 40);
					printw("BOOK RETURNED ON TIME");
				}
				else {
					move(19, 40);
					printw("BOOK RETURNED LATE!!");
					move(21, 40);
					printw("FINE:  Rs.%d", fine);
				}
				issue = fopen("dum.txt", "w");
				if(issue) { 
					
					while(!feof(bkissue)) {
						l = fscanf(bkissue, "%s %s %d %d %d\n", nm, ibook, &d.dd, &d.mm, &d.yy);
						if(strcmp(ibook, retbookname) != 0 && l != -1)
							fprintf(issue,  "%s %s %d %d %d\n", nm, ibook, d.dd, d.mm, d.yy);
					}
						
						
						
				}
							
				fclose(bkissue);
				fclose(issue);
				remove("bookissue.txt");
				rename("dum.txt", "bookissue.txt");
										
			}
			
			else {
				move(17, 40);
				printw("NO SUCH BOOK IS TO BE RETURNED");
			}
		}
		else  {
			move(15, 40);
			printw("YOR ARE NOT A MEMBER");
		}
	}
	fclose(mem);
}

int calc_fine(int id, int im, int iy, int rd, int rm, int ry) {

	int x, y, z, f;
	x = rd - id;
	y = rm - im;
	z = ry - iy;
	if(x <= 7 && y == 0 && z == 0)
		f = 0;
	else if(x > 7 && y == 0 && z == 0) {
	
		if((x - 7) < 7)
			f = 50;
		else if((x - 7) < 14)
			f = 60;
		else if((x - 7) < 21)
			f = 70;
		else if((x - 7) <= 30)
			f = 100;
	}	
	else if(y > 0 || z > 0)
		f = 200;
	
	
	return f;
}

void allbook_display() {
	
	
	refresh();
	fflush(stdout);
	clear();
	bk = fopen("libbook.txt", "r");
	int x = 1, z;
	refresh();
	move(0,60);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	attron(COLOR_PAIR(3));
	addstr("***LIST ALL BOOKS***");
	attroff(COLOR_PAIR(3));
	
	if(!bk) {
	
		move(1,40);
		printw("CANNOT OPEN BOOK FILE!!");
		exit(0);
	}
	move(1, 0);
	init_pair(4,COLOR_WHITE, COLOR_MAGENTA);
	attron(COLOR_PAIR(4));

	printw("NAME\t\t\t\tID\t\t\t\tAUTHOR\t\t\t\tCATEGORY\t\t\tRACKNO");
	
	attroff(COLOR_PAIR(4));
	while(!feof(bk)) {
		z = fscanf(bk, "%s %lu %s %s %d", book.bname, &book.bid, book.author, book.category, &book.rackno);
		if(z != -1) {
		
			x = x + 1;
			move(x, 0);
			printw("%s", book.bname);
			move(x, 32);
			printw("%lu", book.bid);
			move(x, 62);
			printw("%s", book.author);
			move(x, 97);
			printw("%s", book.category);
			move(x, 130);
			printw("%d", book.rackno);
					}
	}
	fclose(bk);
	
}
void allmember_display() {

	int x = 2, z;
	refresh();
	fflush(stdout);
	clear();
	mem = fopen("libmem.txt", "r");
	move(1,60);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	attron(COLOR_PAIR(3));
	addstr("***LIST OF MEMBERS***");
	attroff(COLOR_PAIR(3));
	
	if(!mem) {
	
		move(3,40);
		printw("CANNOT OPEN ISSUE BOOK FILE!!");
		exit(0);
	}
	move(3, 40);
	init_pair(4,COLOR_WHITE, COLOR_MAGENTA);
	attron(COLOR_PAIR(4));

	printw("NAME\t\t\t\tID NO\t\t\t\tPHONENO");
	attroff(COLOR_PAIR(4));
	while(!feof(mem)) {
	
		z = fscanf(mem, "%s %lu %lu", member.mname, &member.mid, &member.phoneno);
		if(z != -1) {
		
			x = x + 2;
			move(x, 40);
			printw("%s", member.mname);
			
			move(x, 72);
			printw("%lu", member.mid);
			
			move(x, 105);
			printw("%lu", member.phoneno);
			
			
		}
	}
	
	fclose(mem);
	
}		
	
void issued_display() {

	refresh();
	fflush(stdout);
	clear();
	int a, b, c, x = 2, z;
	char name[100], ibook[100];
	bkissue = fopen("bookissue.txt", "r");
	move(1,60);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	attron(COLOR_PAIR(3));
	addstr("***LIST OF ISSUED BOOKS***");
	attroff(COLOR_PAIR(3));
	
	
	if(!bkissue) {
		move(3,40);
		printw("CANNOT OPEN ISSUE BOOK FILE!!");
		exit(0);
	}
	move(3,40);
	init_pair(4,COLOR_WHITE, COLOR_MAGENTA);
	attron(COLOR_PAIR(4));

	printw("MEMBER NAME\t\t\tBOOK NAME\t\t\tDATE");
	attroff(COLOR_PAIR(4));
	while(!feof(bkissue)) {
	
		z = fscanf(bkissue, "%s %s %d %d %d", name, ibook, &a, &b, &c);
		if(z != -1) {
			x = x + 2;
			
			move(x, 40);
			printw("%s", name);
			
			move(x, 72);
			printw("%s", ibook);
			
			move(x, 104);
			printw("%d-%d-%d", a, b, c);
			
		}
	}
	fclose(bkissue);

}
		
