# phpMyAdmin MySQL-Dump
# http://phpwizard.net/phpMyAdmin/
#
# Host: db Database : sourcebiz

USE sourcebiz

# --------------------------------------------------------
#
# Table structure for table 'active_sessions'
#

CREATE TABLE active_sessions (
   sid varchar(32) NOT NULL,
   name varchar(32) NOT NULL,
   val text,
   changed varchar(14) NOT NULL,
   PRIMARY KEY (name, sid),
   KEY changed (changed)
);


# --------------------------------------------------------
#
# Table structure for table 'auth_user'
#

CREATE TABLE auth_user (
   user_id varchar(32) NOT NULL,
   username varchar(32) NOT NULL,
   password varchar(32) NOT NULL,
   realname varchar(64) NOT NULL,
   email_usr varchar(128) NOT NULL,
   modification_usr timestamp(14),
   creation_usr timestamp(14),
   perms varchar(255),
   PRIMARY KEY (user_id),
   UNIQUE k_username (username)
);


# --------------------------------------------------------
#
# Table structure for table 'categories'
#

CREATE TABLE categories (
   catid bigint(20) unsigned DEFAULT '0' NOT NULL auto_increment,
   type varchar(64) NOT NULL,
   category varchar(64) NOT NULL,
   PRIMARY KEY (catid),
   UNIQUE catid (catid)
);


# --------------------------------------------------------
#
# Table structure for table 'comments'
#

CREATE TABLE comments (
   cmtid bigint(20) unsigned DEFAULT '0' NOT NULL auto_increment,
   entid_cmt bigint(20) unsigned DEFAULT '0' NOT NULL,
   user_cmt varchar(16) NOT NULL,
   subject_cmt varchar(128) NOT NULL,
   text_cmt blob NOT NULL,
   status_cmt char(1) NOT NULL,
   creation_cmt timestamp(14),
   PRIMARY KEY (cmtid)
);


# --------------------------------------------------------
#
# Table structure for table 'contact'
#

CREATE TABLE contact (
   conid bigint(20) unsigned DEFAULT '0' NOT NULL auto_increment,
   entid_con bigint(20) unsigned DEFAULT '0' NOT NULL,
   name_con varchar(255) NOT NULL,
   logo_con varchar(255),
   type_con varchar(64) NOT NULL,
   description_con text,
   address_con varchar(255) NOT NULL,
   country_con varchar(128) NOT NULL,
   state_con varchar(128) NOT NULL,
   city_con varchar(128) NOT NULL,
   zip_con varchar(16) NOT NULL,
   phone_con varchar(128) NOT NULL,
   fax_con varchar(128),
   email_con varchar(128) NOT NULL,
   homepage_con varchar(255) NOT NULL,
   status_con char(1) NOT NULL,
   modification_con timestamp(14),
   creation_con timestamp(14),
   PRIMARY KEY (conid),
   UNIQUE locid (conid)
);


# --------------------------------------------------------
#
# Table structure for table 'counter'
#

CREATE TABLE counter (
   entid bigint(20) unsigned DEFAULT '0' NOT NULL,
   ent_cnt int(11) DEFAULT '0' NOT NULL,
   homepage_cnt int(11) DEFAULT '0' NOT NULL,
   prf_cnt int(11) DEFAULT '0' NOT NULL,
   con_cnt int(11) DEFAULT '0' NOT NULL,
   svc_cnt int(11) DEFAULT '0' NOT NULL,
   pro_cnt int(11) DEFAULT '0' NOT NULL,
   sol_cnt int(11) DEFAULT '0' NOT NULL,
   cus_cnt int(11) DEFAULT '0' NOT NULL,
   new_cnt int(11) DEFAULT '0' NOT NULL,
   cmt_cnt int(11) DEFAULT '0' NOT NULL,
   UNIQUE entid (entid)
);


# --------------------------------------------------------
#
# Table structure for table 'counter_check'
#

CREATE TABLE counter_check (
   entid bigint(20) unsigned DEFAULT '0' NOT NULL,
   cnt_type varchar(20) NOT NULL,
   ipaddr varchar(15) DEFAULT '127.000.000.001' NOT NULL,
   creation_cnt timestamp(14)
);


# --------------------------------------------------------
#
# Table structure for table 'customers'
#

CREATE TABLE customers (
   cusid bigint(20) unsigned DEFAULT '0' NOT NULL auto_increment,
   entid_cus bigint(20) unsigned DEFAULT '0' NOT NULL,
   name_cus varchar(255) NOT NULL,
   description_cus text NOT NULL,
   homepage_cus varchar(255) NOT NULL,
   status_cus char(1) NOT NULL,
   modification_cus timestamp(14),
   creation_cus timestamp(14),
   PRIMARY KEY (cusid),
   UNIQUE cusid (cusid)
);


# --------------------------------------------------------
#
# Table structure for table 'enterprise'
#

CREATE TABLE enterprise (
   entid bigint(20) unsigned DEFAULT '0' NOT NULL auto_increment,
   name varchar(255) NOT NULL,
   logo varchar(255),
   short_profile text NOT NULL,
   homepage varchar(255) NOT NULL,
   user varchar(32) NOT NULL,
   status char(1) NOT NULL,
   modification timestamp(14),
   creation timestamp(14),
   PRIMARY KEY (entid),
   UNIQUE name (name),
   UNIQUE entid (entid)
);


# --------------------------------------------------------
#
# Table structure for table 'faq'
#

CREATE TABLE faq (
   faqid int(8) unsigned DEFAULT '0' NOT NULL auto_increment,
   language varchar(32) NOT NULL,
   question blob NOT NULL,
   answer blob NOT NULL,
   UNIQUE idx_2 (faqid)
);


# --------------------------------------------------------
#
# Table structure for table 'news'
#

CREATE TABLE news (
   newid bigint(20) unsigned DEFAULT '0' NOT NULL auto_increment,
   entid_new bigint(20) unsigned DEFAULT '0' NOT NULL,
   subject_new varchar(128) NOT NULL,
   text_new text NOT NULL,
   homepage_new varchar(255) NOT NULL,
   status_new char(1) NOT NULL,
   modification_new timestamp(14),
   creation_new timestamp(14),
   PRIMARY KEY (newid),
   UNIQUE newid (newid)
);
