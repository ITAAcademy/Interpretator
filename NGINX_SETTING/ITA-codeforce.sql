-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Хост: localhost
-- Время создания: Ноя 28 2015 г., 11:41
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
  `name` varchar(20) DEFAULT NULL,
  `header` text,
  `etalon` text,
  `footer` text,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=557 ;

--
-- Дамп данных таблицы `assignment_cpp`
--

INSERT INTO `assignment_cpp` (`ID`, `name`, `header`, `etalon`, `footer`) VALUES
(209, 'test example', '#include <iostream>\n#include <cstdlib>\nfunction(float x,string vasya){\n', 'hff', '}\nint main(){\nfunction(2,"true"true);}'),
(210, 'test example', '#include <iostream>\n#include <cstdlib>\nfunction(float x,string vasya){\n', 'hff', '}\nint main(){\nfunction(2,"true"true);}'),
(211, 'test example', '#include <iostream>\n		#include <cstdlib>\nfunction(int  x,int  vasya){\n', 'hff', '}\nint main(){\nfunction(22,2020);}'),
(212, 'test example', '#include <iostream>\n		#include <cstdlib>\nint function(int  x,int  vasya){\n', 'hff', '}\nint main(){\nfunction(2,20);}'),
(213, 'test example', '#include <iostream>\n		#include <cstdlib>\nint function(int  x,int  vasya){\n', 'hff', '}\nint main(){\nif ( 10 ==function(2,20)\nstd::cout << 0 << OK}'),
(214, 'test example', '#include <iostream>\n		#include <cstdlib>\nint function(int  x,int  vasya){\n', 'hff', '}\nint main(){\nif ( 10 ==function(2,20))\nstd::cout << 0 << OK;if ( 12 ==function(2,20))\nstd::cout << 1 << OK;\n}'),
(215, 'test example', '#include <iostream>\n		#include <cstdlib>\nint function(int  x,int  vasya){\n', 'hff', '}\nint main(){\nif ( 10 ==function(2,20))\nstd::cout << 0 << OK;if ( 12 ==function(3,5))\nstd::cout << 1 << OK;\n}'),
(216, 'test example', '#include <iostream>\n		#include <cstdlib>\nint function(int  x,int  vasya){\n', 'hff', '}\nint main(){\nif ( 10 == function(2,20))\nstd::cout << 0 << OK;if ( 12 == function(3,5))\nstd::cout << 1 << OK;\n}'),
(217, 'test example', '#include <iostream>\n		#include <cstdlib>\nint function(int  x,int  vasya){\n', 'hff', '}\nint main(){\nif ( 10 == function(2,20))\nstd::cout << 0 << "OqweK";\nif ( 12 == function(3,5))\nstd::cout << 1 << "OqweK";\n\n}'),
(218, 'test example', '#include <iostream>\n		#include <cstdlib>\nint function(int  x,int  vasya){\n', 'hff', '}\nint main(){\nif ( 10 == function(2,20))\nstd::cout << @0 << "@";\nif ( 12 == function(3,5))\nstd::cout << @1 << "@";\n\n}'),
(219, 'test example', '#include <iostream>\n		#include <cstdlib>\nint function(int  x,int  vasya){\n', 'hff', '}\nint main(){\nif ( 10 == function(2,20))\nstd::cout << "@0@";\nelse\nstd::cout << "@0!@";\nif ( 12 == function(3,5))\nstd::cout << "@1@";\nelse\nstd::cout << "@1!@";\n\n}'),
(220, 'test example', '#include <iostream>\n		#include <cstdlib>\nint function(string  x,string  vasya){\n', 'hff', '}\nint main(){\nif ( 10\n == function(""2"\n",""20"\n"))\nstd::cout << " @0@";\nelse\nstd::cout << " @0!@";\nif ( 12\n == function(""3"\n",""5"\n"))\nstd::cout << " @1@";\nelse\nstd::cout << " @1!@";\n\n}'),
(221, 'test example', '#include <iostream>\n		#include <cstdlib>\n using namespace std;\nint function(int  x,string  vasya){\n', 'hff', '}\nint main(){\nif ( 10\n == function(2\n,""20"\n"))\nstd::cout << " @0@";\nelse\nstd::cout << " @0!@";\nif ( 12\n == function(3\n,""5"\n"))\nstd::cout << " @1@";\nelse\nstd::cout << " @1!@";\n\n}'),
(222, 'test example', '#include <iostream>\n		#include <cstdlib>\n using namespace std;\nint function(int  x,string  vasya){\n', 'hff', '}\nint main(){\nif ( 10\n == function(2\n,""20"\n"))\nstd::cout << " @0@";\nelse\nstd::cout << " @0!@";\nif ( 12\n == function(3\n,""5"\n"))\nstd::cout << " @1@";\nelse\nstd::cout << " @1!@";\n\n}'),
(223, 'test example', '#include <iostream>\n		#include <cstdlib>\n using namespace std;\nint function(int  x,string  vasya){\n', 'hff', '}\nint main(){\nif ( 10\n == function(2\n,"20"\n))\nstd::cout << " @0@";\nelse\nstd::cout << " @0!@";\nif ( 12\n == function(3\n,"5"\n))\nstd::cout << " @1@";\nelse\nstd::cout << " @1!@";\n\n}'),
(265, 'test example', '#include <iostream>\n		#include <cstdlib>\n		#include <algorithm>\n using namespace std;\n\nint function(int  x,string  vasya){\n', 'hff', 'return 0;}\ntemplate<typename T,int size>\n	bool compareArrs(T arr1[size],T arr2[size]){\n		for (int i=0;i<size;i++){if (arr1[i]!=arr2[i])return false;}			return true;\n	}int main(){\nif ( 10\n == function(2\n,""20"\n"))\nstd::cout << " @0@";\nelse\nstd::cout << " @0!@";\nif ( 12\n == function(3\n,""5"\n"))\nstd::cout << " @1@";\nelse\nstd::cout << " @1!@";\n\n}'),
(266, 'test example', '#include <iostream>\n		#include <cstdlib>\n		#include <algorithm>\n using namespace std;\n\nint function(int  x,string  vasya){\n', 'hff', 'return 0;}\ntemplate<typename T,int size>\n	bool compareArrs(T arr1[size],T arr2[size]){\n		for (int i=0;i<size;i++){if (arr1[i]!=arr2[i])return false;}			return true;\n	}int main(){\nif ( 10\n == function(2\n,"20"\n))\nstd::cout << " @0@";\nelse\nstd::cout << " @0!@";\nif ( 12\n == function(3\n,"5"\n))\nstd::cout << " @1@";\nelse\nstd::cout << " @1!@";\n\n}'),
(267, 'test example', '#include <iostream>\n		#include <cstdlib>\n		#include <algorithm>\n using namespace std;\n\nint function(int  x,string  vasya){\n', 'hff', 'return 0;}\ntemplate<typename T,int size>\n	bool compareArrs(T arr1[size],T arr2[size]){\n		for (int i=0;i<size;i++){if (arr1[i]!=arr2[i])return false;}			return true;\n	}int main(){\nif ( 10\n == function(2\n,"20"\n))\nstd::cout << " @0@";\nelse\nstd::cout << " @0!@";\nif ( 12\n == function(3\n,"5"\n))\nstd::cout << " @1@";\nelse\nstd::cout << " @1!@";\n\n}'),
(268, 'test example', '#include <iostream>\n		#include <cstdlib>\n		#include <algorithm>\n using namespace std;\n\nint function(int  x,string  vasya){\n', 'hff', 'return 0;}\ntemplate<typename T,int size>\n	bool compareArrs(T arr1[size],T arr2[size]){\n		for (int i=0;i<size;i++){if (arr1[i]!=arr2[i])return false;}			return true;\n	}int main(){\nif ( 10\n == function(2\n,"20"\n))\nstd::cout << " @0@";\nelse\nstd::cout << " @0!@";\nif ( 12\n == function(3\n,"5"\n))\nstd::cout << " @1@";\nelse\nstd::cout << " @1!@";\n\n}'),
(269, 'test example', '#include <iostream>\n		#include <cstdlib>\n		#include <algorithm>\n using namespace std;\n\nfloat function(int  x,string  vasya){\n', 'hff', 'return 0;}\ntemplate<typename T,int size>\n	bool compareArrs(T arr1[size],T arr2[size]){\n		for (int i=0;i<size;i++){if (arr1[i]!=arr2[i])return false;}			return true;\n	}int main(){\nif ( \n == function(2\n,"20"\n))\nstd::cout << " @0@";\nelse\nstd::cout << " @0!@";\nif (  == function(3\n,"5"\n))\nstd::cout << " @1@";\nelse\nstd::cout << " @1!@";\n\n}'),
(270, 'test example', '#include <iostream>\n		#include <cstdlib>\n		#include <algorithm>\n using namespace std;\n\nfloat function(int  x,string  vasya){\n', 'hff', 'return 0;}\ntemplate<typename T,int size>\n	bool compareArrs(T arr1[size],T arr2[size]){\n		for (int i=0;i<size;i++){if (arr1[i]!=arr2[i])return false;}			return true;\n	}int main(){\nif ( \n == function(2\n,"20"\n))\nstd::cout << " @0@";\nelse\nstd::cout << " @0!@";\nif (  == function(3\n,"5"\n))\nstd::cout << " @1@";\nelse\nstd::cout << " @1!@";\n\n}'),
(271, 'test example', '#include <iostream>\n		#include <cstdlib>\n		#include <algorithm>\n using namespace std;\n\nfloat function(int  x,string  vasya){\n', 'hff', 'return 0;}\ntemplate<typename T,int size>\n	bool compareArrs(T arr1[size],T arr2[size]){\n		for (int i=0;i<size;i++){if (arr1[i]!=arr2[i])return false;}			return true;\n	}int main(){\nif ( 10.0\n == function(2\n,"20"\n))\nstd::cout << " @0@";\nelse\nstd::cout << " @0!@";\nif ( 12.0\n == function(3\n,"5"\n))\nstd::cout << " @1@";\nelse\nstd::cout << " @1!@";\n\n}'),
(275, 'test example', '#include <iostream>\n		#include <cstdlib>\n		#include <algorithm>\n using namespace std;\n\nfloat function(int  x,string  vasya[]){\n', 'hff', 'return 0;}\ntemplate<typename T,int size>\n	bool compareArrs(T arr1[size],T arr2[size]){\n		for (int i=0;i<size;i++){if (arr1[i]!=arr2[i])return false;}			return true;\n	}int main(){\nstring array0[]={"20"\n,"400"\n};\nstring array1[]={"5"\n,"200"\n};\nif ( 10.0\n == function(2\n,array0))\nstd::cout << " @0@";\nelse\nstd::cout << " @0!@";\nif ( 12.0\n == function(3\n,array1))\nstd::cout << " @1@";\nelse\nstd::cout << " @1!@";\n\n}'),
(276, 'test example', '#include <iostream>\n		#include <cstdlib>\n		#include <algorithm>\n using namespace std;\n\nfloat function(float  x[],string  vasya){\n', 'hff', 'return 0;}\ntemplate<typename T,int size>\n	bool compareArrs(T arr1[size],T arr2[size]){\n		for (int i=0;i<size;i++){if (arr1[i]!=arr2[i])return false;}			return true;\n	}int main(){\nfloat array0[]={10.0\n,12.0\n};\nfloat array1[]="5"\n;\nif ( 10.0\n == function(array0,"20"\n))\nstd::cout << " @0@";\nelse\nstd::cout << " @0!@";\nif ( 12.0\n == function(array1,"5"\n))\nstd::cout << " @1@";\nelse\nstd::cout << " @1!@";\n\n}'),
(277, 'test example', '#include <iostream>\n		#include <cstdlib>\n		#include <algorithm>\n using namespace std;\n\nfloat function(float  x[],string  vasya[]){\n', 'hff', 'return 0;}\ntemplate<typename T,int size>\n	bool compareArrs(T arr1[size],T arr2[size]){\n		for (int i=0;i<size;i++){if (arr1[i]!=arr2[i])return false;}			return true;\n	}int main(){\nfloat array0[]={10.0\n,12.0\n};\nstring array1[]={"20"\n,"5"\n};\nif ( [ 10.0, 12.0 ]\n == function(array0,array1))\nstd::cout << " @0@";\nelse\nstd::cout << " @0!@";\n\n}'),
(278, 'test example', '#include <iostream>\n		#include <cstdlib>\n		#include <algorithm>\n using namespace std;\n\nfloat function(float  x[],string  vasya[]){\n', 'hff', 'return 0;}\ntemplate<typename T,int size>\n	bool compareArrs(T arr1[size],T arr2[size]){\n		for (int i=0;i<size;i++){if (arr1[i]!=arr2[i])return false;}			return true;\n	}int main(){\nfloat array0[]={10.0\n,12.0\n};\nstring array1[]={"20"\n,"5"\n};\nif ( [ 10.0, 12.0 ]\n == function(array0,array1))\nstd::cout << " @0@";\nelse\nstd::cout << " @0!@";\n\n}'),
(279, 'test example', '#include <iostream>\n		#include <cstdlib>\n		#include <algorithm>\n using namespace std;\n\nfloat * function(float  x[],string  vasya[]){\n', 'hff', 'return 0;}\ntemplate<typename T,int size>\n	bool compareArrs(T arr1[size],T arr2[size]){\n		for (int i=0;i<size;i++){if (arr1[i]!=arr2[i])return false;}			return true;\n	}int main(){\nfloat array0[]={10.0\n,12.0\n};\nfloat array1[]={10.0\n,12.0\n};\nstring array2[]={"20"\n,"5"\n};\nif (compareArrs<float,2>(array0,function(array1,array2)))\nstd::cout << " @0@";\nelse\nstd::cout << " @0!@";\n\n}'),
(546, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 18:39:40', NULL),
(547, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 18:59:44', NULL),
(548, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:0:54', NULL),
(549, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:19:1', NULL),
(550, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:46:15', NULL),
(551, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:48:10', NULL),
(552, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:52:7', NULL),
(553, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 20:22:2', NULL),
(554, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return 10', '2015-11-19 20:17:29', NULL),
(555, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return 10;', '2015-11-19 20:18:24', NULL),
(556, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-19 21:18:52', NULL);

-- --------------------------------------------------------

--
-- Структура таблицы `assignment_cs`
--

CREATE TABLE IF NOT EXISTS `assignment_cs` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(20) DEFAULT NULL,
  `header` text,
  `etalon` text,
  `footer` text,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=20 ;

--
-- Дамп данных таблицы `assignment_cs`
--

INSERT INTO `assignment_cs` (`ID`, `name`, `header`, `etalon`, `footer`) VALUES
(11, 'hello', '', '\r\n                                                                                \r\n                                                                                using System;\r\nnamespace HelloWorld\r\n{\r\n    class Hello \r\n    {\r\n        static void Main() \r\n        {\r\n            Console.WriteLine("Hello World!");\r\n           \r\n        }\r\n    }\r\n}\r\n                                                                                ', ''),
(12, '127.0.0.1', '\n', '2015-11-27 20:42:11', NULL),
(13, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 23:15:29', NULL),
(14, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 23:21:33', NULL),
(15, '127.0.0.1', ' using System;\n \npublic classa HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:28:32', NULL),
(16, '127.0.0.1', ' using System;\n \npublic classa HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:29:4', NULL),
(17, '127.0.0.1', ' using System;\n \npublic classa HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:30:5', NULL),
(18, '127.0.0.1', ' using System;\n \npublic classa HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:36:45', NULL),
(19, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:36:54', NULL);

-- --------------------------------------------------------

--
-- Структура таблицы `assignment_java`
--

CREATE TABLE IF NOT EXISTS `assignment_java` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `name` varchar(20) DEFAULT NULL,
  `header` varchar(512) DEFAULT NULL,
  `etalon` varchar(512) DEFAULT NULL,
  `footer` varchar(512) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Дамп данных таблицы `assignment_java`
--

INSERT INTO `assignment_java` (`ID`, `name`, `header`, `etalon`, `footer`) VALUES
(0, 'hello wordl', 'class Main#NUM#\r\n{\r\npublic static void main(String args[])\r\n{', 'System.out.println("Hello World!");', '}\r\n}'),
(7, 'javaDefault', 'class Main#NUM# \r\n{ \r\n    public static void main (String[] args)  \r\n   {  ', ' System.out.println ("Hello, world.");', '}}');

-- --------------------------------------------------------

--
-- Структура таблицы `assignment_js`
--

CREATE TABLE IF NOT EXISTS `assignment_js` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `name` varchar(20) CHARACTER SET latin1 DEFAULT NULL,
  `header` varchar(512) CHARACTER SET latin1 DEFAULT NULL,
  `etalon` varchar(512) CHARACTER SET latin1 DEFAULT NULL,
  `footer` varchar(512) CHARACTER SET latin1 DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=ascii;

--
-- Дамп данных таблицы `assignment_js`
--

INSERT INTO `assignment_js` (`ID`, `name`, `header`, `etalon`, `footer`) VALUES
(0, 'hello wordl', 'class Main#NUM#\r\n{\r\npublic static void main(String args[])\r\n{', 'System.out.println("Hello World!");', '}\r\n}'),
(7, 'javaDefault', 'class Main#NUM# \r\n{ \r\n    public static void main (String[] args)  \r\n   {  ', ' System.out.println ("Hello, world.");', '}}'),
(2, 'k', NULL, NULL, NULL),
(0, '127.0.0.1', ' console.log("hh");', '2015-7-1 16:16:13', NULL),
(0, '127.0.0.1', ' console.log("hi");', '2015-7-1 17:26:26', NULL),
(0, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-7-1 20:22:37', NULL),
(0, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-7-1 20:24:54', NULL),
(0, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-7-3 21:23:38', NULL),
(0, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-7-3 21:24:24', NULL);

-- --------------------------------------------------------

--
-- Структура таблицы `assignment_php`
--

CREATE TABLE IF NOT EXISTS `assignment_php` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(20) DEFAULT NULL,
  `header` text,
  `etalon` text,
  `footer` text,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=549 ;

--
-- Дамп данных таблицы `assignment_php`
--

INSERT INTO `assignment_php` (`ID`, `name`, `header`, `etalon`, `footer`) VALUES
(545, '12143', ' ', ' ', ' '),
(546, '127.0.0.1', ' ', '2015-11-13 18:43:0', NULL),
(547, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-14 11:4:54', NULL),
(548, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 18:47:26', NULL);

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
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=642 ;

--
-- Дамп данных таблицы `history`
--

INSERT INTO `history` (`ID`, `ip`, `code`, `date_time`) VALUES
(522, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:05:54'),
(523, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:07:08'),
(524, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:07:10'),
(525, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:07:13'),
(526, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:07:14'),
(527, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:07:19'),
(528, '1054003', '54429', '0000-00-00 00:00:00'),
(529, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:09:24'),
(530, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:11:25'),
(531, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:17:02'),
(532, '1054003', '54440', '0000-00-00 00:00:00'),
(533, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:18:19'),
(534, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:25:43'),
(535, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:25:44'),
(536, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:25:45'),
(537, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:25:45'),
(538, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:25:48'),
(539, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:25:53'),
(540, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:25:54'),
(541, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:25:54'),
(542, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:26:56'),
(543, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:09'),
(544, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:10'),
(545, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:11'),
(546, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:11'),
(547, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:12'),
(548, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:12'),
(549, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:12'),
(550, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:12'),
(551, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:12'),
(552, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:13'),
(553, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:13'),
(554, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:13'),
(555, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:13'),
(556, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:14'),
(557, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:15'),
(558, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:15'),
(559, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:16'),
(560, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:16'),
(561, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:17'),
(562, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:17'),
(563, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:18'),
(564, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:18'),
(565, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:19'),
(566, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:19'),
(567, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:20'),
(568, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:27:20'),
(569, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:28:51'),
(570, '127.0.0.1', 'using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        rConsole.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 21:29:04'),
(571, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:05:03'),
(572, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:13:00'),
(573, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:13:25'),
(574, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:15:04'),
(575, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:15:27'),
(576, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:16:25'),
(577, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:25:54'),
(578, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:26:09'),
(579, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:28:41'),
(580, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:30:27'),
(581, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:32:15'),
(582, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:36:41'),
(583, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:40:33'),
(584, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:42:38'),
(585, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:43:32'),
(586, '127.0.0.1', '\n', '2015-11-27 22:50:24'),
(587, '127.0.0.1', '\n', '2015-11-27 22:50:41'),
(588, '127.0.0.1', '\n', '2015-11-27 22:50:51'),
(589, '10444003', '54555090', '0000-00-00 00:00:00'),
(590, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:55:08'),
(591, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:57:12'),
(592, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:57:19'),
(593, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:57:23'),
(594, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:58:26'),
(595, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 22:58:31'),
(596, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 23:14:37'),
(597, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 23:16:27'),
(598, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 23:18:21'),
(599, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 23:20:18'),
(600, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 23:21:51'),
(601, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 23:22:03'),
(602, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 23:23:15'),
(603, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 23:27:18'),
(604, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 23:29:31'),
(605, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 23:30:46'),
(606, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 23:31:36'),
(607, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-27 23:32:17'),
(608, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 10:52:02'),
(609, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 10:52:08'),
(610, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 10:52:33'),
(611, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 10:53:12'),
(612, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 10:53:25'),
(613, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 10:56:09'),
(614, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 10:58:28'),
(615, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:00:38'),
(616, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:02:28'),
(617, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:08:31'),
(618, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:08:43'),
(619, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:08:53'),
(620, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:09:03'),
(621, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:09:28'),
(622, '127.0.0.1', ' using System;\n \npublic classa HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:10:08'),
(623, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:13:12'),
(624, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:13:22'),
(625, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:13:26'),
(626, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:14:18'),
(627, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:17:09'),
(628, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:17:49'),
(629, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:18:22'),
(630, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:18:27'),
(631, '127.0.0.1', ' using System;\n \npublic class HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:20:58'),
(632, '127.0.0.1', ' using System;\n \npublic classa HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:24:39'),
(633, '127.0.0.1', ' using System;\n \npublic classa HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:24:52'),
(634, '127.0.0.1', ' using System;\n \npublic classa HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:25:17'),
(635, '127.0.0.1', ' using System;\n \npublic classa HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:25:23'),
(636, '104447', '0', '0000-00-00 00:00:00'),
(637, '104447', '0', '0000-00-00 00:00:00'),
(638, '127.0.0.1', ' using System;\n \npublic classa HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:32:43'),
(639, '127.0.0.1', ' using System;\n \npublic classa HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:33:04'),
(640, '127.0.0.1', ' using System;\n \npublic classa HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:33:09'),
(641, '127.0.0.1', ' using System;\n \npublic classa HelloWorld\n{\n    static public void Main ()\n    {\n        Console.WriteLine ("Hello Mono World");\n    }\n} ', '2015-11-28 11:36:26');

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
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=211 ;

--
-- Дамп данных таблицы `results`
--

INSERT INTO `results` (`id`, `session`, `jobid`, `status`, `date`, `result`, `warning`) VALUES
(145, '1054003', 54415, 'in proccess', '2015-11-27', '', ''),
(146, '1054003', 54416, 'failed', '2015-11-27', '', '/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 0 has invalid symbol index 11\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 1 has invalid symbol index 12\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 2 has invalid symbol index 2\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 3 has invalid symbol index 2\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 4 has invalid symbol index 11\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 5 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 6 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 7 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 8 has invalid symbol index 12\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 9 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 10 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 11 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 12 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 13 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 14 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 15 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 16 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 17 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 18 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 19 has invalid symbol index 21\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_line): relocation 0 has invalid symbol index 2\n/usr/bin/../lib/gcc/x86_64-linux-gnu/4.9/../../../x86_64-linux-gnu/crt1.o: In function `_start'':\n(.text+0x20): undefined reference to `main''\nclang: error: linker command failed with exit code 1 (use -v to see invocation)\n'),
(147, '1054003', 54417, 'in proccess', '2015-11-27', '', ''),
(148, '1054003', 54418, 'in proccess', '2015-11-27', '', ''),
(149, '1054003', 54428, 'failed', '2015-11-27', '', '/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 0 has invalid symbol index 11\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 1 has invalid symbol index 12\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 2 has invalid symbol index 2\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 3 has invalid symbol index 2\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 4 has invalid symbol index 11\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 5 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 6 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 7 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 8 has invalid symbol index 12\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 9 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 10 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 11 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 12 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 13 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 14 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 15 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 16 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 17 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 18 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 19 has invalid symbol index 21\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_line): relocation 0 has invalid symbol index 2\n/usr/bin/../lib/gcc/x86_64-linux-gnu/4.9/../../../x86_64-linux-gnu/crt1.o: In function `_start'':\n(.text+0x20): undefined reference to `main''\nclang: error: linker command failed with exit code 1 (use -v to see invocation)\n'),
(150, '1054003', 54430, 'in proccess', '2015-11-27', '', ''),
(151, '1054003', 54439, 'in proccess', '2015-11-27', '', ''),
(152, '1054003', 54440, 'in proccess', '2015-11-27', '', ''),
(153, '10545003', 54440, 'in proccess', '2015-11-27', '', ''),
(154, '127.0.0.1', 0, '2015-11-27 21:26:0', '0000-00-00', '', ''),
(155, '105454003', 54440, 'in proccess', '2015-11-27', '', ''),
(156, '10444003', 54554, 'failed', '2015-11-27', '', '/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 0 has invalid symbol index 11\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 1 has invalid symbol index 12\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 2 has invalid symbol index 2\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 3 has invalid symbol index 2\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 4 has invalid symbol index 11\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 5 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 6 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 7 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 8 has invalid symbol index 12\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 9 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 10 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 11 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 12 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 13 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 14 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 15 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 16 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 17 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 18 has invalid symbol index 13\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_info): relocation 19 has invalid symbol index 21\n/usr/bin/ld: /usr/lib/debug/usr/lib/x86_64-linux-gnu/crt1.o(.debug_line): relocation 0 has invalid symbol index 2\n/usr/bin/../lib/gcc/x86_64-linux-gnu/4.9/../../../x86_64-linux-gnu/crt1.o: In function `_start'':\n(.text+0x20): undefined reference to `main''\nclang: error: linker command failed with exit code 1 (use -v to see invocation)\n'),
(157, '10444003', 5455502, 'in proccess', '2015-11-27', '', ''),
(158, '10444003', 5455506, 'in proccess', '2015-11-27', '', ''),
(159, '10444003', 54555091, 'in proccess', '2015-11-27', '', ''),
(160, '1054003', 54554, 'in proccess', '2015-11-27', '', ''),
(161, '1054003', 54555, 'failed', '2015-11-27', '', './src/code3.cpp:31:19: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(int  x,string  vasya){\n                  ^\n./src/code3.cpp:31:29: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(int  x,string  vasya){\n                            ^\n./src/code3.cpp:35:1: warning: control reaches end of non-void function [-Wreturn-type]\n}\n^\n./src/code3.cpp:39:4: error: expected '')''\n,""20"\n   ^\n./src/code3.cpp:38:13: note: to match this ''(''\n == function(2\n            ^\n./src/code3.cpp:39:6: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n,""20"\n     ^\n./src/code3.cpp:40:1: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n"))\n^\n./src/code3.cpp:42:1: error: expected expression\nelse\n^\n./src/code3.cpp:46:4: error: expected '')''\n,""5"\n   ^\n./src/code3.cpp:45:13: note: to match this ''(''\n == function(3\n            ^\n./src/code3.cpp:46:5: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n,""5"\n    ^\n./src/code3.cpp:47:1: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n"))\n^\n./src/code3.cpp:49:1: error: expected expression\nelse\n^\n7 warnings and 4 errors generated.\n'),
(162, '10444003', 54555090, 'in proccess', '2015-11-27', '', ''),
(163, '10444003', 545550910, 'in proccess', '2015-11-27', '', ''),
(164, '10444003', 545550911, 'in proccess', '2015-11-27', '', ''),
(165, '10444003', 545550912, 'in proccess', '2015-11-27', '', ''),
(166, '10444003', 545550913, 'in proccess', '2015-11-27', '', ''),
(167, '10444003', 545550914, 'in proccess', '2015-11-27', '', ''),
(168, '10444003', 545550915, 'in proccess', '2015-11-27', '', ''),
(169, '10444003', 545550, 'in proccess', '2015-11-27', '', ''),
(170, '10444003', 545551, 'in proccess', '2015-11-27', '', ''),
(171, '10444003', 545552, 'in proccess', '2015-11-27', '', ''),
(172, '10444003', 545553, 'in proccess', '2015-11-27', '', ''),
(173, '10444003', 555553, 'in proccess', '2015-11-27', '', ''),
(174, '10444003', 555554, 'in proccess', '2015-11-27', '', ''),
(175, '10444003', 555564, 'in proccess', '2015-11-27', '', ''),
(176, '10444003', 565564, 'in proccess', '2015-11-27', '', ''),
(177, '10444003', 565570, 'in proccess', '2015-11-27', '', ''),
(178, '10444003', 565571, 'in proccess', '2015-11-27', '', ''),
(179, '10444003', 565572, 'in proccess', '2015-11-27', '', ''),
(180, '10444003', 565573, 'in proccess', '2015-11-28', '', ''),
(181, '10444003', 565574, 'in proccess', '2015-11-28', '', ''),
(182, '10444003', 565575, 'in proccess', '2015-11-28', '', ''),
(183, '10444003', 565576, 'in proccess', '2015-11-28', '', ''),
(184, '10444003', 565586, 'in proccess', '2015-11-28', '', ''),
(185, '10444003', 565589, 'in proccess', '2015-11-28', '', ''),
(186, '10444003', 565590, 'in proccess', '2015-11-28', '', ''),
(187, '10444003', 565591, 'in proccess', '2015-11-28', '', ''),
(189, '10444003', 565592, 'in proccess', '2015-11-28', '', ''),
(191, '10444003', 565593, 'done', '2015-11-28', 'Hello Mono World\n', ''),
(192, '10444003', 565594, 'done', '2015-11-28', 'Hello Mono World\n', ''),
(193, '10444003', 565595, 'done', '2015-11-28', 'Cannot open assembly ''./src/Main3.exe'': No such file or directory.\n', './src/Main3.cs(4,7): error CS1525: Unexpected symbol `classa'', expecting `class'', `delegate'', `enum'', `interface'', `partial'', or `struct''\nCompilation failed: 1 error(s), 0 warnings\n'),
(194, '10444003', 5655922, 'failed', '2015-11-28', '', ''),
(195, '10444003', 56559322, 'failed', '2015-11-28', '', ''),
(196, '10444003', 56559622, 'failed', '2015-11-28', '', ''),
(198, '10444003', 56559722, 'done', '2015-11-28', 'Hello Mono World\n', ''),
(199, '10444003', 56559723, 'done', '2015-11-28', 'Hello Mono World\n', ''),
(201, '104444', 0, 'done', '2015-11-28', 'rm: cannot remove â€˜./src/Main2.exeâ€™: No such file or directory\n', './src/Main2.cs(4,7): error CS1525: Unexpected symbol `classa'', expecting `class'', `delegate'', `enum'', `interface'', `partial'', or `struct''\nCompilation failed: 1 error(s), 0 warnings\n'),
(202, '104445', 0, 'in proccess', '2015-11-28', '', ''),
(203, '104446', 0, 'failed', '2015-11-28', '', 'Compilation failed: 1 error(s), 0 warnings\n'),
(204, '104447', 0, 'done', '2015-11-28', 'Cannot open assembly ''./src/Main3.exe'': No such file or directory.\n', './src/Main3.cs(4,7): error CS1525: Unexpected symbol `classa'', expecting `class'', `delegate'', `enum'', `interface'', `partial'', or `struct''\nCompilation failed: 1 error(s), 0 warnings\n'),
(205, '104448', 0, 'in proccess', '2015-11-28', '', ''),
(207, '104449', 0, 'done', '2015-11-28', 'Cannot open assembly ''./src/Main3.exe'': No such file or directory.\n', './src/Main3.cs(4,7): error CS1525: Unexpected symbol `classa'', expecting `class'', `delegate'', `enum'', `interface'', `partial'', or `struct''\nCompilation failed: 1 error(s), 0 warnings\n'),
(208, '1044501', 0, 'failed', '2015-11-28', '', './src/Main3.cs(4,7): error CS1525: Unexpected symbol `classa'', expecting `class'', `delegate'', `enum'', `interface'', `partial'', or `struct''\nCompilation failed: 1 error(s), 0 warnings\n'),
(209, '1044502', 0, 'failed', '2015-11-28', '', './src/Main0.cs(4,7): error CS1525: Unexpected symbol `classa'', expecting `class'', `delegate'', `enum'', `interface'', `partial'', or `struct''\nCompilation failed: 1 error(s), 0 warnings\n'),
(210, '1044503', 0, 'done', '2015-11-28', 'Hello Mono World\n', '');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
