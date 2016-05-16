# Interpretator
Just interpret it

# MANUAL :)
В gcc 4.8 не можна ініацілізувати regex (використовуємо для range в масивах) - прога крешниться, тому треба поставити
gcc 4.9 - в ньоиу цей баг пофіксили. для цього вводимо наступні команди: 
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install g++-4.9
sudo apt-get install gcc-4.8 g++-4.8
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.8
Остання робить 4.9 дефолтним компілятором. якщо не зробить, то вводимо
sudo update-alternatives --config gcc
і вибираєм версію 4.9


Щоб компілить С#, треба поставити с#-mono:
sudo apt-get install mono-mcs mono-xsp2 mono-xsp2-base

gmcs file_name.cs // compilation
mono file_name.exe //run compiled program



1.	запускаєм термінал
2.	наступною командою ставимо необхідні для роботи сервера бібліотеки
3.	sudo apt-get fcgi pthread jsoncpp lmysqlcppconn lmysql-server clang openjdk-7-jdk libmysql++-dev node.js mono-mcs
4.	заходимо в директорію з ісходніками і мейкфайлом:  cd /dir..
5.	запускаєм компіляцію:	 make -f Makefile
6.	як зібралося, має з*явитися файл test.fcgi
7.	відкрити папку /etc/init.d/ 
8.	скопіювати любий із скритів, задавши ім*я interpreter
9.	скопіювати весь код з Interpretator/init.d/interpreter.sh в скопійований скріпт.
10.	в стрічці  DAEMON_DIR= вказати директорію, де буде знаходитись виконуваний файл сервака і його  файлики
11.	скопіювати файл Interpretator/NGINX_SETTING/default.txt в  /etc/nginx/sites-available/  (замінити)
12.	створити папку, де буде лежати сервер, туди закинути скомпільований test.fcgi
13.	файл  test.fcgi зробити виконуваним
14.	імпортуйте базу  Interpretator/NGINX_SETTING/ITA-codeforce.sql
15.	sudo service interpreter start
16.	відкрийте /server_location/settings.conf   вкажіть юзера, пароль, ім*я бази і т.п, збережіть.
17.	sudo service interpreter restart
18.	всьо, має робити.

JSON sample:
{
"operation": "result",
"session" : "1241q223f4f2341",
"jobid" : 11212,
"code" : "std::cout << \"Hello World!\" << std::endl;",
"task": 1,
"lang": "c++"
}

ii.intita.com

{
"operation": "getFromToken",
"token": "-4032268986048976767",
"session" : "1054003",
"jobid" : 54554,
"code" : "<html>
 <head>
  <title>Тестируем PHP</title>
 </head>
 <body>
 <?php echo '<p>Привет, мир!</p>'; ?>
 </body>
</html>",
"etalon" : " j",
"header" : " j",
"footer" : " j",
"name" : "12143",
"task": 545,
"lang": "c++"
}


{
"operation": "addtask",
  "etalon": "hff",
  "name": "test example",
  "lang": "c++",
  "task": 310
  "function": {
    "function_name": "function",
    "is_array": false,
    "size": 1,
    "type": 0,
    "results": ["10", "12"],
    "args": 	[
	{
      "is_array": true,
      "size": 1,
      "type": 0,
      "arg_name": "x",
      "value": [["1,2"], ["3","4"]]
    	},
	{
      "is_array": false,
      "size": 1,
      "type": 0,
      "arg_name": "vasya",
      "value": ["1", "5"]
    	}
		]
  }
}

{
"operation": "addtask",
  "etalon": "hff",
  "name": "test example",
  "lang": "c++",
  "task": 221,
  "function": {
    "function_name": "function",
    "is_array": false,
    "size": 1,
    "type": 0,
    "results": [10, 12],
    "args": 	[
	{
      "is_array": false,
      "size": 1,
      "type": 0,
      "arg_name": "x",
      "value": [2, 3]
    	},
	{
      "is_array": false,
      "size": 1,
      "type": 3,
      "arg_name": "vasya",
      "value": ["20", "5"]
    	}
		]
  }
}

{
"operation": "start",
"token": "-8668338574358268261",
"session" : "1054003",
"jobid" : 54554,
"code" : "
",
"task": 222,
"lang": "c++"
}

{
"operation": "result",
"token": "-8668338574358268261",
"session" : "1054003",
"jobid" : 54554,
"code" : "
",
"etalon" : " j",
"header" : " j",
"footer" : " j",
"name" : "12143",
"task": 222,
"lang": "c++"
}

{
"operation": "addtask",
  "etalon": "hff",
  "name": "test example",
  "lang": "c++",
  "task": 269,
  "function": {
    "function_name": "function",
    "type": 1,
    "results": [10.0, 12.0],
    "args": 	[
	{
      "type": 0,
      "arg_name": "x",
      "value": [2, 3]
    	},
	{
      "type": 3,
      "arg_name": "vasya",
      "value": ["20", "5"]
    	}
		]
  }
}

{
"operation": "addtask",
  "etalon": "hff",
  "name": "test example",
  "lang": "c++",
  "task": 279,
  "function": {
    "function_name": "function",
    "type": 1,
    "results": [[10.0, 12.0]],
    "args": 	[
	{
      "type": 1,
      "arg_name": "x",
      "value": [[10.0, 12.0]]
    	},
	{
      "type": 3,
      "arg_name": "vasya",
      "value": [["20", "5"]]
    	}
		]
  }
}

{
"operation": "addtask",
  "etalon": "",
  "name": "test example",
  "lang": "c++",
  "task": 80,
  "function": {
    "function_name": "function",
    "type": 1,
    "checkable_args_indexes":[0,1],
    "results": [10.0,11.0 ],
    "compare_mark": [0, 1],
"tests_code":[	"isTrue = true;", "isTrue = true;"],
    "args": 	[
	{
      "type": 1,
      "arg_name": "x",
      "value": [10.0, 12.0],
       "compare_mark": [2, 3],
"etalon_value": [10.0, 12.0]
    	},
	{
      "type": 3,
      "arg_name": "vasya",
      "value": ["safdasdf", "safdasdf"],
       "compare_mark": [4, 0],
"etalon_value": ["safdasdf","safdasdf"]
    	}
		]
  }
}








{
  "operation": "addtask",
  "etalon": "return 3;",
  "lang": "php",
  "task": "110",
  "function": {
    "function_name": "php_110",
    "type": 0,
    "array_type": 0,
    "size": null,
    "unit_test_num": 1,
    "checkable_args_indexes": [
      [
        {
          "first": 0,
          "second": 0
        }
      ]
    ],
    "results": [
      "3"
    ],
    "compare_mark": [
      2
    ],
    "tests_code": [
      ""
    ],
    "args": [
      {
        "type": 0,
        "size": null,
        "arg_name": "x",
        "pattern": {},
        "value": [
          "3"
        ],
        "is_array": 0,
        "etalon_value": [
          ""
        ],
        "compare_mark": [
          2
        ]
      }
    ]
  },
  "name": "php"
}


{
"operation": "copyTask",
    	"task" : "2", 
        "new_task" : "14" 
        }
