typedef struct xbook {

	char bname[100];
	long unsigned bid;
	char author[100];
	char category[100];
	int rackno;
	
	
}xbook;

typedef struct date {

	int dd;
	int mm;
	int yy;
}date;

typedef struct xmember {

	char mname[100];
	long unsigned mid;
	long unsigned phoneno;
			
}xmember;

xmember member;
xbook book;
date d;
FILE *bk;
FILE *mem;
FILE *bkissue;

void add_book(void);
void issue_book(void);
void search_book(void);
void Author_book(void);
void add_new_mem(void);
void delete_book(void);
void category_book(void);
void display_info(void);
int calc_fine(int, int, int, int, int, int);
void book_return(void);
void issued_display(void);
void allmember_display(void);
void allbook_display(void);


