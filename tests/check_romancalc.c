#include<check.h>
#include "../src/romancalc.h"

START_TEST (test_convert_from_roman)
{
  ck_assert_int_eq(convert_from_roman('M'),1000);  
  ck_assert_int_eq(convert_from_roman('C'),100);  
}
END_TEST


START_TEST (test_romancalc_compare)
{
  char m = 'M';
  char c = 'C';
  char also_m = 'M';
  ck_assert_int_eq(compare(&m,&c),-1);
  ck_assert_int_eq(compare(&c,&m),1);
  ck_assert_int_eq(compare(&m,&also_m),0);
}
END_TEST

START_TEST (test_add)
{
  ck_assert_str_eq(add("IV","IV"),"VIII");
  ck_assert_str_eq(add("IV","X"),"XIV");
  ck_assert_str_eq(add("XIV","LX"),"LXXIV");
  ck_assert_str_eq(add("CMIV","X"),"CMXIV");
}
END_TEST

START_TEST (test_str_replace)
{
  ck_assert_str_eq(str_replace("LIX","IX","VIIII"),"LVIIII");
  ck_assert_str_eq(str_replace("LXIX","IX","VIIII"),"LXVIIII");
  ck_assert_str_eq(str_replace("LIXV","IX","VIIII"),"LVIIIIV");
  ck_assert_str_eq(str_replace("IIIIIIIIIII","IIIII","V"),"VVI");
  ck_assert_str_eq(str_replace("VVI","VV","X"),"XI");
}
END_TEST

START_TEST (test_remove_character)
{
  ck_assert_str_eq(remove_character("VI","I"),"V");

}
END_TEST

START_TEST (test_subtract)
{
  ck_assert_str_eq(subtract("IV","II"),"III");

}
END_TEST

Suite * romancalc_suite(void)
{
    Suite *s;
    TCase *tc_core;
    TCase *tc_additional;
    s = suite_create("Romancalc");
    
    tc_core = tcase_create("Core");
    tc_additional = tcase_create("Additional");
    tcase_add_test(tc_core, test_convert_from_roman);
    tcase_add_test(tc_additional, test_romancalc_compare);
    tcase_add_test(tc_additional, test_add);
    tcase_add_test(tc_additional, test_str_replace);
    tcase_add_test(tc_additional, subtract);
    suite_add_tcase(s, tc_core);
    suite_add_tcase(s, tc_additional);
    
    return s;
}

int main(void){
    int number_failed;
    Suite *s;
    SRunner *sr;
    
    s = romancalc_suite();
    sr = srunner_create(s);
    srunner_set_log (sr, "test.log");    
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
}
