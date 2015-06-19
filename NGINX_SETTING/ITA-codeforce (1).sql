-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jun 19, 2015 at 10:01 PM
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
-- Table structure for table `Assignment`
--

CREATE TABLE IF NOT EXISTS `Assignment` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(20) DEFAULT NULL,
  `header` varchar(512) DEFAULT NULL,
  `etalon` varchar(512) DEFAULT NULL,
  `footer` varchar(512) DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=7 ;

--
-- Dumping data for table `Assignment`
--

INSERT INTO `Assignment` (`ID`, `name`, `header`, `etalon`, `footer`) VALUES
(1, 'hello world', '#include <iostream> \r\n int main()\r\n {', 'std::cout << "Hello World!" << std::endl;', 'return 0;}'),
(2, 'pcount(): reports th', '#include <strstream>\r\n#include <iostream>\r\nusing namespace std;\r\nint main()\r\n{', ' char str[80];ostrstream outs(str, sizeof(str));\r\n  outs << "abcdefg ";\r\n  outs << 27 << " "  << 890.23;\r\n  outs << ends;  // null terminate\r\n  cout << "chars in outs: "<< outs.pcount(); // \r\n  cout << " " << str;', ' return 0;}'),
(3, 'cout: output hex', '#include <iostream>\r\n#include <iomanip>\r\nusing namespace std;\r\nint main() {', ' cout << hex << 100 << endl;  cout << setfill(''?'') << setw(10) << 2343.0;', 'return 0;}'),
(4, 'Set cout: hex and ba', '#include <iostream>\r\n#include <iomanip>\r\nusing namespace std;\r\nint main() {', 'cout.setf(ios::hex, ios::basefield);\r\n  cout << 100 << endl;                  // cout 100 in hex\r\n  cout.fill(''?'');\r\n  cout.width(10);\r\n  cout << 2343.0;', 'return 0;}'),
(5, 'cout: uppercase,show', '#include <iostream>\r\nusing namespace std;\r\nint main() {', 'cout.unsetf(ios::dec);\r\n  cout.setf(ios::uppercase | ios::showbase | ios::hex);\r\n  cout << 88 << ''\n'';\r\n  cout.unsetf(ios::uppercase);\r\n  cout << 88 << ''\n'';', 'return 0;}'),
(6, 'Defines your own ter', '#include <iostream>\r\n#include <cstdlib>\r\n#include <exception>\r\nusing namespace std;\r\nvoid myTerminator() {\r\n  cout << "Your own terminate handler\n";\r\n  abort();\r\n}\r\nint main() {', 'set_terminate(myTerminator);   \r\n  try {\r\n    cout << "Inside try block.";\r\n    throw 100; \r\n  }\r\n  catch (double i) { }', 'return 0;}');

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
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=75 ;

--
-- Dumping data for table `History`
--

INSERT INTO `History` (`ID`, `ip`, `code`, `date_time`) VALUES
(1, '127.0.0.1', 'fdgdfgdfgdf', '0000-00-00 00:00:00'),
(2, '127.0.0.1', 'fdgdfgdfgdf', '0000-00-00 00:00:00'),
(3, '127.0.0.1', 'fdgdfgdfgdf', '0000-00-00 00:00:00'),
(4, '127.0.0.1', 'fdgdfgdfgdf', '0000-00-00 00:00:00'),
(5, '127.0.0.1', 'fdgdfgdfgdf', '0000-00-00 00:00:00'),
(6, '127.0.0.1', 'fdgdfgdfgdf', '0000-00-00 00:00:00'),
(7, '127.0.0.1', 'fdgdfgdfgdf', '0000-00-00 00:00:00'),
(8, '127.0.0.1', 'fdgdfgdfgdf', '2015-06-19 18:52:28'),
(9, '127.0.0.1', 'fdgdfgdfgdf', '2015-06-19 18:52:29'),
(10, '127.0.0.1', 'fdgdfgdfgdf', '2015-06-19 18:52:29'),
(11, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 19:47:42'),
(12, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:11:27'),
(13, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:11:27'),
(14, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:11:28'),
(15, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:14:07'),
(16, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:14:08'),
(17, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:14:08'),
(18, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:14:09'),
(19, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:14:10'),
(20, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:15:36'),
(21, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:15:37'),
(22, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:15:38'),
(23, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:15:38'),
(24, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:16:37'),
(25, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:18:55'),
(26, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:18:56'),
(27, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:18:57'),
(28, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:18:57'),
(29, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:31:22'),
(30, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:31:24'),
(31, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:31:29'),
(32, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:31:30'),
(33, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:32:10'),
(34, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:32:53'),
(35, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:33:37'),
(36, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:34:29'),
(37, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:35:06'),
(38, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:35:07'),
(39, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:35:36'),
(40, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:37:21'),
(41, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:37:22'),
(42, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:37:41'),
(43, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:37:46'),
(44, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:37:53'),
(45, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:40:52'),
(46, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:40:53'),
(47, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:40:54'),
(48, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:49:17'),
(49, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:49:19'),
(50, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:49:20'),
(51, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:49:21'),
(52, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:49:22'),
(53, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:49:50'),
(54, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:52:44'),
(55, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:52:45'),
(56, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:52:45'),
(57, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:52:46'),
(58, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:52:49'),
(59, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:52:59'),
(60, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:53:01'),
(61, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:53:03'),
(62, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:53:07'),
(63, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:55:15'),
(64, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:55:20'),
(65, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:58:40'),
(66, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 20:59:23'),
(67, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 21:49:19'),
(68, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 21:49:29'),
(69, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 21:49:34'),
(70, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 21:49:41'),
(71, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 21:49:42'),
(72, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 21:49:44'),
(73, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 21:49:52'),
(74, '127.0.0.1', 'std::cout << "Hello World!" << std::endl;', '2015-06-19 21:50:57');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
