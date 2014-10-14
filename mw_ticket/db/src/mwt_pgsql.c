/*
 * mwt_pgsql.c
 *
 *  Created on: 2014年10月11日
 *      Author: macbook
 */


#include <postgresql/libpq-fe.h>
#include "mwt_pgsql.h"


static const char* db_key[] = {
		"host",
		"port",
		"dbname",
		"user",
		"password"
};

static const char* db_val[] = {
		"localhost",
		"5432",
		"ticket_test",
		"rifle",
		"38619rry"
};

static PGconn *dbcon = NULL;

int pgsql_init() {
	dbcon = PQconnectdbParams(db_key, db_val, 1);
	if (PQstatus(dbcon) == CONNECTION_OK) {
		return 1;
	}
	return 0;
}

void pgsql_release() {
	if (dbcon) {
		PQfinish(dbcon);
		dbcon = NULL;
	}
}

void pgsql_save_result(ssc_result *r) {

}

void pgsql_update_result(ssc_result *r) {

}

ssc_result* pgsql_get_result(unsigned long issue_num) {

}

ssc_result* pgsql_get_result(char* issue_time) {

}

ssc_result* pgsql_get_results(unsigned long issue_beg, unsigned long issue_end) {

}

ssc_result* pgsql_get_results(unsigned long issue_max, int count) {

}

void pgsql_save_order(ssc_order *o) {

}

void pgsql_update_order(ssc_order *o) {

}

ssc_order* pgsql_get_order(unsigned long issue_num) {

}

ssc_order* pgsql_get_orders_by_day(unsigned long issue_day) {

}

ssc_order* pgsql_get_orders_by_month(unsigned long issue_month) {

}

ssc_order* pgsql_get_orders(unsigned long issue_beg, unsigned long issue_end) {

}

ssc_order* pgsql_get_orders(unsigned long issue_max, int count) {

}
