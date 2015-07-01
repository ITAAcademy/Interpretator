/*
 * SqlConnectionPool.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: yurock
 */

#include "inc/SQLConnectionPool.h"
/*
 MyConnectionPool::MyConnectionPool( const char *db, const char *server,
                    const char *user, const char *password )
  {
    p_db = (db ? db : "" );
    p_server = (server ? server : "" );
    p_user = (user ? user : "" );
    p_password = (password ? password : "" );
  }

 MyConnectionPool::~MyConnectionPool()
  {
    clear();
  }

 mysqlpp::Connection*  MyConnectionPool::create()
 {
logfile::addLog("Creating pool connection")
   return new mysqlpp::Connection(
    p_db.empty() ? 0 : p_db.c_str(), p_server.empty() ? 0 : p_server.c_str(),
    p_user.empty() ? 0 : p_user.c_str(),
    p_password.empty() ? 0 : p_password.c_str() );
 }

 void MyConnectionPool::destroy( mysqlpp::Connection *con )
  {
	 logfile::addLog("Deleting pool connection")
    delete con;
  }

 unsigned int MyConnectionPool::max_idle_time()
   {
     // В данном примере достаточно 3 секунд
     // В реальном приложении время ожидания следует вычислять в соответствии
     // с условиями выполнения (таймаут сервера, кол-во соединений и т.д.)
     return 3;
   }
 static void* MyConnectionPool::work_thread( void *running_flag )
 {
   mysqlpp::Connection::thread_start();
   for( int i=0; i < 6; i++ )
   {
     mysqlpp::Connection *con = pool->grab();
     if( !con )
     {
       cerr << "Ошибка при получении соединения из пула" << endl;
       break;
     }
     // Запрос на получение содержимого таблицы wares.
     // Для краткости каждая полученная строка обозначена звёздочкой
     mysqlpp::Query query( con->query( "SELECT * FROM wares" ) );
     mysqlpp::StoreQueryResult res = query.store();
     for( int j=0; j < res.num_rows(); j++ )
       cout.put('*');

     // Запрос выполнен - немедленно освобождаем соединение
     pool->release( cp );
     // Задержка от 1 до 4 секунд прежде чем данное соединение можно будет
     // использовать повторно. В тех случаях, когда время задержки превышает
     // макс. время ожидания, создаётся новое соединение в след.итерации цикла
     sleep( rand()%4 + 1 );
   }
   // Оповещение основной программы о том, что данный поток больше не используется
   *reinterpret_cast<bool*>(running_flag) = false;
   mysqlpp::Connection::thread_end();
   return 0;
 }

 static int MyConnectionPool::create_thread( (void *)(*worker)(void *), (void *)arg )
 {
   pthread_t ptrd;
   return pthread_create( &ptrd, 0, worker, arg );
 }


int mainaa( int argc, char *argv[] )
{
#if defined(WITH_THREADS)
  pool = new MyConnectionPool( "test_db", "localhost", "tdb_user", "tdb_password" );
  try
  {
	  MyConnectionPool::Connection *con = pool->grab();
    if( !con->thread_aware() )
    {
      cerr << "MySQL++ собрана без поддержки потоков" << endl;
      return -1;
    }
    pool->release( cp );
  }
  catch( mysqlpp::Exception &ex )
  {
    cerr << "Ошибка при инициализации пула соединений: " << ex.what() << endl;
    return -1;
  }
  cout << "Пул соединений успешно создан. Начинаем работу с потоками..." << endl;
  srand( time(0) );

  bool running[] = { true, true, true, true, true, true, true, true, true, true };
  const size_t num_threads = sizeof(running) / sizeof(running[0]);

  for( size_t i=0; i < num_threads; i++ )
  {
    if( int err = create_thread( work_thread, (running+i) ) )
    {
      cerr << "Ошибка при создании потока с номером " << i <<
              ": код ошибки " << err << endl;
      return -1;
    }
  }

  // Проверка флагов активности потоков каждую секунду до тех пор,
  // пока выполнение всех потоков не будет завершено
  cout << "Ожидание завершения потоков..." << endl;
  cout.flush();
  do
  {
    sleep(1);
    i = 0;
    while( i < num_threads && !running[i] )
      i++;
  } while( i < num_threads );
  cout << endl << "Все потоки остановлены" << endl;
  delete pool;
  cout << "Завершение работы программы" << endl;
#else
  cout << "Программе " << argv[0] << " необходима поддержка многопоточности" << endl;
#endif
  return 0;
}*/
