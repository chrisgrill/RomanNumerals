#ifndef ROMANCALC_H
#define ROMANCALC_H

char *str_replace(char *orig, char *rep, char *with);
int convert_from_roman(char roman);
char* add(char *rom1, char *rom2);
int compare(const void * rom1, const void * rom2);
char* expand(char *roman);
char* subtract(char *rom1, char *rom2);
void remove_char(char *str, char remove);
#endif /* ROMANCALC_H */


