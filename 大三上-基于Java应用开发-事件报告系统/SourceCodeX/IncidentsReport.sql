-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- 主机: localhost
-- 生成日期: 2018-01-06 10:08:45
-- 服务器版本: 5.5.53-0ubuntu0.14.04.1
-- PHP 版本: 5.5.9-1ubuntu4.20

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- 数据库: `IncidentsReport`
--

-- --------------------------------------------------------

--
-- 表的结构 `INCIDENTS`
--

CREATE TABLE IF NOT EXISTS `INCIDENTS` (
  `IID` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Incident ID',
  `ITYPE` text COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'Incident Type',
  `IREPORTTIME` datetime NOT NULL COMMENT 'Reported  Date time',
  `ICREDIT` text COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'Incidents Credibility: no,unsure,yes',
  `IDESCRIPTION` text COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'Description',
  `IWHOADD` int(11) NOT NULL COMMENT 'Who add this',
  `ILOCATION` text COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'Address typed',
  `LAT` double NOT NULL COMMENT '经度',
  `LNG` double NOT NULL COMMENT '纬度',
  PRIMARY KEY (`IID`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Incidents tables, stores incidents'' infomation' AUTO_INCREMENT=105 ;

--
-- 转存表中的数据 `INCIDENTS`
--

INSERT INTO `INCIDENTS` (`IID`, `ITYPE`, `IREPORTTIME`, `ICREDIT`, `IDESCRIPTION`, `IWHOADD`, `ILOCATION`, `LAT`, `LNG`) VALUES
(1, '/IncidentsReport/static/icons/car_stolen', '2017-12-11 07:41:45', '4', '测试事件，事件类型：lie欺诈。', 1, '11@11', 39.905764575757956, 116.38041905273438),
(2, '/IncidentsReport/static/icons/violence', '2017-12-20 13:00:46', '3', 'test incidents', 1, 'beijing', 39.92011636082244, 116.45114354003907),
(3, '/IncidentsReport/static/icons/fire', '2017-12-12 07:41:45', '1', '测试事件，事件类型：火灾。', 1, 'beijing', 39.80011636082244, 116.80114354003906),
(4, '/IncidentsReport/static/icons/kidnapping', '2017-12-13 07:41:45', '1', '测试事件，事件类型：绑架。', 1, 'beijing', 39.99011636082244, 116.99114354003908),
(5, '/IncidentsReport/static/icons/robbery', '2017-12-14 07:41:45', '1', '测试事件，事件类型：抢劫。', 1, 'beijing', 39.66011636082244, 116.66114354003906),
(7, '/IncidentsReport/static/icons/car_stolen', '2017-12-16 07:41:45', '1', '测试事件，事件类型：车辆偷窃。', 2, 'beijing', 39.37011636082244, 116.21114354003907),
(9, '/IncidentsReport/static/icons/fire', '2017-12-12 07:41:45', '1', '测试事件，事件类型：火灾。', 1, 'beijing', 39.22011636082244, 116.21114354003907),
(10, '/IncidentsReport/static/icons/kidnapping', '2017-12-13 07:41:45', '1', '测试事件，事件类型：绑架。', 1, 'beijing', 39.38011636082244, 116.43114354003907),
(11, '/IncidentsReport/static/icons/robbery', '2017-12-14 07:41:45', '1', '测试事件，事件类型：抢劫。', 1, 'beijing', 39.77011636082244, 116.43114354003907),
(12, '/IncidentsReport/static/icons/stolen', '2017-12-15 07:41:45', '1', '测试事件，事件类型：偷窃。', 2, 'beijing', 39.68011636082244, 116.86114354003907),
(13, '/IncidentsReport/static/icons/car_stolen', '2017-12-16 07:41:45', '1', '测试事件，事件类型：车辆偷窃。', 1, 'beijing', 39.02011636082244, 116.21114354003907),
(14, '/IncidentsReport/static/icons/lie', '2017-12-17 07:41:45', '1', '测试事件，事件类型：欺诈。', 2, 'beijing', 39.80011636082244, 116.80114354003906),
(15, '/IncidentsReport/static/icons/fire', '2017-12-12 07:41:45', '1', '测试事件，事件类型：火灾。', 1, 'beijing', 39.97011636082244, 116.45114354003907),
(16, '/IncidentsReport/static/icons/kidnapping', '2017-12-13 07:41:45', '1', '测试事件，事件类型：绑架。', 1, 'beijing', 39.98011636082244, 116.15114354003907),
(17, '/IncidentsReport/static/icons/robbery', '2017-12-14 07:41:45', '1', '测试事件，事件类型：抢劫。', 2, 'beijing', 39.70011636082244, 116.45114354003907),
(18, '/IncidentsReport/static/icons/lie', '2017-12-15 00:00:00', '2', '??????', 1, 'no location', 39.8992015115692, 116.39808654785156),
(19, '/IncidentsReport/static/icons/stolen', '2017-11-09 00:00:00', '1', '????', 1, 'no location', 39.9113163032711, 116.37216567993164),
(20, '/IncidentsReport/static/icons/car_stolen', '2017-10-11 00:00:00', '1', '?????', 1, 'no location', 39.884977066231485, 116.41542434692383),
(21, '/IncidentsReport/static/icons/violence', '2017-07-04 00:00:00', '6', '????', 1, 'no location', 39.9046871768698, 116.40693247318268),
(22, '/IncidentsReport/static/icons/robbery', '2017-11-08 00:00:00', '1', 'asdasdasd', 1, 'no location', 30.643561323685418, 104.0654182434082),
(23, '/IncidentsReport/static/icons/lie', '2017-05-27 00:00:00', '1', '??2.00?5.00????????????????????', 1, 'no location', 30.65725857159338, 104.0581226348877),
(24, '/IncidentsReport/static/icons/stolen', '2017-11-24 00:00:00', '1', '??????????', 1, 'no location', 30.674165165871326, 104.14429664611816),
(25, '/IncidentsReport/static/icons/violence', '2017-02-09 00:00:00', '1', '????????????21???', 1, 'no location', 30.628902011959713, 104.1423225402832),
(26, '/IncidentsReport/static/icons/fire', '2017-07-20 00:00:00', '1', '???????????????????????', 1, 'no location', 30.644853599775775, 104.12361145019531),
(27, '/IncidentsReport/static/icons/car_stolen', '2016-07-20 00:00:00', '1', '????????????"?A ET209"', 1, 'no location', 30.661245545931028, 104.19116020202637),
(28, '/IncidentsReport/static/icons/car_stolen', '2016-10-17 00:00:00', '1', '????????????"?A C65OX"', 1, 'no location', 30.659768907945107, 104.1932201385498),
(29, '/IncidentsReport/static/icons/car_stolen', '2017-08-03 00:00:00', '1', '????????????"?B OX0FF"', 1, 'no location', 30.66471555639119, 104.19828414916992),
(30, '/IncidentsReport/static/icons/stolen', '2017-05-27 00:00:00', '1', '????50000', 1, 'no location', 30.65290224496248, 104.18060302734375),
(31, '/IncidentsReport/static/icons/stolen', '2016-11-23 00:00:00', '1', '????20000', 1, 'no location', 30.650096371333856, 104.17545318603516),
(32, '/IncidentsReport/static/icons/violence', '2017-10-23 00:00:00', '1', '?????????????????', 1, 'no location', 30.643524401257704, 104.18686866760254),
(33, '/IncidentsReport/static/icons/violence', '2017-06-08 00:00:00', '1', '????????3?????4???', 1, 'no location', 30.69564482276698, 104.12103652954102),
(34, '/IncidentsReport/static/icons/violence', '2017-09-05 00:00:00', '1', '???????????????????????', 1, 'no location', 30.69564482276698, 104.11571502685547),
(35, '/IncidentsReport/static/icons/fire', '2017-12-12 00:00:00', '1', '??????????????????????????????', 1, 'no location', 30.67575231430012, 104.04177188873291),
(36, '/IncidentsReport/static/icons/fire', '2016-10-21 00:00:00', '1', '???????????????????3????????', 1, 'no location', 30.643598246099064, 104.02585029602051),
(37, '/IncidentsReport/static/icons/stolen', '2017-10-18 00:00:00', '1', '????', 1, 'no location', 39.91849199010344, 116.39688491821289),
(38, '/IncidentsReport/static/icons/lie', '2017-03-17 00:00:00', '1', '????????????????', 1, 'no location', 30.691530103906754, 104.03881072998047),
(39, '/IncidentsReport/static/icons/kidnapping', '2017-09-09 00:00:00', '1', '?????', 1, 'no location', 30.579368875982034, 103.98250579833984),
(40, '/IncidentsReport/static/icons/kidnapping', '2017-09-20 00:00:00', '1', '?????', 1, 'no location', 30.578740776576073, 103.98207664489746),
(41, '/IncidentsReport/static/icons/violence', '2016-08-19 00:00:00', '1', '????????????2???', 1, 'no location', 30.69948260870118, 104.07159805297852),
(42, '/IncidentsReport/static/icons/fire', '2017-08-26 00:00:00', '1', 'dtgsdgsdg', 1, 'no location', 30.63429335209255, 104.12283897399902),
(43, '/IncidentsReport/static/icons/kidnapping', '2017-01-23 00:00:00', '1', 'jfghfvfdhggfd', 1, 'no location', 30.630600685784238, 104.10953521728516),
(44, '/IncidentsReport/static/icons/robbery', '2017-12-12 00:00:00', '1', 'uyityyrevgvxcjyvcbh', 1, 'no location', 30.608293985491734, 104.10687446594238),
(45, '/IncidentsReport/static/icons/stolen', '2016-04-11 00:00:00', '1', 'xvfuutfjvhfdhg', 1, 'no location', 30.619447978140055, 104.0969181060791),
(46, '/IncidentsReport/static/icons/stolen', '2016-07-09 00:00:00', '1', 'jfgjfdgsdfgsd', 1, 'no location', 30.617453649947834, 104.07554626464844),
(47, '/IncidentsReport/static/icons/stolen', '2017-05-13 00:00:00', '1', 'tuyfggsdjhjvc', 1, 'no location', 30.618340023105336, 104.07374382019043),
(48, '/IncidentsReport/static/icons/violence', '2017-07-10 00:00:00', '1', 'fjhuijfgxcyuc', 1, 'no location', 30.696530479220755, 104.05305862426758),
(49, '/IncidentsReport/static/icons/violence', '2017-04-10 00:00:00', '1', 'tyixcbfgkxcvfdh', 1, 'no location', 30.70767429496847, 104.10670280456543),
(50, '/IncidentsReport/static/icons/lie', '2017-12-21 00:00:00', '1', 'yiuypinaasaavfdh', 1, 'no location', 30.658809081156228, 104.05814409255981),
(51, '/IncidentsReport/static/icons/stolen', '2017-06-19 00:00:00', '1', 'sfsdufdjghsdh', 1, 'no location', 30.654895842529413, 104.05026912689209),
(52, '/IncidentsReport/static/icons/robbery', '2017-06-19 00:00:00', '1', 'werwetrtsdh', 1, 'no location', 30.66360811978141, 104.05376672744751),
(53, '/IncidentsReport/static/icons/fire', '2017-11-10 00:00:00', '1', '?????', 1, 'no location', 39.89999167197871, 116.43104553222656),
(54, '/IncidentsReport/static/icons/stolen', '2017-11-30 00:00:00', '1', 'gungang', 1, 'no location', 39.90960456049752, 116.3851261138916),
(55, '/IncidentsReport/static/icons/car_stolen', '2017-12-24 00:00:00', '1', '????', 1, 'no location', 29.546430526534465, 106.54541015625),
(56, '/IncidentsReport/static/icons/car_stolen', '2017-12-24 00:00:00', '1', '????', 1, 'no location', 29.524774210786724, 106.48841857910156),
(57, '/IncidentsReport/static/icons/car_stolen', '2017-12-24 00:00:00', '1', '????', 1, 'no location', 29.532690505360033, 106.5618896484375),
(58, '/IncidentsReport/static/icons/fire', '2017-12-24 00:00:00', '1', 'FIRE', 1, 'no location', 29.560616632054543, 106.46987915039062),
(59, '/IncidentsReport/static/icons/fire', '2017-12-25 00:00:00', '1', 'FIRE', 1, 'no location', 29.590177059879466, 106.48052215576172),
(60, '/IncidentsReport/static/icons/fire', '2017-12-25 00:00:00', '1', 'FIRE', 1, 'no location', 29.577338745386907, 106.45133972167969),
(61, '/IncidentsReport/static/icons/stolen', '2017-12-25 00:00:00', '1', 'STEAL', 1, 'no location', 29.528956481341062, 106.60789489746094),
(62, '/IncidentsReport/static/icons/stolen', '2017-12-25 00:00:00', '1', 'STEAL', 1, 'no location', 29.719961119342205, 106.6556167602539),
(63, '/IncidentsReport/static/icons/stolen', '2017-12-26 00:00:00', '1', 'STEAL', 1, 'no location', 29.666575993156652, 106.51657104492188),
(64, '/IncidentsReport/static/icons/lie', '2017-12-26 00:00:00', '1', 'deceit', 1, 'no location', 29.50236624615108, 106.58111572265625),
(65, '/IncidentsReport/static/icons/lie', '2017-12-26 00:00:00', '1', 'deceit', 1, 'no location', 29.598909166010046, 106.56515121459961),
(66, '/IncidentsReport/static/icons/lie', '2017-12-26 00:00:00', '1', 'deceit', 1, 'no location', 29.588609678776056, 106.46713256835938),
(67, '/IncidentsReport/static/icons/robbery', '2017-12-27 00:00:00', '1', ' loot', 1, 'no location', 29.588982866961384, 106.3253402709961),
(68, '/IncidentsReport/static/icons/robbery', '2017-12-27 00:00:00', '1', ' loot', 1, 'no location', 29.608088257406806, 106.30268096923828),
(69, '/IncidentsReport/static/icons/robbery', '2017-12-27 00:00:00', '1', ' loot', 1, 'no location', 29.623907169060086, 106.47777557373047),
(70, '/IncidentsReport/static/icons/kidnapping', '2017-12-28 00:00:00', '1', ' kidnap', 1, 'no location', 29.561960475613336, 106.5512466430664),
(71, '/IncidentsReport/static/icons/kidnapping', '2017-12-28 00:00:00', '1', ' kidnap', 1, 'no location', 29.552702524053675, 106.50146484375),
(72, '/IncidentsReport/static/icons/kidnapping', '2017-12-28 00:00:00', '1', ' kidnap', 1, 'no location', 29.574950041590508, 106.50644302368164),
(73, '/IncidentsReport/static/icons/violence', '2017-12-29 00:00:00', '1', 'kill', 1, 'no location', 29.567634284650865, 106.43709182739258),
(74, '/IncidentsReport/static/icons/violence', '2017-12-29 00:00:00', '1', 'kill', 1, 'no location', 29.559422089438876, 106.42919540405273),
(75, '/IncidentsReport/static/icons/violence', '2017-12-29 00:00:00', '1', 'kill', 1, 'no location', 29.52148801976878, 106.43692016601562),
(76, '/IncidentsReport/static/icons/car_stolen', '2017-12-30 00:00:00', '1', 'CAR STEAL', 1, 'no location', 29.517006678192384, 106.40344619750977),
(77, '/IncidentsReport/static/icons/fire', '2017-12-30 00:00:00', '1', 'FIRE', 1, 'no location', 29.57300917814079, 106.43194198608398),
(78, '/IncidentsReport/static/icons/violence', '2017-12-30 00:00:00', '1', 'KILL', 1, 'no location', 29.622713375554913, 106.5127944946289),
(79, '/IncidentsReport/static/icons/robbery', '2017-12-31 00:00:00', '1', 'loot', 1, 'no location', 29.652553969285417, 106.53528213500977),
(80, '/IncidentsReport/static/icons/robbery', '2017-12-31 00:00:00', '1', 'loot', 1, 'no location', 29.64792925635822, 106.58866882324219),
(81, '/IncidentsReport/static/icons/kidnapping', '2017-12-31 00:00:00', '1', 'hunt', 1, 'no location', 29.620474974612414, 106.59399032592773),
(82, '/IncidentsReport/static/icons/car_stolen', '2018-01-01 00:00:00', '1', 'car steal', 1, 'no location', 29.58166812695672, 106.59536361694336),
(83, '/IncidentsReport/static/icons/car_stolen', '2018-01-01 00:00:00', '1', 'car steal', 1, 'no location', 29.554494451851024, 106.62643432617188),
(84, '/IncidentsReport/static/icons/car_stolen', '2018-01-01 00:00:00', '1', 'car steal', 1, 'no location', 29.530151384025547, 106.6798210144043),
(85, '/IncidentsReport/static/icons/stolen', '2018-01-02 00:00:00', '1', 'into', 1, 'no location', 29.5059518538504, 106.66574478149414),
(86, '/IncidentsReport/static/icons/stolen', '2018-01-02 00:00:00', '1', 'into', 1, 'no location', 29.46889445277982, 106.62866592407227),
(87, '/IncidentsReport/static/icons/stolen', '2018-01-02 00:00:00', '1', 'into', 1, 'no location', 29.441391496603618, 106.61201477050781),
(88, '/IncidentsReport/static/icons/fire', '2018-01-03 00:00:00', '1', 'fire', 1, 'no location', 29.41103991374144, 106.56377792358398),
(89, '/IncidentsReport/static/icons/fire', '2018-01-03 00:00:00', '1', 'fire', 1, 'no location', 29.349112533154784, 106.52755737304688),
(90, '/IncidentsReport/static/icons/fire', '2018-01-03 00:00:00', '1', 'fire', 1, 'no location', 29.32965896558007, 106.48275375366211),
(91, '/IncidentsReport/static/icons/violence', '2018-01-04 00:00:00', '1', 'kill', 1, 'no location', 29.29822613160104, 106.3751220703125),
(92, '/IncidentsReport/static/icons/violence', '2018-01-04 00:00:00', '1', 'kill', 1, 'no location', 29.29388464613594, 106.34679794311523),
(93, '/IncidentsReport/static/icons/violence', '2018-01-04 00:00:00', '1', 'kill', 1, 'no location', 29.307656998416473, 106.32362365722656),
(94, '/IncidentsReport/static/icons/kidnapping', '2018-01-05 00:00:00', '1', 'question', 1, 'no location', 29.48040162881694, 106.37134552001953),
(95, '/IncidentsReport/static/icons/kidnapping', '2018-01-05 00:00:00', '1', 'question', 1, 'no location', 29.491309823157533, 106.38748168945312),
(96, '/IncidentsReport/static/icons/kidnapping', '2018-01-05 00:00:00', '1', 'question', 1, 'no location', 29.490114461894493, 106.29426956176758),
(97, '/IncidentsReport/static/icons/kidnapping', '2018-01-03 00:00:00', '1', 'xyz', 1, 'no location', 40.44276659332214, 115.81787109375),
(98, '/IncidentsReport/static/icons/lie', '2018-01-24 00:00:00', '1', 'erds', 1, 'no location', 39.85072092501597, 115.938720703125),
(99, '/IncidentsReport/static/icons/violence', '2018-01-27 00:00:00', '1', 'wedwsd', 1, 'no location', 39.13006024213511, 117.3779296875),
(100, '/IncidentsReport/static/icons/violence', '2018-01-27 00:00:00', '1', 'wedwsd', 1, 'no location', 39.13006024213511, 117.3779296875),
(101, '/IncidentsReport/static/icons/violence', '2018-01-27 00:00:00', '1', 'wedwsd', 1, 'no location', 39.20671884491848, 116.9219970703125),
(102, '/IncidentsReport/static/icons/stolen', '2018-01-20 00:00:00', '1', 'sdfsdfsadfasdfasdfa', 1, 'no location', 39.91627207101115, 116.3223946094513),
(103, '/IncidentsReport/static/icons/stolen', '2018-01-20 00:00:00', '1', 'sdfsdfsadfasdfasdfa', 1, 'no location', 39.91627207101115, 116.3223946094513),
(104, '/IncidentsReport/static/icons/stolen', '2018-01-18 00:00:00', '1', 'dzvdzsvsdvs', 1, 'no location', 39.93127981799689, 116.4461624622345);

-- --------------------------------------------------------

--
-- 表的结构 `L2ADMIN`
--

CREATE TABLE IF NOT EXISTS `L2ADMIN` (
  `L2ID` int(11) NOT NULL AUTO_INCREMENT COMMENT 'L2admin ID',
  `L2USERNAME` text COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'L2 admin user name',
  `L2PASSWORD` text COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'L2 admin password',
  `L2STATUS` int(11) NOT NULL COMMENT 'L2 admin account status',
  PRIMARY KEY (`L2ID`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Stores data of level 2 admin' AUTO_INCREMENT=7 ;

--
-- 转存表中的数据 `L2ADMIN`
--

INSERT INTO `L2ADMIN` (`L2ID`, `L2USERNAME`, `L2PASSWORD`, `L2STATUS`) VALUES
(2, 'testl2', 'testl2', 1),
(5, 'test4', 'test4', 1),
(6, 'test3', 'test3', 1);

-- --------------------------------------------------------

--
-- 表的结构 `SYSADMIN`
--

CREATE TABLE IF NOT EXISTS `SYSADMIN` (
  `AID` int(11) NOT NULL AUTO_INCREMENT COMMENT 'system admin ID',
  `AUSERNAME` text COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'system admin username',
  `APASSWORD` text COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'system admin password',
  `ASTATUS` int(11) NOT NULL COMMENT 'account status',
  PRIMARY KEY (`AID`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='stores system admin data' AUTO_INCREMENT=9 ;

--
-- 转存表中的数据 `SYSADMIN`
--

INSERT INTO `SYSADMIN` (`AID`, `AUSERNAME`, `APASSWORD`, `ASTATUS`) VALUES
(1, 'dsa', 'dsa', 0),
(2, 'fdsf', 'fdsf', 0),
(3, 'hgd', 'hgd', 0),
(4, 'dfdf', 'dfdf', 0);

-- --------------------------------------------------------

--
-- 表的结构 `USERS`
--

CREATE TABLE IF NOT EXISTS `USERS` (
  `UID` int(11) NOT NULL AUTO_INCREMENT COMMENT 'User ID',
  `UEMAIL` text COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'user email',
  `USTATUS` int(11) NOT NULL COMMENT 'user status',
  `USUBSCRIABE` text COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'user scruabled data.',
  PRIMARY KEY (`UID`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='stores user data' AUTO_INCREMENT=11 ;

--
-- 转存表中的数据 `USERS`
--

INSERT INTO `USERS` (`UID`, `UEMAIL`, `USTATUS`, `USUBSCRIABE`) VALUES
(2, 'test@qq.com', 1, 'chengdu'),
(3, '470229194@qq.com', 0, 'chongqing'),
(4, '11', 0, '39.91485, 116.403765'),
(5, '', 0, '39.91485, 116.403765'),
(6, '470229194@qq.com', 0, '39.91485, 116.403765'),
(7, '123', 0, '39.91485, 116.403765'),
(8, '1899285028@qq.com', 0, '39.91485, 116.403765'),
(9, 'kanch@xyz.com', 0, '39.91485, 116.403765'),
(10, 'jameszhang@qq.com', 0, '39.91485, 116.403765');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
