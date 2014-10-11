/*
​ * mw_ttype.c
 *
 *  Created on: 2014年10月7日
 *      Author: macbook
 */


#include <stdlib.h>
#include <string.h>
#include "mw_ttype.h"

static int result_compare(ssc_result *r1, ssc_result *r2) {
	return r1->issueNum - r2->issueNum;
}

static int order_compare(ssc_order *o1, ssc_order *o2) {
	return o1->order_issue - o2->order_issue;
}

static mw_list* list_sort(mw_list *l) {
	return l;
}

static mw_list* list_add(mw_list *l, mw_list *a) {
	mw_list *v = l->NXT;
	while (v->NXT) {
		v = v->NXT;
	}
	v->NXT = a;
	a->PRE = v;
	return l;
}

static mw_list* list_insert(mw_list *l, mw_list *i, int idx) {
	if (idx == 0) {
		i->NXT = l;
		if (l->PRE) {
			l->PRE->NXT = i;
			i->PRE = l->PRE;
		}
		l->PRE = i;
		return i;
	}

	mw_list *ret = l;
	int cidx = 0;
	while (cidx != idx && l->NXT) {
		l = l->NXT;
		++cidx;
	}

	if (cidx == idx) {
		l->PRE->NXT = i;
		i->PRE = l->PRE;
		i->NXT = l;
	}
	else {
		ret = list_add(ret, i);
	}

	return ret;
}

static mw_list* list_obj_at_idx(mw_list *l, int idx) {
	int cidx = 0;
	while (l->NXT && cidx != idx) {
		l = l->NXT;
		++cidx;
	}
	if (cidx != idx)
		return NULL;
	return l;
}

static struct mw_list_opt *list_base_opt = NULL;

ssc_result* mw_ssc_create_new_result() {
	ssc_result *ret = (ssc_result*)malloc(sizeof(ssc_result));
	if (ret) {
		if (!list_base_opt) {
			list_base_opt = (struct mw_list_opt*)malloc(sizeof(struct mw_list_opt));
			list_base_opt->compare = &result_compare;
			list_base_opt->sort = &list_sort;
			list_base_opt->add_obj = &list_add;
			list_base_opt->insert_obj = &list_insert;
			list_base_opt->obj_at_idx = &list_obj_at_idx;
			list_base_opt->ref = 1;
		}
		memset(ret, 0, sizeof(ssc_result));
		ret->list_base.listopt = &list_base_opt;
	}
	return ret;
}

ssc_result* mw_ssc_create_result(char* res,
								 int resi,
								 unsigned long issue_num,
								 struct tm issue_time) {
	ssc_result *ret = mw_ssc_create_new_result();
	if (ret) {
		ret->issueNum = issue_num;
		ret->issueTime = issue_time;
		ret->issueResS = res;
		ret->issueResI = resi;
	}
	return ret;
}

void mw_ssc_result_free(ssc_result *r) {
	r->list_base.PRE = NULL;
	r->list_base.NXT = NULL;
	r->list_base.listopt->ref -= 1;
	if (r->list_base.listopt->ref == 0) {
		free(r->list_base.listopt);
	}
	r->list_base.listopt = NULL;
	free(r->issueResS);
	free(r);
}

ssc_order* mw_ssc_create_new_order() {
	ssc_order *ret = (ssc_order*)malloc(sizeof(ssc_order));
	if (ret) {
		if (!list_base_opt) {
			list_base_opt = (struct mw_list_opt*)malloc(sizeof(struct mw_list_opt));
			list_base_opt->compare = &order_compare;
			list_base_opt->sort = &list_sort;
			list_base_opt->add_obj = &list_add;
			list_base_opt->insert_obj = &list_insert;
			list_base_opt->obj_at_idx = &list_obj_at_idx;
			list_base_opt->ref = 1;
		}
		memset(ret, 0, sizeof(ssc_order));
		ret->list_base.listopt = &list_base_opt;
	}
	return ret;
}

ssc_order* mw_ssc_create_order(ssc_order_type ot,
							   int bt,
							   unsigned long issue,
							   char *ordernums) {
	ssc_order *ret = mw_ssc_create_new_order();
	if (ret) {
		ret->isWin = -1;
		ret->order_issue = issue;
		ret->order_type = ot;
		ret->order_times = bt;
		int olen = strlen(ordernums);
		ret->order_nums = (char*)malloc((olen+1)*sizeof(char));
		memcpy(ret->order_nums, ordernums, olen);
		ret->order_nums[olen] = '\0';
	}

	return ret;
}

ssc_order* mw_ssc_order_set_result(ssc_order *order, ssc_result *res) {
	if (order->order_issue == res->issueNum) {
		order->result.issueNum = res->issueNum;
		order->result.issueResI = res->issueResI;
		int reslen = strlen(res->issueResS);
		order->result.issueResS = (char*)malloc((reslen+1) * sizeof(char));
		memcpy(order->result.issueResS, res->issueResS, reslen);
		order->result.issueResS[reslen] = '\0';
		order->result.issueTime = res->issueTime;
		order->result.list_base.listopt = res->list_base.listopt;
		order->result.list_base.listopt->ref += 1;
	}
	return order;
}

void mw_ssc_order_free(ssc_order *order) {
	free(order->order_nums);
	free(order->result.issueResS);
	order->list_base.listopt->ref -= 1;
	if (order->list_base.listopt->ref == 0) {
		free(order->list_base);
	}
	order->result.list_base.listopt->ref -= 1;
	if (order->result.list_base.listopt->ref == 0) {
		free(order->result.list_base);
	}
}
