/* adsum_models.h  */
/*
 *  Copyright 2021 , Adsum Networks, www.adsumnetworks.io
 */

#ifndef BT_MESH_ADSUM_LIB_H__
#define BT_MESH_ADSUM_LIB_H__
#define BT_MESH_MODEL_USER_DATA(_type, _user_data)                             \
	(((_user_data) == (_type *)0) ? NULL : (_user_data))
#define ADSUM_OP_KEEPALIVE_MSG BT_MESH_MODEL_OP_3(CONFIG_ADSUM_OP_KEEPALIVE_MSG_ID, CONFIG_ADSUM_COMPANY_ID) 
struct bt_mesh_adsum_keepalive_model_context ;
#define BT_MESH_ADSUM_KEEPALIVE_MODEL(_keepalive_model)                                          \
		BT_MESH_MODEL_VND_CB(CONFIG_ADSUM_COMPANY_ID,       \
			CONFIG_ADSUM_KEEPALIVE_MODEL_ID,                      \
			ADSUM_KEEPALIVE_MODEL_OPS, &(_keepalive_model)->pub,                   \
			BT_MESH_MODEL_USER_DATA(struct bt_mesh_adsum_keepalive_model_context,       \
						_keepalive_model),                        \
			&ADSUM_KEEPALIVE_MODEL_callbacks)
struct bt_mesh_adsum_keepalive_model_context {
	struct bt_mesh_model *model;
	struct bt_mesh_model_pub pub;
	struct net_buf_simple pub_msg;
	uint8_t buf[BT_MESH_MODEL_BUF_LEN(ADSUM_OP_KEEPALIVE_MSG,CONFIG_ADSUM_OP_KEEPALIVE_MSG_MAXLEN_MESSAGE)];
};
#define ADSUM_OP_PERF_UPDATE BT_MESH_MODEL_OP_3(CONFIG_ADSUM_OP_PERF_UPDATE_MSG_ID, CONFIG_ADSUM_COMPANY_ID) 
struct bt_mesh_adsum_perf_srv_model_context ;
#define BT_MESH_ADSUM_PERF_SRV_MODEL(_perf_srv_model)                                          \
		BT_MESH_MODEL_VND_CB(CONFIG_ADSUM_COMPANY_ID,       \
			CONFIG_ADSUM_PERF_SRV_MODEL_ID,                      \
			ADSUM_PERF_SVR_MODEL_OPS, &(_perf_srv_model)->pub,                   \
			BT_MESH_MODEL_USER_DATA(struct bt_mesh_adsum_perf_srv_model_context,       \
						_perf_srv_model),                        \
			&ADSUM_PERF_SRV_MODEL_callbacks)
struct bt_mesh_adsum_perf_srv_model_context {
	struct bt_mesh_model *model;
	struct bt_mesh_model_pub pub;
	struct net_buf_simple pub_msg;
	uint8_t buf[BT_MESH_MODEL_BUF_LEN(ADSUM_OP_PERF_UPDATE,CONFIG_ADSUM_OP_PERF_UPDATE_MAXLEN_MESSAGE)];
};
void adsum_model_init(const struct bt_mesh_comp *comp);
extern const struct bt_mesh_model_cb ADSUM_KEEPALIVE_MODEL_callbacks;
extern const struct bt_mesh_model_cb ADSUM_PERF_SRV_MODEL_callbacks;
extern const struct bt_mesh_model_op ADSUM_KEEPALIVE_MODEL_OPS[] ;
extern const struct bt_mesh_model_op ADSUM_PERF_SVR_MODEL_OPS[] ;
static struct bt_mesh_adsum_keepalive_model_context adsum_keepalive_model ;
static struct bt_mesh_adsum_perf_srv_model_context adsum_perf_srv_model ;
static struct bt_mesh_model Adsum_models[] = {
	BT_MESH_ADSUM_KEEPALIVE_MODEL(&adsum_keepalive_model),
	BT_MESH_ADSUM_PERF_SRV_MODEL(&adsum_perf_srv_model)
};
#endif /* BT_MESH_ADSUM_LIB_H__ */
