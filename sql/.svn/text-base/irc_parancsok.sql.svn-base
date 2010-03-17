DROP TABLE IF EXISTS `irc_parancsok`;
CREATE TABLE `irc_parancsok` (
  `guid` int(10) unsigned NOT NULL auto_increment,
  `parancs` varchar(21) NOT NULL default '',
  `hasznalata` text NOT NULL default '',
  PRIMARY KEY  (`guid`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `irc_parancsok` VALUES ('1', 'rang', 'Rang hasznalata: /mode <channel> <rang> <nev>');
INSERT INTO `irc_parancsok` VALUES ('2', 'nick', 'Nick csere használata: /nick <uj nev>');
INSERT INTO `irc_parancsok` VALUES ('3', 'kick', 'Kick hasznalata: /kick <channel> <nev> (<oka> nem feltetlen kell)');