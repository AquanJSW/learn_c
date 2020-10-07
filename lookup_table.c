/* Exercise 6-5. Write a function undef that will remove a name and definition
 * from the table maintained by lookup and install.
 *
 * Exercise 6-6. Implement a simple version of the #define processor (i.e., no
 * arguments) suitable for use with C programs, based on the routines of this
 * section. You may also find getch and ungetch helpful. */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

#define SIZE_HASHTAB 101
#define BUF_NAME 256
#define BUF_DEF  256

struct def_list {
	char *name;
	char *def;
	struct def_list *next;
};
struct def_list *hashtab[SIZE_HASHTAB];
enum {END, SKIP, INSTALL, UNDEF, SHOW};
const char *usage = "usage:\n"
"- `#define NAME DEF` following a CR will give a definition.\n"
"- `NAME` following a CR will return its definition.\n"
"- `#undef NAME` following a CR will delete the definition.\n";

void undef(const char *name);
void scanarg(int argc, char **argv);
void error(const char *msg);
char getinput(char *name, char *def);
int getch(void);
void ungetch(int c);
void install(const char *name, const char *def);
struct def_list *lookup(const char *name);
char *stralloc(const char *str);
unsigned hash(const char *str);
void showdef(const char *name);

int main(int argc, char *argv[]) {
	char name[BUF_NAME];
	char def[BUF_DEF];
	char status;

	scanarg(argc, argv);
	while ((status = getinput(name, def)) != END)
		switch (status) {
			case INSTALL:
				install(name, def);
				break;
			case SHOW:
				showdef(name);
				break;
			case UNDEF:
				undef(name);
				break;
			default:
				break;
		}
	return 0;
}

char getinput(char *name, char *def) {
	int c, pn, pd;

	pn = pd = 0;
	while ((c = getch()) != EOF && c != '\n') {
		ungetch(c);
		while ((c = getch()) != EOF && c != '\n' && isblank(c));
		/* define line */
		if (c == '#') {
			while ((c=getch()) != EOF && c!='\n' && isalpha(c) && pn<BUF_NAME)
				name[pn++] = (char) c;
			ungetch(c);
			if (pn == BUF_NAME) {
				printf("warning: buffer for name is too small.\n");
				name[--pn] = '\0';
			} else
				name[pn] = '\0';

			if (!strcmp(name, "define")) {
				while ((c = getch()) != EOF && c != '\n' && isblank(c));
				ungetch(c);
				if (!isalpha(c))
					error("invalid name.");
				pn = 0;
				while ((c=getch())!=EOF && c!='\n' && isalnum(c) && pn<BUF_NAME)
					name[pn++] = (char) c;
				ungetch(c);
				if (pn == BUF_NAME) {
					printf("warning: buffer for name is too small.\n");
					name[--pn] = '\0';
				} else
					name[pn] = '\0';

				while ((c = getch()) != EOF && c != '\n' && isblank(c));
				ungetch(c);
				/* only considering the single-line definition */
				while ((c=getch())!=EOF && c!='\n' && pd<BUF_DEF)
					def[pd++] = (char) c;
				ungetch(c);
				if (pd == BUF_DEF) {
					printf("warning: "
					"buffer for definition is too small.\n");
					def[--pd] = '\0';
				} else
					def[pd] = '\0';
				return INSTALL;
			} else if (!strcmp(name, "undef")) {
				while ((c = getch()) != EOF && c != '\n' && isblank(c));
				ungetch(c);
				if (!isalpha(c))
					error("invalid name.");
				pn = 0;
				while ((c=getch())!=EOF && c!='\n' && isalnum(c) && pn<BUF_NAME)
					name[pn++] = (char) c;
				ungetch(c);
				if (pn == BUF_NAME) {
					printf("warning: buffer for name is too small.\n");
					name[--pn] = '\0';
				} else
					name[pn] = '\0';
				return UNDEF;
			}
		/* lookup */
		} else if (isalpha(c)) {
			ungetch(c);
			pn = 0;
			while ((c=getch())!=EOF && c!='\n' && isalnum(c) && pn<BUF_NAME)
				name[pn++] = (char) c;
			ungetch(c);
			if (pn == BUF_NAME) {
				printf("warning: buffer for name is too small.\n");
				name[--pn] = '\0';
			} else
				name[pn] = '\0';
			return SHOW;
		} else {
			ungetch(c);
			pn = 0;
			while ((c=getch())!=EOF && !isspace(c))
				name[pn++] = (char) c;
			ungetch(c);
			if (pn == BUF_NAME) {
				printf("warning: buffer for name is too small.\n");
				name[--pn] = '\0';
			} else
				name[pn] = '\0';
			printf("warning: invalid name \"%s\".\n", name);
		}
	}
	if (c == '\n')
		return SKIP;
	return END;
}

#define SIZE_STKCH 1000
int stkch[SIZE_STKCH];
int pstkch;

int getch(void) {
	return pstkch ? stkch[--pstkch] : getchar();
}

void ungetch(int c) {
	if (pstkch < SIZE_STKCH)
		stkch[pstkch++] = c;
	else
		error("stack for ungetch is used up.");
}

void install(const char *name, const char *def) {
	struct def_list *pd;
	unsigned hashval;

	if (!(pd = lookup(name))) { // not found
		pd = (struct def_list *) malloc(sizeof(struct def_list));
		pd->name = stralloc(name);
		if (!pd || !pd->name)
			printf("warning: memory is used up.\n");
		hashval = hash(name);
		/* 下面两行完成同一散列值的def_list叠加 */
		pd->next = hashtab[hashval]; // 保留原先的def_list
		hashtab[hashval] = pd; // 将pd置为顶层
	} else // found, update definition
		free(pd->def);
	pd->def = stralloc(def);
	if (!pd->def)
		printf("warning: memory is used up.\n");
}

struct def_list *lookup(const char *name) {
	struct def_list *pd;

	for (pd = hashtab[hash(name)]; pd; pd = pd->next)
		if (!strcmp(pd->name, name))
			return pd;
	return NULL;
}

char *stralloc(const char *str) {
	char *pstr;

	pstr = (char *) malloc(sizeof(str)+1);
	if (pstr)
		strcpy(pstr, str);
	else
		error("memory is used up.");
	return pstr;
}

unsigned hash(const char *name) {
	unsigned val;

	val = 0;
	for (; *name != '\0'; name++)
		val = *name + 31 * val;
	return val % SIZE_HASHTAB;
}

void error(const char *msg) {
	printf("error: %s\n", msg);
	exit(1);
}

void showdef(const char *name) {
	struct def_list *pd;

	pd = lookup(name);
	if (pd)
		printf("Name: %s\nDef: %s\n", pd->name, pd->def);
	else
		printf("not found.\n");
}

void scanarg(int argc, char **argv) {
	while (--argc) {
		if (**++argv == '-')
			while (*++*argv != '\0')
				switch (**argv) {
					case 'h':
						printf("%s", usage);
						exit(0);
					default:
						break;
				}
	}
}

void undef(const char *name) {
	struct def_list *pd, *p, **p0;
	unsigned hashval;

	if ((pd = lookup(name))) {
		p = (struct def_list *) malloc(sizeof(struct def_list));
		p0 = &p;
		hashval = hash(name);
		for (pd = hashtab[hashval]; strcmp(pd->name, name);
		pd = pd->next, p=p->next) {
			p->name = stralloc(pd->name);
			p->def = stralloc(pd->def);
			p->next = (struct def_list *) malloc(sizeof(struct def_list));
		}
		p = pd->next;
		hashtab[hashval] = *p0;
	} else
		printf("warning: %s not exist.\n", name);
}