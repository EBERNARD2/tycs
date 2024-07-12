#include <stdio.h>
#include <stdlib.h>

#define HASHSIZE 101

struct nlist { /* table entry: */
  struct nlist *next; /* next entry in chain */
  char *name; /* defined name */
  char *defn; /* replacement text */
};

static struct nlist *hashtab[HASHSIZE];
struct nlist *lookup(char *s);
char *strdup(char *);
char *strdupl(char *s);
void undef(char *s);

unsigned hash(char *s);


int main(void)
{
  return 0;
}


unsigned hash(char *s)
{
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}


struct nlist *lookup(char *s)
{
  struct nlist *np;
  for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    if (strcmp(s, np->name) == 0)
      return np; /* found */

  return NULL; /* not found */
}


struct nlist *install(char *name, char *defn)
{
  struct nlist *np;
  unsigned hashval;
  if ((np = lookup(name)) == NULL) { /* not found */
    np = (struct nlist *) malloc(sizeof(*np));
    if (np == NULL || (np->name = strdupl(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else /* already there */
    free((void *) np->defn); /*free previous defn */
  if ((np->defn = strdupl(defn)) == NULL)
    return NULL;
  return np;
}

char *strdupl(char *s)
{
  int i = 0;
  char *p;
  p = (char *) malloc(strlen(s) + 1);
  if (p != NULL)
    strcpy(p, s);
  return p;
}