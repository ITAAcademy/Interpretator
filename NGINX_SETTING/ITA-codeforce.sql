-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Хост: localhost
-- Время создания: Фев 07 2016 г., 18:20
-- Версия сервера: 5.5.47-0ubuntu0.14.04.1
-- Версия PHP: 5.5.9-1ubuntu4.14

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- База данных: `ITA-codeforce`
--

-- --------------------------------------------------------

--
-- Структура таблицы `assignment`
--

CREATE TABLE IF NOT EXISTS `assignment` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `header` text,
  `etalon` text,
  `footer` text,
  `json` text NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=6 ;

--
-- Дамп данных таблицы `assignment`
--

INSERT INTO `assignment` (`ID`, `header`, `etalon`, `footer`, `json`) VALUES
(1, '#include <iostream>\n		#include <cstdlib>\n		#include <algorithm>\n using namespace std;\n		#include <cxxabi.h>\n		#include <cmath>\n		#include <stdio.h>\n		#include <string.h>\n\n float * function_etalon(float  &x,string  &vasya)\n{\n\n  \n  return 0;\n}\n float * function_main(float  &x,string  &vasya)\n{\n', '\n  \n  ', 'return 0;\n}\ntemplate<typename T,int size>\n			bool compareArrs(T arr1[size],T arr2[size])\n				{\n				for (int i=0;i<size;i++)\n				{\n				//if (strcmp(typeid(T).name(), "f") == 0)\n				//{\n					//if (fabs(arr1[i]) - arr2[i] ) > 0.009) \n				//	return false;\n				//}\n 				//else	\n					if (arr1[i] != arr2[i])\n						return false;\n					}\n					return true;\n			}\nint main()\n					{\nfloat  *result = new float [2];\nfloat  result_etalon [2];\nfloat  *result_for_etalon = new float [2];\nfloat  x;\nfloat  x_etalon;\nfloat  x_for_etalon;\nstring  vasya;\nstring  vasya_etalon;\nstring  vasya_for_etalon;\nbool   variablesCorrectByEtalon;\nbool   variablesCorrect;\nx_for_etalon = x = 10.000000;\nvasya_for_etalon = vasya = "safdasdf";\nx_etalon = 10.000000;\nvasya_etalon = "safdasdf";\nresult_for_etalon[0] = 10.000000;\nresult_for_etalon[1] = 10.000000;\nresult = function_main(x,vasya);\nvariablesCorrect = ( (x * 100 ) - (x_etalon * 100 )   == 0 ) && ( vasya == vasya_etalon );\nvariablesCorrectByEtalon = true;\nif ( compareArrs<float ,2 > ( result, result_for_etalon ) && variablesCorrect)\nstd::cout << " @0@";\nelse\nstd::cout << " @0!@";\nx_for_etalon = x = 12.000000;\nvasya_for_etalon = vasya = "safdasdf";\nx_etalon = 12.000000;\nvasya_etalon = "safdasdf";\nresult_for_etalon[0] = 10.000000;\nresult_for_etalon[1] = 10.000000;\nresult = function_main(x,vasya);\nvariablesCorrect = ( (x * 100 ) - (x_etalon * 100 )   == 0 ) && ( vasya == vasya_etalon );\nvariablesCorrectByEtalon = true;\nif ( compareArrs<float ,2 > ( result, result_for_etalon ) && variablesCorrect)\nstd::cout << " @1@";\nelse\nstd::cout << " @1!@";\n\nreturn 0;\n}', '{\n"operation": "addtask",\n  "etalon": "\n  \n  ",\n  "lang": "c++",\n  "task": 1,\n  "function": {\n    "function_name": "function",\n    "type": 1,\n"array_type": 1, \n"unit_test_num": 2,\n"size" : 2,\n\n    "checkable_args_indexes":[1,1],\n    "results": [[10.0,10.0 ],[10.0,10.0 ]],\n    "compare_mark": [2, 2],\n"tests_code":[	"", ""],\n    "args": 	[\n	{\n      "type": 1,\n      "arg_name": "x",\n      "is_array" : 0,\n      "value": [10.0, 12.0],\n       "compare_mark": [2, 3],\n"etalon_value": [10.0, 12.0]\n    	},\n	{\n      "type": 3,\n      "arg_name": "vasya",\n      "value": ["safdasdf", "safdasdf"],\n      "is_array" : 0,\n       "compare_mark": [4, 0],\n"etalon_value": ["safdasdf","safdasdf"]\n    	}\n		]\n  }\n}'),
(2, 'using System;\n				using System.Collections.Generic;\n				using System.Collections;\n\npublic class MainClass {\nstatic  float  [] function_etalon(ref float  x,ref string  vasya)\n{\n\n    \n  return default(float  [] );\n}\nstatic  float  [] function_main(ref float  x,ref string  vasya)\n{\n', '\n    \n  ', 'return default(float  [] );\n}\nstatic bool ArraysEqual<T>(T[] a1, T[] a2)\n		{\n		    if (a1 == a2)\n		        return true;\n		    if (a1 == null || a2 == null)\n		        return false;\n		    if (a1.Length != a2.Length)\n		        return false;\n			EqualityComparer<T> comparer = EqualityComparer<T>.Default;\n		    for (int i = 0; i < a1.Length; i++)\n		        if (!comparer.Equals(a1[i], a2[i]))\n		            return false;\n		    return true;\n}\npublic static void Main(String[] args)\n		{\nfloat  [] result;\nfloat  [] result_etalon = new float  [2];\nfloat  [] result_for_etalon = new float  [2];\nfloat  x;\nfloat  x_etalon;\nfloat  x_for_etalon;\nstring  vasya;\nstring  vasya_etalon;\nstring  vasya_for_etalon;\nbool   variablesCorrectByEtalon;\nbool   variablesCorrect;\nresult_etalon[0] =  (float ) 10.000000;\nresult_etalon[1] =  (float ) 10.000000;\nx_for_etalon = x = (float)10.000000;\nvasya_for_etalon = vasya = "safdasdf";\nx_etalon = (float)10.000000;\nvasya_etalon = "safdasdf";\nresult_for_etalon[0] =  (float ) 10.000000;\nresult_for_etalon[1] =  (float ) 10.000000;\nresult = function_main(ref x,ref vasya);\nvariablesCorrect = ( (x * 100 ) - (x_etalon * 100 )   == 0 ) && ( String.Equals (vasya, vasya_etalon));\nvariablesCorrectByEtalon = true;\nif (ArraysEqual(result, result_for_etalon) && variablesCorrect)\nSystem.Console.WriteLine(" @0@");\nelse\nSystem.Console.WriteLine(" @0!@");\nresult_etalon[0] =  (float ) 10.000000;\nresult_etalon[1] =  (float ) 10.000000;\nx_for_etalon = x = (float)12.000000;\nvasya_for_etalon = vasya = "safdasdf";\nx_etalon = (float)12.000000;\nvasya_etalon = "safdasdf";\nresult_for_etalon[0] =  (float ) 10.000000;\nresult_for_etalon[1] =  (float ) 10.000000;\nresult = function_main(ref x,ref vasya);\nvariablesCorrect = ( (x * 100 ) - (x_etalon * 100 )   == 0 ) && ( String.Equals (vasya, vasya_etalon));\nvariablesCorrectByEtalon = true;\nif (ArraysEqual(result, result_for_etalon) && variablesCorrect)\nSystem.Console.WriteLine(" @1@");\nelse\nSystem.Console.WriteLine(" @1!@");\n}}', '{\n"operation": "addtask",\n  "etalon": "\n    \n  ",\n  "lang": "c#",\n  "task": 2,\n  "function": {\n    "function_name": "function",\n    "type": 1,\n"array_type": 1, \n"unit_test_num": 2,\n"size" : 2,\n\n    "checkable_args_indexes":[1,1],\n    "results": [[10.0,10.0 ],[10.0,10.0 ]],\n    "compare_mark": [2, 2],\n"tests_code":[	"", ""],\n    "args": 	[\n	{\n      "type": 1,\n      "arg_name": "x",\n      "is_array" : 0,\n      "value": [10.0, 12.0],\n       "compare_mark": [2, 3],\n"etalon_value": [10.0, 12.0]\n    	},\n	{\n      "type": 3,\n      "arg_name": "vasya",\n      "value": ["safdasdf", "safdasdf"],\n      "is_array" : 0,\n       "compare_mark": [4, 0],\n"etalon_value": ["safdasdf","safdasdf"]\n    	}\n		]\n  }\n}'),
(3, 'import java.util.Arrays;\n\npublic class Main{{thId}}{\nstatic  float []function_etalon(float  x,String  vasya)\n{\n\n    \n  return null;\n}\nstatic  float []function_main(float  x,String  vasya)\n{\n', '\n    \n  ', '\n}\npublic static void main(String[] args)\n{\nfloat  [] result;\nfloat  [] result_etalon = new float  [2];\nfloat  [] result_for_etalon = new float  [2];\nfloat  x;\nfloat  x_etalon;\nfloat  x_for_etalon;\nString  vasya;\nString  vasya_etalon;\nString  vasya_for_etalon;\nboolean   variablesCorrectByEtalon;\nboolean   variablesCorrect;\nresult_etalon[0] =  (float ) 10.000000;\nresult_etalon[1] =  (float ) 10.000000;\nx_for_etalon = x = (float)10.000000;\nvasya_for_etalon = vasya = "safdasdf";\nx_etalon = (float)10.000000;\nvasya_etalon = "safdasdf";\nresult_for_etalon[0] =  (float ) 10.000000;\nresult_for_etalon[1] =  (float ) 10.000000;\nresult = function_main(x,vasya);\nvariablesCorrect = ( (x * 100 ) - (x_etalon * 100 )   == 0 ) && ( new String(vasya).equals(vasya_etalon));\nvariablesCorrectByEtalon = true;\nif (Arrays.equals(result, result_for_etalon) && variablesCorrect)\nSystem.out.println(" @0@");\nelse\nSystem.out.println(" @0!@");\nresult_etalon[0] =  (float ) 10.000000;\nresult_etalon[1] =  (float ) 10.000000;\nx_for_etalon = x = (float)12.000000;\nvasya_for_etalon = vasya = "safdasdf";\nx_etalon = (float)12.000000;\nvasya_etalon = "safdasdf";\nresult_for_etalon[0] =  (float ) 10.000000;\nresult_for_etalon[1] =  (float ) 10.000000;\nresult = function_main(x,vasya);\nvariablesCorrect = ( (x * 100 ) - (x_etalon * 100 )   == 0 ) && ( new String(vasya).equals(vasya_etalon));\nvariablesCorrectByEtalon = true;\nif (Arrays.equals(result, result_for_etalon) && variablesCorrect)\nSystem.out.println(" @1@");\nelse\nSystem.out.println(" @1!@");\n}}', '{\n"operation": "addtask",\n  "etalon": "\n    \n  ",\n  "lang": "java",\n  "task": 3,\n  "function": {\n    "function_name": "function",\n    "type": 1,\n"array_type": 1, \n"unit_test_num": 2,\n"size" : 2,\n\n    "checkable_args_indexes":[1,1],\n    "results": [[10.0,10.0 ],[10.0,10.0 ]],\n    "compare_mark": [2, 2],\n"tests_code":[	"", ""],\n    "args": 	[\n	{\n      "type": 1,\n      "arg_name": "x",\n      "is_array" : 0,\n      "value": [10.0, 12.0],\n       "compare_mark": [2, 3],\n"etalon_value": [10.0, 12.0]\n    	},\n	{\n      "type": 3,\n      "arg_name": "vasya",\n      "value": ["safdasdf", "safdasdf"],\n      "is_array" : 0,\n       "compare_mark": [4, 0],\n"etalon_value": ["safdasdf","safdasdf"]\n    	}\n		]\n  }\n}'),
(4, '\n\n<?php \nfunction   function_etalon($x,$vasya)\n{\n\n    \n  return 0;\n}\nfunction   function_main($x,$vasya)\n{\n', '\n    \n  ', 'return 0;\n}\n  $result;\n  $result_etalon;\n  $result_for_etalon;\n  $x;\n  $x_etalon;\n  $x_for_etalon;\n  $vasya;\n  $vasya_etalon;\n  $vasya_for_etalon;\n   $variablesCorrectByEtalon;\n   $variablesCorrect;\n$result_etalon[0] = 10.000000;\n$result_etalon[1] = 10.000000;\n$x_for_etalon = $x = 10.000000;\n$vasya_for_etalon = $vasya = "safdasdf";\n$x_etalon = 10.000000;\n$vasya_etalon = "safdasdf";\n$result_for_etalon[0] = 10.000000;\n$result_for_etalon[1] = 10.000000;\n$result = function_main($x,$vasya);\n$variablesCorrect = ( ($x * 100 ) - ($x_etalon * 100 )   == 0 ) && ( $vasya == $vasya_etalon );\n$variablesCorrectByEtalon = true;\nif ( $result === $result_for_etalon  && $variablesCorrect)\necho " @0@";\nelse\necho " @0!@";\n$result_etalon[0] = 10.000000;\n$result_etalon[1] = 10.000000;\n$x_for_etalon = $x = 12.000000;\n$vasya_for_etalon = $vasya = "safdasdf";\n$x_etalon = 12.000000;\n$vasya_etalon = "safdasdf";\n$result_for_etalon[0] = 10.000000;\n$result_for_etalon[1] = 10.000000;\n$result = function_main($x,$vasya);\n$variablesCorrect = ( ($x * 100 ) - ($x_etalon * 100 )   == 0 ) && ( $vasya == $vasya_etalon );\n$variablesCorrectByEtalon = true;\nif ( $result === $result_for_etalon  && $variablesCorrect)\necho " @1@";\nelse\necho " @1!@";\n?>\n', '{\n"operation": "addtask",\n  "etalon": "\n    \n  ",\n  "lang": "php",\n  "task": 4,\n  "function": {\n    "function_name": "function",\n    "type": 1,\n"array_type": 1, \n"unit_test_num": 2,\n"size" : 2,\n\n    "checkable_args_indexes":[1,1],\n    "results": [[10.0,10.0 ],[10.0,10.0 ]],\n    "compare_mark": [2, 2],\n"tests_code":[	"", ""],\n    "args": 	[\n	{\n      "type": 1,\n      "arg_name": "x",\n      "is_array" : 0,\n      "value": [10.0, 12.0],\n       "compare_mark": [2, 3],\n"etalon_value": [10.0, 12.0]\n    	},\n	{\n      "type": 3,\n      "arg_name": "vasya",\n      "value": ["safdasdf", "safdasdf"],\n      "is_array" : 0,\n       "compare_mark": [4, 0],\n"etalon_value": ["safdasdf","safdasdf"]\n    	}\n		]\n  }\n}'),
(5, '\n\nfunction  function_etalon(x,vasya)\n{\n\n      \n  return 0;\n}\nfunction  function_main(x,vasya)\n{\n', '\n      \n  ', 'return 0;\n}\nvar result=[];\nvar result_etalon=[];\nvar result_for_etalon=[];\nvar x;\nvar x_etalon;\nvar x_for_etalon;\nvar vasya;\nvar vasya_etalon;\nvar vasya_for_etalon;\nvar  variablesCorrectByEtalon;\nvar  variablesCorrect;\nresult_etalon[0] = 10.000000;\nresult_etalon[1] = 10.000000;\nx_for_etalon = x = 10.000000;\nvasya_for_etalon = vasya = "safdasdf";\nx_etalon = 10.000000;\nvasya_etalon = "safdasdf";\nresult_for_etalon[0] = 10.000000;\nresult_for_etalon[1] = 10.000000;\nresult = function_main(x,vasya);\nvariablesCorrect = ( (x * 100 ) - (x_etalon * 100 )   == 0 ) && ( vasya == vasya_etalon );\nvariablesCorrectByEtalon = true;\nif (result.toString()==result_for_etalon.toString() && variablesCorrect)\nconsole.log(" @0@");\nelse\nconsole.log(" @0!@");\nresult_etalon[0] = 10.000000;\nresult_etalon[1] = 10.000000;\nx_for_etalon = x = 12.000000;\nvasya_for_etalon = vasya = "safdasdf";\nx_etalon = 12.000000;\nvasya_etalon = "safdasdf";\nresult_for_etalon[0] = 10.000000;\nresult_for_etalon[1] = 10.000000;\nresult = function_main(x,vasya);\nvariablesCorrect = ( (x * 100 ) - (x_etalon * 100 )   == 0 ) && ( vasya == vasya_etalon );\nvariablesCorrectByEtalon = true;\nif (result.toString()==result_for_etalon.toString() && variablesCorrect)\nconsole.log(" @1@");\nelse\nconsole.log(" @1!@");\n', '{\n"operation": "addtask",\n  "etalon": "\n      \n  ",\n  "lang": "js",\n  "task": 5,\n  "function": {\n    "function_name": "function",\n    "type": 1,\n"array_type": 1, \n"unit_test_num": 2,\n"size" : 2,\n\n    "checkable_args_indexes":[1,1],\n    "results": [[10.0,10.0 ],[10.0,10.0 ]],\n    "compare_mark": [2, 2],\n"tests_code":[	"", ""],\n    "args": 	[\n	{\n      "type": 1,\n      "arg_name": "x",\n      "is_array" : 0,\n      "value": [10.0, 12.0],\n       "compare_mark": [2, 3],\n"etalon_value": [10.0, 12.0]\n    	},\n	{\n      "type": 3,\n      "arg_name": "vasya",\n      "value": ["safdasdf", "safdasdf"],\n      "is_array" : 0,\n       "compare_mark": [4, 0],\n"etalon_value": ["safdasdf","safdasdf"]\n    	}\n		]\n  }\n}');

-- --------------------------------------------------------

--
-- Структура таблицы `history`
--

CREATE TABLE IF NOT EXISTS `history` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `ip` varchar(20) DEFAULT NULL,
  `code` varchar(512) DEFAULT NULL,
  `date_time` datetime DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=98 ;

-- --------------------------------------------------------

--
-- Структура таблицы `results`
--

CREATE TABLE IF NOT EXISTS `results` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `session` varchar(255) CHARACTER SET ascii NOT NULL,
  `jobid` varchar(255) NOT NULL,
  `status` text NOT NULL,
  `date` date NOT NULL,
  `result` text NOT NULL,
  `warning` text NOT NULL,
  PRIMARY KEY (`id`,`session`(100)),
  UNIQUE KEY `SECONDY` (`session`,`jobid`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=83 ;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
