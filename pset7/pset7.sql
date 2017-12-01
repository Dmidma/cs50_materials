-- MySQL dump 10.13  Distrib 5.5.46, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.46-0ubuntu0.14.04.2-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `id` int(10) unsigned NOT NULL,
  `datetime` datetime NOT NULL,
  `transaction` varchar(4) COLLATE utf8_unicode_ci NOT NULL,
  `symbol` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(50) unsigned NOT NULL,
  `price` decimal(65,4) unsigned NOT NULL,
  PRIMARY KEY (`id`,`datetime`),
  CONSTRAINT `history_ibfk_1` FOREIGN KEY (`id`) REFERENCES `users` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
INSERT INTO `history` VALUES (6,'2015-12-03 07:08:54','BUY','FREE',10,0.0320),(6,'2015-12-03 07:10:52','BUY','FB',5,104.3800),(6,'2015-12-03 07:13:58','SELL','FREE',92,0.0300),(6,'2015-12-03 07:14:23','BUY','FREE',2,0.0300),(6,'2015-12-03 07:14:42','SELL','FB',5,104.3800),(6,'2015-12-03 07:14:49','SELL','FREE',2,0.0300),(6,'2015-12-03 07:14:57','SELL','GOOG',7,752.5400),(6,'2015-12-03 09:58:03','BUY','GOOG',5,752.5400),(6,'2015-12-03 09:58:38','BUY','GOOG',5,752.5400),(6,'2015-12-03 10:01:26','BUY','FREE',10,0.0300),(6,'2015-12-05 10:27:48','BUY','FB',3,106.1800),(6,'2015-12-05 10:28:38','BUY','FB',2,106.1800),(6,'2015-12-05 10:29:52','BUY','GOOG',1,766.8100),(6,'2015-12-05 10:49:50','BUY','FB',1,106.1800),(10,'2015-12-03 07:17:49','BUY','GOOG',10,752.5400),(10,'2015-12-03 07:17:58','BUY','FB',10,104.3800),(14,'2015-12-05 08:40:53','BUY','GOOG',5,766.8100),(14,'2015-12-05 08:43:32','BUY','GOOG',5,766.8100),(14,'2015-12-05 08:44:26','BUY','FB',2,106.1800),(15,'2015-12-05 08:47:16','BUY','FB',5,106.1800),(15,'2015-12-05 08:50:33','BUY','FB',3,106.1800),(15,'2015-12-05 08:52:37','BUY','FB',5,106.1800),(15,'2015-12-05 08:56:51','BUY','FB',2,106.1800),(15,'2015-12-05 09:01:06','BUY','FB',5,106.1800),(15,'2015-12-05 09:03:13','BUY','FB',5,106.1800),(15,'2015-12-05 09:04:05','BUY','FB',5,106.1800),(15,'2015-12-05 09:05:35','BUY','YHOO',2,34.9100),(15,'2015-12-05 09:06:20','BUY','FB',2,106.1800),(15,'2015-12-05 09:23:55','BUY','FB',2,106.1800),(15,'2015-12-05 09:25:40','BUY','FB',2,106.1800),(15,'2015-12-05 09:25:59','BUY','FB',2,106.1800),(15,'2015-12-05 09:26:45','BUY','YHOO',3,34.9100),(15,'2015-12-05 09:27:07','BUY','FB',3,106.1800),(15,'2015-12-05 09:28:00','BUY','FB',3,106.1800),(15,'2015-12-05 09:30:08','BUY','TWTR',5,25.0200),(15,'2015-12-05 09:31:25','BUY','TWTR',5,25.0200),(15,'2015-12-05 09:31:34','BUY','TWTR',5,25.0200),(15,'2015-12-05 09:31:47','BUY','FB',5,106.1800),(15,'2015-12-05 09:35:16','BUY','FB',3,106.1800),(15,'2015-12-05 09:37:56','BUY','FB',2,106.1800),(15,'2015-12-05 09:40:16','BUY','FB',2,106.1800),(15,'2015-12-05 09:41:41','BUY','FB',2,106.1800),(15,'2015-12-05 09:50:05','BUY','FB',2,106.1800),(15,'2015-12-05 09:52:11','BUY','FB',2,106.1800),(15,'2015-12-05 09:53:01','BUY','FB',2,106.1800),(15,'2015-12-05 10:02:56','BUY','FB',2,106.1800),(15,'2015-12-05 10:04:02','BUY','FB',2,106.1800),(15,'2015-12-05 10:04:53','BUY','FB',2,106.1800),(15,'2015-12-05 10:07:16','BUY','FB',3,106.1800),(15,'2015-12-05 10:27:26','BUY','FB',3,106.1800),(15,'2015-12-05 10:30:35','BUY','GOOG',3,766.8100),(15,'2015-12-05 10:31:45','BUY','GOOG',3,766.8100),(15,'2015-12-05 10:33:07','BUY','GOOG',5,766.8100),(15,'2015-12-05 10:49:26','BUY','FB',10,106.1800),(15,'2015-12-05 10:53:40','BUY','FB',20,106.1800),(16,'2015-12-05 11:58:44','BUY','FB',2,106.1800),(16,'2015-12-05 11:58:57','BUY','TWTR',2,25.0200),(16,'2015-12-05 11:59:10','BUY','GOOG',2,766.8100),(16,'2015-12-05 11:59:45','BUY','FB',2,106.1800),(16,'2015-12-06 12:00:01','SELL','GOOG',2,766.8100);
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stocks`
--

DROP TABLE IF EXISTS `stocks`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stocks` (
  `id` int(10) unsigned NOT NULL,
  `symbol` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`,`symbol`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stocks`
--

LOCK TABLES `stocks` WRITE;
/*!40000 ALTER TABLE `stocks` DISABLE KEYS */;
INSERT INTO `stocks` VALUES (6,'FB',1),(10,'FB',2),(15,'FB',32),(15,'GOOG',15),(16,'FB',4),(16,'TWTR',2);
/*!40000 ALTER TABLE `stocks` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `email` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'noemail',
  `hash` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'belindazeng','noemail','$1$50$oxJEDBo9KDStnrhtnSzir0',10000.0000),(2,'caesar','noemail','$1$50$GHABNWBNE/o4VL7QjmQ6x0',10000.0000),(3,'jharvard','noemail','$1$50$RX3wnAMNrGIbgzbRYrxM1/',10000.0000),(4,'malan','noemail','$1$50$lJS9HiGK6sphej8c4bnbX.',10000.0000),(5,'rob','noemail','$1$HA$l5llES7AEaz8ndmSo5Ig41',10000.0000),(6,'skroob','noemail','$1$50$euBi4ugiJmbpIbvTTfmfI.',65.3300),(7,'zamyla','noemail','$1$50$uwfqB45ANW.9.6qaQ.DcF.',10000.0000),(10,'Ali','noemail','$1$i0d8t0PR$N8KZhqwtcXWXy/1IlZJAI0',1430.8000),(14,'dmidma','noemail','$1$ytnsdJPM$NduZRcPv7qiQijJgZBET..',2119.5400),(15,'sa','noemail','$1$yEoUoEd3$PNYoeALuqxJSTklIArt5F/',999986358.5800),(16,'mou','noemail','$1$gZPOYM6A$GmktlzE74.jQ1GG8VxgmV.',9525.2400);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-12-06  0:07:31
