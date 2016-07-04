AUTOMAKE_OPTIONS = no-exeext
TESTS = check_romancalc
check_PROGRAMS = check_romancalc
check_romancalc_SOURCES = check_romancalc.c $(top_builddir)/src/romancalc.h
check_romancalc_LDADD = $(top_builddir)/src/libromancalc.a -lcheck
AM_LDFLAGS = -lcheck