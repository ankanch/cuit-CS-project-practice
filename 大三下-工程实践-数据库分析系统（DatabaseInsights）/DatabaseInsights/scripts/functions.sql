--------------------------------------------------------
--  File created - Monday-April-02-2018   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Function F_LOGIN_USER
--------------------------------------------------------

  CREATE OR REPLACE EDITIONABLE FUNCTION "DI"."F_LOGIN_USER" 
(
  V_USERNAME IN VARCHAR2 
, V_PASSWORD IN VARCHAR2
, V_USESSION IN VARCHAR2 
) RETURN NUMBER AS 
V_USERID NUMBER;
BEGIN
    -- First check if the user already login (by check username and session matches,we stores username in cookies)
    BEGIN
        SELECT USERID INTO V_USERID FROM T_DI_USER WHERE USESSION=V_USESSION;
        RETURN 1;
    EXCEPTION 
        WHEN NO_DATA_FOUND THEN
            -- user didn't login, then we check if username and password matches, if so, login.
            BEGIN
                SELECT USERID INTO V_USERID FROM T_DI_USER WHERE USERNAME=V_USERNAME AND PASSWORD=V_PASSWORD;
            EXCEPTION 
                WHEN NO_DATA_FOUND THEN
                    RETURN -1;
            END;
    END;
    -- log user in, and update session
    UPDATE T_DI_USER SET LASTLOGIN=SYSDATE,USESSION=V_USESSION WHERE USERID=V_USERID;  
    RETURN 1; 
END F_LOGIN_USER;

/
--------------------------------------------------------
--  DDL for Function F_CREATE_USER
--------------------------------------------------------

  CREATE OR REPLACE EDITIONABLE FUNCTION "DI"."F_CREATE_USER" 
(
  NEW_USERNAME IN VARCHAR2 
, NEW_PASSWORD IN VARCHAR2 
, NEW_EMAIL IN VARCHAR2 
) RETURN NUMBER AS 
NEW_ID NUMBER;
BEGIN 
    BEGIN
        SELECT USERID INTO NEW_ID FROM T_DI_USER WHERE USERNAME=NEW_USERNAME;
    EXCEPTION 
        WHEN NO_DATA_FOUND THEN
            INSERT INTO T_DI_USER(USERNAME,PASSWORD,EMAIL,STATUS) VALUES(NEW_USERNAME,NEW_PASSWORD,NEW_EMAIL,1);
            COMMIT;
            SELECT USERID INTO NEW_ID FROM T_DI_USER WHERE USERNAME=NEW_USERNAME;
            RETURN NEW_ID;
    END;
    RETURN -1; 
END F_CREATE_USER;

/
--------------------------------------------------------
--  DDL for Function F_VALIDATE_SESSION
--------------------------------------------------------

  CREATE OR REPLACE EDITIONABLE FUNCTION "DI"."F_VALIDATE_SESSION" 
(
 V_USESSION IN VARCHAR2 
) RETURN NUMBER AS 
V_USERID NUMBER;
BEGIN
    -- First check if the user already login (by check username and session matches,we stores username in cookies)
    BEGIN
        SELECT USERID INTO V_USERID FROM T_DI_USER WHERE USESSION=V_USESSION;
        RETURN 1;
    EXCEPTION 
        WHEN NO_DATA_FOUND THEN
            RETURN -1;
        WHEN OTHERS THEN
            RETURN -1;
    END;
END F_VALIDATE_SESSION;

/
