#include <my_global.h>
//#include <mysql.h>
#include </usr/include/mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>


int main(int argc, char **argv)
{  
  
  //Estrutura para arquivo de configuracao
  config_t cfg;
  config_setting_t *setting;
  const char *str;
  
  const char *host, *dbuser, *dbpasswd, *dbname;
  
  //Inicializando a lib de leitura de configuracoes	
  config_init(&cfg);      

  /* Read the file. If there is an error, report it and exit. */
  if(! config_read_file(&cfg, "pam_glpi.conf"))
  {
    fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
            config_error_line(&cfg), config_error_text(&cfg));
    config_destroy(&cfg);
    return(EXIT_FAILURE);
  }
  
  // Recuperando os campos caso o arquivo de configuracao tenha sido aberto com sucesso
   /* Get the store name. */
  if(config_lookup_string(&cfg, "host", &host))
    printf("host: %s\n\n", host);
  else
    fprintf(stderr, "No 'host' setting in configuration file.\n");
  
  if(config_lookup_string(&cfg, "dbuser", &dbuser))
    printf("dbuser: %s\n\n", dbuser);
  else
    fprintf(stderr, "No 'dbuser' setting in configuration file.\n");
    
  if(config_lookup_string(&cfg, "dbpasswd", &dbpasswd))
    printf("dbpasswd: %s\n\n", dbpasswd);
  else
    fprintf(stderr, "No 'dbpasswd' setting in configuration file.\n");
  
  if(config_lookup_string(&cfg, "dbname", &dbname))
    printf("dbname: %s\n\n", dbname);
  else
    fprintf(stderr, "No 'dbname' setting in configuration file.\n");      
  
  
  
  MYSQL *con = mysql_init(NULL);

  char *SQL_QUERY = "select glpi_tickets.id, glpi_tickets.content, glpi_plugin_fields_tickethosts.hostsfield from glpi_tickets inner join glpi_plugin_fields_tickethosts on (glpi_tickets.id = glpi_plugin_fields_tickethosts.items_id);";
 	
  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

//  if (mysql_real_connect(con, "localhost", "root", "root", "glpi", 0, NULL, 0) == NULL)
  if (mysql_real_connect(con, host, dbuser, dbpasswd, dbname, 0, NULL, 0) == NULL)  
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }  

/*
  if (mysql_query(con, "select * from glpi_users")) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }
*/
//if (mysql_query(con, "select * from glpi_users"))
  
  if (mysql_query(con, SQL_QUERY))  
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      //finish_with_error(con);
  }
  
  MYSQL_RES *result = mysql_store_result(con);
  
  if (result == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      //finish_with_error(con);
  }

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;
  
  while ((row = mysql_fetch_row(result))) 
  { 
      int i = 0;
      for(i = 0; i < num_fields; i++) 
      { 
          printf("%s ", row[i] ? row[i] : "NULL"); 
      } 
      printf("\n"); 
  }
  
  mysql_free_result(result);

  mysql_close(con);
  exit(0);
}
