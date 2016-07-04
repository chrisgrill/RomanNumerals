#ifndef ROMANCALC_H
#define ROMANCALC_H

char *str_replace(char *orig, char *rep, char *with);
int convert_from_roman(char roman);
char* convert_to_roman(int val);
char* add(char *rom1, char *rom2);
int compare(const void * rom1, const void * rom2);
char* expand(char *compressed);
#endif /* ROMANCALC_H */


