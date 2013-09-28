#ifndef _TABLES_H
#define _TABLES_H

signed char get_fuel_correction(unsigned int rpm, double load);
void print_fuel_table();
void read_fuel_table();

void save_fuel_table();
void load_fuel_table();

#endif

