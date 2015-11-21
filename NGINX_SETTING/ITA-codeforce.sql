-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Nov 21, 2015 at 03:04 PM
-- Server version: 5.5.43-0ubuntu0.14.04.1
-- PHP Version: 5.5.9-1ubuntu4.14

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `ITA-codeforce`
--

-- --------------------------------------------------------

--
-- Table structure for table `assignment_cpp`
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
-- Dumping data for table `assignment_cpp`
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
-- Table structure for table `assignment_java`
--

CREATE TABLE IF NOT EXISTS `assignment_java` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `name` varchar(20) DEFAULT NULL,
  `header` varchar(512) DEFAULT NULL,
  `etalon` varchar(512) DEFAULT NULL,
  `footer` varchar(512) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `assignment_java`
--

INSERT INTO `assignment_java` (`ID`, `name`, `header`, `etalon`, `footer`) VALUES
(0, 'hello wordl', 'class Main#NUM#\r\n{\r\npublic static void main(String args[])\r\n{', 'System.out.println("Hello World!");', '}\r\n}'),
(7, 'javaDefault', 'class Main#NUM# \r\n{ \r\n    public static void main (String[] args)  \r\n   {  ', ' System.out.println ("Hello, world.");', '}}');

-- --------------------------------------------------------

--
-- Table structure for table `assignment_js`
--

CREATE TABLE IF NOT EXISTS `assignment_js` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `name` varchar(20) CHARACTER SET latin1 DEFAULT NULL,
  `header` varchar(512) CHARACTER SET latin1 DEFAULT NULL,
  `etalon` varchar(512) CHARACTER SET latin1 DEFAULT NULL,
  `footer` varchar(512) CHARACTER SET latin1 DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=ascii;

--
-- Dumping data for table `assignment_js`
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
-- Table structure for table `assignment_php`
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
-- Dumping data for table `assignment_php`
--

