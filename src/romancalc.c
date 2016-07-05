#include <stdlib.h>
#include <string.h>
#include "romancalc.h"
#include "str_replace.h"

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

//Convert subtractive representations (i.e IV) to additive representations (i.e IIII)
//TODO: Optimize this by determining how much memory I should actually be allocating
char* expand(char *roman)
{
  int i;
  char *resp;
  resp = malloc(255 * sizeof(roman));
  strcpy(resp, roman);

  for (i = MKEYS-1; i >= 0; i--)
    {
      sub_to_add_map *sym = &stam[i];      
      resp = str_replace(resp, sym->sub, sym->add);
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
  qsort(resp, strlen(resp), 1, compare);
  for (i = 0; i < SKEYS; i++)
    {
      sum_map *sym = &sm[i];
      resp = str_replace(resp, sym->bad, sym->good);

    }
  for (i = 0; i < MKEYS; i++)
    {
      sub_to_add_map *sym = &stam[i];
      resp = str_replace(resp, sym->add, sym->sub);
    }
  
  return resp;
}

//Subtract rom2 from rom1
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
	      //Remove the matching character from both strings
	      memmove(&resp[i], &resp[i + 1], strlen(resp) - i);
	      memmove(&tmp[j], &tmp[j + 1], strlen(tmp) - j);
	    }
	}
    }
  free(tmp);
  return resp;
}


