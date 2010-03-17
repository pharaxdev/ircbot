DROP TABLE IF EXISTS `szoveg`;
CREATE TABLE `szoveg` (
  `guid` int(10) unsigned NOT NULL auto_increment,
  `szoveg` varchar(255) NOT NULL default '',
  PRIMARY KEY  (`guid`)
) ENGINE=MyISAM AUTO_INCREMENT=75 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `szoveg` VALUES ('1', 'szoveg');