-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jun 25, 2015 at 04:23 PM
-- Server version: 5.5.43-0ubuntu0.14.04.1
-- PHP Version: 5.5.9-1ubuntu4.9

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
-- Table structure for table `Assignment_CPP`
--

CREATE TABLE IF NOT EXISTS `Assignment_CPP` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(20) DEFAULT NULL,
  `header` varchar(512) DEFAULT NULL,
  `etalon` varchar(512) DEFAULT NULL,
  `footer` varchar(512) DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=8 ;

--
-- Dumping data for table `Assignment_CPP`
--

INSERT INTO `Assignment_CPP` (`ID`, `name`, `header`, `etalon`, `footer`) VALUES
(1, 'hello world', '#include <iostream> \r\n int main()\r\n {', 'std::cout << "Hello World!" << std::endl;', 'return 0;}'),
(2, 'pcount(): reports th', '#include <strstream>\r\n#include <iostream>\r\nusing namespace std;\r\nint main()\r\n{', ' char str[80];ostrstream outs(str, sizeof(str));\r\n  outs << "abcdefg ";\r\n  outs << 27 << " "  << 890.23;\r\n  outs << ends;  // null terminate\r\n  cout << "chars in outs: "<< outs.pcount(); // \r\n  cout << " " << str;', ' return 0;}'),
(3, 'cout: output hex', '#include <iostream>\r\n#include <iomanip>\r\nusing namespace std;\r\nint main() {', ' cout << hex << 100 << endl;  cout << setfill(''?'') << setw(10) << 2343.0;', 'return 0;}'),
(4, 'Set cout: hex and ba', '#include <iostream>\r\n#include <iomanip>\r\nusing namespace std;\r\nint main() {', 'cout.setf(ios::hex, ios::basefield);\r\n  cout << 100 << endl;                  // cout 100 in hex\r\n  cout.fill(''?'');\r\n  cout.width(10);\r\n  cout << 2343.0;', 'return 0;}'),
(5, 'cout: uppercase,show', '#include <iostream>\r\nusing namespace std;\r\nint main() {', 'cout.unsetf(ios::dec);\r\n  cout.setf(ios::uppercase | ios::showbase | ios::hex);\r\n  cout << 88 << ''\n'';\r\n  cout.unsetf(ios::uppercase);\r\n  cout << 88 << ''\n'';', 'return 0;}'),
(6, 'Defines your own ter', '#include <iostream>\r\n#include <cstdlib>\r\n#include <exception>\r\nusing namespace std;\r\nvoid myTerminator() {\r\n  cout << "Your own terminate handler\n";\r\n  abort();\r\n}\r\nint main() {', 'set_terminate(myTerminator);   \r\n  try {\r\n    cout << "Inside try block.";\r\n    throw 100; \r\n  }\r\n  catch (double i) { }', 'return 0;}'),
(7, 'javaDefault', 'class Main#NUM# \r\n{ \r\n    public static void main (String[] args)  \r\n   {  ', ' System.out.println ("Hello, world.");', '}}');

-- --------------------------------------------------------

--
-- Table structure for table `Assignment_JAVA`
--

