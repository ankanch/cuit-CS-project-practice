--------------------------------------------------------
--  File created - Wednesday-January-24-2018   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Sequence SEQ_AI_ADMIN
--------------------------------------------------------

   CREATE SEQUENCE  "DI"."SEQ_AI_ADMIN"  MINVALUE 1 MAXVALUE 9999999999999999999999999999 INCREMENT BY 1 START WITH 1 CACHE 20 NOORDER  NOCYCLE  NOKEEP  NOSCALE  GLOBAL ;
--------------------------------------------------------
--  DDL for Sequence SEQ_AI_CERTIFICATION
--------------------------------------------------------

   CREATE SEQUENCE  "DI"."SEQ_AI_CERTIFICATION"  MINVALUE 1 MAXVALUE 9999999999999999999999999999 INCREMENT BY 1 START WITH 1 CACHE 20 NOORDER  NOCYCLE  NOKEEP  NOSCALE  GLOBAL ;
--------------------------------------------------------
--  DDL for Sequence SEQ_AI_COLUMN
--------------------------------------------------------

   CREATE SEQUENCE  "DI"."SEQ_AI_COLUMN"  MINVALUE 1 MAXVALUE 9999999999999999999999999999 INCREMENT BY 1 START WITH 1 CACHE 20 NOORDER  NOCYCLE  NOKEEP  NOSCALE  GLOBAL ;
--------------------------------------------------------
--  DDL for Sequence SEQ_AI_CUSTOMIZED
--------------------------------------------------------

   CREATE SEQUENCE  "DI"."SEQ_AI_CUSTOMIZED"  MINVALUE 1 MAXVALUE 9999999999999999999999999999 INCREMENT BY 1 START WITH 1 CACHE 20 NOORDER  NOCYCLE  NOKEEP  NOSCALE  GLOBAL ;
--------------------------------------------------------
--  DDL for Sequence SEQ_AI_DATABASE
--------------------------------------------------------

   CREATE SEQUENCE  "DI"."SEQ_AI_DATABASE"  MINVALUE 1 MAXVALUE 9999999999999999999999999999 INCREMENT BY 1 START WITH 1 CACHE 20 NOORDER  NOCYCLE  NOKEEP  NOSCALE  GLOBAL ;
--------------------------------------------------------
--  DDL for Sequence SEQ_AI_REPORT
--------------------------------------------------------

   CREATE SEQUENCE  "DI"."SEQ_AI_REPORT"  MINVALUE 1 MAXVALUE 9999999999999999999999999999 INCREMENT BY 1 START WITH 1 CACHE 20 NOORDER  NOCYCLE  NOKEEP  NOSCALE  GLOBAL ;
--------------------------------------------------------
--  DDL for Sequence SEQ_AI_TABLE
--------------------------------------------------------

   CREATE SEQUENCE  "DI"."SEQ_AI_TABLE"  MINVALUE 1 MAXVALUE 9999999999999999999999999999 INCREMENT BY 1 START WITH 1 CACHE 20 NOORDER  NOCYCLE  NOKEEP  NOSCALE  GLOBAL ;
--------------------------------------------------------
--  DDL for Sequence SEQ_AI_USER
--------------------------------------------------------

   CREATE SEQUENCE  "DI"."SEQ_AI_USER"  MINVALUE 1 MAXVALUE 9999999999999999999999999999 INCREMENT BY 1 START WITH 1 CACHE 20 NOORDER  NOCYCLE  NOKEEP  NOSCALE  GLOBAL ;
