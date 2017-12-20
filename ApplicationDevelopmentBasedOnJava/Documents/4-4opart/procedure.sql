/**
 * 添加事件
 */
create procedure ADDINCIDENTS(
  IN itype VARCHAR,
  IN ides VARCHAR,
  IN iloc VARCHAR,
  IN iwho  VARCHAR,
  OUT state INT )
BEGIN
  set state = 0;
  insert into INCIDENT(ITYPE, IDESCRIPTION, ILOCATION, IWHOADD)
    values(itype, ides, iloc, iwho);
  set state = 1;
END;

/**
 * 事件可信度标记
 */
create or replace procedure MARKCREDIT (
  IN idd INT,
  IN iced FLOAT,
  OUT state FLOAT
)
BEGIN
  set state = 0;

  update INCIDENTS set ICREDIT = icred
    where ID = idd;

    set state = 1;
END;


/**
 * 获取指定区域的事件
 */
create or replace procedure SELECTINCIDENTS(
  IN iloc VARCHAR,
)
BEGIN
  select * from INCIDENTS
  where ILOCATION = iloc;
END;


/**
 * 添加订阅用户
 */
create or replace procedure ADDSUBSCRIABER (
  IN uemail VARCHAR,
  IN uid INT,
  IN usub VARCHAR,
  OUT state INT
)
BEGIN
  set state = 0;
  update USERS set SUBSCRIABE = usub, EMAIL = uemail
    where ID = uid;

  set state = 1;
END;


/**
 * 搜索事件
 */
create or replace procedure SEARCHINCIDENTS (
  IN itype VARCHAR,
  IN ikey VARCHAR,
  IN idate DATE,
  IN iced FLOAT
)
BEGIN
  select *
  from INCIDENTS
  where ITYPE = itype
  AND IDESCRIPTION LIKE '%ikey%'
  AND IREPORTTIME = idate
  AND ICREDIT = icred
END;
