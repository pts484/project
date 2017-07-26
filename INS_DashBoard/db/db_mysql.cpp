#include "db_mysql.h"
#include "define.h"

DB_MySQL::DB_MySQL() {
	
	connection = NULL;
	sql_result = NULL;

	printf("MySQL client Version : %s\n", mysql_get_client_info());
	mysql_init(&mysql);
}

DB_MySQL::~DB_MySQL(void) {
}

inline void DB_MySQL::checkConnection(void) {
	
	printf("Mysql connection error : %s", mysql_error(&mysql));
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
}


resultTable DB_MySQL::runQuery(const char *query) {

	resultTable result = { false, 0, 0 };
	result.recode.clear();

	unsigned int num_fields = 0;

	printf("%s\n", query);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0){
	
		fprintf(stderr, "Mysql query error : %s", mysql_error(&mysql));
		return result;
	}

	sql_result = mysql_store_result(connection);

	num_fields = mysql_num_fields(sql_result);
	result.col = num_fields;

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL){

		++(result.row);

		for (int i = 0; i < num_fields; ++i) {

			result.recode << sql_row[i];
		}
	}
	mysql_free_result(sql_result);
	result.chk = true;

	return result;
}