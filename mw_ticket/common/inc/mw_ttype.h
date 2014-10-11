/*
 * mw_ttype.h
 *
 *  Created on: Oct 5, 2014
 *      Author: rifle
 */

#include <time.h>

typedef enum ssc_order_type {
	NONE,
	LAST_TWO,
	LAST_THREE,
	MID_THREE,
	FIRST_THREE,
	ALL_FIVE
} ssc_order_type;

typedef struct mw_list {
	mw_list *PRE;
	mw_list *NXT;
	struct mw_list_opt *listopt;
} mw_list;

typedef struct mw_list_opt {
	mw_list* 	(*add_obj)(mw_list *l, mw_list *a);
	mw_list* 	(*insert_obj)(mw_list *l, mw_list *i, int idx);
	mw_list* 	(*obj_at_idx)(int idx);
	int 		(*compare)(mw_list *v1, struct mw_list *v2);
	mw_list* 	(*sort)(mw_list *l);
	int			ref;
};

typedef struct ssc_result {
	mw_list			list_base;
	unsigned long 	issueNum;
	struct tm 		issueTime;
	char* 			issueResS;
	int				issueResI;
} ssc_result;


typedef struct ssc_order {
	mw_list			list_base;
	ssc_order_type	order_type;
	int				order_times;
	unsigned long	order_issue;
	char			*order_nums;
	ssc_result		result;
	int				isWin;
} ssc_order;


extern ssc_result* mw_ssc_create_new_result();
extern ssc_result* mw_ssc_create_result(char* res,
									    int resi,
										unsigned long issue_num,
										struct tm issue_time);
extern void mw_ssc_result_free(ssc_result *r);

extern ssc_order* mw_ssc_create_new_order();
extern ssc_order* mw_ssc_create_order(ssc_order_type ot,
									  int bt,
									  unsigned long issue,
									  char *ordernums);
extern ssc_order* mw_ssc_order_set_result(ssc_order *order, ssc_result *res);
extern void mw_ssc_order_free(ssc_order *o);
