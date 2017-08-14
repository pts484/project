#include "db_mysql.h"

DB_MySQL::DB_MySQL() {
	
	connection = NULL;
	sql_result = NULL;

	printf("MySQL client Version : %s\n", mysql_get_client_info());
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_options(&mysql, MYSQL_INIT_COMMAND, "SET NAMES utf8");
}

DB_MySQL::~DB_MySQL(void) {
}

inline void DB_MySQL::checkConnection(void) {
	
	printf("Mysql connection error : %s", mysql_error(&mysql));
}

bool DB_MySQL::isConnection(void) {
	return connection == 0 ? false : true;
}

bool DB_MySQL::connectDB(void) {

	printf("connecting... -> %s:%d\n", DB_HOST, DB_PORT);

	if (!(connection = mysql_real_connect(&mysql, DB_HOST, 
												 DB_USER, DB_PASS, DB_NAME, 
												 DB_PORT, NULL, 0))) {
		printf("connecting Faild\n");
		return false;
	}
	else {
		printf("connecting Success\n");
		return true;
	}
}

void DB_MySQL::disconnectDB() {
	mysql_close(&mysql);
	connection = 0;
}


resultTable DB_MySQL::runQuery(const char *query) {

	resultTable result;

	result.chk = false;
	result.recode.clear();

	unsigned int num_row = 0;
	unsigned int num_col = 0;

	if (!isConnection()) {
		qDebug() << "do Not Connecttion Database";
		return result;
	}

	printf("%s\n", query);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0){
	
		qDebug() << "Mysql query error : " << mysql_error(&mysql);
		return result;
	}

	sql_result = mysql_store_result(connection);

	num_row = mysql_num_rows(sql_result);
	num_col = mysql_num_fields(sql_result);

	while((sql_row = mysql_fetch_row(sql_result)) != NULL){

		QStringList mObj;

		for (int j = 0; j < num_col; ++j) {

			mObj << STR_UTF8(sql_row[j]);
		}
		result.recode << mObj;
	}
	mysql_free_result(sql_result);
	result.chk = true;

	return result;
}