INSERT INTO `assignment_php` (`ID`, `name`, `header`, `etalon`, `footer`) VALUES
(545, '12143', ' ', ' ', ' '),
(546, '127.0.0.1', ' ', '2015-11-13 18:43:0', NULL),
(547, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-14 11:4:54', NULL),
(548, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 18:47:26', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `history`
--

CREATE TABLE IF NOT EXISTS `history` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `ip` varchar(20) DEFAULT NULL,
  `code` varchar(512) DEFAULT NULL,
  `date_time` datetime DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=463 ;

--
-- Dumping data for table `history`
--

INSERT INTO `history` (`ID`, `ip`, `code`, `date_time`) VALUES
(332, '127.0.0.1', ' ', '2015-11-13 18:46:56'),
(333, '127.0.0.1', ' ', '2015-11-13 18:46:57'),
(334, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-13 18:47:14'),
(335, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-13 18:47:18'),
(336, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-13 18:47:20'),
(337, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-13 18:53:15'),
(338, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-13 18:53:16'),
(339, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-13 18:53:19'),
(340, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-13 18:53:20'),
(341, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-13 18:57:59'),
(342, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-13 18:58:04'),
(343, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-13 18:58:54'),
(344, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-13 19:04:20'),
(345, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-13 19:05:02'),
(346, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-13 19:05:05'),
(347, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-13 19:07:23'),
(348, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-13 19:07:26'),
(349, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-13 19:07:41'),
(350, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-14 11:01:01'),
(351, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-14 11:04:13'),
(352, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-14 11:04:39'),
(353, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-14 11:04:41'),
(354, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-14 11:04:42'),
(355, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-14 11:04:46'),
(356, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-14 11:04:47'),
(357, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-14 11:04:50'),
(358, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-14 11:04:55'),
(359, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-17 18:22:17'),
(360, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-17 18:22:22'),
(361, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-17 18:22:25'),
(362, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-17 18:25:34'),
(363, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-17 18:25:35'),
(364, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-17 18:25:36'),
(365, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-17 18:25:36'),
(366, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-17 18:25:37'),
(367, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-17 18:26:01'),
(368, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-17 18:26:04'),
(369, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-17 18:33:52'),
(370, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-17 18:33:53'),
(371, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-17 18:33:54'),
(372, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-17 18:34:16'),
(373, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-17 18:34:22'),
(374, '127.0.0.1', '<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <?php echo ''<p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p>''; ?>\n </body>\n</html>', '2015-11-17 18:34:23'),
(375, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 18:35:53'),
(376, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 18:35:54'),
(377, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 18:39:41'),
(378, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 18:47:24'),
(379, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 18:47:27'),
(380, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 18:48:39'),
(381, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 18:48:40'),
(382, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 18:54:58'),
(383, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 18:59:45'),
(384, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:00:49'),
(385, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:00:55'),
(386, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:03:39'),
(387, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:03:43'),
(388, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:09:52'),
(389, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:09:55'),
(390, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:09:58'),
(391, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:13:40'),
(392, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:13:42'),
(393, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:13:45'),
(394, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:14:57'),
(395, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:14:57'),
(396, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:17:03'),
(397, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:17:05'),
(398, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:18:59'),
(399, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:30:29'),
(400, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:30:30'),
(401, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:30:39'),
(402, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:33:35'),
(403, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:33:39'),
(404, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:33:40'),
(405, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:42:58'),
(406, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:48:06'),
(407, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:48:07'),
(408, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:48:11'),
(409, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:48:36'),
(410, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:53:24'),
(411, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 19:54:06'),
(412, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 20:03:40'),
(413, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 20:03:43'),
(414, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 20:08:31'),
(415, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 20:08:34'),
(416, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 20:19:07'),
(417, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-17 20:20:19'),
(418, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return 10;', '2015-11-17 21:34:56'),
(419, '127.0.0.1', 'return 10;', '2015-11-18 20:10:32'),
(420, '127.0.0.1', 'return 10;', '2015-11-18 20:10:35'),
(421, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-19 19:56:57'),
(422, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-19 19:56:58'),
(423, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-19 20:00:51'),
(424, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-19 20:00:52'),
(425, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-19 20:15:48'),
(426, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return 10', '2015-11-19 20:17:25'),
(427, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return 10', '2015-11-19 20:17:30'),
(428, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return 10;', '2015-11-19 21:16:52'),
(429, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-19 21:18:31'),
(430, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-19 21:18:37'),
(431, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-19 21:18:40'),
(432, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-19 21:18:43'),
(433, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-19 21:28:11'),
(434, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-19 21:32:39'),
(435, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-19 21:32:41'),
(436, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-19 21:39:01'),
(437, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-19 21:39:04'),
(438, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-19 21:42:09'),
(439, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-19 21:42:15'),
(440, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return 10;', '2015-11-19 21:44:49'),
(441, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return 0;', '2015-11-19 21:45:07'),
(442, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return "gdfgfdg";', '2015-11-19 21:47:12'),
(443, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return "gdfgfdg";', '2015-11-19 21:47:14'),
(444, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return 0;', '2015-11-19 22:01:39'),
(445, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return 0;', '2015-11-19 22:01:43'),
(446, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return 0;', '2015-11-21 09:03:14'),
(447, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-21 11:00:45'),
(448, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-21 11:00:50'),
(449, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-21 11:24:15'),
(450, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-21 11:24:16'),
(451, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-11-21 11:24:17'),
(452, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return 10;', '2015-11-21 11:24:53'),
(453, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return 12;', '2015-11-21 11:30:50'),
(454, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return 12;', '2015-11-21 11:30:51'),
(455, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return x;', '2015-11-21 11:58:00'),
(456, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return y;', '2015-11-21 11:58:25'),
(457, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return y;', '2015-11-21 11:58:29'),
(458, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; return vasya;', '2015-11-21 11:59:39'),
(459, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; int k = 5; k /=0; return x;', '2015-11-21 12:01:23'),
(460, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; int k = 5; k /=0; return x;', '2015-11-21 12:01:26'),
(461, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; int k = 5; k /=0; return x;', '2015-11-21 12:05:14'),
(462, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; int k = 5; return x;', '2015-11-21 12:08:52');

-- --------------------------------------------------------

--
-- Table structure for table `results`
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
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=128 ;

--
-- Dumping data for table `results`
--

INSERT INTO `results` (`id`, `session`, `jobid`, `status`, `date`, `result`, `warning`) VALUES
(54, '123', 545, 'failed', '2015-11-13', '', ''),
(55, '1203', 545, 'failed', '2015-11-13', '', ''),
(56, '12003', 545, 'done', '2015-11-13', ' \n<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p> </body>\n</html>\n ', ''),
(57, '120003', 545, 'done', '2015-11-13', ' \n<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p> </body>\n</html>\n ', ''),
(58, '1205003', 545, 'failed', '2015-11-14', '', ''),
(59, '105003', 5454, 'done', '2015-11-14', ' \n<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p> </body>\n</html>\n ', ''),
(60, '105003', 54554, 'done', '2015-11-14', ' \n<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p> </body>\n</html>\n ', ''),
(61, '1054003', 54554, 'done', '2015-11-14', ' \n<html>\n <head>\n  <title>Ð¢ÐµÑÑ‚Ð¸Ñ€ÑƒÐµÐ¼ PHP</title>\n </head>\n <body>\n <p>ÐŸÑ€Ð¸Ð²ÐµÑ‚, Ð¼Ð¸Ñ€!</p> </body>\n</html>\n ', ''),
(62, '01054003', 54554, 'failed', '2015-11-17', '', ''),
(63, '010540103', 54554, 'failed', '2015-11-17', '', ''),
(64, '0010540103', 54554, 'failed', '2015-11-17', '', ''),
(65, '1241q223f4f2341', 11212, 'failed', '2015-11-17', '', ''),
(66, '1241q2203f4f2341', 11212, 'failed', '2015-11-17', '', ''),
(67, '1241q22032f4f2341', 11212, 'failed', '2015-11-17', '', ''),
(68, '123', 11212, 'failed', '2015-11-17', '', ''),
(69, '1g23', 11212, 'failed', '2015-11-17', '', ''),
(70, '1g2f3', 11212, 'failed', '2015-11-17', '', ''),
(71, '1g2ff3', 11212, 'failed', '2015-11-17', '', ''),
(72, '1g2fkf3', 11212, 'failed', '2015-11-17', '', ''),
(73, '127.0.0.1', 0, '2015-11-17 19:1:53', '0000-00-00', '', ''),
(74, '1g20fkf3', 11212, 'failed', '2015-11-17', '', ''),
(75, '1g20gfkf3', 11212, 'failed', '2015-11-17', '', ''),
(77, '1gj20gfkf3', 11212, 'failed', '2015-11-17', '', ''),
(78, '1gj20gfk00f3', 11212, 'failed', '2015-11-17', '', ''),
(79, '1gj120gfk00f3', 11212, 'failed', '2015-11-17', '', ''),
(80, '1g0j120gfk00f3', 11212, 'failed', '2015-11-17', '', ''),
(81, '1g0j120gf0k00f3', 11212, 'failed', '2015-11-17', '', ''),
(82, '1g0j120jgf0k00f3', 11212, 'done', '2015-11-17', 'Hello World!\nVM: 12652; RSS: 1060\n', ''),
(83, '1g0j120j0gf0k00f3', 11212, 'done', '2015-11-17', 'Hello World!\nVM: 12652; RSS: 1060\n', ''),
(84, '1g0j0120j0gf0k00f3', 11212, 'done', '2015-11-17', 'Hello World!\nVM: 12652; RSS: 1060\n', ''),
(85, '1g0juoioi0120j0gf0k00f3', 11212, 'failed', '2015-11-17', '', ''),
(86, '1g0juoioji0120j0gf0k00f3', 11212, 'failed', '2015-11-17', '', ''),
(88, '1gkhjk0juoioji0120j0gf0k00f3', 11212, 'done', '2015-11-17', 'Hello World!\nVM: 12652; RSS: 1056\n', ''),
(89, '1gkhjk0juoioji0120j0gf0k00f3', 112612, 'done', '2015-11-17', 'Hello World!\nVM: 12652; RSS: 1060\n', ''),
(90, '1gkhjkh0juoioji0120j0gf0k00f3', 112612, 'done', '2015-11-17', 'Hello World!\nVM: 12652; RSS: 1056\n', ''),
(91, '1gkhjk0h0juoioji0120j0gf0k00f3', 112612, 'done', '2015-11-17', 'Hello World!\nVM: 12652; RSS: 1060\n', ''),
(93, '1gkhj0k0h0juoioji0120j0gf0k00f3', 112612, 'done', '2015-11-17', 'Hello World!\nVM: 12652; RSS: 1056\n', ''),
(94, '1gkhhj0k0h0juoioji0120j0gf0k00f3', 112612, 'done', '2015-11-17', 'Hello World!\nVM: 12652; RSS: 1060\n', ''),
(95, '1gkhhjhj0k0h0juoioji0120j0gf0k00f3', 112612, 'done', '2015-11-17', 'Hello World!\nVM: 12652; RSS: 1060\n', ''),
(96, '1gkhhjghj0k0h0juoioji0120j0gf0k00f3', 112612, 'done', '2015-11-17', 'Hello World!\nVM: 12652; RSS: 1060\n', ''),
(97, '1gkhhgjghj0k0h0juoioji0120j0gf0k00f3', 112612, 'done', '2015-11-17', 'Hello World!\nVM: 12652; RSS: 1060\n', './src/code0.cpp:30:19: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(int  x,int  vasya){\n                  ^\n./src/code0.cpp:30:26: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(int  x,int  vasya){\n                         ^\n./src/code0.cpp:33:124: warning: control reaches end of non-void function [-Wreturn-type]\nusing std::cout;using std::endl;double vm, rss;process_mem_usage(vm, rss);cout << "VM: " << vm << "; RSS: " << rss << endl;}\n                                                                                                                           ^\n3 warnings generated.\n'),
(99, '1gkhhggjghj0k0h0juoioji0120j0gf0k00f3', 112612, 'done', '2015-11-17', 'Hello World!\n0OqweKHello World!\n', './src/code1.cpp:30:19: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(int  x,int  vasya){\n                  ^\n./src/code1.cpp:30:26: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(int  x,int  vasya){\n                         ^\n2 warnings generated.\n'),
(100, '1gkdhhggjghj0k0h0juoioji0120j0gf0k00f3', 112612, 'done', '2015-11-17', 'Hello World!\n0OqweKHello World!\nVM: 12652; RSS: 1056\n', './src/code0.cpp:30:19: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(int  x,int  vasya){\n                  ^\n./src/code0.cpp:30:26: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(int  x,int  vasya){\n                         ^\n2 warnings generated.\n'),
(101, '1gkdhhggjghj0k0h0juoioji0120j0gf0k00f3', 1126122, 'done', '2015-11-18', '@0@@1!@VM: 12652; RSS: 1060\n', './src/code0.cpp:30:19: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(int  x,int  vasya){\n                  ^\n./src/code0.cpp:30:26: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(int  x,int  vasya){\n                         ^\n2 warnings generated.\n'),
(102, '12401q223f4f2341', 11212, 'failed', '2015-11-19', '', './src/code3.cpp:32:52: error: expected '';'' after return statement\nstd::cout << "Hello World!" << std::endl; return 10\n                                                   ^\n                                                   ;\n./src/code3.cpp:30:19: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(int  x,int  vasya){\n                  ^\n./src/code3.cpp:30:26: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(int  x,int  vasya){\n                         ^\n2 warnings and 1 error generated.\n'),
(103, '12401gq223f4f2341', 11212, 'done', '2015-11-19', 'Hello World!\n@0@Hello World!\n@1!@VM: 12652; RSS: 1056\n', './src/code2.cpp:30:19: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(int  x,int  vasya){\n                  ^\n./src/code2.cpp:30:26: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(int  x,int  vasya){\n                         ^\n2 warnings generated.\n'),
(105, '12401hgq223f4f2341', 11212, 'failed', '2015-11-19', '', './src/code2.cpp:30:14: error: unknown type name ''string''; did you mean ''std::string''?\nint function(string  x,string  vasya){\n             ^~~~~~\n             std::string\n/usr/bin/../lib/gcc/x86_64-linux-gnu/4.8/../../../../include/c++/4.8/bits/stringfwd.h:62:33: note: ''std::string'' declared here\n  typedef basic_string<char>    string;   \n                                ^\n./src/code2.cpp:30:24: error: unknown type name ''string''; did you mean ''std::string''?\nint function(string  x,string  vasya){\n                       ^~~~~~\n                       std::string\n/usr/bin/../lib/gcc/x86_64-linux-gnu/4.8/../../../../include/c++/4.8/bits/stringfwd.h:62:33: note: ''std::string'' declared here\n  typedef basic_string<char>    string;   \n                                ^\n./src/code2.cpp:30:22: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(string  x,string  vasya){\n                     ^\n./src/code2.cpp:30:32: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(string  x,string  vasya){\n                               ^\n./src/code2.cpp:36:16: error: expected '')''\n == function(""2"\n               ^\n./src/code2.cpp:36:13: note: to match this ''(''\n == function(""2"\n            ^\n./src/code2.cpp:36:17: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n == function(""2"\n                ^\n./src/code2.cpp:38:1: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n"))\n^\n./src/code2.cpp:40:1: error: expected expression\nelse\n^\n./src/code2.cpp:43:16: error: expected '')''\n == function(""3"\n               ^\n./src/code2.cpp:43:13: note: to match this ''(''\n == function(""3"\n            ^\n./src/code2.cpp:43:17: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n == function(""3"\n                ^\n./src/code2.cpp:45:1: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n"))\n^\n./src/code2.cpp:47:1: error: expected expression\nelse\n^\n6 warnings and 6 errors generated.\nrm: cannot remove â€˜code2.cppâ€™: No such file or directory\n'),
(106, '1241q22k3f4f2341', 11212, 'failed', '2015-11-19', '', './src/code0.cpp:30:14: error: unknown type name ''string''; did you mean ''std::string''?\nint function(string  x,string  vasya){\n             ^~~~~~\n             std::string\n/usr/bin/../lib/gcc/x86_64-linux-gnu/4.8/../../../../include/c++/4.8/bits/stringfwd.h:62:33: note: ''std::string'' declared here\n  typedef basic_string<char>    string;   \n                                ^\n./src/code0.cpp:30:24: error: unknown type name ''string''; did you mean ''std::string''?\nint function(string  x,string  vasya){\n                       ^~~~~~\n                       std::string\n/usr/bin/../lib/gcc/x86_64-linux-gnu/4.8/../../../../include/c++/4.8/bits/stringfwd.h:62:33: note: ''std::string'' declared here\n  typedef basic_string<char>    string;   \n                                ^\n./src/code0.cpp:30:22: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(string  x,string  vasya){\n                     ^\n./src/code0.cpp:30:32: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(string  x,string  vasya){\n                               ^\n./src/code0.cpp:36:16: error: expected '')''\n == function(""2"\n               ^\n./src/code0.cpp:36:13: note: to match this ''(''\n == function(""2"\n            ^\n./src/code0.cpp:36:17: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n == function(""2"\n                ^\n./src/code0.cpp:38:1: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n"))\n^\n./src/code0.cpp:40:1: error: expected expression\nelse\n^\n./src/code0.cpp:43:16: error: expected '')''\n == function(""3"\n               ^\n./src/code0.cpp:43:13: note: to match this ''(''\n == function(""3"\n            ^\n./src/code0.cpp:43:17: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n == function(""3"\n                ^\n./src/code0.cpp:45:1: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n"))\n^\n./src/code0.cpp:47:1: error: expected expression\nelse\n^\n6 warnings and 6 errors generated.\nrm: cannot remove â€˜code0.cppâ€™: No such file or directory\n'),
(107, '1241q22k3fk4f2341', 11212, 'failed', '2015-11-19', '', './src/code1.cpp:31:19: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(int  x,string  vasya){\n                  ^\n./src/code1.cpp:31:29: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(int  x,string  vasya){\n                            ^\n./src/code1.cpp:34:1: warning: control reaches end of non-void function [-Wreturn-type]\n}\n^\n./src/code1.cpp:38:4: error: expected '')''\n,""20"\n   ^\n./src/code1.cpp:37:13: note: to match this ''(''\n == function(2\n            ^\n./src/code1.cpp:38:6: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n,""20"\n     ^\n./src/code1.cpp:39:1: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n"))\n^\n./src/code1.cpp:41:1: error: expected expression\nelse\n^\n./src/code1.cpp:45:4: error: expected '')''\n,""5"\n   ^\n./src/code1.cpp:44:13: note: to match this ''(''\n == function(3\n            ^\n./src/code1.cpp:45:5: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n,""5"\n    ^\n./src/code1.cpp:46:1: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n"))\n^\n./src/code1.cpp:48:1: error: expected expression\nelse\n^\n7 warnings and 4 errors generated.\nrm: cannot remove â€˜code1.cppâ€™: No such file or directory\n'),
(108, 'hfghgf', 11212, 'failed', '2015-11-19', '', './src/code0.cpp:31:19: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(int  x,string  vasya){\n                  ^\n./src/code0.cpp:31:29: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(int  x,string  vasya){\n                            ^\n./src/code0.cpp:34:1: warning: control reaches end of non-void function [-Wreturn-type]\n}\n^\n./src/code0.cpp:38:4: error: expected '')''\n,""20"\n   ^\n./src/code0.cpp:37:13: note: to match this ''(''\n == function(2\n            ^\n./src/code0.cpp:38:6: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n,""20"\n     ^\n./src/code0.cpp:39:1: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n"))\n^\n./src/code0.cpp:41:1: error: expected expression\nelse\n^\n./src/code0.cpp:45:4: error: expected '')''\n,""5"\n   ^\n./src/code0.cpp:44:13: note: to match this ''(''\n == function(3\n            ^\n./src/code0.cpp:45:5: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n,""5"\n    ^\n./src/code0.cpp:46:1: warning: missing terminating ''"'' character [-Winvalid-pp-token]\n"))\n^\n./src/code0.cpp:48:1: error: expected expression\nelse\n^\n7 warnings and 4 errors generated.\n'),
(109, 'hhfghgf', 11212, 'done', '2015-11-19', 'Hello World!\n', './src/code1.cpp:31:19: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(int  x,string  vasya){\n                  ^\n./src/code1.cpp:31:29: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(int  x,string  vasya){\n                            ^\n./src/code1.cpp:34:1: warning: control reaches end of non-void function [-Wreturn-type]\n}\n^\n3 warnings generated.\n'),
(110, 'hhfghfgf', 11212, 'done', '2015-11-19', 'Hello World!\n', './src/code3.cpp:31:19: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(int  x,string  vasya){\n                  ^\n./src/code3.cpp:31:29: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(int  x,string  vasya){\n                            ^\n./src/code3.cpp:34:1: warning: control reaches end of non-void function [-Wreturn-type]\n}\n^\n3 warnings generated.\n'),
(111, 'hhfghhfgf', 11212, 'done', '2015-11-19', 'Hello World!\n', './src/code3.cpp:30:19: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(int  x,int  vasya){\n                  ^\n./src/code3.cpp:30:26: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(int  x,int  vasya){\n                         ^\n./src/code3.cpp:33:1: warning: control reaches end of non-void function [-Wreturn-type]\n}\n^\n3 warnings generated.\n'),
(112, 'hhfghhfhgf', 11212, 'done', '2015-11-19', 'Hello World!\n@0@Hello World!\n@1!@VM: 12652; RSS: 1056\n', './src/code0.cpp:30:19: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(int  x,int  vasya){\n                  ^\n./src/code0.cpp:30:26: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(int  x,int  vasya){\n                         ^\n2 warnings generated.\n'),
(113, 'hhfgfhhfhgf', 11212, 'done', '2015-11-19', 'Hello World!\n@0!@Hello World!\n@1!@VM: 12652; RSS: 1060\n', './src/code2.cpp:30:19: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(int  x,int  vasya){\n                  ^\n./src/code2.cpp:30:26: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(int  x,int  vasya){\n                         ^\n2 warnings generated.\n'),
(115, 'hhfgfhhfhgf', 112142, 'done', '2015-11-19', 'Hello World!\n @0!@Hello World!\n @1!@VM: 12656; RSS: 1056\n', './src/code0.cpp:31:19: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(int  x,string  vasya){\n                  ^\n./src/code0.cpp:31:29: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(int  x,string  vasya){\n                            ^\n2 warnings generated.\n'),
(116, 'hhfgffhhfhgf', 112142, 'failed', '2015-11-19', '', './src/code1.cpp:33:50: error: cannot initialize return object of type ''int'' with an lvalue of type ''const char [8]''\nstd::cout << "Hello World!" << std::endl; return "gdfgfdg";\n                                                 ^~~~~~~~~\n./src/code1.cpp:31:19: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(int  x,string  vasya){\n                  ^\n./src/code1.cpp:31:29: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(int  x,string  vasya){\n                            ^\n2 warnings and 1 error generated.\n'),
(117, 'hhyfgffhhfhgf', 112142, 'done', '2015-11-19', 'Hello World!\n @0!@Hello World!\n @1!@VM: 12656; RSS: 1060\n', './src/code3.cpp:31:19: warning: unused parameter ''x'' [-Wunused-parameter]\nint function(int  x,string  vasya){\n                  ^\n./src/code3.cpp:31:29: warning: unused parameter ''vasya'' [-Wunused-parameter]\nint function(int  x,string  vasya){\n                            ^\n2 warnings generated.\n'),
(118, '1241q223f4f2341', 113212, 'failed', '2015-11-21', '', './src/code0.cpp:33:21: warning: unused parameter ''x'' [-Wunused-parameter]\nfloat function(int  x,string  vasya){\n                    ^\n./src/code0.cpp:33:31: warning: unused parameter ''vasya'' [-Wunused-parameter]\nfloat function(int  x,string  vasya){\n                              ^\n./src/code0.cpp:42:2: error: expected expression\n == function(2\n ^\n./src/code0.cpp:48:8: error: expected expression\nif ( <U+000C> == function(3\n              ^\n2 warnings and 2 errors generated.\n'),
(119, '1241q2223f4f2341', 11212, 'done', '2015-11-21', 'Hello World!\n @0!@Hello World!\n @1!@VM: 12656; RSS: 1060\n', './src/code3.cpp:33:21: warning: unused parameter ''x'' [-Wunused-parameter]\nfloat function(int  x,string  vasya){\n                    ^\n./src/code3.cpp:33:31: warning: unused parameter ''vasya'' [-Wunused-parameter]\nfloat function(int  x,string  vasya){\n                              ^\n2 warnings generated.\n'),
(120, '1241q21223f4f2341', 11212, 'done', '2015-11-21', 'Hello World!\n @0@Hello World!\n @1!@VM: 12656; RSS: 1060\n', './src/code2.cpp:33:21: warning: unused parameter ''x'' [-Wunused-parameter]\nfloat function(int  x,string  vasya){\n                    ^\n./src/code2.cpp:33:31: warning: unused parameter ''vasya'' [-Wunused-parameter]\nfloat function(int  x,string  vasya){\n                              ^\n2 warnings generated.\n'),
(121, '12412q223f4f2341', 11212, 'done', '2015-11-21', 'Hello World!\n @0!@Hello World!\n @1@VM: 12656; RSS: 1060\n', './src/code1.cpp:33:21: warning: unused parameter ''x'' [-Wunused-parameter]\nfloat function(int  x,string  vasya[]){\n                    ^\n./src/code1.cpp:33:31: warning: unused parameter ''vasya'' [-Wunused-parameter]\nfloat function(int  x,string  vasya[]){\n                              ^\n2 warnings generated.\n'),
(122, 'qwe', 123, 'done', '2015-11-21', 'Hello World!\n @0@VM: 12656; RSS: 1056\n', './src/code3.cpp:33:37: warning: unused parameter ''vasya'' [-Wunused-parameter]\nfloat * function(float  x[],string  vasya[]){\n                                    ^\n1 warning generated.\n'),
(123, 'qewe', 123, 'failed', '2015-11-21', '', './src/code1.cpp:35:50: error: use of undeclared identifier ''y''\nstd::cout << "Hello World!" << std::endl; return y;\n                                                 ^\n./src/code1.cpp:33:25: warning: unused parameter ''x'' [-Wunused-parameter]\nfloat * function(float  x[],string  vasya[]){\n                        ^\n./src/code1.cpp:33:37: warning: unused parameter ''vasya'' [-Wunused-parameter]\nfloat * function(float  x[],string  vasya[]){\n                                    ^\n2 warnings and 1 error generated.\n'),
(124, '1qewe', 123, 'failed', '2015-11-21', '', './src/code0.cpp:35:50: error: cannot initialize return object of type ''float *'' with an lvalue of type ''string *'' (aka ''basic_string<char> *'')\nstd::cout << "Hello World!" << std::endl; return vasya;\n                                                 ^~~~~\n./src/code0.cpp:33:25: warning: unused parameter ''x'' [-Wunused-parameter]\nfloat * function(float  x[],string  vasya[]){\n                        ^\n1 warning and 1 error generated.\n'),
(125, '1qegwe', 123, 'done', '2015-11-21', 'Hello World!\n', './src/code2.cpp:33:37: warning: unused parameter ''vasya'' [-Wunused-parameter]\nfloat * function(float  x[],string  vasya[]){\n                                    ^\n./src/code2.cpp:35:56: warning: division by zero is undefined [-Wdivision-by-zero]\nstd::cout << "Hello World!" << std::endl; int k = 5; k /=0; return x;\n                                                       ^ ~\n2 warnings generated.\n'),
(126, '1fqegwe', 123, 'done', '2015-11-21', 'Hello World!\nFloating point exception\n', './src/code3.cpp:33:37: warning: unused parameter ''vasya'' [-Wunused-parameter]\nfloat * function(float  x[],string  vasya[]){\n                                    ^\n./src/code3.cpp:35:56: warning: division by zero is undefined [-Wdivision-by-zero]\nstd::cout << "Hello World!" << std::endl; int k = 5; k /=0; return x;\n                                                       ^ ~\n2 warnings generated.\n'),
(127, '1fqeggwe', 123, 'done', '2015-11-21', 'Hello World!\n @0@VM: 12656; RSS: 1056\n', './src/code2.cpp:33:37: warning: unused parameter ''vasya'' [-Wunused-parameter]\nfloat * function(float  x[],string  vasya[]){\n                                    ^\n1 warning generated.\n');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
