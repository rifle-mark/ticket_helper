/*
 * mwt_pgsql.h
 *
 *  Created on: 2014年10月11日
 *      Author: macbook
 */

#ifndef DB_INC_MWT_PGSQL_H_
#define DB_INC_MWT_PGSQL_H_

#include <mw_ttype.h>

void pgsql_init();
void pgsql_release();

void pgsql_save_result(ssc_result *r);
void pgsql_update_result(ssc_result *r);
ssc_result* pgsql_get_result(unsigned long issue_num);
ssc_result* pgsql_get_result(char* issue_time);
ssc_result* pgsql_get_results(unsigned long issue_beg, unsigned long issue_end);
ssc_result* pgsql_get_results(unsigned long issue_max, int count);

void pgsql_save_order(ssc_order *o);
void pgsql_update_order(ssc_order *o);
ssc_order* pgsql_get_order(unsigned long issue_num);
ssc_order* pgsql_get_orders_by_day(unsigned long issue_day);
ssc_order* pgsql_get_orders_by_month(unsigned long issue_month);
ssc_order* pgsql_get_orders(unsigned long issue_beg, unsigned long issue_end);
ssc_order* pgsql_get_orders(unsigned long issue_max, int count);

#endif /* DB_INC_MWT_PGSQL_H_ */
