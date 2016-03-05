-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Хост: localhost
-- Время создания: Мар 05 2016 г., 11:08
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
  `header` mediumtext,
  `etalon` mediumtext,
  `footer` mediumtext,
  `json` mediumtext NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=138 ;

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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=12 ;

-- --------------------------------------------------------

--
-- Структура таблицы `results`
--

CREATE TABLE IF NOT EXISTS `results` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `session` varchar(255) NOT NULL,
  `jobid` varchar(255) NOT NULL,
  `status` mediumtext NOT NULL,
  `date` date NOT NULL,
  `result` mediumtext NOT NULL,
  `warning` mediumtext NOT NULL,
  PRIMARY KEY (`id`,`session`(100)),
  UNIQUE KEY `SECONDY` (`session`,`jobid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=56 ;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
