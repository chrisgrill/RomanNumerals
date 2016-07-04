#include<check.h>
#include "../src/romancalc.h"

START_TEST (test_convert_from_roman)
{
  ck_assert_int_eq(convert_from_roman('M'),1000);  
  ck_assert_int_eq(convert_from_roman('C'),100);  
}
END_TEST

START_TEST (test_convert_to_roman)
{
  ck_assert_str_eq(convert_to_roman(1000),"M");
  ck_assert_str_eq(convert_to_roman(100),"C");
}
END_TEST

START_TEST (test_romancalc_compare)
{
  ck_assert_int_eq(compare('M','C'),1);
  ck_assert_int_eq(compare('C','M'),-1);
  ck_assert_int_eq(compare('M','M'),0);
}
END_TEST

START_TEST (test_expand)
{
  ck_assert_str_eq(expand("IV"),"IIII");
}
END_TEST

START_TEST (test_add)
{
  ck_assert_str_eq(add("IV","X"),"XIIII");
  ck_assert_str_eq(add("CMIV","X"),"DCCCCXIIII");
}
END_TEST

START_TEST (test_str_replace)
{
  ck_assert_str_eq(str_replace("LIX","IX","VIIII"),"LVIIII");
  ck_assert_str_eq(str_replace("LXIX","IX","VIIII"),"LXVIIII");
  ck_assert_str_eq(str_replace("LIXV","IX","VIIII"),"LVIIIIV");
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
    tcase_add_test(tc_additional, test_convert_to_roman);
    tcase_add_test(tc_additional, test_romancalc_compare);
    tcase_add_test(tc_additional, test_expand);
    tcase_add_test(tc_additional, test_add);
    tcase_add_test(tc_additional, test_str_replace);
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
