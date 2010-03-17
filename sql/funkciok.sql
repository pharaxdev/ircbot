DROP TABLE IF EXISTS `funkciok`;
CREATE TABLE `funkciok` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `nev` varchar(21) NOT NULL default '',
  `status` varchar(10) NOT NULL default '',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=75 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `funkciok` VALUES ('1', 'reconnect', 'be');
INSERT INTO `funkciok` VALUES ('2', 'test', 'be');
INSERT INTO `funkciok` VALUES ('3', 'koszones', 'be');
INSERT INTO `funkciok` VALUES ('4', 'elkoszones', 'be');
INSERT INTO `funkciok` VALUES ('5', 'log', 'be');
INSERT INTO `funkciok` VALUES ('6', 'svn', 'be');