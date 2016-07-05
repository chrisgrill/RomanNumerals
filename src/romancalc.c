#include <stdlib.h>
#include <string.h>
#include "romancalc.h"

//Lookup table of roman numeral and integer values
typedef struct {char key; int val;} digits;
//Lookup table for converting between subtractive representations and additive representaions
typedef struct {char *sub; char *add;} sub_to_add_map;
//Lokup table for combinations that break the rules of repeating numerals
typedef struct {char *bad; char* good;} sum_map;

//Static lookup tables
static digits d[]={{'M',1000},{'D',500},{'C',100},{'L',50},{'X',10},{'V',5},{'I',1}};
static sub_to_add_map stam[]={{"CM","DCCCC"},{"CD","CCCC"},{"XC","LXXXX"},{"XL","XXXX"},{"IX","VIIII"},{"IV","IIII"}};
static sum_map sm[]={{"IIIII","V"},{"VV","X"},{"XXXX","L"},{"LL","C"},{"CCCCC","D"},{"DD","M"}};

//Let the preprocessor determine number of keys in static table
#define DKEYS (sizeof(d)/sizeof(digits))
#define MKEYS (sizeof(stam)/sizeof(sub_to_add_map))
#define SKEYS (sizeof(sm)/sizeof(sum_map))

//TODO Move this to another file. I did not write this function.
//It is a common enough process to pull form internet. Could probably be optimized
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
//This is used for comparing the values a numeral represents
int convert_from_roman(char roman)
{
  int i;
  for (i=0; i < DKEYS; i++)
    {
      //Get a pointer to the ith entry in the digits map
      digits *sym = &d[i];
      if (sym->key == roman)
	{
	  return sym->val;
	}
    }

  return 0;
}


//Convert numeral to integer value and compare, right now return value is based on descending order
int compare(const void * rom1, const void * rom2)
{
  int val1;
  int val2;
  val1 = convert_from_roman(*(char*)rom1);
  val2 = convert_from_roman(*(char*)rom2);
  return (val1>val2)?-1:(val1<val2);

}

char* expand(char *roman)
{
  int i;
  char *resp;
  resp = malloc(255 * sizeof(roman));
  strcpy(resp,roman);

  for (i = MKEYS-1; i >= 0; i--)
    {
      sub_to_add_map *sym = &stam[i];      
      resp = str_replace(resp,sym->sub,sym->add);
    }
  return resp;
}

//Add two roman numeral numbers
char* add(char *rom1, char *rom2)
{
  int i;
  char *resp;
  char *resp2;

  resp = expand(rom1);
  resp2 = expand(rom2);
  strcat(resp, resp2);
  free(resp2);
  qsort(resp,strlen(resp),1,compare);
  for (i = 0; i < SKEYS; i++)
    {
      sum_map *sym = &sm[i];
      resp = str_replace(resp,sym->bad,sym->good);

    }
  for (i = 0; i < MKEYS; i++)
    {
      sub_to_add_map *sym = &stam[i];
      resp = str_replace(resp,sym->add,sym->sub);
    }
  
  return resp;
}


char* subtract(char *rom1, char *rom2)
{
  int i;
  char *resp;
  char *tmp;

  resp = expand(rom1);
  tmp = expand(rom2);
  
  for (i = 0; i < strlen(resp); i++)
    {
      for (int j = 0; j < strlen(tmp); j++)
	{
	  if (resp[i] == tmp[j])
	    {
	      memmove(&resp[i], &resp[i + 1], strlen(resp) - i);
	      memmove(&tmp[j], &tmp[j + 1], strlen(tmp) - j);
	    }
	}
    }
  free(tmp);
  return resp;
}


