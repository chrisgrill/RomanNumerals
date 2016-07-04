#include <stdlib.h>
#include <string.h>
#include "romancalc.h"

//Defining a new type for a lookup table of roman numeral and integer values
typedef struct {char *key; int val;} roman_table;
typedef struct {char key; int val;} digits;
typedef struct {char *sub; char *add;} sub_to_add_map;
//Static lookup table of values  

static digits d[]={{'M',1000},{'D',500},{'C',100},{'L',50},{'X',10},{'V',5},{'I',1}};
static sub_to_add_map stam[]={{"CM","DCCCC"},{"CD","CCCC"},{"XC","LXXXX"},{"XL","XXXX"},{"IX","VIIII"},{"IV","IIII"}};

//Let the preprocessor determine number of keys in static table
#define NKEYS (sizeof(rt)/sizeof(roman_table))
#define DKEYS (sizeof(d)/sizeof(digits))
#define MKEYS (sizeof(stam)/sizeof(sub_to_add_map))

char *str_replace(char *orig, char *rep, char *with) {
  char *result; // the return string
  char *ins;    // the next insert point
  char *tmp;    // varies
  int len_rep;  // length of rep
  int len_with; // length of with
  int len_front; // distance between rep and end of last rep
  int count;    // number of replacements

  if (!orig)
    return NULL;
  if (!rep)
    rep = "";
  len_rep = strlen(rep);
  if (!with)
    with = "";
  len_with = strlen(with);

  ins = orig;
  for (count = 0; tmp = strstr(ins, rep); ++count) {
    ins = tmp + len_rep;
  }

  // first time through the loop, all the variable are set correctly
  // from here on,
  //    tmp points to the end of the result string
  //    ins points to the next occurrence of rep in orig
  //    orig points to the remainder of orig after "end of rep"
  tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

  if (!result)
    return orig;

  while (count--) {
    ins = strstr(orig, rep);
    len_front = ins - orig;
    tmp = strncpy(tmp, orig, len_front) + len_front;
    tmp = strcpy(tmp, with) + len_with;
    orig += len_front + len_rep; // move to next "end of rep"
  }
  strcpy(tmp, orig);
  return result;
}

//Return the integer value of a fundamental roman numeral
int convert_from_roman(char roman)
{
  int i;
  for (i=0; i < DKEYS; i++)
    {
      digits *sym = &d[i];
      if (sym->key == roman)
	{
	  return sym->val;
	}
    }

  return 0;
}



int compare(const void * rom1, const void * rom2)
{
  int val1;
  int val2;
  val1 = convert_from_roman(*(char*)rom1);
  val2 = convert_from_roman(*(char*)rom2);
  return (val1<val2)?-1:(val1>val2);

}

char* expand(char *compressed)
{
  int i;
  for (i=0; i < MKEYS; i++)
    {
      sub_to_add_map *sym = &stam[i];
      if (strcmp(sym->sub,compressed) == 0)
	{
	  return sym->add;
	}

    }
  return NULL;


}

char* add(char *rom1, char *rom2)
{
  int i;
  char *resp;
  char *resp2;
  resp = malloc(255 * sizeof(rom1));
  resp2 = malloc(255 * sizeof(rom2));
  strcpy(resp, rom1);
  strcpy(resp2, rom2);
  

  for (i = MKEYS-1; i >= 0; i--)
    {
      sub_to_add_map *sym = &stam[i];
      
      resp = str_replace(resp,sym->sub,sym->add);
      resp2 = str_replace(resp2,sym->sub,sym->add);
    }
  strcat(resp, resp2);
  qsort(resp,strlen(resp),1,compare);
  return resp;
  //return "\0";
}


//TODO Remove
static roman_table rt[]={{"M",1000},{"CM",900},{"D",500},{"CD",400},{"C",100},{"XC",90},{"L",50},{"XL",40},{"X",10},{"IX",9},{"V",5},{"IV",4},{"I",1}};

char* convert_to_roman(int val)
{
  int i;
  for (i=0; i < NKEYS; i++)
    {
      roman_table *sym = &rt[i];
      if (val == sym->val)
	{
	  return sym->key;
	}
    }
  return "\0";

}
