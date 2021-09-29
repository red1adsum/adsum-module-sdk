/* adsum_models.h  */
/*
 *  * Adsum Networks 2021
 *  KeepAlive and Perfermance Models Library 
 */
#ifndef BT_MESH_ADSUMNET_LIB_H__
#define BT_MESH_ADSUMNET_LIB_H__




/** Internal utility macro for type checking model user data.
 *
 * Produces a "Comparison of distinct pointer types" warning if @p _user_data
 * is of the wrong type.
 * */
#define BT_MESH_MODEL_USER_DATA(_type, _user_data)                             \
	(((_user_data) == (_type *)0) ? NULL : (_user_data))

// Adsum element unicast address
//#define ADSUM_COMPANY_ID BT_COMP_ID_LF // Kconfig hidden
/* *	=	=	=	=	=	=	=	=	=	 ADSUM KEEPALIVE MODEL =	=	=	=	=	=	=	=	= * */
// MODEL OP_CODE 

// Model ID and sign
//#define ADSUM_KEEPALIVE_MODEL_ID 0x0000 // Kconfig hidden
//#define ADSUM_OP_KEEPALIVE_MSG_ID 0x00 // Kconfig hidden
#define ADSUM_OP_KEEPALIVE_MSG BT_MESH_MODEL_OP_3(CONFIG_ADSUM_OP_KEEPALIVE_MSG_ID, CONFIG_ADSUM_COMPANY_ID) 
//#define ADSUM_OP_KEEPALIVE_MSG_MAXLEN_MESSAGE 2 // Kconfig 

// * Forward declaration of the Bluetooth Mesh ADSUM KeepAlive Model context . * /
struct bt_mesh_adsum_keepalive_model_context ;
#define BT_MESH_ADSUM_KEEPALIVE_MODEL(_keepalive_model)                                          \
		BT_MESH_MODEL_VND_CB(CONFIG_ADSUM_COMPANY_ID,       \
			CONFIG_ADSUM_KEEPALIVE_MODEL_ID,                      \
			ADSUM_KEEPALIVE_MODEL_OPS, &(_keepalive_model)->pub,                   \
			BT_MESH_MODEL_USER_DATA(struct bt_mesh_adsum_keepalive_model_context,       \
						_keepalive_model),                        \
			&ADSUM_KEEPALIVE_MODEL_callbacks)

// ADSUM KeepAlive Model  context.
struct bt_mesh_adsum_keepalive_model_context {
	// ** Access model pointer. * /
	struct bt_mesh_model *model;
	// ** Publish parameters. * /
	struct bt_mesh_model_pub pub;
	// ** Publication message. * /
	struct net_buf_simple pub_msg;
	// ** Publication message buffer. * /
	uint8_t buf[BT_MESH_MODEL_BUF_LEN(ADSUM_OP_KEEPALIVE_MSG,CONFIG_ADSUM_OP_KEEPALIVE_MSG_MAXLEN_MESSAGE)];
};



/* * =	=	=	=	=	=	=	=	= ADSUM PERFORMANCE SERVER : MODEL =	=	=	=	=	=	=	=	= * */ //
// MODEL OP_CODE
// MODEL OP_CODE  
//#define ADSUM_OP_PERF_UPDATE_MSG_ID 0x02  // Kconfig
#define ADSUM_OP_PERF_UPDATE BT_MESH_MODEL_OP_3(CONFIG_ADSUM_OP_PERF_UPDATE_MSG_ID, CONFIG_ADSUM_COMPANY_ID) 
//#define ADSUM_OP_PERF_UPDATE_MAXLEN_MESSAGE 100 // Kconfig
// Model ID
//#define ADSUM_PERF_SRV_MODEL_ID 0x0001 // Kconfig hidden
// Publication and Subscribtion params 

// * Forward declaration of the Bluetooth Mesh ADSUM Perf Server context . * /
struct bt_mesh_adsum_perf_srv_model_context ;
#define BT_MESH_ADSUM_PERF_SRV_MODEL(_perf_srv_model)                                          \
		BT_MESH_MODEL_VND_CB(CONFIG_ADSUM_COMPANY_ID,       \
			CONFIG_ADSUM_PERF_SRV_MODEL_ID,                      \
			ADSUM_PERF_SVR_MODEL_OPS, &(_perf_srv_model)->pub,                   \
			BT_MESH_MODEL_USER_DATA(struct bt_mesh_adsum_perf_srv_model_context,       \
						_perf_srv_model),                        \
			&ADSUM_PERF_SRV_MODEL_callbacks)

// ADSUM Perf Server Model  context.
struct bt_mesh_adsum_perf_srv_model_context {
	// ** Access model pointer. * /
	struct bt_mesh_model *model;
	// ** Publish parameters. * /
	struct bt_mesh_model_pub pub;
	// ** Publication message. * /
	struct net_buf_simple pub_msg;
	// ** Publication message buffer. * /
	uint8_t buf[BT_MESH_MODEL_BUF_LEN(ADSUM_OP_PERF_UPDATE,CONFIG_ADSUM_OP_PERF_UPDATE_MAXLEN_MESSAGE)];
};


/* * =	=	=	=	=	=	=	=	= =	=	=	=	=	=	=	=	= * */ //
// adsum models init 

void adsum_model_init(const struct bt_mesh_comp *comp);


// Externals
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

#endif /* BT_MESH_ADSUMNET_LIB_H__ */