--------------------------------------------------------
--  DDL for Table T_ANALYSIS_CUSTOMIZED
--------------------------------------------------------

  CREATE TABLE "DI"."T_ANALYSIS_CUSTOMIZED" 
   (	"AID" NUMBER(*,0), 
	"USERID" NUMBER(*,0), 
	"GENERATEDATE" DATE, 
	"DESCRIPTION" VARCHAR2(256 BYTE), 
	"SCRIPT" VARCHAR2(4000 BYTE)
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;

   COMMENT ON COLUMN "DI"."T_ANALYSIS_CUSTOMIZED"."AID" IS '自定义操作ID';
   COMMENT ON COLUMN "DI"."T_ANALYSIS_CUSTOMIZED"."USERID" IS '所属用户';
   COMMENT ON COLUMN "DI"."T_ANALYSIS_CUSTOMIZED"."GENERATEDATE" IS '建立日期';
   COMMENT ON COLUMN "DI"."T_ANALYSIS_CUSTOMIZED"."DESCRIPTION" IS '操作描述';
   COMMENT ON COLUMN "DI"."T_ANALYSIS_CUSTOMIZED"."SCRIPT" IS '操作脚本';
--------------------------------------------------------
--  DDL for Table T_DATABASE_CERTIFICATION
--------------------------------------------------------

  CREATE TABLE "DI"."T_DATABASE_CERTIFICATION" 
   (	"CID" NUMBER(*,0), 
	"USERID" NUMBER(*,0), 
	"DID" NUMBER(*,0), 
	"USERNAME" VARCHAR2(64 BYTE), 
	"PASSWORD" VARCHAR2(64 BYTE), 
	"PRIVILEGE" VARCHAR2(128 BYTE)
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;

   COMMENT ON COLUMN "DI"."T_DATABASE_CERTIFICATION"."CID" IS '凭证ID';
   COMMENT ON COLUMN "DI"."T_DATABASE_CERTIFICATION"."USERID" IS '所属用户';
   COMMENT ON COLUMN "DI"."T_DATABASE_CERTIFICATION"."DID" IS '关联数据库';
   COMMENT ON COLUMN "DI"."T_DATABASE_CERTIFICATION"."USERNAME" IS '访问账户';
   COMMENT ON COLUMN "DI"."T_DATABASE_CERTIFICATION"."PASSWORD" IS '访问密码';
   COMMENT ON COLUMN "DI"."T_DATABASE_CERTIFICATION"."PRIVILEGE" IS '权限列表';
--------------------------------------------------------
--  DDL for Table T_DATABASE_COLUMN
--------------------------------------------------------

  CREATE TABLE "DI"."T_DATABASE_COLUMN" 
   (	"COLID" NUMBER(*,0), 
	"TID" NUMBER(*,0), 
	"DID" NUMBER(*,0), 
	"USERID" NUMBER(*,0), 
	"COLUMNNAME" VARCHAR2(32 BYTE), 
	"DATATYPE" VARCHAR2(32 BYTE), 
	"ISPRIMARY" NUMBER(*,0), 
	"ISFOREIGNKEY" NUMBER(*,0), 
	"FOREIGNKEYREF" NUMBER(*,0)
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;

   COMMENT ON COLUMN "DI"."T_DATABASE_COLUMN"."COLID" IS '列ID';
   COMMENT ON COLUMN "DI"."T_DATABASE_COLUMN"."TID" IS '所属表';
   COMMENT ON COLUMN "DI"."T_DATABASE_COLUMN"."DID" IS '所属数据库';
   COMMENT ON COLUMN "DI"."T_DATABASE_COLUMN"."USERID" IS '所属用户';
   COMMENT ON COLUMN "DI"."T_DATABASE_COLUMN"."COLUMNNAME" IS '列名';
   COMMENT ON COLUMN "DI"."T_DATABASE_COLUMN"."DATATYPE" IS '列数据类型';
   COMMENT ON COLUMN "DI"."T_DATABASE_COLUMN"."ISPRIMARY" IS '是否为主键';
   COMMENT ON COLUMN "DI"."T_DATABASE_COLUMN"."ISFOREIGNKEY" IS '是否为外键';
   COMMENT ON COLUMN "DI"."T_DATABASE_COLUMN"."FOREIGNKEYREF" IS '外键引用列ID';
--------------------------------------------------------
--  DDL for Table T_DATABASE_INFO
--------------------------------------------------------

  CREATE TABLE "DI"."T_DATABASE_INFO" 
   (	"DID" NUMBER(*,0), 
	"USERID" NUMBER(*,0), 
	"NAME" VARCHAR2(128 BYTE), 
	"HOST" VARCHAR2(128 BYTE), 
	"ADDDATE" DATE, 
	"LASTVISIT" DATE
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;

   COMMENT ON COLUMN "DI"."T_DATABASE_INFO"."DID" IS '数据库ID';
   COMMENT ON COLUMN "DI"."T_DATABASE_INFO"."USERID" IS '所属用户';
   COMMENT ON COLUMN "DI"."T_DATABASE_INFO"."NAME" IS '数据库名';
   COMMENT ON COLUMN "DI"."T_DATABASE_INFO"."HOST" IS '数据库主机地址';
   COMMENT ON COLUMN "DI"."T_DATABASE_INFO"."ADDDATE" IS '添加日期';
   COMMENT ON COLUMN "DI"."T_DATABASE_INFO"."LASTVISIT" IS '上次访问时间';
--------------------------------------------------------
--  DDL for Table T_DATABASE_REPORT
--------------------------------------------------------

  CREATE TABLE "DI"."T_DATABASE_REPORT" 
   (	"RID" NUMBER(*,0), 
	"USERID" NUMBER(*,0), 
	"TITLE" VARCHAR2(64 BYTE), 
	"GENERATEDATE" DATE
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;

   COMMENT ON COLUMN "DI"."T_DATABASE_REPORT"."RID" IS '简报ID';
   COMMENT ON COLUMN "DI"."T_DATABASE_REPORT"."USERID" IS '所属用户';
   COMMENT ON COLUMN "DI"."T_DATABASE_REPORT"."TITLE" IS '简报标题';
   COMMENT ON COLUMN "DI"."T_DATABASE_REPORT"."GENERATEDATE" IS '生成日期';
--------------------------------------------------------
--  DDL for Table T_DATABASE_TABLE
--------------------------------------------------------

  CREATE TABLE "DI"."T_DATABASE_TABLE" 
   (	"TID" NUMBER(*,0), 
	"DID" NUMBER(*,0), 
	"USERID" NUMBER(*,0)
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;

   COMMENT ON COLUMN "DI"."T_DATABASE_TABLE"."TID" IS '表ID';
   COMMENT ON COLUMN "DI"."T_DATABASE_TABLE"."DID" IS '所属数据库';
   COMMENT ON COLUMN "DI"."T_DATABASE_TABLE"."USERID" IS '所属用户';
--------------------------------------------------------
--  DDL for Table T_DI_ADMIN
--------------------------------------------------------

  CREATE TABLE "DI"."T_DI_ADMIN" 
   (	"ADMINID" NUMBER(*,0), 
	"USERNAME" VARCHAR2(32 BYTE), 
	"PASSWORD" VARCHAR2(64 BYTE), 
	"EMAIL" VARCHAR2(128 BYTE), 
	"LASTLOGIN" DATE
   ) SEGMENT CREATION DEFERRED 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  TABLESPACE "USERS" ;

   COMMENT ON COLUMN "DI"."T_DI_ADMIN"."ADMINID" IS '管理员ID';
   COMMENT ON COLUMN "DI"."T_DI_ADMIN"."USERNAME" IS '管理员用户名';
   COMMENT ON COLUMN "DI"."T_DI_ADMIN"."PASSWORD" IS '管理员密码';
   COMMENT ON COLUMN "DI"."T_DI_ADMIN"."EMAIL" IS '管理员邮箱';
   COMMENT ON COLUMN "DI"."T_DI_ADMIN"."LASTLOGIN" IS '上次登录时间';
--------------------------------------------------------
--  DDL for Table T_DI_USER
--------------------------------------------------------

  CREATE TABLE "DI"."T_DI_USER" 
   (	"USERID" NUMBER(*,0), 
	"USERNAME" VARCHAR2(32 BYTE), 
	"PASSWORD" VARCHAR2(64 BYTE), 
	"STATUS" NUMBER(*,0), 
	"LASTLOGIN" DATE, 
	"EMAIL" VARCHAR2(32 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1
  BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;

   COMMENT ON COLUMN "DI"."T_DI_USER"."USERID" IS '用户ID';
   COMMENT ON COLUMN "DI"."T_DI_USER"."USERNAME" IS '用户名';
   COMMENT ON COLUMN "DI"."T_DI_USER"."PASSWORD" IS '用户密码';
   COMMENT ON COLUMN "DI"."T_DI_USER"."STATUS" IS '账户状态';
   COMMENT ON COLUMN "DI"."T_DI_USER"."LASTLOGIN" IS '上次登录时间';
   COMMENT ON COLUMN "DI"."T_DI_USER"."EMAIL" IS '用户邮箱';
REM INSERTING into DI.T_ANALYSIS_CUSTOMIZED
SET DEFINE OFF;
REM INSERTING into DI.T_DATABASE_CERTIFICATION
SET DEFINE OFF;
REM INSERTING into DI.T_DATABASE_COLUMN
SET DEFINE OFF;
REM INSERTING into DI.T_DATABASE_INFO
SET DEFINE OFF;
REM INSERTING into DI.T_DATABASE_REPORT
SET DEFINE OFF;
REM INSERTING into DI.T_DATABASE_TABLE
SET DEFINE OFF;
REM INSERTING into DI.T_DI_ADMIN
SET DEFINE OFF;
REM INSERTING into DI.T_DI_USER
SET DEFINE OFF;
--------------------------------------------------------
--  DDL for Index T_ANALYSIS_CUSTOMIZED_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DI"."T_ANALYSIS_CUSTOMIZED_PK" ON "DI"."T_ANALYSIS_CUSTOMIZED" ("AID") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index T_DATABASE_CERTIFICATION_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DI"."T_DATABASE_CERTIFICATION_PK" ON "DI"."T_DATABASE_CERTIFICATION" ("CID") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index T_DATABASE_COLUMN_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DI"."T_DATABASE_COLUMN_PK" ON "DI"."T_DATABASE_COLUMN" ("COLID") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index T_DATABASE_INFO_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DI"."T_DATABASE_INFO_PK" ON "DI"."T_DATABASE_INFO" ("DID") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index T_DATABASE_REPORT_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DI"."T_DATABASE_REPORT_PK" ON "DI"."T_DATABASE_REPORT" ("RID") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index T_DATABASE_TABLE_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DI"."T_DATABASE_TABLE_PK" ON "DI"."T_DATABASE_TABLE" ("TID") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index T_DI_ADMIN_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DI"."T_DI_ADMIN_PK" ON "DI"."T_DI_ADMIN" ("ADMINID") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Index T_DI_USER_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DI"."T_DI_USER_PK" ON "DI"."T_DI_USER" ("USERID") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1
  BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS" ;
--------------------------------------------------------
--  DDL for Trigger T_ANALYSIS_CUSTOMIZED_TRG
--------------------------------------------------------

  CREATE OR REPLACE EDITIONABLE TRIGGER "DI"."T_ANALYSIS_CUSTOMIZED_TRG" 
BEFORE INSERT ON T_ANALYSIS_CUSTOMIZED 
FOR EACH ROW 
BEGIN
  <<COLUMN_SEQUENCES>>
  BEGIN
    IF INSERTING AND :NEW.AID IS NULL THEN
      SELECT SEQ_AI_CUSTOMIZED.NEXTVAL INTO :NEW.AID FROM SYS.DUAL;
    END IF;
  END COLUMN_SEQUENCES;
END;
/
ALTER TRIGGER "DI"."T_ANALYSIS_CUSTOMIZED_TRG" ENABLE;
--------------------------------------------------------
--  DDL for Trigger T_DATABASE_CERTIFICATION_TRG
--------------------------------------------------------

  CREATE OR REPLACE EDITIONABLE TRIGGER "DI"."T_DATABASE_CERTIFICATION_TRG" 
BEFORE INSERT ON T_DATABASE_CERTIFICATION 
FOR EACH ROW 
BEGIN
  <<COLUMN_SEQUENCES>>
  BEGIN
    IF INSERTING AND :NEW.CID IS NULL THEN
      SELECT SEQ_AI_CERTIFICATION.NEXTVAL INTO :NEW.CID FROM SYS.DUAL;
    END IF;
  END COLUMN_SEQUENCES;
END;
/
ALTER TRIGGER "DI"."T_DATABASE_CERTIFICATION_TRG" ENABLE;
--------------------------------------------------------
--  DDL for Trigger T_DATABASE_COLUMN_TRG
--------------------------------------------------------

  CREATE OR REPLACE EDITIONABLE TRIGGER "DI"."T_DATABASE_COLUMN_TRG" 
BEFORE INSERT ON T_DATABASE_COLUMN 
FOR EACH ROW 
BEGIN
  <<COLUMN_SEQUENCES>>
  BEGIN
    IF INSERTING AND :NEW.COLID IS NULL THEN
      SELECT SEQ_AI_COLUMN.NEXTVAL INTO :NEW.COLID FROM SYS.DUAL;
    END IF;
  END COLUMN_SEQUENCES;
END;
/
ALTER TRIGGER "DI"."T_DATABASE_COLUMN_TRG" ENABLE;
--------------------------------------------------------
--  DDL for Trigger T_DATABASE_INFO_TRG
--------------------------------------------------------

  CREATE OR REPLACE EDITIONABLE TRIGGER "DI"."T_DATABASE_INFO_TRG" 
BEFORE INSERT ON T_DATABASE_INFO 
FOR EACH ROW 
BEGIN
  <<COLUMN_SEQUENCES>>
  BEGIN
    IF INSERTING AND :NEW.DID IS NULL THEN
      SELECT SEQ_AI_DATABASE.NEXTVAL INTO :NEW.DID FROM SYS.DUAL;
    END IF;
  END COLUMN_SEQUENCES;
END;
/
ALTER TRIGGER "DI"."T_DATABASE_INFO_TRG" ENABLE;
--------------------------------------------------------
--  DDL for Trigger T_DATABASE_REPORT_TRG
--------------------------------------------------------

  CREATE OR REPLACE EDITIONABLE TRIGGER "DI"."T_DATABASE_REPORT_TRG" 
BEFORE INSERT ON T_DATABASE_REPORT 
FOR EACH ROW 
BEGIN
  <<COLUMN_SEQUENCES>>
  BEGIN
    IF INSERTING AND :NEW.RID IS NULL THEN
      SELECT SEQ_AI_REPORT.NEXTVAL INTO :NEW.RID FROM SYS.DUAL;
    END IF;
  END COLUMN_SEQUENCES;
END;
/
ALTER TRIGGER "DI"."T_DATABASE_REPORT_TRG" ENABLE;
--------------------------------------------------------
--  DDL for Trigger T_DATABASE_TABLE_TRG
--------------------------------------------------------

  CREATE OR REPLACE EDITIONABLE TRIGGER "DI"."T_DATABASE_TABLE_TRG" 
BEFORE INSERT ON T_DATABASE_TABLE 
FOR EACH ROW 
BEGIN
  <<COLUMN_SEQUENCES>>
  BEGIN
    IF INSERTING AND :NEW.TID IS NULL THEN
      SELECT SEQ_AI_TABLE.NEXTVAL INTO :NEW.TID FROM SYS.DUAL;
    END IF;
  END COLUMN_SEQUENCES;
END;
/
ALTER TRIGGER "DI"."T_DATABASE_TABLE_TRG" ENABLE;
--------------------------------------------------------
--  DDL for Trigger T_DI_ADMIN_TRG
--------------------------------------------------------

  CREATE OR REPLACE EDITIONABLE TRIGGER "DI"."T_DI_ADMIN_TRG" 
BEFORE INSERT ON T_DI_ADMIN 
FOR EACH ROW 
BEGIN
  <<COLUMN_SEQUENCES>>
  BEGIN
    IF INSERTING AND :NEW.ADMINID IS NULL THEN
      SELECT SEQ_AI_ADMIN.NEXTVAL INTO :NEW.ADMINID FROM SYS.DUAL;
    END IF;
  END COLUMN_SEQUENCES;
END;
/
ALTER TRIGGER "DI"."T_DI_ADMIN_TRG" ENABLE;
--------------------------------------------------------
--  DDL for Trigger T_DI_USER_TRG
--------------------------------------------------------

  CREATE OR REPLACE EDITIONABLE TRIGGER "DI"."T_DI_USER_TRG" 
BEFORE INSERT ON T_DI_USER 
FOR EACH ROW 
BEGIN
  <<COLUMN_SEQUENCES>>
  BEGIN
    IF INSERTING AND :NEW.USERID IS NULL THEN
      SELECT SEQ_AI_USER.NEXTVAL INTO :NEW.USERID FROM SYS.DUAL;
    END IF;
  END COLUMN_SEQUENCES;
END;
/
ALTER TRIGGER "DI"."T_DI_USER_TRG" ENABLE;
--------------------------------------------------------
--  Constraints for Table T_DATABASE_REPORT
--------------------------------------------------------

  ALTER TABLE "DI"."T_DATABASE_REPORT" MODIFY ("RID" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_REPORT" MODIFY ("USERID" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_REPORT" MODIFY ("TITLE" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_REPORT" MODIFY ("GENERATEDATE" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_REPORT" ADD CONSTRAINT "T_DATABASE_REPORT_PK" PRIMARY KEY ("RID")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Constraints for Table T_ANALYSIS_CUSTOMIZED
--------------------------------------------------------

  ALTER TABLE "DI"."T_ANALYSIS_CUSTOMIZED" MODIFY ("AID" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_ANALYSIS_CUSTOMIZED" MODIFY ("USERID" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_ANALYSIS_CUSTOMIZED" MODIFY ("GENERATEDATE" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_ANALYSIS_CUSTOMIZED" MODIFY ("DESCRIPTION" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_ANALYSIS_CUSTOMIZED" MODIFY ("SCRIPT" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_ANALYSIS_CUSTOMIZED" ADD CONSTRAINT "T_ANALYSIS_CUSTOMIZED_PK" PRIMARY KEY ("AID")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Constraints for Table T_DATABASE_TABLE
--------------------------------------------------------

  ALTER TABLE "DI"."T_DATABASE_TABLE" MODIFY ("TID" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_TABLE" MODIFY ("DID" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_TABLE" MODIFY ("USERID" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_TABLE" ADD CONSTRAINT "T_DATABASE_TABLE_PK" PRIMARY KEY ("TID")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Constraints for Table T_DATABASE_COLUMN
--------------------------------------------------------

  ALTER TABLE "DI"."T_DATABASE_COLUMN" MODIFY ("COLID" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_COLUMN" MODIFY ("TID" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_COLUMN" MODIFY ("DID" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_COLUMN" MODIFY ("USERID" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_COLUMN" MODIFY ("COLUMNNAME" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_COLUMN" MODIFY ("DATATYPE" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_COLUMN" MODIFY ("ISPRIMARY" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_COLUMN" MODIFY ("ISFOREIGNKEY" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_COLUMN" ADD CONSTRAINT "T_DATABASE_COLUMN_PK" PRIMARY KEY ("COLID")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Constraints for Table T_DATABASE_INFO
--------------------------------------------------------

  ALTER TABLE "DI"."T_DATABASE_INFO" MODIFY ("DID" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_INFO" MODIFY ("USERID" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_INFO" MODIFY ("NAME" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_INFO" MODIFY ("HOST" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_INFO" MODIFY ("ADDDATE" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_INFO" ADD CONSTRAINT "T_DATABASE_INFO_PK" PRIMARY KEY ("DID")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Constraints for Table T_DI_ADMIN
--------------------------------------------------------

  ALTER TABLE "DI"."T_DI_ADMIN" MODIFY ("ADMINID" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DI_ADMIN" MODIFY ("USERNAME" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DI_ADMIN" MODIFY ("PASSWORD" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DI_ADMIN" MODIFY ("EMAIL" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DI_ADMIN" ADD CONSTRAINT "T_DI_ADMIN_PK" PRIMARY KEY ("ADMINID")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Constraints for Table T_DATABASE_CERTIFICATION
--------------------------------------------------------

  ALTER TABLE "DI"."T_DATABASE_CERTIFICATION" MODIFY ("CID" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_CERTIFICATION" MODIFY ("USERID" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_CERTIFICATION" MODIFY ("DID" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_CERTIFICATION" MODIFY ("USERNAME" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_CERTIFICATION" MODIFY ("PASSWORD" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DATABASE_CERTIFICATION" ADD CONSTRAINT "T_DATABASE_CERTIFICATION_PK" PRIMARY KEY ("CID")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Constraints for Table T_DI_USER
--------------------------------------------------------

  ALTER TABLE "DI"."T_DI_USER" MODIFY ("USERID" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DI_USER" MODIFY ("USERNAME" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DI_USER" MODIFY ("PASSWORD" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DI_USER" MODIFY ("STATUS" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DI_USER" MODIFY ("EMAIL" NOT NULL ENABLE);
  ALTER TABLE "DI"."T_DI_USER" ADD CONSTRAINT "T_DI_USER_PK" PRIMARY KEY ("USERID")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1
  BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "USERS"  ENABLE;
--------------------------------------------------------
--  Ref Constraints for Table T_ANALYSIS_CUSTOMIZED
--------------------------------------------------------

  ALTER TABLE "DI"."T_ANALYSIS_CUSTOMIZED" ADD CONSTRAINT "T_ANALYSIS_CUSTOMIZED_FK1" FOREIGN KEY ("USERID")
	  REFERENCES "DI"."T_DI_USER" ("USERID") ENABLE;
--------------------------------------------------------
--  Ref Constraints for Table T_DATABASE_CERTIFICATION
--------------------------------------------------------

  ALTER TABLE "DI"."T_DATABASE_CERTIFICATION" ADD CONSTRAINT "T_DATABASE_CERTIFICATION_FK1" FOREIGN KEY ("USERID")
	  REFERENCES "DI"."T_DI_USER" ("USERID") ENABLE;
  ALTER TABLE "DI"."T_DATABASE_CERTIFICATION" ADD CONSTRAINT "T_DATABASE_CERTIFICATION_FK2" FOREIGN KEY ("DID")
	  REFERENCES "DI"."T_DATABASE_INFO" ("DID") ENABLE;
--------------------------------------------------------
--  Ref Constraints for Table T_DATABASE_COLUMN
--------------------------------------------------------

  ALTER TABLE "DI"."T_DATABASE_COLUMN" ADD CONSTRAINT "T_DATABASE_COLUMN_FK1" FOREIGN KEY ("USERID")
	  REFERENCES "DI"."T_DI_USER" ("USERID") ENABLE;
  ALTER TABLE "DI"."T_DATABASE_COLUMN" ADD CONSTRAINT "T_DATABASE_COLUMN_FK2" FOREIGN KEY ("DID")
	  REFERENCES "DI"."T_DATABASE_INFO" ("DID") ENABLE;
  ALTER TABLE "DI"."T_DATABASE_COLUMN" ADD CONSTRAINT "T_DATABASE_COLUMN_FK3" FOREIGN KEY ("TID")
	  REFERENCES "DI"."T_DATABASE_TABLE" ("TID") ENABLE;
--------------------------------------------------------
--  Ref Constraints for Table T_DATABASE_INFO
--------------------------------------------------------

  ALTER TABLE "DI"."T_DATABASE_INFO" ADD CONSTRAINT "T_DATABASE_INFO_FK1" FOREIGN KEY ("USERID")
	  REFERENCES "DI"."T_DI_USER" ("USERID") ENABLE;
--------------------------------------------------------
--  Ref Constraints for Table T_DATABASE_REPORT
--------------------------------------------------------

  ALTER TABLE "DI"."T_DATABASE_REPORT" ADD CONSTRAINT "T_DATABASE_REPORT_FK1" FOREIGN KEY ("USERID")
	  REFERENCES "DI"."T_DI_USER" ("USERID") ENABLE;
--------------------------------------------------------
--  Ref Constraints for Table T_DATABASE_TABLE
--------------------------------------------------------

  ALTER TABLE "DI"."T_DATABASE_TABLE" ADD CONSTRAINT "T_DATABASE_TABLE_FK1" FOREIGN KEY ("USERID")
	  REFERENCES "DI"."T_DI_USER" ("USERID") ENABLE;
  ALTER TABLE "DI"."T_DATABASE_TABLE" ADD CONSTRAINT "T_DATABASE_TABLE_FK2" FOREIGN KEY ("DID")
	  REFERENCES "DI"."T_DATABASE_INFO" ("DID") ENABLE;
