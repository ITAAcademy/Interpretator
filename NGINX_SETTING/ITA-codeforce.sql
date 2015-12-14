-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Хост: localhost
-- Время создания: Дек 14 2015 г., 16:29
-- Версия сервера: 5.5.46-0ubuntu0.14.04.2
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
-- Структура таблицы `assignment_cpp`
--

CREATE TABLE IF NOT EXISTS `assignment_cpp` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `header` text,
  `etalon` text,
  `footer` text,
  `json` text NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=551 ;

-- --------------------------------------------------------

--
-- Структура таблицы `assignment_cs`
--

CREATE TABLE IF NOT EXISTS `assignment_cs` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `header` text,
  `etalon` text,
  `footer` text,
  `json` text NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Структура таблицы `assignment_java`
--

CREATE TABLE IF NOT EXISTS `assignment_java` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `header` text,
  `etalon` text,
  `footer` text,
  `json` text NOT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `ID` (`ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=56 ;

-- --------------------------------------------------------

--
-- Структура таблицы `assignment_js`
--

CREATE TABLE IF NOT EXISTS `assignment_js` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `header` varchar(512) CHARACTER SET latin1 DEFAULT NULL,
  `etalon` varchar(512) CHARACTER SET latin1 DEFAULT NULL,
  `footer` varchar(512) CHARACTER SET latin1 DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=ascii;

-- --------------------------------------------------------

--
-- Структура таблицы `assignment_php`
--

CREATE TABLE IF NOT EXISTS `assignment_php` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `header` text,
  `etalon` text,
  `footer` text,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=549 ;

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
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=499 ;

-- --------------------------------------------------------

--
-- Структура таблицы `results`
--

CREATE TABLE IF NOT EXISTS `results` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `session` varchar(255) CHARACTER SET ascii NOT NULL,
  `jobid` int(11) NOT NULL,
  `status` text NOT NULL,
  `date` date NOT NULL,
  `result` text NOT NULL,
  `warning` text NOT NULL,
  PRIMARY KEY (`id`,`session`(100)),
  UNIQUE KEY `SECONDY` (`session`,`jobid`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=16 ;

--
-- Дамп данных таблицы `results`
--

INSERT INTO `results` (`id`, `session`, `jobid`, `status`, `date`, `result`, `warning`) VALUES
(1, '127.0.0.1', 0, '2015-12-9 14:23:2', '0000-00-00', '', ''),
(2, '21', 11114, 'done', '2015-12-09', 'Segmentation fault\n', './src/code2.cpp:37:34: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                 ^\n./src/code2.cpp:37:45: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                            ^\n./src/code2.cpp:41:32: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                               ^\n./src/code2.cpp:41:43: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                                          ^\n4 warnings generated.\n'),
(3, '210', 11114, 'done', '2015-12-09', 'Segmentation fault\n', './src/code0.cpp:37:34: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                 ^\n./src/code0.cpp:37:45: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                            ^\n./src/code0.cpp:41:32: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                               ^\n./src/code0.cpp:41:43: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                                          ^\n4 warnings generated.\n'),
(4, '21g0', 11114, 'done', '2015-12-09', 'Segmentation fault\n', './src/code2.cpp:37:34: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                 ^\n./src/code2.cpp:37:45: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                            ^\n./src/code2.cpp:41:32: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                               ^\n./src/code2.cpp:41:43: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                                          ^\n4 warnings generated.\n'),
(5, '21g00', 11114, 'done', '2015-12-09', ' @0@ @1@', './src/code1.cpp:37:34: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                 ^\n./src/code1.cpp:37:45: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                            ^\n./src/code1.cpp:41:32: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                               ^\n./src/code1.cpp:41:43: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                                          ^\n4 warnings generated.\n'),
(6, '21qg00', 11114, 'done', '2015-12-09', ' @0@ @1!@', './src/code0.cpp:37:34: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                 ^\n./src/code0.cpp:37:45: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                            ^\n./src/code0.cpp:41:32: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                               ^\n./src/code0.cpp:41:43: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                                          ^\n4 warnings generated.\n'),
(7, '21q0g00', 11114, 'failed', '2015-12-09', '', 'Main3.java:1: error: illegal character: 35\n#include <iostream>\n^\nMain3.java:1: error: class, interface, or enum expected\n#include <iostream>\n         ^\nMain3.java:2: error: illegal character: 35\n		#include <cstdlib>\n		^\nMain3.java:3: error: illegal character: 35\n		#include <algorithm>\n		^\nMain3.java:5: error: illegal character: 35\n		#include <cxxabi.h>\n		^\nMain3.java:5: error: class, interface, or enum expected\n		#include <cxxabi.h>\n		         ^\nMain3.java:6: error: illegal character: 35\n		#include <cmath>\n		^\nMain3.java:7: error: illegal character: 35\n		#include <stdio.h>\n		^\nMain3.java:8: error: illegal character: 35\n		#include <string.h>\n		^\nMain3.java:13: error: class, interface, or enum expected\n}\n^\nMain3.java:19: error: class, interface, or enum expected\nss[0] = "adin";\n^\nMain3.java:20: error: class, interface, or enum expected\nss[1] = "two";\n^\nMain3.java:21: error: class, interface, or enum expected\nreturn ss;\n^\nMain3.java:24: error: class, interface, or enum expected\nreturn 0;\n^\nMain3.java:25: error: class, interface, or enum expected\n}\n^\nMain3.java:29: error: class, interface, or enum expected\n		for (int i=0;i<size;i++)\n		             ^\nMain3.java:29: error: class, interface, or enum expected\n		for (int i=0;i<size;i++)\n		                    ^\nMain3.java:39: error: class, interface, or enum expected\n			}\n			^\nMain3.java:41: error: class, interface, or enum expected\n	}\n	^\nMain3.java:45: error: class, interface, or enum expected\nstring * result;\n^\nMain3.java:46: error: class, interface, or enum expected\nstring * result_for_etalon;\n^\nMain3.java:47: error: class, interface, or enum expected\nfloat  x;\n^\nMain3.java:48: error: class, interface, or enum expected\nfloat  x_etalon;\n^\nMain3.java:49: error: class, interface, or enum expected\nfloat  x_for_etalon;\n^\nMain3.java:50: error: class, interface, or enum expected\nstring  vasya;\n^\nMain3.java:51: error: class, interface, or enum expected\nstring  vasya_etalon;\n^\nMain3.java:52: error: class, interface, or enum expected\nstring  vasya_for_etalon;\n^\nMain3.java:53: error: class, interface, or enum expected\nbool isTrue;\n^\nMain3.java:54: error: class, interface, or enum expected\nbool variablesCorrectByEtalon,variablesCorrect;\n^\nMain3.java:55: error: class, interface, or enum expected\nresult_etalon[0] = "adin"\n^\nMain3.java:57: error: class, interface, or enum expected\nresult_etalon[1] = "two"\n^\nMain3.java:59: error: class, interface, or enum expected\nx_for_etalon = x = 10.0\n^\nMain3.java:61: error: class, interface, or enum expected\nvasya_for_etalon = vasya = "safdasdf"\n^\nMain3.java:63: error: class, interface, or enum expected\nx_etalon = 10.0\n^\nMain3.java:65: error: class, interface, or enum expected\nvasya_etalon = "safdasdf"\n^\nMain3.java:67: error: class, interface, or enum expected\nvariablesCorrect = (  ( floor(x * 100 ) - floor(x_etalon * 100 ) )  == 0 ) && ( vasya == vasya_etalon );\n^\nMain3.java:68: error: class, interface, or enum expected\n result_for_etalon = function_etalon(x_for_etalon,vasya_for_etalon);\n ^\nMain3.java:69: error: class, interface, or enum expected\n result = function_main(x,vasya);\n ^\nMain3.java:70: error: class, interface, or enum expected\nisTrue = true;\n^\nMain3.java:71: error: class, interface, or enum expected\nvariablesCorrectByEtalon = (  ( floor(x * 100 ) - floor(x_for_etalon * 100 ) )  == 0 ) && ( vasya == vasya_for_etalon );isTrue = true;\n^\nMain3.java:71: error: class, interface, or enum expected\nvariablesCorrectByEtalon = (  ( floor(x * 100 ) - floor(x_for_etalon * 100 ) )  == 0 ) && ( vasya == vasya_for_etalon );isTrue = true;\n                                                                                                                        ^\nMain3.java:72: error: class, interface, or enum expected\nif ( compareArrs<string,2 > ( result_etalon, result ) && variablesCorrect && isTrue)\n^\nMain3.java:74: error: class, interface, or enum expected\nelse\n^\nMain3.java:76: error: class, interface, or enum expected\nresult_etalon[0] = "adin"\n^\nMain3.java:78: error: class, interface, or enum expected\nresult_etalon[1] = "twoa"\n^\nMain3.java:80: error: class, interface, or enum expected\nx_for_etalon = x = 12.0\n^\nMain3.java:82: error: class, interface, or enum expected\nvasya_for_etalon = vasya = "safdasdf"\n^\nMain3.java:84: error: class, interface, or enum expected\nx_etalon = 12.0\n^\nMain3.java:86: error: class, interface, or enum expected\nvasya_etalon = "safdasdf"\n^\nMain3.java:88: error: class, interface, or enum expected\nvariablesCorrect = (  ( floor(x * 100 ) - floor(x_etalon * 100 ) )  == 0 ) && ( vasya == vasya_etalon );\n^\nMain3.java:89: error: class, interface, or enum expected\n result_for_etalon = function_etalon(x_for_etalon,vasya_for_etalon);\n ^\nMain3.java:90: error: class, interface, or enum expected\n result = function_main(x,vasya);\n ^\nMain3.java:91: error: class, interface, or enum expected\nisTrue = true;\n^\nMain3.java:92: error: class, interface, or enum expected\nvariablesCorrectByEtalon = (  ( floor(x * 100 ) - floor(x_for_etalon * 100 ) )  == 0 ) && ( vasya == vasya_for_etalon );isTrue = true;\n^\nMain3.java:92: error: class, interface, or enum expected\nvariablesCorrectByEtalon = (  ( floor(x * 100 ) - floor(x_for_etalon * 100 ) )  == 0 ) && ( vasya == vasya_for_etalon );isTrue = true;\n                                                                                                                        ^\nMain3.java:93: error: class, interface, or enum expected\nif ( compareArrs<string,2 > ( result_etalon, result ) && variablesCorrect && isTrue)\n^\nMain3.java:95: error: class, interface, or enum expected\nelse\n^\nMain3.java:98: error: class, interface, or enum expected\nreturn 0;\n^\nMain3.java:99: error: class, interface, or enum expected\n}\n^\n59 errors\n'),
(8, '1241q223f4f2341', 11212, 'done', '2015-12-09', 'Hello World!\nSegmentation fault\n', './src/code3.cpp:37:34: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                 ^\n./src/code3.cpp:37:45: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                            ^\n./src/code3.cpp:41:32: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                               ^\n./src/code3.cpp:41:43: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                                          ^\n4 warnings generated.\n'),
(9, '221', 11114, 'done', '2015-12-09', 'Segmentation fault\n', './src/code2.cpp:37:34: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                 ^\n./src/code2.cpp:37:45: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                            ^\n./src/code2.cpp:41:32: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                               ^\n./src/code2.cpp:41:43: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                                          ^\n4 warnings generated.\n'),
(10, '2211', 11114, 'done', '2015-12-09', ' @0!@ @1@', './src/code1.cpp:37:34: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                 ^\n./src/code1.cpp:37:45: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                            ^\n./src/code1.cpp:41:32: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                               ^\n./src/code1.cpp:41:43: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                                          ^\n4 warnings generated.\n'),
(11, '22111', 11114, 'done', '2015-12-09', ' @0@ @1@', './src/code0.cpp:37:34: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                 ^\n./src/code0.cpp:37:45: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                            ^\n./src/code0.cpp:41:32: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                               ^\n./src/code0.cpp:41:43: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                                          ^\n4 warnings generated.\n'),
(12, '245', 11114, 'failed', '2015-12-10', '', './src/code1.cpp:37:36: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_etalon(float *  &x,string *  &vasya)\n                                   ^\n./src/code1.cpp:37:49: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_etalon(float *  &x,string *  &vasya)\n                                                ^\n./src/code1.cpp:41:34: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_main(float *  &x,string *  &vasya)\n                                 ^\n./src/code1.cpp:41:47: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_main(float *  &x,string *  &vasya)\n                                              ^\n./src/code1.cpp:94:22: error: no matching function for call to ''function_etalon''\n result_for_etalon = function_etalon(x_for_etalon,vasya_for_etalon);\n                     ^~~~~~~~~~~~~~~\n./src/code1.cpp:37:10: note: candidate function not viable: no known conversion from ''float'' to ''float *&'' for 1st argument\nstring * function_etalon(float *  &x,string *  &vasya)\n         ^\n./src/code1.cpp:95:11: error: no matching function for call to ''function_main''\n result = function_main(x,vasya);\n          ^~~~~~~~~~~~~\n./src/code1.cpp:41:10: note: candidate function not viable: no known conversion from ''float'' to ''float *&'' for 1st argument\nstring * function_main(float *  &x,string *  &vasya)\n         ^\n./src/code1.cpp:115:22: error: no matching function for call to ''function_etalon''\n result_for_etalon = function_etalon(x_for_etalon,vasya_for_etalon);\n                     ^~~~~~~~~~~~~~~\n./src/code1.cpp:37:10: note: candidate function not viable: no known conversion from ''float'' to ''float *&'' for 1st argument\nstring * function_etalon(float *  &x,string *  &vasya)\n         ^\n./src/code1.cpp:116:11: error: no matching function for call to ''function_main''\n result = function_main(x,vasya);\n          ^~~~~~~~~~~~~\n./src/code1.cpp:41:10: note: candidate function not viable: no known conversion from ''float'' to ''float *&'' for 1st argument\nstring * function_main(float *  &x,string *  &vasya)\n         ^\n4 warnings and 4 errors generated.\n'),
(13, '2001', 11114, 'done', '2015-12-10', 'Segmentation fault\n', './src/code0.cpp:37:34: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                 ^\n./src/code0.cpp:37:45: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                            ^\n./src/code0.cpp:41:32: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                               ^\n./src/code0.cpp:41:43: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                                          ^\n4 warnings generated.\n'),
(14, '200h1', 11114, 'done', '2015-12-10', ' @0!@ @1@', './src/code3.cpp:37:34: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                 ^\n./src/code3.cpp:37:45: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_etalon(float  &x,string  &vasya)\n                                            ^\n./src/code3.cpp:41:32: warning: unused parameter ''x'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                               ^\n./src/code3.cpp:41:43: warning: unused parameter ''vasya'' [-Wunused-parameter]\nstring * function_main(float  &x,string  &vasya)\n                                          ^\n4 warnings generated.\n'),
(15, '21', 111114, 'done', '2015-12-10', ' @0!@ @1@', './src/code3.cpp:37:35: warning: unused parameter ''x'' [-Wunused-parameter]\n string * function_etalon(float  &x,string  &vasya)\n                                  ^\n./src/code3.cpp:37:46: warning: unused parameter ''vasya'' [-Wunused-parameter]\n string * function_etalon(float  &x,string  &vasya)\n                                             ^\n./src/code3.cpp:41:33: warning: unused parameter ''x'' [-Wunused-parameter]\n string * function_main(float  &x,string  &vasya)\n                                ^\n./src/code3.cpp:41:44: warning: unused parameter ''vasya'' [-Wunused-parameter]\n string * function_main(float  &x,string  &vasya)\n                                           ^\n4 warnings generated.\n');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