CREATE TABLE IF NOT EXISTS `Assignment_JAVA` (
  `ID` int(11) NOT NULL DEFAULT '0',
  `name` varchar(20) DEFAULT NULL,
  `header` varchar(512) DEFAULT NULL,
  `etalon` varchar(512) DEFAULT NULL,
  `footer` varchar(512) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `Assignment_JAVA`
--

INSERT INTO `Assignment_JAVA` (`ID`, `name`, `header`, `etalon`, `footer`) VALUES
(0, 'hello wordl', 'class Main#NUM#\r\n{\r\npublic static void main(String args[])\r\n{', 'System.out.println("Hello World!");', '}\r\n}'),
(7, 'javaDefault', 'class Main#NUM# \r\n{ \r\n    public static void main (String[] args)  \r\n   {  ', ' System.out.println ("Hello, world.");', '}}');

-- --------------------------------------------------------

--
-- Table structure for table `History`
--

CREATE TABLE IF NOT EXISTS `History` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `ip` varchar(20) DEFAULT NULL,
  `code` varchar(512) DEFAULT NULL,
  `date_time` datetime DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=296 ;

--
-- Dumping data for table `History`
--

INSERT INTO `History` (`ID`, `ip`, `code`, `date_time`) VALUES
(1, '123', '123', '2015-06-02 00:00:00'),
(242, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-23 21:22:22'),
(243, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-23 21:26:37'),
(244, '127.0.0.1', 'System.out.println("Hello World!");', '2015-06-23 21:28:13'),
(245, '127.0.0.1', 'System.out.println("Hello World!");', '2015-06-23 21:57:14'),
(246, '127.0.0.1', 'System.out.println("Hello World!");', '2015-06-23 21:57:35'),
(247, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-24 19:02:44'),
(248, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-24 19:12:01'),
(249, '127.0.0.1', 'System.out.println("Hello World!");', '2015-06-24 19:21:22'),
(250, '127.0.0.1', 'System.out.println("Hello World!");', '2015-06-24 19:29:31'),
(251, '127.0.0.1', 'System.out.println("Hello World!");', '2015-06-24 19:29:58'),
(252, '127.0.0.1', ' System.out.println("Hello World!");   std::cout << "Hello World!" << std::endl;', '2015-06-25 15:23:59'),
(253, '127.0.0.1', ' System.out.println("Hello World!");   std::cout << "Hello World!" << std::endl;', '2015-06-25 15:28:13'),
(254, '127.0.0.1', ' System.out.println("Hello World!");   std::cout << "Hello World!" << std::endl;', '2015-06-25 15:28:23'),
(255, '127.0.0.1', ' System.out.println("Hello World!");   std::cout << "Hello World!" << std::endl;', '2015-06-25 15:28:27'),
(256, '127.0.0.1', ' System.out.println("Hello World!");   std::cout << "Hello World!" << std::endl;', '2015-06-25 15:28:28'),
(257, '127.0.0.1', ' System.out.println("Hello World!");   std::cout << "Hello World!" << std::endl;', '2015-06-25 15:28:29'),
(258, '127.0.0.1', ' System.out.println("Hello World!");   std::cout << "Hello World!" << std::endl;', '2015-06-25 15:28:29'),
(259, '127.0.0.1', ' System.out.println("Hello World!");   std::cout << "Hello World!" << std::endl;', '2015-06-25 15:28:30'),
(260, '127.0.0.1', ' System.out.println("Hello World!");   std::cout << "Hello World!" << std::endl;', '2015-06-25 15:28:31'),
(261, '127.0.0.1', ' System.out.println("Hello World!");   std::cout << "Hello World!" << std::endl;', '2015-06-25 15:28:31'),
(262, '127.0.0.1', ' System.out.println("Hello World!");   std::cout << "Hello World!" << std::endl;', '2015-06-25 15:28:32'),
(263, '127.0.0.1', ' System.out.println("Hello World!");   std::cout << "Hello World!" << std::endl;', '2015-06-25 15:28:33'),
(264, '127.0.0.1', ' System.out.println("Hello World!");   std::cout << "Hello World!" << std::endl;', '2015-06-25 15:28:33'),
(265, '127.0.0.1', ' System.out.println("Hello World!");   std::cout << "Hello World!" << std::endl;', '2015-06-25 15:28:34'),
(266, '127.0.0.1', ' System.out.println("Hello World!");   std::cout << "Hello World!" << std::endl;', '2015-06-25 15:28:35'),
(267, '127.0.0.1', 'std::cout << "Hello World!" << std::endl; //System.out.println("Hello World!");  ', '2015-06-25 15:31:50'),
(268, '127.0.0.1', ' System.out.println("Hello World!");   std::cout << "Hello World!" << std::endl;', '2015-06-25 15:33:05'),
(269, '127.0.0.1', ' System.out.println("Hello World!");   std::cout << "Hello World!" << std::endl;', '2015-06-25 15:43:34'),
(270, '127.0.0.1', ' System.out.println("Hello World!");   std::cout << "Hello World!" << std::endl;', '2015-06-25 15:46:26'),
(271, '127.0.0.1', ' System.out.println("Hello World!");   ', '2015-06-25 15:49:04'),
(272, '127.0.0.1', ' System.out.println("Hello World!"); 34  ', '2015-06-25 15:51:05'),
(273, '127.0.0.1', ' System.out.println("Hello World!"); 34  ', '2015-06-25 15:52:25'),
(274, '127.0.0.1', ' System.out.println("Hello World!"); 34  ', '2015-06-25 15:52:27'),
(275, '127.0.0.1', ' System.out.println("Hello World!"); 34  ', '2015-06-25 15:52:30'),
(276, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-06-25 15:54:34'),
(277, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-06-25 15:56:12'),
(278, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-06-25 15:56:14'),
(279, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-06-25 15:56:16'),
(280, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-06-25 15:56:17'),
(281, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-06-25 15:56:19'),
(282, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-06-25 15:56:26'),
(283, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-06-25 15:56:27'),
(284, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-06-25 15:56:29'),
(285, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-06-25 15:56:30'),
(286, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-06-25 16:09:14'),
(287, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-06-25 16:09:23'),
(288, '127.0.0.1', ' std::cout << "Hello World!" << std::endl;', '2015-06-25 16:09:25'),
(289, '127.0.0.1', ' std::cout << "Hello Worlda!" << std::endl;', '2015-06-25 16:09:37'),
(290, '127.0.0.1', ' System.out.println("Hello World!"); ', '2015-06-25 16:09:52'),
(291, '127.0.0.1', ' std::cout << "Hello Worlda!" << std::endl;', '2015-06-25 16:10:13'),
(292, '127.0.0.1', ' std::cout << "Hello Worlda!" << std::endl;', '2015-06-25 16:13:42'),
(293, '127.0.0.1', ' std::cout << "Hello Worlda!" << std::endl;', '2015-06-25 16:13:44'),
(294, '127.0.0.1', ' std::cout << "Hello Worlda!" << std::endl;', '2015-06-25 16:13:45'),
(295, '127.0.0.1', ' std::cout << "Hello Worlda!" << std::endl;', '2015-06-25 16:20:26');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
